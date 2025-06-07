#include "sectores.hpp"

bool DivisorSector::obtener_seccion(Rango_seccion& puntos_seccion) {
    mutex.lock();
    if (division_completa) {
        // Ya no quedan mas secciones por tratar
        mutex.unlock();
        // Cada hilo recibira su false
        return false;
    }

    // Definicion de las esquinas de la seccion
    Esquina_pixeles superior_izquierda = {
        seccion_x * base_imagen / n_secciones_x,
        seccion_y * altura_imagen / n_secciones_y
    };
    
    Esquina_pixeles inferior_derecha = {
        seccion_x * base_imagen / n_secciones_x + base_imagen / n_secciones_x,
        seccion_y * altura_imagen / n_secciones_y + altura_imagen / n_secciones_y
    };

    puntos_seccion = {superior_izquierda, inferior_derecha};


    // Actualizacion y comprobacion de valores limites
    if(++seccion_x == n_secciones_x) {
        seccion_x = 0;
        if(++seccion_y == n_secciones_y) {
            division_completa = true;
        }
    }

    mutex.unlock();
    return true;
}