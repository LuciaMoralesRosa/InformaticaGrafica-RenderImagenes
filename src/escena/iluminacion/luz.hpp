#ifndef LUZ_HPP
#define LUZ_HPP

#include "../../color/RGB.hpp"
#include "../../geom/maths/punto.hpp"

class Luz {
    private:
        RGB potencia;
        Punto posicion;
    
        public:
        Luz(const RGB& _potencia, const Punto& _posicion)
            : potencia(_potencia), posicion(_posicion) {}
};

#endif // LUZ_HPP