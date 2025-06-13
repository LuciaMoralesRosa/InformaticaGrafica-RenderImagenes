#include "escena.hpp"

#include <thread>
#include <list>

#include "sample_aleatoria.hpp"
#include "aceleracion/sectores.hpp"
#include "../geom/maths/vector4.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

const int N_REBOTES = 8;



// -------------------------- Operaciones internas -------------------------- //
RGB colorInterseccion(const Primitiva* primitiva, vector<Primitiva*> primitivas,
	const Punto& pInterseccion, Luz& luz,
	RGB& colorDisipado, EVENTO efecto, Direccion direccionRayo){

	// Comprobar si el plano esta contra la luz
	//if(primitiva->planoContraLuz(camara, luz, pInterseccion)) {
	//	// Si está contra la luz -> negro.
	//	return RGB(0);
	//}

	Direccion distanciaLuz = distancia(luz.getCentro(), pInterseccion);
	float modDistancia = distanciaLuz.modulo();
	float t;

	// Comprobar si alguna primitiva le da sombra
	for (Primitiva* p : primitivas){
		if(p->intersecta_con_rayo(Rayo(luz.getCentro(), -distanciaLuz), t)
		&& (1 - t) * modDistancia > 1e-6
		&& (p != primitiva || distancia(pInterseccion, luz.getCentro() - t * (distanciaLuz)).modulo() > 1e-4)) {
			return RGB(0);
		}
	}

	// Esta a la luz -> calcular color
	RGB Li = luz.getPotencia() / (pow(modDistancia, 2));
	float cosine = abs(prod_escalar(primitiva->getNormal(pInterseccion), distanciaLuz.normalizar()));

	return Li * primitiva->getFr(efecto, direccionRayo, pInterseccion, primitiva->getNormal(pInterseccion)) * cosine * colorDisipado;

}

// -------------------------- Operaciones internas -------------------------- //



// -------------------------- Operaciones privadas -------------------------- //
void Escena::renderizar_sector(int RPP, int x_izquierda, int x_derecha,
	int y_abajo, int y_arriba) {
	generador_aleatorios aleatorio(0, 1);	// Generador de numeros aleatorios
	RGB color_pixel;						// Color acumulado por píxel
	Rayo rayo_camara;						// Rayo generado desde la cámara

	Primitiva* primitiva = nullptr;
	float minT, t = 0.0f;
	Punto p_interseccion;

	RGB color_emitido;
	RGB color_rayo;
	EVENTO efecto;
	Direccion direccion_rayo;

	// Recorrer todos los pixeles del sector
	for (int x = x_izquierda; x < x_derecha; x++){
		for (int y = y_abajo; y < y_arriba; y++) {

			color_pixel = RGB(); // Inicializar a negro
			
			// Multiples rayos por pixel para antialiasing
			for (int k = 0; k < RPP; k++) {
				color_emitido = RGB(255, 255, 255);
				color_rayo = RGB();
                rayo_camara = camara.rayo_aleatorio_en_seccion(y, x, aleatorio);
				bool terminar = false;
				int nRebotes = 0;
				//while (!terminar || nRebotes < N_REBOTES) {
				while (nRebotes < N_REBOTES) {

					// Obtener la figura y el punto de interseccion
					minT = 1e6;
					primitiva = nullptr;
					for (Primitiva* p : primitivas){
						if (p->intersecta_con_rayo(rayo_camara, t) && t < minT) {
							// Si intersecta y tiene menor distancia guardamos el dato
							minT = t;
							primitiva = p;
						}
					}

					if (primitiva == nullptr) {
						// Si no ha intersectado con ninguna primitiva
						break;
					} 

					p_interseccion = rayo_camara.getOrigen() + minT*rayo_camara.getDireccion();
					efecto = primitiva->evento_aleatorio();

					switch(efecto) {
						case ABSORCION:
							terminar = true;
							break;
						case EMISION:
							color_rayo += primitiva->k_e * color_emitido;
							terminar = true;
							break;
						case ESPECULAR:
							color_emitido *= primitiva->getFr(efecto, direccion_rayo, p_interseccion, primitiva->getNormal(p_interseccion));
							break;
						case REFRACCION:
							color_emitido *= primitiva->getFr(efecto, direccion_rayo, p_interseccion, primitiva->getNormal(p_interseccion));
							break;
						default: // DIFUSO
							for (Luz luz : luces){
								color_rayo += colorInterseccion(primitiva, primitivas,
									p_interseccion, luz,
									color_emitido, efecto, direccion_rayo);
							}
							color_emitido *= M_PI * primitiva->getFr(efecto, direccion_rayo, p_interseccion, primitiva->getNormal(p_interseccion));
							break;
					}
					
					// Update the ray.
					p_interseccion = p_interseccion + 1e-4 * direccion_rayo;
					rayo_camara = Rayo(p_interseccion, direccion_rayo);

					nRebotes++;
				}
				if (isnan(color_rayo[0]) || isnan(color_rayo[1]) || isnan(color_rayo[2])){
					k--;
				}
				else{
					color_pixel += color_rayo;
				}
			}

			// Promediar color acumulado por el número de muestras
			int indice_pixel = x * camara.base + y;
			imagen[indice_pixel] = color_pixel / RPP;
		}
	}
}


RGB Escena::calcular_luz_directa(Primitiva* p, Direccion wo, Direccion n, Punto x, double sigma) {
    RGB L = RGB();

    for(Luz luz : luces) {
		Direccion direccion_luz = luz.getCentro() - x;
        Direccion wi = direccion_luz.normalizar();
        double d_cuadrado = prod_escalar(direccion_luz, direccion_luz);
        double coseno = prod_escalar(n, wi);

        if (coseno > 0) {
			Primitiva* primitiva_bloqueo;
			float distancia;
			Rayo rayo_sombra(luz.getCentro(), -wi);

            if (intersecta_con_primitiva(primitiva_bloqueo, rayo_sombra, distancia) &&
				distancia >= sqrt(d_cuadrado) - 0.0001) {
		        RGB fr = RGB(); //evaluacion_brdf(p);
				RGB potencia = luz.getPotencia();

				RGB contribucion = (coseno * fr) * (potencia / d_cuadrado);
                if (sigma != 0.0){
					contribucion = contribucion * pow(M_E, -sigma * d_cuadrado);
				} 

				L = L + contribucion;
            }
        }
    }
    return L;
}


RGB Escena::lanzar_rayo(Primitiva* primitiva, Direccion wo, Direccion n, Punto x, int n_rebotes) {
	Primitiva* p;
    Direccion normal = n;
	float distancia;

    if (prod_escalar(wo, n) > 0.0) {
 		// invierte la normal para que apunte hacia el lado opuesto a wo		
 		normal = -normal;
	} 

	if(n_rebotes == N_REBOTES) { // Temporal
		return RGB();
	}
	n_rebotes++;

	Direccion wi = angulo_solido_uniforme(normal, x);
	Rayo rayo_wi = Rayo(x, wi);
	bool interseccion = intersecta_con_primitiva(p, rayo_wi, distancia);
	Punto punto_interseccion = rayo_wi(distancia);

	if(!interseccion || distancia <= 0.0) {
		return calcular_luz_directa(primitiva, wo, normal, x);
	}

	RGB fr = RGB();/*primitiva->getEmision() / primitiva->getEmision().emision_maxima();*/
	RGB L = fr * lanzar_rayo(p, wi, p->getNormal(punto_interseccion), punto_interseccion, n_rebotes)
			+ calcular_luz_directa(primitiva, wo, normal, x);

	return L;
}


bool Escena::intersecta_con_primitiva(Primitiva*& primitiva, const Rayo& rayo,
	float& distancia_primitiva) {
	float menor_distancia = 1e6; 
	Primitiva* primitiva_intersectada = nullptr;
    
	    // Buscar la primitiva más cercana que intersecta con el rayo
	for (Primitiva* p : primitivas) {
		float t; // Distancia actual hasta primitiva
		if (p->intersecta_con_rayo(rayo, t) && t < menor_distancia) {
			menor_distancia = t;
            primitiva_intersectada = p;
        }
    }

	// Si no se encontró ninguna intersección, retornar false
	if(primitiva_intersectada == nullptr) {
		return false;
	}

	// Actualizar los parámetros de salida
	primitiva = primitiva_intersectada;
	distancia_primitiva = menor_distancia;

	return true;
}
// -------------------------- Operaciones privadas -------------------------- //


// ------------------------------ Operaciones ------------------------------- //
void Escena::renderizar_escena(int RPP, int n_sectores) {
    // Dividir escena en sectores
    DivisorSector sectores(camara.base, camara.altura, n_sectores);

	vector<thread> arrayHilos(n_sectores);
	for (int t = 0; t < n_sectores; t++) {
		arrayHilos[t] = thread([this, RPP, &sectores](){
			Rango_seccion rs;
			while (sectores.obtener_seccion(rs)) {
				this->renderizar_sector(
                    RPP,
                    rs.superior_izquierda.x,
                    rs.inferior_derecha.x,
                    rs.superior_izquierda.y,
                    rs.inferior_derecha.y
                );
			}
		});
	}

	for (int t = 0; t < n_sectores; t++){
		arrayHilos[t].join();	
	}
}
// ------------------------------ Operaciones ------------------------------- //
