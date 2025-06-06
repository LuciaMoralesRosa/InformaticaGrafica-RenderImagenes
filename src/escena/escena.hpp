#ifndef ESCENA_HPP
#define ESCENA_HPP


#include "camara.hpp"
#include "iluminacion/luz.hpp"
#include "../color/RGB.hpp"
#include "../geom/primitivas/primitiva.hpp"
#include "../geom/primitivas/esfera.hpp"
#include "../geom/primitivas/plano.hpp"

class DivisorSector;
class Escena {

    private:
        Camara camara;
        vector<Primitiva*> primitivas;
        vector<Luz*> luces;
        vector<RGB> imagen;
        
        void renderizar_seccion(int RPP, int x_izquierda, int x_derecha, int y_abajo, int y_arriba);
        bool gestionar_rebotes(Primitiva*& primitiva_intersectada, Rayo& rayo);
        Primitiva* intersectar_primitiva(const Rayo& rayo, float& min_t, float& t);

    
    public:
        Escena(const Camara& _camara, const vector<Primitiva*>& _primitivas,
            const vector<Luz*>& _luces)
            :
            camara(_camara), primitivas(_primitivas), luces(_luces),
            imagen(vector<RGB>(camara.altura*camara.base)) {}

        // Getters -------------------------------------------------------------
        int getBase() const { return camara.base; }
        int getAltura() const { return camara.altura; }
        const vector<RGB>& getImagen() const { return imagen; }

        // Operaciones ---------------------------------------------------------
        void renderizar_escena(int RPP = 1, int n_sectores = 1);
};


#endif // ESCENA_HPP