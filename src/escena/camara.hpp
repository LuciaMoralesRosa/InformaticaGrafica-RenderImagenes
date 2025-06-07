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

        // Constructores -------------------------------------------------------
        Camara() {}
        Camara(const Punto& _origen, const Direccion& _l,
            const Direccion& _u, const Direccion& _f,
            int _base, int _altura);


        // Operaciones ---------------------------------------------------------
        /**
         * @brief Genera un rayo aleatorio que pasa por una sección específica
         * del plano de la cámara, con desplazamientos aleatorios para antialiasing
         * 
         * @param a Coordenada horizontal dentro de la sección de la cámara
         * @param b Coordenada vertical dentro de la sección de la cámara
         * @param aleatorio Generador de números aleatorios
         * 
         * @return Rayo generado desde el origen de la cámara hacia el punto
         *         desplazado en el plano.
         */
        Rayo rayo_aleatorio_en_seccion(int a, int b, generador_aleatorios& aleatorio);

};


#endif // CAMARA_HPP