#ifndef LUZ_HPP
#define LUZ_HPP

#include "../../color/RGB.hpp"
#include "../../geom/maths/punto.hpp"

class Luz {
    private:
        RGB potencia;
        Punto centro;
    
        public:
        Luz(const RGB& _potencia, const Punto& _centro)
            : potencia(_potencia), centro(_centro) {}

        Punto getCentro() { return centro; }
        RGB getPotencia() { return potencia; }
};

#endif // LUZ_HPP