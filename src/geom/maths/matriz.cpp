#include "matriz.hpp"

// ------------------------------ Constructores ------------------------------//
Matriz::Matriz() {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++)
            m[i][j] = 0;
    }
}

Matriz::Matriz(float m[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++)
            this->m[i][j] = m[i][j];
    }
}
// ------------------------------ Constructores ----------------------------- //


// ------------------------------ Operaciones ------------------------------- //
void Matriz::matriz_traslacion(float x, float y, float z){
for (int i = 0; i < DIM; i++)
    m[i][i] = 1;
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
}

void Matriz::matriz_escalado(float x, float y, float z){
    m[0][0] = x;
    m[1][1] = y;
    m[2][2] = z;
    m[3][3] = 1;
}

void Matriz::matriz_rotacion_x(float angulo){
    angulo = angulo * M_PI / 180;
    m[0][0] = 1;
    m[1][1] = cos(angulo);
    m[1][2] = -sin(angulo);
    m[2][1] = sin(angulo);
    m[2][2] = cos(angulo);
    m[3][3] = 1;
}

void Matriz::matriz_rotacion_y(float angulo){
    angulo = angulo * M_PI / 180;
    m[0][0] = cos(angulo);
    m[0][2] = sin(angulo);
    m[1][1] = 1;
    m[2][0] = -sin(angulo);
    m[2][2] = cos(angulo);
    m[3][3] = 1;
}

void Matriz::matriz_rotacion_z(float angulo){
    angulo = angulo * M_PI / 180;
    m[0][0] = cos(angulo);
    m[0][1] = -sin(angulo);
    m[1][0] = sin(angulo);
    m[1][1] = cos(angulo);
    m[2][2] = 1;
    m[3][3] = 1;
}

void Matriz::cambiar_filas(Matriz matriz, int f1, int f2) {
    for (int i = 0; i < DIM; i++) {
        swap(matriz.m[f1][i], matriz.m[f2][i]);
    }
}

bool Matriz::invertir_matriz() {
    Matriz matriz_identidad = Matriz();
    for (int i = 0; i < DIM; i++) {
        matriz_identidad.m[i][i] = 1.0;
    }

    for (int i = 0; i < DIM; i++) {
        // Buscar el elemento pivote en la columna i
        int fila_pivote = i;
        for (int j = i + 1; j < DIM; j++) {
            if (abs(m[j][i]) > abs(m[fila_pivote][i])) {
                fila_pivote = j;
            }
        }

        // Intercambiar filas si es necesario
        if (fila_pivote != i) {
            cambiar_filas(m, i, fila_pivote);
            cambiar_filas(matriz_identidad, i, fila_pivote);
        }

        // Si el pivote es cero, la matriz no es invertible
        float pivote = m[i][i];
        if (pivote == 0.0) {
            cout << "Matriz cannt be inverted." << endl;
            return false;
        }

        // Normalizar la fila i dividiendo por el pivote
        for (int j = 0; j < DIM; j++) {
            m[i][j] /= pivote;
            matriz_identidad.m[i][j] /= pivote;
        }

        // Borrar los elementos por debajo y por encima del pivote
        for (int j = 0; j < DIM; j++) {
            if (j != i) {
                float factor = m[j][i];
                for (int k = 0; k < DIM; k++) {
                    m[j][k] -= factor * m[i][k];
                    matriz_identidad.m[j][k] -= factor * matriz_identidad.m[i][k];
                }
            }
        }
    }

    // Copiar la matriz identidad invertida a la matriz original
    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            m[i][j] = matriz_identidad.m[i][j];
        }
    }

    return true;
}

// ------------------------------- Operadores ------------------------------- //
ostream &operator<< (ostream &o, const Matriz &m) {
    o << "Matriz 4x4:\n";
    for (int i = 0; i < DIM; i++) {
        o << "\t| ";
        for(int j = 0; j < DIM; j++) {    
            o << fixed << setprecision(2) << m.m[i][j] << "  ";
        }
        o << " |\n";
    }
    return o;
}
// ------------------------------- Operadores ------------------------------- //