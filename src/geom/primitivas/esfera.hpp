#ifndef ESFERA_HPP
#define ESFERA_HPP

#include "primitiva.hpp"
#include "../maths/punto.hpp"
#include "../maths/direccion.hpp"


class Esfera : public Primitiva {
    
    private:
        Punto centro;	// Centro de la esfera.
        float radio;	// Raio de la esfera.

    public:
        // Constructor ---------------------------------------------------------
        Esfera(const Punto& c, float r, const string nombre = "",
            const RGB &emision = RGB())
            :   Primitiva(nombre, emision), centro(c), radio(r) {}

        // Getters -------------------------------------------------------------
        Punto getCentro() const { return centro; }

        /**
         * @brief Obtiene la normal de la esfera en un punto de su superficie
         * 
         * @param p Punto en la superficie de la esfera
         * @return Normal de la esfera en el punto
         */
        Direccion getNormal(const Punto& p) const override {
            return distancia(p, centro).normalizar();
        }
        
        // Operaciones ---------------------------------------------------------
        /**
         * @brief Comprueba si un rayo intersecta con la esfera
         * 
         * @param rayo Rayo a comprobar
         * @param t Distancia al punto de interseccion desde 
         * @return true si el rayo intersecta con la esfera
         *         false en caso contrario
         */
        bool intersecta_con_rayo(const Rayo& rayo, float& t) override;
};

#endif // ESFERA_HPP