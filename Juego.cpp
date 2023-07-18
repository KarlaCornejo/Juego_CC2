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
	m_JuegoTerminado = false;

	std::unique_ptr<ModeloMapa> modeloMapa = std::make_unique<ModeloMapa>();
	ControladorMapa controladorMapa(*modeloMapa);
	controladorMapa.cargar(sf::Vector2f(0, 0), RUTA_TEXTURA_CELDA, sf::Vector2u(TAMANO_CELDA, TAMANO_CELDA), ANCHO_MAPA, ALTO_MAPA);
	mapaVista.cargarMapa(std::move(modeloMapa));

	if (!m_TexturaFondo.loadFromFile("Media/Image/fondo.png"))
		std::cout << "Error al cargar la textura del fondo" << std::endl;
	m_SpriteFondo.setTexture(m_TexturaFondo);
	m_SpriteFondo.setPosition(-180, -60);
}

void Juego::reiniciarJuego(sf::RenderWindow& ventana, int numJugadores)
{
	std::cout << "Te quiero" << std::endl;

	std::unique_ptr<ModeloMapa> modeloMapa = std::make_unique<ModeloMapa>();
	ControladorMapa controladorMapa(*modeloMapa);
	controladorMapa.cargar(sf::Vector2f(0, 0), RUTA_TEXTURA_CELDA, sf::Vector2u(TAMANO_CELDA, TAMANO_CELDA), ANCHO_MAPA, ALTO_MAPA);
	mapaVista.cargarMapa(std::move(modeloMapa));

	m_JuegoTerminado = false;
	m_IrAlMenu = false;
	//m_Jugadores.clear();
	m_Jugadores_m.clear();
	ModeloJugador* modelo = new ModeloJugador();
	ControladorJugador* controlador = new ControladorJugador(*modelo, *mapaVista.getModeloMapa(), sf::Vector2i(1, Derecha));
	std::string ruta = "./Media/Image/player.png";
	VistaJugador* jugador = new VistaJugador(*modelo, *controlador, ruta,TiempoPorFrame);
	m_Jugadores_m.push_back(jugador);

} 

void Juego::ejecutar(sf::RenderWindow& ventana)
{
	std::cout << "Te quiero mucho" << std::endl;
	sf::Clock reloj;
	sf::Time tiempoDesdeUltimaActualizacion = sf::Time::Zero;
	//std::cout <<"X: " << mapa.getFilasColumnas().x << std::endl;
	//std::cout <<"Y: "<< mapa.getFilasColumnas().y << std::endl;
	system("pause");
	ventana.setView(sf::View(sf::Vector2f((21 * 32) / 2, (21 * 32) / 2), sf::Vector2f(21 * 32, 21 * 32)));

	while (ventana.isOpen() && !m_JuegoTerminado)
	{
		procesarEventos(ventana);

		tiempoDesdeUltimaActualizacion += reloj.restart();

		while (tiempoDesdeUltimaActualizacion >= TiempoPorFrame)
		{
			tiempoDesdeUltimaActualizacion -= TiempoPorFrame;

			for (auto& jugador : m_Jugadores_m)
			{
				jugador->manejarJugador();
				jugador->actualizarSprite(TiempoPorFrame);
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
	ventana.draw(m_SpriteFondo);
	ventana.draw(mapaVista);
	m_Jugadores_m[0]->dibujar(ventana);
	ventana.display();
}



