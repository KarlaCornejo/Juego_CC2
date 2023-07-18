#ifndef JUGADOR_VISTA_H_INCLUDED
#define JUGADOR_VISTA_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "ModeloJugador.h"
#include "ControladorJugador.h"

class VistaJugador
{
public:
    VistaJugador(ModeloJugador& modelo, ControladorJugador& controlador, std::string& rutaArchivo, sf::Time& deltasTime);
    void actualizarSprite(sf::Time&);
    void dibujar(sf::RenderWindow& ventana);
    void manejarJugador();

private:

    ModeloJugador& m_modelo;
    ControladorJugador& m_controlador;
    sf::Time deltaTime;
    int m_velocidadAnimacion = 0 / 4;
    sf::Texture m_texturaJugador;
    sf::Sprite m_spriteJugador;
    std::string m_rutaArchivo;
    int m_cuadroAnimacion = 0;
   // int m_posicionX = 1, m_posicionY=1;

};

#endif // JUGADOR_VISTA_H_INCLUDED
