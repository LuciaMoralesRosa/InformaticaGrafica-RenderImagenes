#ifndef OPERACIONES_HPP
#define OPERACIONES_HPP


#include <iostream>
#include <cmath>
#include <utility>  // Para pair

using namespace std;

/**
 * @brief Calcula los factores de un numero entero positivo n
 */
inline pair<int, int> calcular_factores(int n) {
    int raiz = static_cast<int>(sqrt(n));
    for (int i = raiz; i >= 1; --i) {
        if (n % i == 0) {
            int otro = n / i;
            return {i, otro};
        }
    }
    // Esto nunca debería pasar si n > 0
    return {1, n};
}


#endif // OPERACIONES_HPP