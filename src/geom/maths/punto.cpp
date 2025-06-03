#include "punto.hpp"

// ------------------------------ Operaciones ------------------------------- //
Vector4 convertir_a_vector4 (Punto p) {
    return Vector4(p.getX(), p.getY(), p.getZ(), 1);
}
// ------------------------------ Operaciones ------------------------------- //


// ------------------------------- Operadores ------------------------------- //
istream &operator>> (istream &i, Punto &p) {
    i >> p.x >> p.y >> p.z;
    return i;
}
// ------------------------------- Operadores ------------------------------- //
