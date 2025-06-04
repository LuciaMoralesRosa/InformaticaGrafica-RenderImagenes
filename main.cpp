#include <iostream>

#include "escena/escena.hpp"
#include "formato/PPM.hpp"

vector<Primitiva*> primitivas;
vector<Luz*> luces;
Camara camara;

void cornellBox() {
    Plano left(Direccion(1, 0, 0), 1, RGB(255, 0, 0));
    Plano right(Direccion(-1, 0, 0), 1, RGB(0, 255, 0));
    Plano floor(Direccion(0, 1, 0), 1, RGB(5, 5, 5));
    Plano ceiling(Direccion(0, -1, 0), 1, RGB(5, 5, 5));
    Plano back(Direccion(0, 0, -1), 1, RGB(255, 255, 5));

    Esfera uno(Punto(-0.5, -0.7, 0.25), 0.3, RGB(150, 0, 100));
    Esfera dos(Punto(0.5, -0.7, -0.25), 0.3, RGB(0, 0, 150));

    primitivas.push_back(&left);
    primitivas.push_back(&right);
    primitivas.push_back(&floor);
    primitivas.push_back(&ceiling);
    primitivas.push_back(&back);
    primitivas.push_back(&uno);
    primitivas.push_back(&dos);

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

    escena.renderizar_imagen(1);
    cout << "Imagen renderizada..." << endl;

    PPM imagen("P3", "CornellBox", 255, escena.getBase(), escena.getAltura(), 255, escena.getImagen());
    imagen.escribir_imagen("cornellbox.ppm");
    return 0;
}