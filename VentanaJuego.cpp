#include "VentanaJuego.h"

void VentanaJuego::ejecutar() {
    sf::RenderWindow ventana(sf::VideoMode(UI_WIDTH, UI_HEIGHT), "Bomberman", sf::Style::Close);
    Juego juego;

    juego.reiniciarJuego(ventana, 1);
    juego.ejecutar(ventana);
}
