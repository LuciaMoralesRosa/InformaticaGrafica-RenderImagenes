#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "../geom/maths/direccion.hpp"
#include "../geom/maths/punto.hpp"
#include "../geom/maths/vector4.hpp"

void isNan(float valor) {
	if(isnan(valor)) {
		cout << "Es NAN" << endl;
	}
}
void isNan(Direccion d) {
	isNan(d.getX());
	isNan(d.getY());
	isNan(d.getZ());
}
void isNan(Vector4 v) {
	isNan(v.getX());
	isNan(v.getY());
	isNan(v.getZ());
}
void isNan(Punto p) {
	isNan(p.getX());
	isNan(p.getY());
	isNan(p.getZ());
}



#endif // DEBUG_HPP