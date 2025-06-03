#ifndef RAYO_HPP
#define RAYO_HPP

#include "../maths/vector4.hpp"
#include "../maths/punto.hpp"
#include "../maths/direccion.hpp"

class Rayo {
    private:
        Vector4 origen;         // Origen del rayo
        Vector4 direccion;      // Direccion del rayo

    public:
        // Constructores -------------------------------------------------------
        Rayo() {}
        Rayo(const Punto& o, const Direccion& d) : origen(o), direccion(d) {}

        // Getters -------------------------------------------------------------
        Vector4 getOrigen() const { return origen; }
        Vector4 getDireccion() const { return direccion; }

        // Operadores ----------------------------------------------------------
        /**
         * @brief Obtiene el punto del rayo a una distancia t desde el origen
         * 
         * @param t Distancia desde el origen del rayo
         * @return Punto del rayo a distancia t del origen
         */
        Vector4 operator()(float t) const { return origen + t * direccion; }
};

#endif // RAYO_HPP