#include <iostream>

#include "src/escena/escena.hpp"
#include "src/formato/PPM.hpp"

vector<Primitiva*> primitivas;
vector<Luz> luces;
Camara camara;

void cornellBox() {
    primitivas.push_back(new Plano(Direccion(1, 0, 0), 1, "rojo", RGB(255, 0, 0)));
    primitivas.push_back(new Plano(Direccion(-1, 0, 0), 1, "verde", RGB(0, 255, 0)));
    primitivas.push_back(new Plano(Direccion(0, 1, 0), 1, "suelo", RGB(255, 255, 255)));
    primitivas.push_back(new Plano(Direccion(0, -1, 0), 1, "techo" , RGB(200, 200, 200)));
    primitivas.push_back(new Plano(Direccion(0, 0, -1), 1, "fondo", RGB(150, 150, 150)));
    primitivas.push_back(new Esfera(Punto(-0.5, -0.7, 0.25), 0.3, "rosa", RGB(255, 187, 249)));
    primitivas.push_back(new Esfera(Punto(0.5, -0.7, -0.25), 0.3, "azul", RGB(172, 190, 255)));

    camara = Camara(Punto(0, 0, -3.5), Direccion(-1, 0, 0), Direccion(0, 1, 0),
        Direccion(0, 0, 3), 256, 256);

    luces.push_back(Luz(RGB(1, 1, 1), Punto(0, 0.5, 0)));

}

using namespace std;
int main() {
    cout << "Comenzando ejecucion..." << endl;
    cornellBox();
    cout << "Cornellbox creada..." << endl;

    Escena escena(camara, primitivas, luces);
    cout << "Escena creada..." << endl;

    escena.renderizar_escena(1, 1);
    cout << "Imagen renderizada..." << endl;

    PPM imagen("P3", "CornellBox", 255, escena.getBase(), escena.getAltura(), 255, escena.getImagen());
    imagen.escribir_imagen("cornellbox.ppm");
    return 0;
}