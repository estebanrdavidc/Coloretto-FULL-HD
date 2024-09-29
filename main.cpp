#include "juego.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Bienvenido a Coloretto!" << endl;
    cout << "Ingrese el número de jugadores (3-5): ";
    int numJugadores;
    cin >> numJugadores;

    while (numJugadores < 3 || numJugadores > 5) {
        cout << "Número de jugadores inválido. Por favor, ingrese un número entre 3 y 5: ";
        cin >> numJugadores;
    }

    Juego juego(numJugadores);

    while (!juego.juegoTerminado()) {
        juego.mostrarEstadoJuego();
        juego.jugarTurno();
    }

    cout << "¡El juego ha terminado!" << endl;
    juego.calcularPuntajes();

    return 0;
}