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

Rayo Camara::obtener_rayo_aleatorio_en_seccion(int a, int b, generador_aleatorios& aleatorio) {
    Punto punto_izquierda_superior = f + l + u;

    // antialising -> vector randomizado
    Direccion direccion_rayo = Direccion(punto_izquierda_superior
        - (a + aleatorio.get()) * base_pixel * l.normalizar()
        - (b + aleatorio.get()) * altura_pixel * u.normalizar());

    // Crear el rayo desde la camara
    return Rayo(origen, direccion_rayo);
}
