#include "aleatorio.hpp"

generador_aleatorios aleatorio_unitario(-1, 1);

float generar_aleatorio(float a, float b){
    // Generador aleatorio global o local
    random_device rd;
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_real_distribution<float> distrib(a, b); // intervalo [a, b)

    float valor = distrib(gen); // valor aleatorio entre a y b
    return valor;
}
