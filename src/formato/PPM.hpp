#ifndef PPM_HPP
#define PPM_HPP

#include <string>
#include <vector>

#include "../color/RGB.hpp"

using namespace std;

class PPM {
    private:
        string formato;
        string comentario;
        float m;
        int base;
        int altura;
        int c;
        vector<RGB> tripletasRGB;

    public:
        // Constructores ------------------------------------------------------- 
        PPM(string _formato, string _comentario,
            float _m = 0, int _base = 0, int _altura = 0,
            int _c = 0, vector<RGB> _tripletasRGB = {})
            :
            formato(_formato), comentario(_comentario), m(_m), base(_base), 
            altura(_altura), c(_c), tripletasRGB(_tripletasRGB) {}
        
        PPM(const string ruta);

        // Setters -------------------------------------------------------------
        void setTripletasRGB(const vector<RGB>& nuevas_tripletasRGB);
        void setTripleta(const RGB& nueva_tripleta, int i);

        // Operaciones ---------------------------------------------------------
        void escribir_imagen(const string ruta) const;

        // Operadores ----------------------------------------------------------
        friend ostream& operator<<(std::ostream& os, const PPM& img);
};

#endif // PPM_HPP