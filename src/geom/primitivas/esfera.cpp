#include "esfera.hpp"

bool Esfera::intersecta_con_rayo(const Rayo& rayo, float& t) {
    // Vector4 origen_centro = distancia((Punto)rayo.getOrigen(), centro);
    
    // float a = prod_escalar(rayo.getDireccion(), rayo.getDireccion());
    // float b = 2 * prod_escalar(origen_centro, rayo.getDireccion());
    // float c = prod_escalar(origen_centro, origen_centro) - radio * radio;
    
    // float raiz = b * b - 4 * a * c;
    // if (raiz < 0) {
    //     return false;
    // }
    // else {
    //     float t1 = (-b - sqrt(raiz)) / (2 * a);
    //     float t2 = (-b + sqrt(raiz)) / (2 * a);
    //     if (t1 >= 0) {
    //         t = t1;
    //         return true;
    //     }
    //     if (t2 >= 0) {
    //         t = t2;
    //         return true;
    //     }
    //     return false;
    // }

    		Vector4 oc = distancia(rayo.getOrigen(), centro);
		float a = prod_escalar(rayo.getDireccion(), rayo.getDireccion());
		float b = 2 * prod_escalar(oc, rayo.getDireccion());
		float c = prod_escalar(oc, oc) - radio * radio;
		float discriminant = b * b - 4 * a * c;
		if (discriminant < 0) {
			return false;
		}
		else {
			float t1 = (-b - sqrt(discriminant)) / (2 * a);
			float t2 = (-b + sqrt(discriminant)) / (2 * a);
			if (t1 < 0 && t2 < 0)
				return false;
			if (t1 >= 0){
				t = t1;
				return true;
			}
			if (t2 >= 0){
				t = t2;
				return true;
			}
			return true;
		}
}