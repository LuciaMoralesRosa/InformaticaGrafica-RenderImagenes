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
        bool intersecta_con_primitiva(Primitiva*& primitiva_intersectada,
            const Rayo& rayo, float& distancia_primitiva);


        /**
         * @brief Lanza un rayo desde un punto de intersección y calcula la
         * radiancia resultante
         * 
         * Esta función implementa la lógica principal del trazado de rayos
         * Evalúa la contribución de luz reflejada indirectamente a través de
         * múltiples rebotes (hasta un máximo definido por N_REBOTES) y la luz
         * directa incidente sobre el punto de intersección.
         *
         * Si el rayo no intersecta ninguna primitiva, se retorna la luz directa
         * en el punto. En cada rebote se genera una nueva dirección (`wi`)
         * distribuida uniformemente sobre el hemisferio definido por la normal,
         * y se llama recursivamente a esta función.
         * 
         * @param primitiva Puntero a la primitiva sobre la que incide el rayo
         * @param wo Dirección de salida del rayo
         * @param n Normal en el punto de intersección
         * @param x Punto de intersección donde se evalúa el rayo
         * @param n_rebotes Número actual de rebotes del rayo
         * 
         * @return RGB Radiancia total en 'x' por luz directa e indirecta
         */
        RGB lanzar_rayo(Primitiva* primitiva, Direccion wo, Direccion n, Punto x, int n_rebotes = 0);


        /**
         * @brief Calcula la luz directa que incide sobre un punto de una
         * primitiva
         * 
         * Esta función recorre todas las luces de la escena y evalúa la
         * contribución directa de cada una sobre el punto dado. Tiene en cuenta
         * el ángulo de incidencia (coseno), la distancia a la luz, y si hay
         * oclusión (sombras) por otras primitivas
         * 
         * Si se proporciona un valor no nulo de sigma, se aplica una atenuación
         * exponencial basada en la distancia al cuadrado
         * 
         * @param p Puntero a la primitiva sobre la que se calcula la iluminación
         * @param wo Dirección de salida del rayo
         * @param n Normal en el punto de intersección
         * @param x Punto sobre la primitiva donde se evalúa la luz
         * @param sigma Coeficiente de atenuación exponencial
         * 
         * @return RGB Intensidad de luz directa recibida en el punto
         */
        RGB calcular_luz_directa(Primitiva* p, Direccion wo, Direccion n, Punto x, double sigma = 0.0);


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