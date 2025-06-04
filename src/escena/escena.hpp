#ifndef ESCENA_HPP
#define ESCENA_HPP


#include "camara.hpp"
#include "iluminacion/luz.hpp"
#include "../color/RGB.hpp"
#include "../geom/primitivas/primitiva.hpp"
#include "../geom/primitivas/esfera.hpp"
#include "../geom/primitivas/plano.hpp"


class Escena {

    private:
        Camara camara;
        vector<Primitiva*> primitivas;
        vector<Luz*> luces;
        vector<RGB> imagen;
    
    public:
        Escena(const Camara& _camara, const vector<Primitiva*>& _primitivas,
            const vector<Luz*>& _luces)
            :
            camara(_camara), primitivas(_primitivas), luces(_luces) {}

        // Getters -------------------------------------------------------------
        int getBase() const { return camara.base; }
        int getAltura() const { return camara.altura; }
        const vector<RGB>& getImagen() const { return imagen; }

        // Operaciones ---------------------------------------------------------
        void renderizar_imagen(int RPP);
};


#endif // ESCENA_HPP