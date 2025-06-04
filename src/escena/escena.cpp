#include "escena.hpp"

void Escena::renderizar_imagen(int RPP) {
    vector<Punto> puntos_rayos;
    camara.posicion_aleatoria(puntos_rayos, RPP);

    cout << "En renderizar imagen..." << endl;

    // Generar rayos
    vector<Rayo> rayos;
    for(int i = 0; i < static_cast<int>(puntos_rayos.size()); i++){
        Rayo rayo(camara.origen, distancia(Punto(), puntos_rayos[i]));
        for(Primitiva* p : primitivas) {
            float t;
            if(p->intersecta_con_rayo(rayo, t)) {
                imagen.push_back(p->getEmision());
            }
        }
    } 
}