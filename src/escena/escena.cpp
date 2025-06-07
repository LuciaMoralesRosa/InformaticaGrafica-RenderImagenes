#include "escena.hpp"

#include "aceleracion/sectores.hpp"
#include "../geom/maths/vector4.hpp"
#include <thread>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int N_REBOTES = 1;

// -------------------------- Operaciones internas -------------------------- //
/**
 * @brief Determina si una primitiva intermedia bloquea la luz entre una fuente 
 * y un punto de intersección.
 *
 * @param primitiva La primitiva inicialmente intersectada por el
 * 					rayo desde la cámara.
 * @param p_bloqueadora	La primitiva candidata a bloquear la luz.
 * @param rayo_luz	El rayo trazado desde la fuente de luz hacia la escena.
 * @param punto_luz	Vector desde el punto de luz hacia el punto de intersección.
 * @param luz La fuente de luz que emite el rayo.
 * @param punto_interseccion El punto donde se desea evaluar la iluminación.
 *
 * @return true si la primitiva bloqueadora interfiere la luz antes de llegar al
 * 		   punto de intersección, false en caso contrario.
 */
bool bloquea_luz(Primitiva* primitiva, Primitiva* p_bloqueadora, Rayo rayo_luz,
				 Direccion punto_luz, Luz luz, Punto punto_interseccion) {
	float distancia_primitiva;

	// Verificar si el rayo de luz intersecta con la posible bloqueadora
	if(!p_bloqueadora->intersecta_con_rayo(rayo_luz, distancia_primitiva)) {
		return false;
	}

 	// Verifica si la intersección ocurre entre la fuente y el punto
    // Si está demasiado cerca del origen o más allá del receptor, se descarta
	bool dentro_del_rango = (1 - distancia_primitiva) * punto_luz.modulo() > 1e-6;
	if (!dentro_del_rango) {
		return false;
	}

	// Calcular el punto donde la bloqueadora intersecta con el rayo de luz
	Punto punto_bloqueo = luz.getCentro() - distancia_primitiva * (punto_luz);

	// Verificar si la intersección ocurre con la misma primitiva pero en
	// otro punto (primitivas con varios puntos de interseccion. Ej: esfera)
	float error_en_posicion = distancia(punto_interseccion, punto_bloqueo).modulo();
	bool es_otro_punto = error_en_posicion > 1e-4;
	
	return (p_bloqueadora != primitiva || es_otro_punto);
}

/**
 * @brief Calcula la luz directa en el punto de interseccion de la primitiva
 * proporcionada por la luz
 * 
 * @param primitiva Primitiva sobre la que se esta evaluando la luz
 * @param l Luz a evaluar
 * @param punto_interseccion Punto concreto sobre el que se evalua la luz
 * 
 * @return Luz directa proporcionada por la luz sobre el punto
 */
RGB calcular_luz_directa(Primitiva* primitiva, Luz l, Punto punto_interseccion) {
	Direccion d = distancia(l.getCentro(), punto_interseccion);
	float d_modulo = d.modulo();
	RGB luz_entrada = l.getPotencia() / pow(d_modulo, 2);
	RGB brdf = primitiva->getEmision() / M_PI;
	Direccion n = primitiva->getNormal(punto_interseccion);
	float n_distancia = prod_escalar(n, d);
	float geometria = abs(n_distancia/ d_modulo);	
	return luz_entrada*brdf*geometria;
}
// -------------------------- Operaciones internas -------------------------- //



// -------------------------- Operaciones privadas -------------------------- //
void Escena::renderizar_sector(int RPP, int x_izquierda, int x_derecha,
	int y_abajo, int y_arriba) {
	generador_aleatorios aleatorio(0, 1);	// Generador de numeros aleatorios
	RGB color_pixel;						// Color acumulado por píxel
	Rayo rayo;								// Rayo generado desde la cámara

	// Recorrer todos los pixeles del sector
	for (int x = x_izquierda; x < x_derecha; x++){
		for (int y = y_abajo; y < y_arriba; y++) {

			color_pixel = RGB(); // Inicializar a negro
			
			// Multiples rayos por pixel para antialiasing
			for (int k = 0; k < RPP; k++) {
                rayo = camara.rayo_aleatorio_en_seccion(y, x, aleatorio);
				color_pixel += lanzar_rayo(rayo);				
			}

			// Promediar color acumulado por el número de muestras
			int indice_pixel = x * camara.base + y;
			imagen[indice_pixel] = color_pixel / RPP;
		}
	}
}


RGB Escena::lanzar_rayo(const Rayo& rayo) {
	Primitiva* primitiva = nullptr; // Primitiva intersectada 
	float t = 0.0f; 				// Distancia a la interseccion

	if(!intersecta_con_primitiva(primitiva, rayo, t)) {
		return RGB();
	}

	Punto punto_interseccion = rayo(t);
	RGB luz_directa = RGB();

	// Calcular la contribucion de cada fuente de luz
	for(Luz& luz : luces) {
		if(!hay_primitiva_bloqueadora(primitiva, luz, punto_interseccion)) {
			luz_directa += calcular_luz_directa(primitiva, luz, punto_interseccion);
		}
	}
	return luz_directa;
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


bool Escena::hay_primitiva_bloqueadora(Primitiva* primitiva, Luz& luz,
	const Punto& punto_interseccion) {
    // Revisar si algún plano está en contraluz con respecto a la luz
	for(Primitiva* p : primitivas) {
		if(dynamic_cast<Plano*>(p) != nullptr) {
			if(plano_contra_la_luz(p, luz)) {
				cout << "Plano a contra luz" << endl;
				return true;
			}
		}
	}

	// Calcular dirección del rayo desde la luz hacia el punto de intersección
	Direccion punto_luz = distancia(luz.getCentro(), punto_interseccion);
	Rayo rayo_luz = Rayo(luz.getCentro(), -punto_luz);

    // Verificar si alguna primitiva bloquea la luz hacia el punto
	for(Primitiva* p_bloqueadora : primitivas) {
		if(bloquea_luz(primitiva, p_bloqueadora, rayo_luz, punto_luz, luz, punto_interseccion)) {
			return true;
		}
	}

	return false;
}


bool Escena::plano_contra_la_luz(Primitiva* primitiva, Luz luz) {
	float distancia_interseccion;
	
    Direccion camara_luz = distancia(luz.getCentro(), camara.origen);
    Rayo rayo_camara_luz(camara.origen, camara_luz);

	// Comprobar si el plano intersecta con el rayo antes de llegar a la luz
    bool hay_interseccion = primitiva->intersecta_con_rayo(rayo_camara_luz, distancia_interseccion);

    return hay_interseccion && distancia_interseccion < 1.0f;
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
