#ifndef PRIMITIVA_HPP
#define PRIMITIVA_HPP

#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#include "rayo.hpp"
#include "../../color/RGB.hpp"
#include "../maths/direccion.hpp"
#include "../maths/punto.hpp"

using namespace std;

#define N_AIRE 1.000293

enum EVENTO { // Eventos de interacción de la luz con la geometría
    EMISION = 0,
    DIFUSO = 1,
    ESPECULAR = 2,
    REFRACCION = 3,
    ABSORCION = 4
};

class Primitiva {
     public:
        RGB k_d, k_s, k_t, k_e;
    private:
        // Color de la primitiva
        double p_d, p_s, p_t, p_e;
        double n_dentro, n_fuera;
        string nombre;
        char canal_maximo_rgb;
        
    public:
        Primitiva(RGB kd, RGB ks, RGB kt, RGB ke, double n_d = N_AIRE, double n_f = N_AIRE, const string nombre = "");

        virtual bool intersecta_con_rayo(const Rayo& rayo,  float& t) = 0;


        EVENTO evento_aleatorio();

        string getNombre() const { return nombre; }
        virtual Direccion getNormal(const Punto& p) const = 0;

        RGB getFr(EVENTO ph, Direccion& d, Punto p, Direccion n) const;



    RGB fr_solo_difuso(Punto x, Direccion wi, Direccion wo, Direccion n);
    RGB fr_difuso(Punto x, Direccion wi, Direccion wo, Direccion n);
    RGB fr_especular(Punto x, Direccion wi, Direccion wo, Direccion n);
    RGB fr_refraccion(Punto x, Direccion wi, Direccion wo, Direccion n);

    RGB fr(Punto x, Direccion wi, Direccion wo, Direccion n);

    Direccion reflejar(Direccion wi, Direccion n);
    Direccion refractar(Direccion wi, Direccion n);

    bool esLuzArea() {
        return k_e.emision_maxima() > 0 && k_d.emision_maxima() == 0 && k_s.emision_maxima() == 0 && k_t.emision_maxima() == 0;
    };
};

#endif // PRIMITIVA_HPP