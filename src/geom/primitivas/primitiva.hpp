#ifndef PRIMITIVA_HPP
#define PRIMITIVA_HPP

#include "../color/RGB.hpp"


class Primitiva {
    private:
        // Color de la primitiva
        RGB emision;

    public:
        bool intersecta_con_rayo(Rayo rayo_a_comprobar);
};

#endif // PRIMITIVA_HPP