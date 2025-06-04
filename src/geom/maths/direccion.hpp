#ifndef DIRECCION_HPP
#define DIRECCION_HPP

#include "vector4.hpp"

class Direccion : public Vector4 {
    public:
        // Constructores -------------------------------------------------------
        Direccion(float x = 0, float y = 0, float z = 0) : Vector4(x, y, z, 0) {}
        Direccion(Vector4 v) : Vector4(v.getX(), v.getY(), v.getZ(), 0) {}

        // Operaciones ---------------------------------------------------------
        friend Vector4 convertir_a_vector4(Direccion d);

        /**
         * @brief Genera una direccion aleatoria normalizada dentro de la esfera 
         * unitaria
         * 
         * @return Direccion aleatoria normalizada
         */
        Direccion direccion_aleatoria();

        // Operadores ----------------------------------------------------------
        friend istream &operator>>(istream &i, Direccion &d);
};


#endif // DIRECCION_HPP