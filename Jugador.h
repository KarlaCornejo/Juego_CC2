#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <memory>
#include <cmath>
#include "Mapa.h"

#define VIDA_INICIAL 2
#define VELOCIDAD_INICIAL 140
#define TAMANO_SPRITE_JUGADOR 32

enum Direccion { Abajo, Derecha, Arriba, Izquierda };

class Jugador
{
public:
	Jugador();
	Jugador(int id, std::string nombre, std::string rutaArchivo, int limiteFrames, sf::Vector2f posicionCelda, Mapa* generadorMapa);
	void setPosition(sf::Vector2f posicionCelda);
	sf::Vector2f getPosition();
	void dibujarJugador(sf::RenderWindow& ventana);
	void manejarEntradaJugador(Mapa& generadorMapa);
	void moverJugador(sf::Time deltaTiempo);
	void actualizarJugador(sf::Time deltaTiempo);
	int getVida();
	std::string getNombre();
	~Jugador();

private:
	sf::Texture m_texturaJugador;
	sf::Sprite m_spriteJugador; 
	int m_posicionX, m_posicionY;
	int m_id;
	int m_vida;
	float m_velocidadJugador;
	bool m_actualizarAnimacion = true;
	bool m_comienzo = true;
	sf::Vector2f m_posicionEnfoque;
	std::string m_nombreJugador;
	std::string m_rutaArchivo;
	sf::Vector2i m_animacion;
	int m_velocidadAnimacion;
	int m_cuadroAnimacion;
	sf::Vector2f m_movimientoAnterior;
	std::vector<sf::Vector2f*> m_listaVisitados;

	bool puedeMoverse;
	bool m_obtenerPosicionEnfoque;
};

#endif // JUGADOR_H_INCLUDED