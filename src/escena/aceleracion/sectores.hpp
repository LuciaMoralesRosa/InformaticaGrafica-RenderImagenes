#ifndef SECTORES_HPP
#define SECTORES_HPP

#include <mutex>
#include "../../geom/maths/operaciones.hpp"

using namespace std;

struct Esquina_pixeles
{
    int x;
    int y;
};

struct Rango_seccion {
    Esquina_pixeles superior_izquierda;
    Esquina_pixeles inferior_derecha;
};

class DivisorSector {
    private:
        int base_imagen;
        int altura_imagen;     // Tamaño de la imagen
        int total_secciones;
        int n_secciones_x, n_secciones_y;       // Numero de secciones en X e Y
        int seccion_x, seccion_y;           
        int seccion_actual;
        bool division_completa;
        mutex mutex;

    public:
        DivisorSector(int _base_imagen, int _altura_imagen, int _total_secciones)
        :   base_imagen(_base_imagen), altura_imagen(_altura_imagen),
            total_secciones(_total_secciones),
            seccion_x(0), seccion_y(0),
            seccion_actual(0),
            division_completa(false) {
                pair<int, int> factores = calcular_factores(total_secciones);
                n_secciones_x = factores.first;
                n_secciones_y = factores.second;
            }

        bool obtener_seccion(Rango_seccion& puntos_seccion);
};
#endif // SECTORES_HPP