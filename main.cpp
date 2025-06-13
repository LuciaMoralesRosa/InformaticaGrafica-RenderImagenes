#include <iostream>

#include "src/escena/escena.hpp"
#include "src/formato/PPM.hpp"
#include "src/otros/colores.hpp"

vector<Primitiva*> primitivas;
vector<Luz> luces;
Camara camara;

void cornellBox_original() {
    primitivas.push_back(new Plano(Direccion(1, 0, 0),  1.0f,  ROJO,   NEGRO,  NEGRO,  NEGRO,   N_AIRE, N_AIRE,  string("rojo")));
    primitivas.push_back(new Plano(Direccion(-1, 0, 0), 1.0f,  VERDE,  NEGRO,  NEGRO,  NEGRO,   N_AIRE, N_AIRE,  string("verde")));
    primitivas.push_back(new Plano(Direccion(0, 1, 0),  1.0f,  SUELO,  NEGRO,  NEGRO,  NEGRO,   N_AIRE, N_AIRE,  string("suelo")));
    primitivas.push_back(new Plano(Direccion(0, -1, 0), 1.0f,  TECHO,  NEGRO,  NEGRO,  NEGRO,   N_AIRE, N_AIRE,  string("techo")));
    primitivas.push_back(new Plano(Direccion(0, 0, -1), 1.0f,  FONDO,  NEGRO,  NEGRO,  NEGRO,   N_AIRE, N_AIRE,  string("fondo")));
    primitivas.push_back(new Esfera(Punto(-0.5, -0.7, 0.25), 0.3, ROSA,   NEGRO,  NEGRO,  NEGRO,   N_AIRE, N_AIRE,  string("rosa")));
    primitivas.push_back(new Esfera(Punto(0.5, -0.7, -0.25), 0.3, AZUL,   NEGRO,  NEGRO,  NEGRO,   N_AIRE, N_AIRE,  string("azul")));

    camara = Camara(Punto(0, 0, -3.5), Direccion(-1, 0, 0), Direccion(0, 1, 0),
        Direccion(0, 0, 3), 256, 256);

    luces.push_back(Luz(RGB(1, 1, 1), Punto(0, 0.5, 0)));
}


void cornellBox_causticas() {
    primitivas.push_back(new Plano(Direccion(1, 0, 0),  1.0f,  ROJO,   NEGRO,  NEGRO,  NEGRO,   N_AIRE, N_AIRE,  string("rojo")));
    primitivas.push_back(new Plano(Direccion(-1, 0, 0), 1.0f,  VERDE,  NEGRO,  NEGRO,  NEGRO,   N_AIRE, N_AIRE,  string("verde")));
    primitivas.push_back(new Plano(Direccion(0, 1, 0),  1.0f,  SUELO,  NEGRO,  NEGRO,  NEGRO,   N_AIRE, N_AIRE,  string("suelo")));
    primitivas.push_back(new Plano(Direccion(0, -1, 0), 1.0f,  NEGRO,  NEGRO,  NEGRO,  BLANCO,   N_AIRE, N_AIRE,  string("techo")));
    primitivas.push_back(new Plano(Direccion(0, 0, -1), 1.0f,  FONDO,  NEGRO,  NEGRO,  NEGRO,   N_AIRE, N_AIRE,  string("fondo")));
    primitivas.push_back(new Esfera(Punto(0.0,-0.6,0.0), 0.3, ROSA,   RGB_GRIS*0.1,  BLANCO*0.9,  NEGRO,   1.5, N_AIRE,  string("rosa")));

    camara = Camara(Punto(0, 0, -3.5), Direccion(-1, 0, 0), Direccion(0, 1, 0),
        Direccion(0, 0, 3), 256, 256);

    luces.push_back(Luz(RGB(1, 1, 1), Punto(0, 0.5, 0)));
}



using namespace std;
int main() {
    cout << "Comenzando ejecucion..." << endl;
    cornellBox_original();
    cout << "Cornellbox creada..." << endl;

    Escena escena(camara, primitivas, luces);
    cout << "Escena creada..." << endl;

    escena.renderizar_escena(30, 1);
    cout << "Imagen renderizada..." << endl;

    PPM imagen("P3", "CornellBox", 255, escena.getBase(), escena.getAltura(), 255, escena.getImagen());
    imagen.escribir_imagen("cornellbox.ppm");
    return 0;
}