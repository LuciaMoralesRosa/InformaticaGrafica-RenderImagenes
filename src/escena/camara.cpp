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

    // Esquina superior izquierda del plano de imagen
    float x_inicio = l.getX();
    float y_inicio = -u.getY();
    float z = f.modulo();

    cout << "-L: " << x_inicio << ", -U: " << y_inicio << endl;
    cout << "Base pixel: " << base_pixel << " y altura pixel: " << altura_pixel << endl;

    for (int b = 0; b < base; b++) {
        for (int a = 0; a < altura; a++) {
            for (int r = 0; r < rpp; r++) {
                // Coordenadas del pixel (a, b)
                float pixel_x = x_inicio + b * base_pixel;
                float pixel_y = y_inicio + a * altura_pixel;

                // Generar aleatorio dentro del pixel
                float punto_x = generar_aleatorio(pixel_x, pixel_x + base_pixel);
                float punto_y = generar_aleatorio(pixel_y, pixel_y + altura_pixel);

                posiciones.push_back(Punto(punto_x, punto_y, z));
                //cout << "Punto: [" << punto_x << ", " << punto_y << ", " << z << "]" << endl;
            }
        }
    }
    cout << "Posiciones[5]: " << posiciones[5] << endl;
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
