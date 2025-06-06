#include <iostream>

#include "escena/escena.hpp"
#include "formato/PPM.hpp"

vector<Primitiva*> primitivas;
vector<Luz*> luces;
Camara camara;

void cornellBox() {
    primitivas.push_back(new Plano(Direccion(1, 0, 0), 1, RGB(255, 0, 0)));
    primitivas.push_back(new Plano(Direccion(-1, 0, 0), 1, RGB(0, 255, 0)));
    primitivas.push_back(new Plano(Direccion(0, 1, 0), 1, RGB(5, 5, 5)));
    primitivas.push_back(new Plano(Direccion(0, -1, 0), 1, RGB(5, 5, 5)));
    primitivas.push_back(new Plano(Direccion(0, 0, -1), 1, RGB(255, 255, 5)));
    primitivas.push_back(new Esfera(Punto(-0.5, -0.7, 0.25), 0.3, RGB(150, 0, 100)));
    primitivas.push_back(new Esfera(Punto(0.5, -0.7, -0.25), 0.3, RGB(0, 0, 150)));

    camara = Camara(Punto(0, 0, -3.5), Direccion(-1, 0, 0), Direccion(0, 1, 0),
        Direccion(0, 0, 3), 256, 256);

}

using namespace std;
int main() {
    cout << "Comenzando ejecucion..." << endl;
    cornellBox();
    cout << "Cornellbox creada..." << endl;

    Escena escena(camara, primitivas, luces);
    cout << "Escena creada..." << endl;

    escena.renderizar_escena();
    cout << "Imagen renderizada..." << endl;

    PPM imagen("P3", "CornellBox", 255, escena.getBase(), escena.getAltura(), 255, escena.getImagen());
    imagen.escribir_imagen("cornellbox.ppm");
    return 0;
}