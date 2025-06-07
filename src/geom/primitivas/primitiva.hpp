#ifndef PRIMITIVA_HPP
#define PRIMITIVA_HPP

#include <string>

#include "rayo.hpp"
#include "../../color/RGB.hpp"
#include "../maths/direccion.hpp"
#include "../maths/punto.hpp"

using namespace std;

class Primitiva {
    private:
        // Color de la primitiva
        string nombre;
        RGB emision;

    public:
        Primitiva(const string nombre = "", const RGB &emision = RGB()) 
            : nombre(nombre), emision(emision) {}

        virtual bool intersecta_con_rayo(const Rayo& rayo,  float& t) = 0;


        string getNombre() const { return nombre; }
        RGB getEmision() const { return emision; }
        virtual Direccion getNormal(const Punto& p) const = 0;
};

#endif // PRIMITIVA_HPP