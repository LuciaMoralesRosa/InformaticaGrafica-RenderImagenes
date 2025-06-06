#include "RGB.hpp"


// ----------------------------- Comprobaciones ----------------------------- //
bool RGB::es_negro() const {
    return r==0 && b==0 && g==0;
}

bool RGB::es_blanco() const {
    return r==255 && b==255 && g==255;
}

bool RGB::es_invalido() const {
    return r==-1 && g==-1 && b==-1;
}
// ----------------------------- Comprobaciones ----------------------------- //


// ------------------------------- Operadores ------------------------------- //

RGB operator+(const RGB& c1, const RGB& c2) {
    return RGB(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

RGB operator+=(RGB& c1, const RGB& c2) {
    c1 = c1 + c2;
    return c1;
}

const float& RGB::operator[](int i) const {
    switch(i) {
			case R:
				return r;
			case G:
				return g;
			case B:
				return b;
			default:
				throw invalid_argument("Indice invalido");
		}
}

ostream &operator<< (ostream &o, const RGB &c){
    o << c[0] << " " << c[1] << " " << c[2];
    return o;
}

istream &operator>> (istream &i, RGB &c){
    i >> c.rgb[0] >> c.rgb[1] >> c.rgb[2];
    return i;
}
// ------------------------------- Operadores ------------------------------- //
