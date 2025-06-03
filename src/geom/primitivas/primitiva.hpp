#ifndef PRIMITIVA_HPP
#define PRIMITIVA_HPP

#include "rayo.hpp"
#include "../color/RGB.hpp"
#include "../maths/direccion.hpp"
#include "../maths/punto.hpp"

class Primitiva {
    private:
        // Color de la primitiva
        RGB emision;

    public:
        Primitiva(const RGB &emision = RGB()) : emision(emision) {}
        virtual bool intersecta_con_rayo(Rayo rayo_a_comprobar) = 0;
};

#endif // PRIMITIVA_HPP