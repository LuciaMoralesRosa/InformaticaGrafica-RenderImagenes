#include "camara.hpp"

#include "../geom/maths/aleatorio.hpp"

// -------------------------------- Constructor --------------------------------
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
// -------------------------------- Constructor --------------------------------


// -------------------------------- Operaciones --------------------------------
Rayo Camara::rayo_aleatorio_en_seccion(int a, int b, generador_aleatorios& aleatorio) {
    Punto esquina_superior_izquierda = f + l + u;

    // Offset aleatorio para antialiasing en X y Y
    float offset_x = a + aleatorio.get();
    float offset_y = b + aleatorio.get();

    // Dirección desplazada del rayo en el plano de la cámara
    Direccion desplazamiento_l = l.normalizar() * (offset_x * base_pixel);
    Direccion desplazamiento_u = u.normalizar() * (offset_y * altura_pixel);
    Direccion desplazamiento = desplazamiento_l + desplazamiento_u;

    // Dirección final del rayo desde el origen hacia el punto en el plano
    return Rayo(origen, Direccion(esquina_superior_izquierda - desplazamiento));
}
// -------------------------------- Operaciones --------------------------------
