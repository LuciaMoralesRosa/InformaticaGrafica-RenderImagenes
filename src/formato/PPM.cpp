#include "PPM.hpp"

#include <sstream>
#include <fstream>
#include <iomanip>

#define RGB_VALOR 255.0f

// ------------------------------ Constructor ------------------------------- //
PPM::PPM(const string ruta) {
    ifstream fichero(ruta);
    if (!fichero) {
        cerr << "Error al abrir el archivo." << endl;
    }

    getline(fichero, formato);
    if(formato != "P3") {
        cerr << "Formato de imagen no soportado: " << formato << endl;
        exit(1);
    }

    string linea;
    getline(fichero, linea);
    if(linea[0] == '#') {
        if(linea[1] != 'M') {
            // No hay m pero si comentario
            comentario = linea.substr(1);
            getline(fichero, linea);
        }
        else {
            // Hay m
            m = stof(linea.substr(5));
            getline(fichero, linea);
            if(linea[0] == '#') {
                comentario = linea.substr(1);
                getline(fichero, linea);
            }
        }
    }

    istringstream iss(linea);
    iss >> base >> altura;
    if (iss.fail()) {
        cerr << "Error al leer las dimensiones de la imagen." << endl;
        exit(1);
    }

    getline(fichero, linea);
    c = stoi(linea);

    vector<RGB> colores;
    while (getline(fichero, linea)) {
        istringstream ss(linea);
        int r, g, b;
        while (ss >> r >> g >> b) {
            colores.emplace_back((r*m)/c * RGB_VALOR, (g*m)/c * RGB_VALOR, (b*m)/c * RGB_VALOR);
        }
    }

    tripletasRGB = colores;
    if (tripletasRGB.size() != static_cast<size_t>(base * altura)) {
        cerr << "Error: El numero de tripletas RGB no coincide con las "
                << "dimensiones de la imagen." << endl;
        exit(1);
    }
}
// ------------------------------ Constructor ------------------------------- //

// -------------------------------- Setters --------------------------------- //
void PPM::setTripletasRGB(const vector<RGB>& nuevas_tripletasRGB) {
    tripletasRGB = nuevas_tripletasRGB;
}

void PPM::setTripleta(const RGB& nueva_tripleta, int i) {
    if (i >= 0 && static_cast<size_t>(i) < tripletasRGB.size()) {
        tripletasRGB[i] = nueva_tripleta;
    } else {
        throw out_of_range("En indice de la tripleta RGB es invalido.");
    }
}
// -------------------------------- Setters --------------------------------- //

// ------------------------------ Operaciones ------------------------------- //
void PPM::escribir_imagen(const string ruta) const {
    ofstream fichero(ruta);
    if (!fichero.is_open()) {
        cerr << "Error abriendo el fichero de salida \"" << ruta << "\"" << endl;
        exit(1);
    }

    fichero << formato << endl;
    fichero << "#MAX=" << m << endl;
    fichero << '#' + comentario << endl;
    fichero << base << " " << altura << endl;
    fichero << c << endl;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < base; j++) {
            fichero << fixed << setprecision(0) <<
                    (tripletasRGB[i*base + j][0] * c) / (m * RGB_VALOR) << " "
                    << fixed << setprecision(0) << 
                    (tripletasRGB[i*base + j][1] * c) / (m * RGB_VALOR) << " "
                    << fixed << setprecision(0) << 
                    (tripletasRGB[i*base + j][2] * c) / (m * RGB_VALOR) << "     ";
        }
        fichero << endl;
    }
    fichero.close();
}
// ------------------------------ Operaciones ------------------------------- //


// ------------------------------ Operadores -------------------------------- //
ostream& operator<<(ostream& os, const PPM& img) {
    os << "IMAGEN PPM:\n";
    os << "\tFormato: " << img.formato << "\n";
    os << "\tm: " << img.m << "\n";
    os << "\tComentario: " << img.comentario << "\n";
    os << "\tBase: " << img.base << "\n";
    os << "\tAltura: " << img.altura << "\n";
    os << "\tc: " << img.c << "\n";
    //os << "\tTripletas RGB (" << img.tripletasRGB.size() << "):\n";
    //for (int i = 0; i < img.altura; i++) {
    //    for (int j = 0; j < img.base; j++) {
    //        os << img.tripletasRGB[i*img.base + j] << " "
    //                << img.tripletasRGB[i*img.base + j] << " "
    //                << img.tripletasRGB[i*img.base + j] << "     ";
    //    }
    //    os << endl;
    //}
    
    return os;
}
// ------------------------------ Operadores -------------------------------- //
