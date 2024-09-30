#include "juego.h"
#include "colores.h"
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;

Juego::Juego(int numJugadores) : jugadores(numJugadores), pilas(numJugadores), pilasHabilitadas(numJugadores, true), rondaFinalIniciada(false), jugadorActual(0) {
    inicializarMazo();
    mezclarMazo();
}

void Juego::inicializarMazo() {
    vector<string> colores = {"Verde", "Amarillo", "Azul", "Rojo", "Morado", "Rosado", "Naranja"};
    for (const auto& color : colores) {
        for (int i = 0; i < 9; ++i) {
            mazo.push(Carta(color));
        }
    }
    for (int i = 0; i < 10; ++i) {
        mazo.push(Carta("Comodín", 2, true));
    }
    mazo.push(Carta("Comodín Dorado", 0, true, false, true));
    mazo.push(Carta("Comodín Multicolor", 0, true, false, false, true));
    mazo.push(Carta("Comodín Multicolor", 0, true, false, false, true));
}

void Juego::mezclarMazo() {
    vector<Carta> tempMazo;
    while (!mazo.empty()) {
        tempMazo.push_back(mazo.top());
        mazo.pop();
    }
    
    auto rng = default_random_engine {};
    shuffle(tempMazo.begin(), tempMazo.end(), rng);
    
    for (const auto& carta : tempMazo) {
        mazo.push(carta);
    }
}


bool Juego::todasPilasDeshabilitadas() const {
    return all_of(pilasHabilitadas.begin(), pilasHabilitadas.end(), 
                       [](bool habilitada) { return !habilitada; });
}

bool Juego::hayPilasDisponibles() const {
    for (size_t i = 0; i < pilas.size(); ++i) {
        if (pilasHabilitadas[i] && pilas[i].size() < 3) {
            return true;
        }
    }
    return false;
}

bool Juego::hayPilasParaTomar() const {
    for (size_t i = 0; i < pilas.size(); ++i) {
        if (pilasHabilitadas[i] && !pilas[i].empty()) {
            return true;
        }
    }
    return false;
}

void Juego::jugarTurno() {
    if (jugadores[jugadorActual].haTerminado() || (todasPilasDeshabilitadas() && !hayPilasParaTomar())) {
        jugadorActual = (jugadorActual + 1) % jugadores.size();
        return;
    }

    cout << "Turno del Jugador " << jugadorActual + 1 << endl;
    
    int opcion;
    if (hayPilasDisponibles() && hayPilasParaTomar()) {
        cout << "1. Robar carta" << endl;
        cout << "2. Tomar pila" << endl;
        cin >> opcion;
    } else if (hayPilasParaTomar()) {
        cout << "No hay pilas disponibles para colocar cartas. Debes tomar una pila." << endl;
        opcion = 2;
    } else {
        cout << "No hay pilas para tomar. Debes robar una carta." << endl;
        opcion = 1;
    }

    if (opcion == 1 && hayPilasDisponibles()) {
        Carta carta = mazo.top();
        mazo.pop();

        if (mazo.size() == 16) {
            cout << "¡RONDA FINAL!, ROBANDO OTRA CARTA" << endl;
            rondaFinalIniciada = true;
            mazo.pop();
        }

        cout << "Has robado una carta " << colorearTexto(carta.color, carta.color) << endl;
        
        cout << "Elige una pila para colocar la carta (0-" << pilas.size() - 1 << "): ";
        int pila;
        cin >> pila;

        while (pila < 0 || pila >= pilas.size() || pilas[pila].size() >= 3 || !pilasHabilitadas[pila]) {
            cout << "Pila inválida, llena o deshabilitada. Elige otra: ";
            cin >> pila;
        }

        pilas[pila].push_back(carta);
    } else if (opcion == 2 && hayPilasParaTomar()) {
        cout << "Elige una pila para tomar (0-" << pilas.size() - 1 << "): ";
        int pila;
        cin >> pila;

        while (pila < 0 || pila >= pilas.size() || pilas[pila].empty() || !pilasHabilitadas[pila]) {
            cout << "Pila inválida, vacía o deshabilitada. Elige otra: ";
            cin >> pila;
        }

        bool tieneComodinDorado = false;
        for (const auto& carta : pilas[pila]) {
            jugadores[jugadorActual].agregarCarta(carta);
            if (carta.esComodinDorado) {
                tieneComodinDorado = true;
            }
        }
        
        if (tieneComodinDorado && !mazo.empty()) {
            Carta cartaExtra = mazo.top();
            mazo.pop();
            jugadores[jugadorActual].agregarCarta(cartaExtra);
            cout << "Has tomado una carta extra del mazo debido al Comodín Dorado: " << colorearTexto(cartaExtra.color, cartaExtra.color) << endl;
        }
        
        pilas[pila].clear();
        pilasHabilitadas[pila] = false;
        jugadores[jugadorActual].terminarRonda();
    } else {
        cout << "Opción no válida. Saltando turno." << endl;
    }

    jugadorActual = (jugadorActual + 1) % jugadores.size();

    if (juegoTerminado()) {
        finalizarJuego();
    } else if (all_of(jugadores.begin(), jugadores.end(), 
                    [](const Jugador& j) { return j.haTerminado(); }) ||
        (todasPilasDeshabilitadas() && !hayPilasParaTomar())) {
        reiniciarRonda();
    }
}

void Juego::mostrarEstadoJuego() const {
    cout << "\nEstado del juego:" << endl;
    cout << "Cartas en el mazo: " << mazo.size() << endl;
    
    for (size_t i = 0; i < pilas.size(); ++i) {
        cout << "Pila " << i << (pilasHabilitadas[i] ? " (Habilitada): " : " (Deshabilitada): ");
        for (const auto& carta : pilas[i]) {
            cout << colorearTexto(carta.color, carta.color) << " ";
        }
        cout << endl;
    }

    for (size_t i = 0; i < jugadores.size(); ++i) {
        cout << "Jugador " << i + 1 << (jugadores[i].haTerminado() ? " (Terminado): " : ": ");
        mostrarCartasJugador(jugadores[i]);
        cout << endl;
    }
}

void Juego::mostrarCartasJugador(const Jugador& jugador) const {
    const auto& mano = jugador.obtenerMano();
    for (const auto& [color, cantidad] : mano) {
        cout << colorearTexto(color, color) << ": " << cantidad << ", ";
    }
    // Mostrar comodines
    int comodinesNormales = jugador.obtenerComodinesNormales();
    int comodinesMulticolor = jugador.obtenerComodinesMulticolor();
    bool tieneComodinDorado = jugador.obtenerComodinDorado();
    
    if (comodinesNormales > 0) {
        cout << "Comodines: " << comodinesNormales << ", ";
    }
    if (comodinesMulticolor > 0) {
        cout << "Comodines Multicolor: " << comodinesMulticolor << ", ";
    }
    if (tieneComodinDorado) {
        cout << "Comodín Dorado: 1, ";
    }
}

bool Juego::juegoTerminado() const {
    return rondaFinalIniciada && all_of(jugadores.begin(), jugadores.end(), 
                    [](const Jugador& j) { return j.haTerminado(); });
}

void Juego::finalizarJuego() {
    cout << "\n¡El juego ha terminado!" << endl;
    mostrarEstadoJuego();
    calcularPuntajes();
}

void Juego::calcularPuntajes() const {
    cout << "\nPuntajes finales:" << endl;
    for (size_t i = 0; i < jugadores.size(); ++i) {
        cout << "Jugador " << i + 1 << ": " << jugadores[i].calcularPuntuacion() << " puntos" << endl;
    }
}

void Juego::reiniciarRonda() {
    for (auto& jugador : jugadores) {
        jugador.reiniciarRonda();
    }
    for (auto& pila : pilas) {
        pila.clear();
    }
    fill(pilasHabilitadas.begin(), pilasHabilitadas.end(), true);
}
