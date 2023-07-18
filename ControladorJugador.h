#ifndef JUGADOR_CONTROLADOR_H_INCLUDED
#define JUGADOR_CONTROLADOR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "ModeloJugador.h"
#include "ModeloMapa.h"
#include <iostream>
class ControladorJugador
{
public:
    ControladorJugador(ModeloJugador& modelo, ModeloMapa& mapa, sf::Vector2i);

    void manejarEntradaJugador(sf::Sprite&);
    //void colocarBomba(sf::Keyboard::Key key);
    //void actualizar(sf::Time deltaTiempo);
    sf::Vector2f getPosition();
    void moverJugador(sf::Sprite& m_spriteJugador, sf::Time& deltaTiempo, sf::Texture& m_texturaJugador);

    void actualizarAnimacion
    (sf::Time& deltaTiempo, sf::Sprite& spriteJugador, int m_velocidadAnimacion, int m_cuadroAnimacion, sf::Texture& m_texturaJugador);
    sf::Vector2i m_animacion;
    bool m_movimientoRealizado = true;
private:
    ModeloJugador& m_modelo;
    sf::Vector2f m_posicionEnfoque = sf::Vector2f(2,2);
    int m_cuadroAnimacion = 0;
    bool m_actualizarAnimacion = true;
    ModeloMapa& m_mapa;
};

#endif // JUGADOR_CONTROLADOR_H_INCLUDED
