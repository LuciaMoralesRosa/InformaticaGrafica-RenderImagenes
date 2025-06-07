#ifndef ESCENA_HPP
#define ESCENA_HPP


#include "camara.hpp"
#include "iluminacion/luz.hpp"
#include "../color/RGB.hpp"
#include "../geom/primitivas/primitiva.hpp"
#include "../geom/primitivas/esfera.hpp"
#include "../geom/primitivas/plano.hpp"

class DivisorSector;
class Escena {

    private:
        Camara camara;
        vector<Primitiva*> primitivas;
        vector<Luz> luces;
        vector<RGB> imagen;

        // Operaciones privadas ------------------------------------------------
        /**
         * @brief Renderiza una sección de la imagen dividiendo en píxeles y
         * disparando múltiples rayos por píxel para realizar antialiasing.
         *
         * @param RPP            Número de rayos por píxel para el antialiasing
         * @param x_izquierda    Coordenada X inicial de la sección a renderizar
         * @param x_derecha      Coordenada X final de la sección a renderizar
         * @param y_abajo        Coordenada Y inicial de la sección a renderizar
         * @param y_arriba       Coordenada Y final de la sección a renderizar
         *
         * Esta función recorre cada píxel dentro del rectángulo definido,
         * genera múltiples rayos aleatorios desde la cámara, calcula el color
         * resultante para cada rayo, acumula y promedia el color para producir
         * un resultado con suavizado (antialiasing).
         *
         * El resultado final se almacena en el buffer de imagen de la escena.
         */
        void renderizar_sector(int RPP, int x_izquierda, int x_derecha,
            int y_abajo, int y_arriba);
        
        /**
         * @brief Calcula el color resultante al lanzar un rayo en la escena
         * 
         * Esta función determina si el rayo desde la camara intersecta alguna 
         * primitiva. Si hay intersección, calcula la contribución de luz
         * directa de todas las fuentes de luz visibles desde el punto de
         * intersección, descartando aquellas bloqueadas.
         * 
         * @param rayo El rayo que se lanza desde la cámara u otra fuente.
         * @return RGB El color resultante de la luz directa en el punto de
         *             intersección o negro si no hay intersección.
         */
        RGB lanzar_rayo(const Rayo& rayo);

        /**
         * @brief Determina si un rayo intersecta con alguna primitiva de la
         * escena
         *
         * Recorre todas las primitivas de la escena y busca la intersección más
         * cercana con el rayo dado. Si se encuentra una intersección, se
         * devuelve la primitiva intersectada y la distancia a la intersección
         *
         * @param[out] primitiva Referencia al puntero donde se almacenará la
         *             primitiva intersectada. Si no hay intersección, se deja
         *             sin modificar
         * @param[in]  rayo      Rayo lanzado para detectar intersecciones
         * @param[out] distancia_primitiva Distancia desde el origen del rayo
         *             hasta la intersección más cercana. Si no hay interseccion
         *             se deja sin modificar
         *
         * @return true si el rayo intersecta con alguna primitiva,
         *         false en caso contrario.
         */
        bool intersecta_con_primitiva(Primitiva*& primitiva_intersectada, const Rayo& rayo, float& distancia_primitiva);

        /**
         * @brief Determina si existe alguna primitiva que bloquea la luz hacia
         *        un punto dado
         * 
         * Este método verifica primero si algún plano está en contraluz con
         * respecto a la fuente de luz, y luego comprueba si alguna primitiva
         * intermedia bloquea el camino de la luz desde la fuente hasta el punto
         * de intersección
         * 
         * @param primitiva Puntero a la primitiva objetivo que recibe la luz
         * @param luz Referencia a la fuente de luz considerada
         * @param punto_interseccion Punto donde se evalúa la iluminación
         * 
         * @return true si alguna primitiva bloquea la luz hacia el punto,
         *         false en caso contrario.
         */
        bool hay_primitiva_bloqueadora(Primitiva* primitiva, Luz& luz,
            const Punto& punto);

        /**
         * @brief Determina si una primitiva plana se encuentra a contraluz
         *        respecto a una fuente de luz
         *
         * @param primitiva Puntero a la primitiva que se evaluará
         * @param luz Fuente de luz respecto a la cual se evaluará la contraluz
         * 
         * @return true si la primitiva está a contraluz,
         *         false en caso contrario.
         */
        bool plano_contra_la_luz(Primitiva* p, Luz l);


    public:
        Escena(const Camara& _camara, const vector<Primitiva*>& _primitivas,
            const vector<Luz>& _luces)
            :
            camara(_camara), primitivas(_primitivas), luces(_luces),
            imagen(vector<RGB>(camara.altura*camara.base)) {}

        // Getters -------------------------------------------------------------
        int getBase() const { return camara.base; }
        int getAltura() const { return camara.altura; }
        const vector<RGB>& getImagen() const { return imagen; }

        // Operaciones ---------------------------------------------------------
        /**
         * @brief Renderiza toda la escena utilizando múltiples hilos y
         *        renderizado por sectores
         *
         * Esta función divide la imagen en múltiples sectores para paralelizar
         * el proceso de renderizado. Cada hilo renderiza uno o más sectores,
         * generando varios rayos por pixel para mejorar la calidad de la imagen
         * mediante antialiasing
         *
         * @param RPP Rayos por píxel. 
         * @param n_sectores Número de sectores en los que se divide la imagen
         */
        void renderizar_escena(int RPP = 1, int n_sectores = 1);
};


#endif // ESCENA_HPP