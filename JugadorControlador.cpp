#include "JugadorControlador.h"

JugadorControlador::JugadorControlador(JugadorModelo& modelo, Mapa& mapa)
    : m_modelo(modelo), m_mapa(mapa)
{
}

void JugadorControlador::manejarEntradaJugador()
{
    sf::Vector2f movimiento(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        movimiento.y = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        movimiento.y = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        movimiento.x = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        movimiento.x = 1;
    }

    if (movimiento.x != 0 || movimiento.y != 0)
    {
        // Realizar el movimiento del jugador en el mapa
    }
}

void JugadorControlador::colocarBomba(sf::Keyboard::Key key)
{
    bool canUseLower = false;
    if ((key == sf::Keyboard::Q))
    {
        std::cout << "USA LA LETRA Q" << std::endl;

        for (int i = 0; i < m_modelo.getBombas().size() && canUseLower == false; i++)
        {
            if (m_modelo.getBombas()[i].obtenerUsoBomba() == false)
            {
                canUseLower = true;
                m_modelo.getBombas()[i].crearBomba(m_mapa.obtenerPosicionPunto(m_modelo.getPosicionX(),m_modelo.getPosicionY()), sf::Vector2f(m_modelo.getPosicionX(), m_modelo.getPosicionY()), 2, m_mapa);

            }
        }
    }
}

sf::Vector2f JugadorControlador::getPosition() const
{
	return sf::Vector2f();
}


void JugadorControlador::moverJugador(sf::Time deltaTiempo, sf::Sprite m_spriteJugador, int m_velocidadAnimacion, int m_cuadroAnimacion, bool m_actualizarAnimacion, sf::Texture m_texturaJugador)
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
		movimiento.x = m_modelo.getVelocidad();
		m_actualizarAnimacion = true;
		m_animacion.y = Derecha;
	}
	if (m_posicionEnfoque.x < m_spriteJugador.getPosition().x)
	{
		movimiento.x = -(m_modelo.getVelocidad());
		m_actualizarAnimacion = true;
		m_animacion.y = Izquierda;
	}

	if (m_posicionEnfoque.y > m_spriteJugador.getPosition().y)
	{
		movimiento.y = m_modelo.getVelocidad();
		m_actualizarAnimacion = true;
		m_animacion.y = Abajo;
	}

	else if (m_posicionEnfoque.y < m_spriteJugador.getPosition().y)
	{
		movimiento.y = -(m_modelo.getVelocidad());
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

void JugadorControlador::actualizarAnimacion(sf::Time deltaTiempo, sf::Sprite m_spriteJugador, int m_velocidadAnimacion, int m_cuadroAnimacion, bool m_actualizarAnimacion, sf::Texture m_texturaJugador)
{
	JugadorControlador::moverJugador(deltaTiempo, m_spriteJugador, m_velocidadAnimacion, m_cuadroAnimacion, m_actualizarAnimacion, m_texturaJugador);
	for (int i = 0; i < m_modelo.getBombas().size(); i++)
	{

		for (int j = 0; j < m_modelo.getBombas().size(); j++)
		{
			if (j != i)
			{
				m_modelo.getBombas()[i].danarBomba(&m_modelo.getBombas()[j]);
			}
		}

		if (m_modelo.getVida() >= 0)
		{
			m_modelo.getBombas()[i].actualizar(m_mapa);
			if (m_modelo.getBombas()[i].dañarJugador(sf::Vector2f(round(m_spriteJugador.getPosition().x / TAMANO_CELDA), round(m_spriteJugador.getPosition().y / TAMANO_CELDA))) == true)
			{
				m_modelo.setVida(0);
				return;
			}
		}
	}
	// Actualizar la animación del jugador
}
