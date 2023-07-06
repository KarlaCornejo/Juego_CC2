#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include <iostream>
#include "Mapa.h"
#define RUTA_TEXTURA_CELDA "Media/Image/tile.png"
#include <memory>
#include <string>

#define UI_HEIGHT 496
#define UI_WIDTH 724

class Juego
{
public:
	Juego(); ///Constructor
	void ejecutar(sf::RenderWindow& ventana);
	void reiniciarJuego(sf::RenderWindow& ventana, int numJugadores);

private:
	void procesarEventos(sf::RenderWindow& ventana);
	//void actualizar(sf::Time deltaTiempo);
	void renderizar(sf::RenderWindow& ventana);
	bool m_EstaEnPausa = false;
private:
	sf::View m_VistaJuego; sf::Time TiempoPorFrame;
	sf::Clock reloj;
	sf::Clock c_MostrarFPS;
	sf::Time t_MostrarFPS;

	int m_CuadrosPorSegundo;
	sf::Texture m_TexturaFondo;
	sf::Sprite m_SpriteFondo;
	int m_CuadrosPorSegundoSeleccionado;
	bool m_JuegoTerminado;
	bool m_DetenerJuego = false;

	bool m_IrAlMenu = false;

	std::vector<bool> m_JugadoresVivos;
	std::vector<Jugador*> m_Jugadores;

	int m_NumJugadores;

	Jugador m_ListaJugadores;

	Mapa mapa;
};

#endif // JUEGO_H_INCLUDED