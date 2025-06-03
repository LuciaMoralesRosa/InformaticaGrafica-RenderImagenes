#include "vector4.hpp"

float Vector4::modulo() const {
    return sqrt(x * x + y * y + z * z);
}

// ------------------------------- Operaciones ------------------------------ //
Vector4 Vector4::normalizar() const {
    if(es_punto) {
        throw runtime_error("No se puede normalizar un punto.");
    }
    return *this / modulo();
}


float prod_escalar(const Vector4 &d1, const Vector4 &d2) {
    if(d1.es_punto() || d2.es_punto()) {
        throw runtime_error("No se puede hacer el producto escalar de un punto.");
    }
    return d1.x * d2.x + d1.y * d2.y + d1.z * d2.z;
}

Vector4 prod_vectorial(const Vector4 &d1, const Vector4 &d2) {
    if(d1.es_punto() || d2.es_punto()) {
        throw runtime_error("No se puede hacer el producto escalar de un punto.");
    }
    return Vector4( d1.y * d2.z - d1.z * d2.y, 
                    d1.z * d2.x - d1.x * d2.z, 
                    d1.x * d2.y - d1.y * d2.x, 
                    0);
}

Vector4 distancia(Vector4 &p1, Vector4 &p2) {
    if(p1.es_direccion() || p2.es_direccion()) {
        throw runtime_error("No se puede calcular la distancia entre direcciones.");
    }
    return Vector4(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z, 0);
}

float angulo_entre_direcciones (const Vector4 &d1, const Vector4 &d2) {
    if(d1.es_punto() || d2.es_punto()) {
        throw runtime_error("No se puede hacer el producto escalar de un punto.");
    }
    return acos(prod_escalar(d1, d2) / (d1.modulo() * d2.modulo()));
}
// ------------------------------- Operaciones ------------------------------ //


// ---------------------- Transformaciones de matrices ---------------------- //
void Vector4::aplicar_matriz(Matriz m) {
    Vector4 aux = Vector4(0, 0, 0, 0);
    aux.x = m.getComponente(0, 0) * 
            x + m.getComponente(0, 1) * 
            y + m.getComponente(0, 2) * 
            z + m.getComponente(0, 3) * punto_direccion;
    aux.y = m.getComponente(1, 0) * 
            x + m.getComponente(1, 1) * 
            y + m.getComponente(1, 2) * 
            z + m.getComponente(1, 3) * punto_direccion;
    aux.z = m.getComponente(2, 0) * 
            x + m.getComponente(2, 1) * 
            y + m.getComponente(2, 2) * 
            z + m.getComponente(2, 3) * punto_direccion;
    aux.punto_direccion = m.getComponente(3, 0) * 
            x + m.getComponente(3, 1) * 
            y + m.getComponente(3, 2) *
            z + m.getComponente(3, 3) * punto_direccion;
    *this = aux;
}

void Vector4::trasladar(float x, float y, float z) {
    Matriz m = Matriz();
    m.matriz_traslacion(x, y, z);
    this->aplicar_matriz(m);
}

void Vector4::escalar(float x, float y, float z) {
    Matriz m = Matriz();
    m.matriz_escalado(x, y, z);
    this->aplicar_matriz(m);
}

void Vector4::rotar_x(float grados) {
    Matriz m = Matriz();
    m.matriz_rotacion_x(grados);
    this->aplicar_matriz(m);
}

void Vector4::rotar_y(float grados) {
    Matriz m = Matriz();
    m.matriz_rotacion_y(grados);
    this->aplicar_matriz(m);
}

void Vector4::rotar_z(float grados) {
    Matriz m = Matriz();
    m.matriz_rotacion_z(grados);
    this->aplicar_matriz(m);
}

void Vector4::cambiar_base(Vector4 o, Vector4 u, Vector4 v, Vector4 w) {
    Matriz m = Matriz();
    m.setComponente(0, 0, u.x);
    m.setComponente(1, 0, u.y);
    m.setComponente(2, 0, u.z);
    m.setComponente(0, 1, v.x);
    m.setComponente(1, 1, v.y);
    m.setComponente(2, 1, v.z);
    m.setComponente(0, 2, w.x);
    m.setComponente(1, 2, w.y);
    m.setComponente(2, 2, w.z);
    m.setComponente(0, 3, o.x);
    m.setComponente(1, 3, o.y);
    m.setComponente(2, 3, o.z);
    m.setComponente(3, 3, 1);
    
    this->aplicar_matriz(m);
}

void Vector4::invertir_cambiar_base(Vector4 o, Vector4 u, Vector4 v, Vector4 w) {
    Matriz m = Matriz();
    m.setComponente(0, 0, u.x);
    m.setComponente(1, 0, u.y);
    m.setComponente(2, 0, u.z);
    m.setComponente(0, 1, v.x);
    m.setComponente(1, 1, v.y);
    m.setComponente(2, 1, v.z);
    m.setComponente(0, 2, w.x);
    m.setComponente(1, 2, w.y);
    m.setComponente(2, 2, w.z);
    m.setComponente(0, 3, o.x);
    m.setComponente(1, 3, o.y);
    m.setComponente(2, 3, o.z);
    m.setComponente(3, 3, 1);
    m.invertir_matriz();
    this->aplicar_matriz(m);
}
// ---------------------- Transformaciones de matrices ---------------------- //



// ------------------------------- Operadores ------------------------------- //
Vector4 operator+(const Vector4 &v1, const Vector4 &v2) {
    return Vector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.punto_direccion);
}

Vector4 operator-(const Vector4 &v1, const Vector4 &v2) {
    return Vector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.punto_direccion);
}

Vector4 operator-(const Vector4 &v) {
    return Vector4(-v.x, -v.y, -v.z, v.punto_direccion);
}

Vector4 operator*(const Vector4 &v, const float &s) {
    return Vector4(v.x * s, v.y * s, v.z * s, 0);
}

Vector4 operator*(const float &s, const Vector4 &v) {
    return v * s;
}

Vector4 operator/(const Vector4 &v, const float &s) {
    return Vector4(v.x / s, v.y / s, v.z / s, 0);
}

Vector4 operator/(const float &s, const Vector4 &v) {
    return v / s;
}

bool operator== (const Vector4 &v1, const Vector4 &v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.punto_direccion == v2.punto_direccion;
}

const float& Vector4::operator[](int i) const {
    switch (i%3) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }
    return x;
}

ostream &operator<< (ostream &o, const Vector4 &v){
    o << (v.punto_direccion?"(":"[") << v.x << ", " << v.y << ", " << v.z << (v.punto_direccion?")":"]");
    return o;
}
// ------------------------------- Operadores ------------------------------- //
