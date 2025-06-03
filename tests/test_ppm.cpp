#include "test_ppm.hpp"

#include "../src/formato/PPM.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void test_lectura_escritura_ppm(){

    string ruta = "assets/base/seymour_park.ppm";

    PPM imagen(ruta);
    cout << imagen << endl;

    imagen.escribir_imagen("test_PPM.ppm");
    
}