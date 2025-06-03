#ifndef PUNTO_HPP
#define PUNTO_HPP

#include "vector4.hpp"

// Object that represents a point in 3D space.
class Punto : public Vector4 {
    public:
        // Constructores -------------------------------------------------------
        Punto(float x = 0, float y = 0, float z = 0) : Vector4(x, y, z, 1) {}
        Punto(Vector4 v) : Vector4(v.getX(), v.getY(), v.getZ(), 1) {}

        // Operaciones ---------------------------------------------------------
        friend Vector4 convertir_a_vector4(Punto p);

        // Operadores ----------------------------------------------------------
        friend istream &operator>>(istream &i, Punto &p);
};

#endif // PUNTO_HPP