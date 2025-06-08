#ifndef ALEATORIO_HPP
#define ALEATORIO_HPP

#include <random>
#include <ctime>

using namespace std;

/**
 * @class generador_aleatorios
 * @brief Clase para generar números aleatorios en un rango continuo [a, b).
 *
 * Esta clase utiliza el generador Mersenne Twister (mt19937) junto con una
 * distribución uniforme real para devolver números aleatorios de punto flotante
 * en el rango especificado por el usuario.
 */
class generador_aleatorios {
    private: 
        // Motor de generación de números aleatorios (Mersenne Twister).
        mt19937 gen;

        // Distribución uniforme en el rango [a, b).
        uniform_real_distribution<float> distribucion_uniforme;

    public:
        /**
         * @brief Constructor que inicializa el generador con un rango [a, b).
         * 
         * Se utiliza la hora actual (std::time(0)) para generar una semilla diferente
         * en cada ejecución, garantizando números aleatorios distintos.
         * 
         * @param a Límite inferior del rango (incluido).
         * @param b Límite superior del rango (no incluido).
         */
        generador_aleatorios(float a, float b) :
            gen(time(0)), distribucion_uniforme(a, b) {}

        /**
         * @brief Devuelve un número aleatorio en el rango [a, b].
         * 
         * @return double Número aleatorio con distribución uniforme.
         */
        float get() { return distribucion_uniforme(gen); }
};

extern generador_aleatorios aleatorio_unitario;

float generar_aleatorio(float a, float b);


#endif // ALEATORIO_HPP
