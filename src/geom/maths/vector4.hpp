#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include <cmath>
#include <stdexcept>
#include <array>

#include "matriz.hpp"

using namespace std;
class Matriz;

// Clase de cuatro componentes que representa una coordenada homogenea en 3D
class Vector4 {
    protected:
        // Coordenadas del vector
        float x, y, z;

        // Indica si el valor es punto(1) o si es una direccion(0)
        int punto_direccion;

    public:
        Vector4(float x = 0, float y = 0, float z = 0, int es_punto = 0) :
            x(x), y(y), z(z), punto_direccion(es_punto) {}

        // Getters -------------------------------------------------------------
        float getX() const { return x; }
        float getY() const { return y; }
        float getZ() const { return z; }
        int getEsPunto() const { return punto_direccion; }

        array<float, 3> getVector3() const {
            return {x, y, z};
        }

        // Setters -------------------------------------------------------------
        void setX(float x) { this->x = x; }
        void setY(float y) { this->y = y; }
        void setZ(float z) { this->z = z; }
        
        // Comprobaciones ------------------------------------------------------
        bool es_punto() const { return punto_direccion == 1; }
        bool es_direccion() const { return punto_direccion == 0; }

        // Operaciones ---------------------------------------------------------
        /**
         * @brief Modulo del vector
         * 
         * @return Si es distancia, devuelve el modulo de la direccion.
         * @return Si es punto, devuelve la distancia desde el origen.
         */
        float modulo() const;

        /**
         * @brief Normaliza la direccion.
         * @note Debe ser usado en una direccion.
         */
        Vector4 normalizar() const;

        /**
         * @brief Producto escalar entre dos direcciones
         * @note Debe ser usado en dos direcciones
         * 
         * @param d1 Primera direccion
         * @param d2 Segunda direccion
         * 
         * @return El producto escalar entre los dos vectores
         */
        friend float prod_escalar(const Vector4 &d1, const Vector4 &d2);

        // Returns the cross product of two directions.
        /**
         * @brief Producto vectorial entre dos direcciones
         * @note Debe ser usado en dos direcciones
         * 
         * @param d1 Primera direccion
         * @param d2 Segunda direccion
         * 
         * @return El producto vectorial entre los dos vectores
         */
        friend Vector4 prod_vectorial(const Vector4 &d1, const Vector4 &d2);

        /**
         * @brief Calcula el vector direccion o distancia entre dos puntos
         * @details vec_direccion = p1 - p2
         * @note Debe ser usado en dos puntos
         * 
         * @param p1 Primer punto
         * @param p2 Segundo punto
         * 
         * @return El vector direccion de p2 a p1
         */
        friend Vector4 distancia(Vector4 p1, Vector4 p2);

        /**
         * @brief Calcula el angulo entre dos direcciones
         * 
         * @param d1 Primera direccion
         * @param d2 Segunda direccion
         */
        friend float angulo_entre_direcciones(const Vector4 &d1, const Vector4 &d2);

        // Transformaciones de matrices ----------------------------------------
        /**
         * @brief Aplica la matriz de transformacion al vector
         * 
         * @param m Matriz de transformacion
         */
        void aplicar_matriz(Matriz m);

        /**
         * @brief Traslada el vector a una nueva posicion
         * 
         * @param x Traslacion en el eje X
         * @param x Traslacion en el eje Y
         * @param x Traslacion en el eje Z
         */
        void trasladar(float x, float y, float z);

        /**
         * @brief Escala el vector en los ejes X, Y y Z
         * 
         * @param x Escalado en el eje X
         * @param x Escalado en el eje Y
         * @param x Escalado en el eje Z
         */
        void escalar(float x, float y, float z);

        /**
         * @brief Rota el vector al rededor del eje X
         * 
         * @param grados Angulo de rotacion en grados
         */
        void rotar_x(float grados);

        /**
         * @brief Rota el vector al rededor del eje Y
         * 
         * @param grados Angulo de rotacion en grados
         */
        void rotar_y(float grados);

        /**
         * @brief Rota el vector al rededor del eje Z
         * 
         * @param grados Angulo de rotacion en grados
         */
        void rotar_z(float grados);

        /**
         * @brief Cambia la base del vector a una nueva base definida por los 
         * parametros o, u, v y w
         * 
         * @param o Origen de la nueva base
         * @param u Vector unitario en el eje X de la nueva base
         * @param v Vector unitario en el eje Y de la nueva base
         * @param w Vector unitario en el eje Z de la nueva base
         */
        void cambiar_base(Vector4 o, Vector4 u, Vector4 v, Vector4 w);

        /**
         * @brief Revierte la transformacion aplicada previamente
         * @details Construye una matriz de cambio de base a partir de un
         * sistema de coordenadas definido por los vectores u, v, w
         * (base ortonormal) y el origen o, y luego invierte esa transformación
         * para revertir una transformación previa aplicada.
         * 
         * @param o Origen de la nueva base
         * @param u Vector unitario en el eje X de la nueva base
         * @param v Vector unitario en el eje Y de la nueva base
         * @param w Vector unitario en el eje Z de la nueva base
         */
        void invertir_cambiar_base(Vector4 o, Vector4 u, Vector4 v, Vector4 w);


        // Operadores ----------------------------------------------------------
        friend Vector4 operator+(const Vector4 &v1, const Vector4 &v2);
        friend Vector4 operator-(const Vector4 &v1, const Vector4 &v2);
        friend Vector4 operator-(const Vector4 &v);
        friend Vector4 operator*(const Vector4 &v, const float &s);
        friend Vector4 operator*(const float &s, const Vector4 &v);
        friend Vector4 operator/(const Vector4 &v, const float &s);
        friend Vector4 operator/(const float &s, const Vector4 &v);
        friend bool operator== (const Vector4 &v1, const Vector4 &v2);
        const float& operator[](int i) const;
    	friend ostream &operator<< (ostream &o, const Vector4 &v);
};

#endif // VECTOR4_HPP