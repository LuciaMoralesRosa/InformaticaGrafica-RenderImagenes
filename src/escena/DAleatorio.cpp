
#include "DAleatorio.hpp"
#include <cmath>
#include <random>

using namespace std;

Direccion multiplicar(Matriz matriz, Direccion d) {
    float v[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            v[i] += matriz.m[i][k] * d[k];
        }
    }
    return Direccion(v[0], v[1], v[2]);
}

// Matriz de cambio de base
Matriz DireccionMuestraAleatoria::cambioBase() {
    Direccion aleatorio = Direccion((double)rand() / RAND_MAX,
        (double)rand() / RAND_MAX, (double)rand() / RAND_MAX).normalizar();
    Direccion y = prod_vectorial(normal, aleatorio).normalizar();
    while (y.modulo() == 0) {
        aleatorio = Direccion((double)rand() / RAND_MAX,
        (double)rand() / RAND_MAX, (double)rand() / RAND_MAX).normalizar();
        y = prod_vectorial(normal, aleatorio).normalizar();
    }
    Direccion x = prod_vectorial(y, normal).normalizar();

    float M[4][4];
    M[0][0] = x[0]; M[0][1] = y[0]; M[0][2] = normal.normalizar()[0]; M[0][3] = this->x[0];
    M[1][0] = x[1]; M[1][1] = y[1]; M[1][2] = normal.normalizar()[1]; M[1][3] = this->x[1];
    M[2][0] = x[2]; M[2][1] = y[2]; M[2][2] = normal.normalizar()[2]; M[2][3] = this->x[2];
    M[3][0] = 0;      M[3][1] = 0;      M[3][2] = 0;      M[3][3] = 1;

    return Matriz(M);
}

// Genera una direccion aleatoria en la hemiesfera
Direccion DireccionMuestraAleatoria::anguloUniforme() {
    double xi1 = (double)rand() / RAND_MAX;
    double th = (M_PI/2)*xi1;
    double xi2 = (double)rand() / RAND_MAX;
    double phi = 2*M_PI*xi2;
    Direccion d = Direccion(sin(th)*cos(phi), sin(th)*sin(phi), cos(th));
    return multiplicar(cambioBase(),d);
}

// Genera una direccion aleatoria en la hemiesfera con angulo solido uniforme
Direccion DireccionMuestraAleatoria::anguloSolidoUniforme() {
    double xi1 = (double)rand() / RAND_MAX;
    double th = acos(xi1);
    double xi2 = (double)rand() / RAND_MAX;
    double phi = 2*M_PI*xi2;
    Direccion d = Direccion(sin(th)*cos(phi), sin(th)*sin(phi), cos(th));
    return multiplicar(cambioBase(),d);
}

// Genera una direccion aleatoria en la hemiesfera con coseno uniforme
Direccion DireccionMuestraAleatoria::cosenoUniforme() {
    double xi1 = (double)rand() / RAND_MAX;
    double th = acos(sqrt(1-xi1));
    double xi2 = (double)rand() / RAND_MAX;
    double phi = 2*M_PI*xi2;
    Direccion d = Direccion(sin(th)*cos(phi), sin(th)*sin(phi), cos(th));
    Matriz cambio_base = cambioBase();
    return multiplicar(cambio_base, d);
}

// Genera una direccion aleatoria en la esfera con angulo solido uniforme
Direccion muestraAnguloSolido() {
    double xi1 = (double)rand() / RAND_MAX;
    double th = acos(2*xi1-1);
    double xi2 = (double)rand() / RAND_MAX;
    double phi = 2*M_PI*xi2;
    Direccion d = Direccion(sin(th)*cos(phi), sin(th)*sin(phi), cos(th));
    return d;
}