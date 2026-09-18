//
// Created by Ary on 18/09/2026.
//


#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Para std::max

using namespace std;

int main() {
    // Optimización de lectura para cadenas grandes (hasta 10^6 caracteres)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    // Arreglo de 256 posiciones (para caracteres ASCII) inicializado en -1
    // Guarda la última posición donde se vio cada carácter
    vector<int> ultima_pos(256, -1);

    int max_len = 0;
    int izq = 0; // Puntero izquierdo de la ventana

    // Recorremos la cadena carácter por carácter con el puntero derecho
    for (int der = 0; der < s.length(); ++der) {
        char c = s[der];

        // Si el carácter ya apareció DENTRO de la ventana actual
        if (ultima_pos[c] >= izq) {
            // Movemos el inicio de la ventana justo a la derecha de la repetición anterior
            izq = ultima_pos[c] + 1;
        }

        // Registramos/actualizamos la posición del carácter actual
        ultima_pos[c] = der;

        // Calculamos la longitud de la ventana actual y conservamos la máxima
        max_len = max(max_len, der - izq + 1);
    }

    cout << max_len << "\n";

    return 0;
}