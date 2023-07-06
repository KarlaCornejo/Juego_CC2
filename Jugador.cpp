#include "Jugador.h"
#include <cmath>

Jugador::Jugador() {}

Jugador::Jugador(int id, std::string nombre, std::string rutaArchivo, int limiteFrames, sf::Vector2f posicionCelda, Mapa* generadorMapa)
	: m_id(0)
	, m_vida(2)
	, m_velocidadJugador(140)
	, m_nombreJugador("vacío")
	, m_rutaArchivo("./Media/Imagen/player.png")
	, m_animacion(1, Abajo)
{
	m_id = id;
	m_nombreJugador = nombre;
	puedeMoverse = true;
	m_obtenerPosicionEnfoque = true;
	m_listaVisitados.push_back(new sf::Vector2f(0, 0));
	if (!m_texturaJugador.loadFromFile(rutaArchivo))
		std::cout << "error" << std::endl;
	m_spriteJugador.setTexture(m_texturaJugador);
	m_velocidadAnimacion = limiteFrames / 4;
	m_posicionX = posicionCelda.x;
	m_movimientoAnterior = sf::Vector2f(0, 0);
	m_posicionY = posicionCelda.y;
	m_spriteJugador.setPosition(sf::Vector2f(m_posicionX * TAMANO_CELDA, m_posicionY * TAMANO_CELDA));
	m_posicionEnfoque = generadorMapa->obtenerPosicionPunto(ANCHO_MAPA / 2, ALTO_MAPA / 2);
	m_spriteJugador.setTextureRect(sf::IntRect
	(m_animacion.x * TAMANO_SPRITE_JUGADOR
		, m_animacion.y * TAMANO_SPRITE_JUGADOR
		, TAMANO_SPRITE_JUGADOR, TAMANO_SPRITE_JUGADOR));
}

void Jugador::setPosition(sf::Vector2f posicionCelda)
{
	m_spriteJugador.setPosition(sf::Vector2f(posicionCelda.x * TAMANO_CELDA, posicionCelda.y * TAMANO_CELDA));
}

void Jugador::dibujarJugador(sf::RenderWindow& ventana)
{
	if (m_vida != 0)
	{
		ventana.draw(m_spriteJugador);
	}
}

sf::Vector2f Jugador::getPosition()
{
	return sf::Vector2f(m_posicionX, m_posicionY);
}

void Jugador::manejarEntradaJugador(Mapa& generadorMapa)
{
	sf::Vector2f movimiento(0.f, 0.f);
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
	{

		movimiento.y = -1;
		std::cout << "Subiendo: " << movimiento.y << std::endl;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
	{

		movimiento.y = +1;
		std::cout << "Abajo: " << movimiento.y << " PosY: " << m_posicionY << std::endl;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{

		movimiento.x = -1;
		std::cout << "Izquierda: " << movimiento.x << " PosX: " << m_posicionX << std::endl;

	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		movimiento.x = +1;
		std::cout << "Derecha: " << movimiento.x << " PosX: " << m_posicionX << std::endl;
	}
	if ((generadorMapa.getNumeroCelda(m_posicionY + movimiento.y, m_posicionX + movimiento.x) == TIPOSUELO)
		&& (abs(m_spriteJugador.getPosition().x - generadorMapa.obtenerPosicionPunto(m_posicionX + movimiento.x, m_posicionY + movimiento.y).x)
			+ abs(m_spriteJugador.getPosition().y - generadorMapa.obtenerPosicionPunto(m_posicionX + movimiento.x, m_posicionY + movimiento.y).y) <= TAMANO_CELDA + 5))
	{
		m_posicionX += movimiento.x;
		m_posicionY += movimiento.y;
	}
	m_posicionEnfoque = generadorMapa.obtenerPosicionPunto(m_posicionX, m_posicionY);
}

std::string Jugador::getNombre()
{
	return m_nombreJugador;
}

void Jugador::moverJugador(sf::Time deltaTiempo)
{
	sf::Vector2f movimiento(0.f, 0.f); if (abs(m_posicionEnfoque.x - m_spriteJugador.getPosition().x) < 2)
	{
		m_spriteJugador.setPosition(m_posicionEnfoque.x, m_spriteJugador.getPosition().y);
		m_actualizarAnimacion = false;
	}
	if (abs(m_posicionEnfoque.y - m_spriteJugador.getPosition().y) < 2)
	{
		m_spriteJugador.setPosition(m_spriteJugador.getPosition().x, m_posicionEnfoque.y);
		m_actualizarAnimacion = false;
	}
	if (m_posicionEnfoque.x > m_spriteJugador.getPosition().x)
	{
		movimiento.x = m_velocidadJugador;
		m_actualizarAnimacion = true;
		m_animacion.y = Derecha;
	}
	if (m_posicionEnfoque.x < m_spriteJugador.getPosition().x)
	{
		movimiento.x = -m_velocidadJugador;
		m_actualizarAnimacion = true;
		m_animacion.y = Izquierda;
	}

	if (m_posicionEnfoque.y > m_spriteJugador.getPosition().y)
	{
		movimiento.y = m_velocidadJugador;
		m_actualizarAnimacion = true;
		m_animacion.y = Abajo;
	}

	else if (m_posicionEnfoque.y < m_spriteJugador.getPosition().y)
	{
		movimiento.y = -m_velocidadJugador;
		m_actualizarAnimacion = true;
		m_animacion.y = Arriba;
	}
	m_cuadroAnimacion++;
	if (m_actualizarAnimacion && m_cuadroAnimacion > m_velocidadAnimacion)
	{
		m_animacion.x++;
		m_cuadroAnimacion = 0;
	}

	if (m_animacion.x * TAMANO_SPRITE_JUGADOR >= m_texturaJugador.getSize().x)
	{
		m_animacion.x = 0;
	}

	m_spriteJugador.setTextureRect(sf::IntRect
	(m_animacion.x * TAMANO_SPRITE_JUGADOR
		, m_animacion.y * TAMANO_SPRITE_JUGADOR
		, TAMANO_SPRITE_JUGADOR
		, TAMANO_SPRITE_JUGADOR
	));
	m_spriteJugador.move(movimiento.x * deltaTiempo.asSeconds()
		, movimiento.y * deltaTiempo.asSeconds());
}

void Jugador::actualizarJugador(sf::Time deltaTiempo)
{
	Jugador::moverJugador(deltaTiempo);
}

int Jugador::getVida()
{
	return m_vida;
}
Jugador::~Jugador()
{

}