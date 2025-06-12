#include "escena.hpp"

#include <thread>

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

RGB evaluacion_brdf(Primitiva* primitiva) {
	return primitiva->getEmision() / M_PI;
}

// -------------------------- Operaciones internas -------------------------- //



// -------------------------- Operaciones privadas -------------------------- //
void Escena::renderizar_sector(int RPP, int x_izquierda, int x_derecha,
	int y_abajo, int y_arriba) {
	generador_aleatorios aleatorio(0, 1);	// Generador de numeros aleatorios
	RGB color_pixel;						// Color acumulado por píxel
	Rayo rayo;								// Rayo generado desde la cámara

	Primitiva* primitiva = nullptr;
	float t = 0.0f;

	// Recorrer todos los pixeles del sector
	for (int x = x_izquierda; x < x_derecha; x++){
		for (int y = y_abajo; y < y_arriba; y++) {

			color_pixel = RGB(); // Inicializar a negro
			
			// Multiples rayos por pixel para antialiasing
			for (int k = 0; k < RPP; k++) {
                rayo = camara.rayo_aleatorio_en_seccion(y, x, aleatorio);
				if(intersecta_con_primitiva(primitiva, rayo, t)) {
					Punto interseccion = rayo(t-1e-4);
					color_pixel += lanzar_rayo(primitiva, rayo.getDireccion(),
					primitiva->getNormal(interseccion), interseccion);				
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
		        RGB fr = evaluacion_brdf(p);
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

	RGB fr = primitiva->getEmision() / primitiva->getEmision().emision_maxima();
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
