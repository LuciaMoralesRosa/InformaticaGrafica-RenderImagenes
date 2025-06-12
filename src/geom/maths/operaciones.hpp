#ifndef OPERACIONES_HPP
#define OPERACIONES_HPP


#include <iostream>
#include <cmath>
#include <utility>  // Para pair

#include "direccion.hpp"
#include "punto.hpp"
#include "matriz.hpp"

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


inline Direccion multiplicar(Matriz matriz, Direccion d) {
    float v[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            v[i] += matriz.m[i][k] * d[k];
        }
    }
    return Direccion(v[0], v[1], v[2]);
}

inline void generar_matriz_float(float M[][4], Direccion d, Direccion y, Direccion n, Punto x) {
    M[0][0] = d[0];     M[0][1] = y[0];     M[0][2] = n[0];    M[0][3] = x[0];
    M[1][0] = d[1];     M[1][1] = y[1];     M[1][2] = n[1];    M[1][3] = x[1];
    M[2][0] = d[2];     M[2][1] = y[2];     M[2][2] = n[2];    M[2][3] = x[2];
    M[3][0] = 0;        M[3][1] = 0;        M[3][2] = 0;       M[3][3] = 1;
}


inline Matriz matriz_cb(Direccion normal, Punto x) {
    Direccion aleatorio = Direccion(
        (double)rand() / RAND_MAX,
        (double)rand() / RAND_MAX,
        (double)rand() / RAND_MAX
    ).normalizar();

    Direccion y = prod_vectorial(normal, aleatorio).normalizar();

    while (y.modulo() == 0) {
        aleatorio = Direccion(
            (double)rand() / RAND_MAX,
            (double)rand() / RAND_MAX,
            (double)rand() / RAND_MAX
        ).normalizar();
        
        y = prod_vectorial(normal, aleatorio).normalizar();
    }

    Direccion d = prod_vectorial(y, normal).normalizar();

    float M[4][4];
    generar_matriz_float(M, d, y, normal.normalizar(), x);

    Matriz m(M);
    return m;
}

#endif // OPERACIONES_HPP