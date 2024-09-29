#ifndef CARTA_H
#define CARTA_H

#include <string>

using namespace std;

struct Carta {
    string color;
    int puntos;
    bool esComodin;
    bool esRondaFinal;
    bool esComodinDorado;
    bool esComodinMulticolor;

    Carta(string c = "", int p = 0, bool comodin = false, bool rondaFinal = false, bool comodinDorado = false, bool comodinMulticolor = false)
        : color(c), puntos(p), esComodin(comodin), esRondaFinal(rondaFinal), esComodinDorado(comodinDorado), esComodinMulticolor(comodinMulticolor) {}
};

#endif // CARTA_H