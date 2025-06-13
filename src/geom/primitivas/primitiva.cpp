#include "primitiva.hpp"

#include "../maths/aleatorio.hpp"

generador_aleatorios ruleta_rusa(0, 1);
generador_aleatorios normalGenerator(-1, 1);

Primitiva::Primitiva(RGB kd, RGB ks, RGB kt, RGB ke, double n_d, double n_f, const string nombre)
    :   k_d(kd), k_s(ks), k_t(kt), k_e(ke), n_dentro(n_d), n_fuera(n_f), nombre(nombre) {

		// Gets the channel with the maximum contribution.
		char cd, cs, ct, ce;
		double maximo_difuso = kd.emision_maxima(&cd);
		double maximo_especular = ks.emision_maxima(&cs);
		double maximo_refraccion = kt.emision_maxima(&ct);
		double maximo_emision = ke.emision_maxima(&ce);
		double maximo_difuso_especular = max(maximo_difuso, maximo_especular);
		double maximo_refraccion_emision = max(maximo_refraccion, maximo_emision);
		double maxContribution = max(maximo_difuso_especular, maximo_refraccion_emision);
		if(maximo_difuso == maxContribution) {
            canal_maximo_rgb = cd;
        }
		else if(maximo_especular == maxContribution) {
            canal_maximo_rgb = cs;
        }
		else if(maximo_refraccion == maxContribution) {
            canal_maximo_rgb = ct;
        }
		else {
            canal_maximo_rgb = ce;
        }

		// Checks that the sum of the color coeficients is 1 or less.
		for (int i = 0; i < 3; ++i)
			if (kd[i] + ks[i] + kt[i] + ke[i] > 255) {
				cout << "Error: the sum of figure color coeficients must be for channel, as much, 255.\n";
				exit(1);
		}
}

EVENTO Primitiva::evento_aleatorio() {
		float r = ruleta_rusa.get();
		float aux = k_d[canal_maximo_rgb];
		if (r < aux) return DIFUSO;
		aux += k_s[canal_maximo_rgb];
		if (r < aux) return ESPECULAR;
		aux += k_t[canal_maximo_rgb];
		if (r < aux) return REFRACCION;
		aux += k_e[canal_maximo_rgb];
		if (r < aux) return EMISION;
        return ABSORCION;
}



// Gets a random direction to bounce the ray.
Direccion randBounce(const Punto& p, Direccion normal) {
    Direccion res = Direccion(normalGenerator.get(), normalGenerator.get(), normalGenerator.get());
    if (res.modulo() > 1)
            res = Direccion(normalGenerator.get(), normalGenerator.get(), normalGenerator.get());
    return prod_escalar(res, normal) > 0 ? res.normalizar() : -res.normalizar();
}

Direccion reflectionBounce (const Direccion& d, const Punto& p, Direccion normal) {
    Direccion dNorm = d.normalizar();
    Direccion localNormal = normal;
    if (prod_escalar(dNorm, localNormal) < 0) {
        localNormal = -localNormal;
    }
    return (dNorm - 2 * localNormal * prod_escalar(dNorm, localNormal)).normalizar();
}

Direccion refractionBounce (const Direccion& wi, const Direccion& n, float eta) {
    float cosThetaI = prod_escalar(n, wi);
    float sin2ThetaI = max(0.f, 1.0f - cosThetaI * cosThetaI);
    float sin2ThetaT = eta * eta * sin2ThetaI;
    float cosThetaT = sqrt(1 - sin2ThetaT);
    return eta * -wi + (eta * cosThetaI - cosThetaT) * n;
}

RGB Primitiva::getFr(EVENTO ph, Direccion& d, Punto p, Direccion n) const {
    double nRefraccion = n_dentro / n_fuera;
    Direccion wi;
    Direccion normal, aux;
    float eta;
    switch (ph) {
        case DIFUSO:
            aux = randBounce(p, n);
            d = prod_escalar(aux, d) < 0 ? aux : -aux;
            return k_d / (M_PI * k_d[canal_maximo_rgb]);
        case ESPECULAR:
            d = reflectionBounce(d, p, n);
            return k_s / k_s[canal_maximo_rgb];
        case REFRACCION:
            wi = d;
            wi = -wi.normalizar();
            if(prod_escalar(wi, normal) < 0){
                normal = -normal;
                eta = nRefraccion / 1;
            } else{
                eta = 1 / nRefraccion;
            }
            d = refractionBounce(wi, normal, eta);
            return k_t / k_t[canal_maximo_rgb];
        case EMISION:
            return k_e / k_e[canal_maximo_rgb];
        default:
            return RGB();
    }
}








// INTENTO FALLIDO --------------------------------------------------------------

RGB Primitiva::fr_solo_difuso(Punto x, Direccion wi, Direccion wo, Direccion n) {
    return k_d/M_PI;
}
RGB Primitiva::fr_difuso(Punto x, Direccion wi, Direccion wo, Direccion n) {
    return k_d/p_d;
}
RGB Primitiva::fr_especular(Punto x, Direccion wi, Direccion wo, Direccion n) {
    return k_s/p_s;
}
RGB Primitiva::fr_refraccion(Punto x, Direccion wi, Direccion wo, Direccion n) {
    return k_t/p_t;
}
RGB Primitiva::fr(Punto x, Direccion wi, Direccion wo, Direccion n) {
    RGB rgb = RGB({0,0,0});
    Direccion wr = reflejar(wo, n);
    Direccion wt = refractar(wo, n);
    if (wi == wr) { // especular
        rgb = k_s/p_s;
    } else if (wi == wt) { // refracción
        rgb = k_t/p_t;
    } else { // difuso
        rgb =  k_d/p_d;
    }
    return rgb;
}
Direccion Primitiva::reflejar(Direccion wi, Direccion n) {
    return wi - 2* prod_escalar(wi, n) * n;
}
Direccion Primitiva::refractar(Direccion wi, Direccion n) {
    float eta = n_fuera / n_dentro;
    float cosI = prod_escalar(n.normalizar(), wi.normalizar());
    Direccion normal = n.normalizar();
    if (cosI < 0) {
        cosI = -cosI;
    } else {
        normal = -normal;
        eta = 1 / eta;
    }
    double k = 1 - eta * eta * (1.0 - cosI*cosI);
    if (k < 0) {
        return Direccion();
    } else {
        return eta*wi.normalizar() + (eta * cosI - sqrt(k))*normal;
    }
}