#include "Juego.h"
#include <functional>
#include <string>
#include <iostream>
#include <sstream>

std::string toString(int num)
{
	std::stringstream ss;
	std::string resultado;
	ss << num;
	ss >> resultado;
	return resultado;
}

Juego::Juego()
{
	TiempoPorFrame = sf::seconds(1.f / 60.f);
	t_MostrarFPS = sf::seconds(1);
	m_JuegoTerminado = false;
	if (!mapa.cargar(sf::Vector2f(0, 0), RUTA_TEXTURA_CELDA, sf::Vector2u(TAMANO_CELDA, TAMANO_CELDA), ANCHO_MAPA, ALTO_MAPA))
		std::cout << "error";
	m_CuadrosPorSegundo = 0;
	if (!m_TexturaFondo.loadFromFile("Media/Imagen/fondo.png"))
		std::cout << "error al cargar " << "Media/Imagen/fondo.png" << std::endl;
	m_SpriteFondo.setTexture(m_TexturaFondo);
	m_SpriteFondo.setPosition(-180, -60);
	if (!mapa.cargar(sf::Vector2f(0, 0), RUTA_TEXTURA_CELDA, sf::Vector2u(TAMANO_CELDA, TAMANO_CELDA), ANCHO_MAPA, ALTO_MAPA))
		std::cout << "error";
}

void Juego::reiniciarJuego(sf::RenderWindow& ventana, int numJugadores)
{
	m_JuegoTerminado = false;
	m_IrAlMenu = false;
	m_Jugadores.clear();
	m_JugadoresVivos.clear();
	m_JugadoresVivos.push_back(true);
	m_Jugadores.push_back(new Jugador(0, "Azul", "./Media/Imagen/jugador.png", m_CuadrosPorSegundoSeleccionado, sf::Vector2f(1, 1), &mapa));
	if (!mapa.cargar(sf::Vector2f(0, 0), RUTA_TEXTURA_CELDA, sf::Vector2u(TAMANO_CELDA, TAMANO_CELDA), ANCHO_MAPA, ALTO_MAPA))
		std::cout << "error";
}

void Juego::ejecutar(sf::RenderWindow& ventana)
{
	sf::Clock reloj;
	sf::Time tiempoDesdeUltimaActualizacion = sf::Time::Zero;
	ventana.setView(sf::View(sf::Vector2f((mapa.getFilasColumnas().x * 32) / 2, (mapa.getFilasColumnas().y * 32) / 2), sf::Vector2f(mapa.getFilasColumnas().x * 32, mapa.getFilasColumnas().y * 32)));
	while (ventana.isOpen() && m_JuegoTerminado == false)
	{
		if (m_EstaEnPausa == false)
		{
			procesarEventos(ventana);        tiempoDesdeUltimaActualizacion += reloj.restart();

			while (tiempoDesdeUltimaActualizacion > TiempoPorFrame)
			{
				tiempoDesdeUltimaActualizacion -= TiempoPorFrame;
				procesarEventos(ventana);
				m_Jugadores[0]->manejarEntradaJugador(mapa);
				m_Jugadores[0]->actualizarJugador(TiempoPorFrame);
			}
		}

		renderizar(ventana);
	}
	ventana.setView(sf::View(sf::Vector2f(UI_WIDTH / 2, UI_HEIGHT / 2), sf::Vector2f(UI_WIDTH, UI_HEIGHT)));
}

void Juego::procesarEventos(sf::RenderWindow& ventana)
{
	sf::Event evento;
	while (ventana.pollEvent(evento))
	{
		switch (evento.type)
		{
		case sf::Event::Closed:
			ventana.close();
			break;
		case sf::Event::KeyPressed:
			ventana.setKeyRepeatEnabled(false);
			if (evento.key.code == sf::Keyboard::Escape)
			{
				m_EstaEnPausa = true;
			}
			break;
		}
	}
}

void Juego::renderizar(sf::RenderWindow& ventana)
{
	ventana.clear();
	ventana.draw(mapa);
	m_Jugadores[0]->dibujarJugador(ventana);
	ventana.display();
}




