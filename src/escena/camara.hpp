#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <vector>

#include "../geom/maths/vector4.hpp"
#include "../geom/maths/direccion.hpp"
#include "../geom/maths/punto.hpp"
#include "../geom/primitivas/rayo.hpp"
#include "../geom/maths/aleatorio.hpp"

class Camara {

    public:
        Punto origen;       // Origen de la camara
        Direccion l;        // Direccion LEFT (izquierda)
        Direccion u;        // Direccion UP (arriba)
        Direccion f;        // Direccion FORWARD (adelante)
        int base;           // Base de la imagen en pixeles
        int altura;         // Altura de la imagen en pixeles
        float base_pixel;   // Ancho de cada pixel
        float altura_pixel; // Alto de cada pixel

    public:

        // Constructor.
        Camara() {}

        // Constructor.
        Camara(const Punto& _origen, const Direccion& _l,
            const Direccion& _u, const Direccion& _f,
            int _base, int _altura);

        void posicion_aleatoria(vector<Punto>& posiciones, int rpp) const;
        Rayo obtener_rayo_aleatorio_en_seccion(int a, int b, generador_aleatorios& aleatorio);

};


#endif // CAMARA_HPP