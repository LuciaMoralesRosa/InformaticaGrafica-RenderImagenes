#include "plano.hpp"

bool Plano::intersecta_con_rayo(const Rayo& rayo, float& t) {
    // Producto escalar = 0 -> Rayo ⊥ Normal del plano -> Rayo || Plano
    // float escalar = prod_escalar(rayo.getDireccion(), normal);
    // if (abs(escalar) > 1e-6) {
    //     // Plano: 'n·'p = d
    //     // Rayo: r(t) = 'o + t'd
    //     // Interseccion: t = (d-'n·'o) / 'n·'d = (d-'n·'o) / escalar
    //     float n_o = prod_escalar(distancia(Punto(0,0,0), rayo.getOrigen()), normal);
    //     t = -(d - n_o) / escalar;
    //     return t >= 0;
    // }
    // // Rayo || Plano -> No hay interseccion
    // return false; 

    float denom = prod_escalar(rayo.getDireccion(), normal);
		if (abs(denom) > 1e-6) {
			t = -(d - prod_escalar(distancia(Punto(0,0,0), rayo.getOrigen()), normal))
                / denom;
			return t >= 0;
		}
		// If not, then it's false (because tray and plane are parallel).
		return false;
}

