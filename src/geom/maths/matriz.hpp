#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#define DIM 4

#define _USE_MATH_DEFINES
#include <iostream>
#include <ostream>
#include <iomanip>
#include <cmath>
#include <math.h>

#include "vector4.hpp"

using namespace std;

// Class that represents a transformation Matriz.
class Matriz {
    
    private:
	// Matriz representada como un array de 4x4
	float m[DIM][DIM];

    public:

        // Constructores -------------------------------------------------------
        Matriz();
        Matriz (float m[DIM][DIM]);
        
        // Setters -------------------------------------------------------------
        void setComponente(int i, int j, float valor) { m[i][j] = valor; }

        // Getters -------------------------------------------------------------
        float getComponente(int i, int j) const { return m[i][j]; }

        // Operaciones ---------------------------------------------------------
        /**
         * @brief Convierte la matriz de transformacion a una de traslacion
         * 
         * @param x Traslacion en el eje X
         * @param x Traslacion en el eje Y
         * @param x Traslacion en el eje Z
         */
        void matriz_traslacion(float x, float y, float z);

        /**
         * @brief Convierte la matriz de transformacion a una de escalado
         * 
         * @param x Escalado en el eje X
         * @param x Escalado en el eje Y
         * @param x Escalado en el eje Z
         */
        void matriz_escalado(float x, float y, float z);

        /**
         * @brief Convierte la matriz de transformacion a una de rotacion sobre
         * el eje X
         * 
         * @param angulo Angulo de rotacion en grados
         */
        void matriz_rotacion_x(float angulo);

        /**
         * @brief Convierte la matriz de transformacion a una de rotacion sobre
         * el eje Y
         * 
         * @param angulo Angulo de rotacion en grados
         */
        void matriz_rotacion_y(float angulo);

        /**
         * @brief Convierte la matriz de transformacion a una de rotacion sobre
         * el eje Z
         * 
         * @param angulo Angulo de rotacion en grados
         */
        void matriz_rotacion_z(float angulo);

        // Swap two rows in a Matriz
        /**
         * @brief Cambia la posicion de dos filas en una matriz
         * 
         * @param Matriz Matriz a la que se aplica el cambio
         * @param f1 Primera fila a cambiar
         * @param f2 Segunda fila a cambiar
         */
        void cambiar_filas(Matriz Matriz, int f1, int f2);

        /**
         * @brief Invierte la matriz usando el metodo de Gauss-Jordan
         * 
         * @return true si la matriz es invertible, false en caso contrario
         */
        bool invertir_matriz();

        // TODO: eliminar
        void imageOnes () {
            for (int i = 0; i < DIM; i++)
                    m[i][i] = 1;
        }


        // Operadores ----------------------------------------------------------
        friend ostream &operator<< (ostream &o, const Matriz &m);

};

#endif // MATRIZ_HPP