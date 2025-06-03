#ifndef PLANO_HPP
#define PLANO_HPP

#include "primitiva.hpp"


class Plano : public Primitiva {
    private:
        Direccion normal;   // Normal del plano
        float d;            // Distancia desde el origen al plano
}

#endif // PLANO_HPP