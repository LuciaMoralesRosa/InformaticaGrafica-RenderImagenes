#ifndef PRIMITIVA_HPP
#define PRIMITIVA_HPP

#include "rayo.hpp"
#include "../../color/RGB.hpp"
#include "../maths/direccion.hpp"
#include "../maths/punto.hpp"

class Primitiva {
    private:
        // Color de la primitiva
        RGB emision;

    public:
        Primitiva(const RGB &emision = RGB()) : emision(emision) {}
        virtual bool intersecta_con_rayo(const Rayo& rayo,  float& t) = 0;

        RGB getEmision() const { return emision; }
};

#endif // PRIMITIVA_HPP