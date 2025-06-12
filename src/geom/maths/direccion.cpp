#include "direccion.hpp"

#include "aleatorio.hpp"

// ------------------------------ Operaciones ------------------------------- //
Direccion Direccion::direccion_aleatoria() {
    float x = aleatorio_unitario.get();
    float y = aleatorio_unitario.get();
    float z = aleatorio_unitario.get();
    while(x*x + y*y + z*z > 1) {
        x = aleatorio_unitario.get();
        y = aleatorio_unitario.get();
        z = aleatorio_unitario.get();
    }
    return Direccion(x, y, z).normalizar();
}
// ------------------------------ Operaciones ------------------------------- //


// ------------------------------- Operadores ------------------------------- //
istream &operator>>(istream &i, Direccion &d) {
    i >> d.x >> d.y >> d.z;
    return i;
}
// ------------------------------- Operadores ------------------------------- //
