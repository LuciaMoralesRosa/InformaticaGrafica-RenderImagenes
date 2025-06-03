#ifndef RGB_HPP
#define RGB_HPP

#define R 0
#define G 1
#define B 2

#include <iostream>

using namespace std;

class RGB {
    private:
        float r, g, b;
        float rgb[3] = {r, g, b};

    public:

        /** 
         * @brief Constructor con valores de componentes RGB. 
         * @note Por defecto se establece en negro
         * 
         * @param red El valor del componente rojo del color.
         * @param green El valor del componente verde del color.
         * @param blue El valor del componente azul del color.
         */
        RGB(float red = 0, float green = 0, float blue = 0) : 
            r(red), g(green), b(blue) {};


        /** 
         * @brief Destructor.
         */
        ~RGB() {}


        // Getters -------------------------------------------------------------
        float getR() const {return r;}
        float getG() const {return g;}
        float getB() const {return b;}


        // Comprobaciones ------------------------------------------------------
        bool es_negro() const;
        bool es_blanco() const;
        bool es_invalido() const;


        // Operadores ----------------------------------------------------------
        /**
         * @brief Acceso a los valores de los componentes RGB.
         * 
         * @param i El índice del componente (0 para R, 1 para G, 2 para B).
         * @return El valor del componente RGB correspondiente.
         */
        const float& operator[](int i) const;

        /**
         * @brief Escribe el color en el flujo de salida.
         * 
         * @param o El flujo de salida.
         * @param c El color a escribir.
         * @return El flujo de salida.
         */
        friend ostream &operator<< (ostream &o, const RGB &c);

        /**
         * @brief Lee el color desde el flujo de entrada.
         * 
         * @param i El flujo de entrada.
         * @param c El color a leer.
         * @return El flujo de entrada.
         */
        friend istream &operator>> (istream &i, RGB &c);
};



#endif // RGB_HPP