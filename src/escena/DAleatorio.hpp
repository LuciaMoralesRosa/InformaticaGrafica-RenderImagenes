
#ifndef DALEATORIO_HPP
#define DALEATORIO_HPP

#include "../geom/maths/matriz.hpp"
#include "../geom/maths/direccion.hpp"
#include "../geom/maths/punto.hpp"


// Clase para generar numeros aleatorios
class DireccionMuestraAleatoria {
    public:
    Direccion normal;   // Normal de la superficie
    Punto x;            // Punto de la superficie

    // Constructor
    DireccionMuestraAleatoria(Direccion normal, Punto x) : normal(normal), x(x) {
        //srand(time(NULL));
    };

    // Matriz de cambio de base
    Matriz cambioBase();

    // Genera una direccion aleatoria en la hemiesfera
    Direccion anguloUniforme();

    // Genera una direccion aleatoria en la hemiesfera con angulo solido uniforme
    Direccion anguloSolidoUniforme();

    // Genera una direccion aleatoria en la hemiesfera con coseno uniforme
    Direccion cosenoUniforme();
};

// Genera una direccion aleatoria en la esfera con angulo solido uniforme
Direccion muestraAnguloSolido();

#endif // ALEATORIO_H