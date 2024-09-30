#include "jugador.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

Jugador::Jugador() : haTerminadoRonda(false), comodinesNormales(0), tieneComodinDorado(false), comodinesMulticolor(0) {}

void Jugador::agregarCarta(const Carta& carta) {
    if (carta.esComodin) {
        if (carta.esComodinDorado) {
            tieneComodinDorado = true;
        } else if (carta.esComodinMulticolor) {
            comodinesMulticolor++;
        } else {
            comodinesNormales++;
        }
    } else {
        mano[carta.color]++;
    }
}

void Jugador::terminarRonda() {
    haTerminadoRonda = true;
}

bool Jugador::haTerminado() const {
    return haTerminadoRonda;
}

void Jugador::reiniciarRonda() {
    haTerminadoRonda = false;
}

int calcularPuntosPorCantidad(int cantidad) {
    switch (cantidad) {
        case 1: return 1;
        case 2: return 3;
        case 3: return 6;
        case 4: return 10;
        case 5: return 15;
        default: return 21;
    }
}

int Jugador::calcularPuntuacion() const {
    vector<pair<string, int>> colores;
    for (const auto& [color, cantidad] : mano) {
        if (color != "Comodín") {
            colores.push_back({color, cantidad});
        }
    }
    
    sort(colores.begin(), colores.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    int puntuacion = 0;
    int comodinesEspeciales = (tieneComodinDorado ? 1 : 0) + comodinesMulticolor;
    
    for (int i = 0; i < min(3, static_cast<int>(colores.size())); ++i) {
        int cantidad = colores[i].second;
        while (comodinesEspeciales > 0 && cantidad < 6) {
            cantidad++;
            comodinesEspeciales--;
        }
        puntuacion += calcularPuntosPorCantidad(cantidad);
    }

    
    for (int i = 3; i < colores.size() && comodinesEspeciales > 0; ++i) {
        int cantidad = colores[i].second;
        while (comodinesEspeciales > 0 && cantidad < 6) {
            cantidad++;
            comodinesEspeciales--;
        }
        puntuacion += calcularPuntosPorCantidad(cantidad);
    }

    
    for (int i = 3; i < colores.size(); ++i) {
        if (colores[i].second <= 6) {
            puntuacion -= calcularPuntosPorCantidad(colores[i].second);
        }
    }

    puntuacion += comodinesNormales * 2;

    return puntuacion;
}

const map<string, int>& Jugador::obtenerMano() const {
    return mano;
}

int Jugador::obtenerComodinesNormales() const {
    return comodinesNormales;
}

int Jugador::obtenerComodinesMulticolor() const {
    return comodinesMulticolor;
}

bool Jugador::obtenerComodinDorado() const {
    return tieneComodinDorado;
}

    int puntuacion = calcularPuntuacion();
    cout << "Puntuación calculada: " << puntuacion << endl;
    
}
