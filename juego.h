#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include <stack>
#include "jugador.h"
#include "carta.h"

using namespace std;

class Juego {
private:
    vector<Jugador> jugadores;
    stack<Carta> mazo;
    vector<vector<Carta>> pilas;
    vector<bool> pilasHabilitadas;
    bool rondaFinalIniciada;
    int jugadorActual;

    void inicializarMazo();
    void mezclarMazo();
    bool todasPilasDeshabilitadas() const;
    bool hayPilasDisponibles() const;
    bool hayPilasParaTomar() const;
    void mostrarCartasJugador(const Jugador& jugador) const;
    void finalizarJuego();

public:
    Juego(int numJugadores);
    void jugarTurno();
    void mostrarEstadoJuego() const;
    bool juegoTerminado() const;
    void calcularPuntajes() const;
    void reiniciarRonda();
};

#endif // JUEGO_H
