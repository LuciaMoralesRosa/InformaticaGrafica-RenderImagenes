#include "escena.hpp"

#include "aceleracion/sectores.hpp"
#include <thread>


const int N_REBOTES = 1;

Primitiva* Escena::intersectar_primitiva(const Rayo& rayo, float& min_t, float& t) {
    
	Primitiva* primitiva_intersectada = nullptr;
    for (Primitiva* p : primitivas) {
		if (p->intersecta_con_rayo(rayo, t) && t < min_t) {
            min_t = t;
            primitiva_intersectada = p;
        }
    }
    return primitiva_intersectada; // nullptr si no hay intersección
}


bool Escena::gestionar_rebotes(Primitiva*& primitiva_intersectada, Rayo& rayo) {
	float menor_distancia_a_primitiva = 1e10;
	float distancia_a_primitiva;

	primitiva_intersectada = intersectar_primitiva(
		rayo,
		menor_distancia_a_primitiva,
		distancia_a_primitiva
	);
	if(primitiva_intersectada == nullptr) {
		cout << "Es nulo" << endl;

		return false;
	}

	return true;
	
	//gestionar_interseccion(p);

}

void Escena::renderizar_seccion(int RPP, int x_izquierda, int x_derecha, int y_abajo, int y_arriba) {

	RGB color_pixel;						// Color del pixel
	Rayo rayo;								// Rayo a evaluar
	Primitiva* primitiva_intersectada = nullptr;
	generador_aleatorios aleatorio(0, 1);	// Generador numero aleatorio


	// Recorrer todos los pixeles de la seccion
	for (int b = x_izquierda; b < x_derecha; b++){
		for (int a = y_abajo; a < y_arriba; a++) {

			color_pixel = RGB();
			for (int k = 0; k < RPP; k++) {
				// Generar rayo aleatorio desde la camara en el pixel
                rayo = camara.obtener_rayo_aleatorio_en_seccion(a, b, aleatorio);

				int rebote = 0;
				bool terminar = false;
				while(rebote < N_REBOTES) {
					if(!gestionar_rebotes(primitiva_intersectada, rayo)) {
						break;
					}
					rebote++;
				}
				color_pixel = color_pixel + primitiva_intersectada->getEmision();				
			}
			//cout << "Color del pixel " << color_pixel << endl;
			imagen[b*camara.base + a] = color_pixel / RPP;
		}
	}
}


void Escena::renderizar_escena(int RPP, int n_sectores) {
    // Dividir escena en sectores
    DivisorSector sectores(camara.base, camara.altura, n_sectores);

	vector<thread> arrayHilos(n_sectores);
	for (int t = 0; t < n_sectores; t++) {
		arrayHilos[t] = thread([this, RPP, &sectores](){
			Rango_seccion rs;
			while (sectores.obtener_seccion(rs)) {
				this->renderizar_seccion(
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