#ifndef JUGADOR_H
#define JUGADOR_H

#include <map>
#include <string>
#include "carta.h"

using namespace std;

class Jugador {
private:
    map<string, int> mano;
    bool haTerminadoRonda;
    int comodinesNormales;
    bool tieneComodinDorado;
    int comodinesMulticolor;

public:
    Jugador();
    void agregarCarta(const Carta& carta);
    void terminarRonda();
    bool haTerminado() const;
    void reiniciarRonda();
    int calcularPuntuacion() const;
    const map<string, int>& obtenerMano() const;
    int obtenerComodinesNormales() const;
    int obtenerComodinesMulticolor() const;
    bool obtenerComodinDorado() const;  
    void probarCalculoPuntuacion();
};

#endif // JUGADOR_H