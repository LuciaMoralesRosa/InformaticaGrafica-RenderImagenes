#include "camara.hpp"

#include "../geom/maths/aleatorio.hpp"

Camara::Camara(const Punto& _origen, const Direccion& _l, const Direccion& _u,
    const Direccion& _f, int _base, int _altura)
    :   
    origen(_origen), l(_l), u(_u), f(_f), base(_base), altura(_altura),
    base_pixel(2 * l.modulo() / base),  altura_pixel(2 * u.modulo() / altura) {
        
    if (prod_escalar(l, u) != 0 ||
        prod_escalar(l, f) != 0 ||
        prod_escalar(u, f) != 0) {
        throw "Alguno de los vectores que definen la camara no son perpendiculares.";
    }
}


void Camara::posicion_aleatoria(vector<Punto>& posiciones, int rpp) const {
    posiciones.clear();

    // Coordenada esquina izquieda superior del pixel actual
    float x = -l.modulo();
    float y = -u.modulo();
    float z = f.modulo();

    for(int b = 0; b < base; b++) {
        for(int a = 0; a < altura; a++) {
            for(int r = 0; r < rpp; r++) {
                // Generar aleatorio en el pixel actual
                float punto_x = generar_aleatorio(x, x + base_pixel);
                float punto_y = generar_aleatorio(y, y + altura_pixel);
                posiciones.push_back(Punto(punto_x, punto_y, z));
            }
            y = y + altura_pixel;
        }
        x = x + base_pixel;
    }
}
