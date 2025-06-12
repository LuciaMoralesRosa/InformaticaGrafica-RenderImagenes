#ifndef SAMPLE_ALEATORIA
#define SAMPLE_ALEATORIA

#include <cmath>
#include <random>

#include "../geom/maths/operaciones.hpp"
#include "../geom/maths/matriz.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;


// Genera una direccion aleatoria en la hemiesfera con angulo solido uniforme
Direccion angulo_solido_uniforme(Direccion normal, Punto p) {
    double aleatorio_1 = (double)rand() / RAND_MAX;
    double th = acos(aleatorio_1);
    double aleatorio_2 = (double)rand() / RAND_MAX;
    double phi = 2*M_PI*aleatorio_2;
    Direccion d = Direccion(sin(th)*cos(phi), sin(th)*sin(phi), cos(th));

    // Reajustar el sistema de coordenadas
    Matriz cambio_base = matriz_cb(normal, p);
    return multiplicar(cambio_base, d);
}

// Genera una direccion aleatoria en la hemiesfera con coseno uniforme
Direccion coseno_uniforme(Direccion normal, Punto p) {
    double aleatorio_1 = (double)rand() / RAND_MAX;
    double th = acos(sqrt(1-aleatorio_1));
    double aleatorio_2 = (double)rand() / RAND_MAX;
    double phi = 2*M_PI*aleatorio_2;
    Direccion d = Direccion(sin(th)*cos(phi), sin(th)*sin(phi), cos(th));

    // Reajustar el sistema de coordenadas
    Matriz cambio_base = matriz_cb(normal, p);
    return multiplicar(cambio_base, d);
}

#endif // SAMPLE_ALEATORIA