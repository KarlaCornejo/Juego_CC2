#ifndef JUGADOR_CONTROLADOR_H_INCLUDED
#define JUGADOR_CONTROLADOR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "JugadorModelo.h"
#include "Mapa.h"

class JugadorControlador
{
public:
    JugadorControlador(JugadorModelo& modelo, Mapa& mapa);

    void manejarEntradaJugador();
    void colocarBomba(sf::Keyboard::Key key);
    void actualizar(sf::Time deltaTiempo);
    sf::Vector2f getPosicion() const;

private:
    JugadorModelo& m_modelo;
    Mapa& m_mapa;
    sf::Vector2f m_posicionEnfoque;
    sf::Vector2i m_animacion;

    void moverJugador(sf::Time deltaTiempo, sf::Sprite spriteJugador, int m_velocidadAnimacion, int m_cuadroAnimacion, bool m_actualizarAnimacion, sf::Texture m_texturaJugador);

    void actualizarAnimacion(sf::Time deltaTiempo, sf::Sprite spriteJugador, int m_velocidadAnimacion, int m_cuadroAnimacion, bool m_actualizarAnimacion, sf::Texture m_texturaJugador);

};

#endif // JUGADOR_CONTROLADOR_H_INCLUDED
