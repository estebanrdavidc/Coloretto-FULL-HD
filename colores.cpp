#include "colores.h"

using namespace std;

string colorearTexto(const string& texto, const string& color) {
    string codigoColor;
    if (color == "Verde") codigoColor = "\033[32m";
    else if (color == "Amarillo") codigoColor = "\033[33m";
    else if (color == "Azul") codigoColor = "\033[34m";
    else if (color == "Rojo") codigoColor = "\033[31m";
    else if (color == "Morado") codigoColor = "\033[35m";
    else if (color == "Rosado") codigoColor = "\033[95m";
    else if (color == "Naranja") codigoColor = "\033[91m";
    else if (color == "Comodín") codigoColor = "\033[97m";
    else codigoColor = "\033[0m";

    return codigoColor + texto + "\033[0m";
}