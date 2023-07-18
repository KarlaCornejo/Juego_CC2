#include <SFML/Graphics.hpp>
#include "VentanaInicio.h"

int main()
{
    sf::RenderWindow ventana(sf::VideoMode(UI_WIDTH, UI_HEIGHT), "Bomberman", sf::Style::Close);

    VentanaInicio ventanaInicio(UI_WIDTH, UI_HEIGHT);
    ventanaInicio.ejecutar();

    return 0;
}