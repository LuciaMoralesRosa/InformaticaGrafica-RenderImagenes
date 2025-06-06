#include "escena.hpp"

#include "aceleracion/sectores.hpp"
#include <thread>



void Escena::renderizar_seccion(int RPP, int minX, int maxX, int minY, int maxY) {

	RGB colorPixel;										// Color del pixel
	RGB colorRayo;										// Color del rayo
	Rayo rayoCamara;									// Rayo actual desde la camara
	float t;										// Distancia a la primitiva mas cercana
	Punto pInter;										// Punto de interseccion del rayo con primitiva
	RGB colorEmitido;									// Color emitido por la primitiva


	// Recorrer todos los pixeles de la seccion
	for (int b = minX; b < maxX; b++){
		for (int a = minY; a < maxY; a++) {

			// Establecer color inicial del pixel a negro
			colorPixel = RGB();

			// Para cada rayo lanzado a este pixel, ie, N_RPP
			for (int k = 0; k < RPP; k++) {

				// Estavlecer color del rayo a negro
				colorRayo = RGB();

				// Establecer color de emision a blanco
				colorEmitido = RGB(1);
                rayoCamara = camara.obtener_rayo_aleatorio_en_seccion(a, b);

                for (Primitiva* p : primitivas){
                    if (p->intersecta_con_rayo(rayoCamara, t)) {
                        // Si intersecta y tiene menor distancia guardamos el dato
                        
                        imagen[b*camara.base + a] = p->getEmision();;
                    }
                }

            }
		}
	}
}

void Escena::lanzar_hilos(int RPP, DivisorSector& sectores, int n_sectores) {
	vector<thread> arrayHilos(n_sectores);
	cout << "Creando hilos... " << endl;
	for (int t = 0; t < n_sectores; t++) {
		arrayHilos[t] = thread([this, RPP, &sectores]() {
			try {
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
			} catch (const std::exception& e) {
				std::cerr << "Excepción capturada en hilo: " << e.what() << std::endl;
			} catch (...) {
				std::cerr << "Excepción desconocida en hilo." << std::endl;
			}
		});
	}

	for (int t = 0; t < n_sectores; t++){
		arrayHilos[t].join();	
	} 
}

void Escena::renderizar_escena(int RPP, int n_sectores) {
    vector<Punto> puntos_rayos;

    // Dividir escena en secciones
    DivisorSector sectores(camara.base, camara.altura, n_sectores);
	cout << "Sectores creados..." << endl;
    lanzar_hilos(RPP, sectores, n_sectores);


}