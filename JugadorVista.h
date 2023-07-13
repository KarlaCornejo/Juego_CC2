#ifndef JUGADOR_VISTA_H_INCLUDED
#define JUGADOR_VISTA_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "JugadorModelo.h"
#include "JugadorControlador.h"

class JugadorVista
{
public:
    JugadorVista(const JugadorModelo& modelo, JugadorControlador& controlador);

    void dibujar(sf::RenderWindow& ventana);

private:
    const JugadorModelo& m_modelo;
    JugadorControlador& m_controlador;
    sf::Time deltaTime;
    sf::Texture m_texturaJugador;
    sf::Sprite m_spriteJugador;
   

    void actualizarSprite();
};

#endif // JUGADOR_VISTA_H_INCLUDED
