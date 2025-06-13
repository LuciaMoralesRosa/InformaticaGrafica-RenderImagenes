#ifndef PLANO_HPP
#define PLANO_HPP

#include "primitiva.hpp"

class Plano : public Primitiva {
    
    private:
        Direccion normal;   // Normal del plano
        float d;            // Distancia desde el origen al plano

    public:
        // Constructores -------------------------------------------------------
        /**
         * @brief Constructor del plano a partir de una normal y una distancia
         * desde el origen
         */
        Plano(const Direccion &normal, float d, RGB kd, RGB ks, RGB kt, RGB ke, double n_d = N_AIRE, double n_f = N_AIRE, const string nombre = "")
            :   Primitiva(kd, ks, kt, ke, n_d, n_f, nombre), normal(normal.normalizar()), d(d) {}

        /**
         * @brief Constructor de un plano a partir de una normal y un punto
         */
        Plano(const Direccion &normal, const Punto &p, RGB kd, RGB ks, RGB kt, RGB ke, double n_d = N_AIRE, double n_f = N_AIRE, const string nombre = "")
            :   Primitiva(kd, ks, kt, ke, n_d, n_f, nombre), normal(normal.normalizar()),
                d(abs(prod_escalar(normal, distancia(Punto(), p)))) {}


        // Getters -------------------------------------------------------------
        Direccion getNormal(const Punto& p) const override { return normal; }

        // Operaciones ---------------------------------------------------------
        bool intersecta_con_rayo(const Rayo& rayo, float& t) override;
};

#endif // PLANO_HPP