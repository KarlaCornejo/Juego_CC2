#include "ControladorJugador.h"

ControladorJugador::ControladorJugador(ModeloJugador& modelo, ModeloMapa& mapa, sf::Vector2i inicioJugador)
	: m_modelo(modelo), m_mapa(mapa), m_animacion(sf::Vector2i(1, Abajo))
{
	m_modelo.setPosicionX(inicioJugador.x);
	m_modelo.setPosicionY(inicioJugador.y);
}

void ControladorJugador::manejarEntradaJugador(sf::Sprite& m_spriteJugador)
{
	sf::Vector2f movimiento(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movimiento.y = -1.f;
		std::cout << "Subiendo: " << movimiento.y << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movimiento.y = 1.f;
		std::cout << "Abajo: " << movimiento.y << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movimiento.x = -1.f;
		std::cout << "Izquierda: " << movimiento.x << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movimiento.x = 1.f;
		std::cout << "Derecha: " << movimiento.x << std::endl;
	}

	// Calcula la nueva posición del jugador
	sf::Vector2i nuevaPosicion(m_modelo.getPosicionX() + static_cast<int>(movimiento.x),
		m_modelo.getPosicionY() + static_cast<int>(movimiento.y));

	// Verifica si la nueva posición colisiona con un bloque
	if (m_mapa.getNumeroCelda(nuevaPosicion.y, nuevaPosicion.x) == TIPOMURO)
	{
		// El jugador colisiona con un bloque, no se permite el movimiento
		std::cout << "Colisión con bloque" << std::endl;
		return;
	}

	// Actualiza la posición del jugador si no hay colisión con un bloque
	m_modelo.setPosicionX(nuevaPosicion.x);
	m_modelo.setPosicionY(nuevaPosicion.y);

	m_posicionEnfoque = m_mapa.obtenerPosicionPunto(m_modelo.getPosicionX(), m_modelo.getPosicionY());
}



sf::Vector2f ControladorJugador::getPosition()
{
	return sf::Vector2f(static_cast<float>(m_modelo.getPosicionX()), static_cast<float>(m_modelo.getPosicionY()));
}

void ControladorJugador::moverJugador(sf::Sprite& m_spriteJugador, sf::Time& deltaTiempo, sf::Texture& m_texturaJugador)
{
    sf::Vector2f movimiento(0.f, 0.f);
    float velocidad = m_modelo.getVelocidad(); // Obtener la velocidad del modelo

    sf::Vector2f posicionActual = m_spriteJugador.getPosition();
    sf::Vector2f posicionObjetivo = m_posicionEnfoque;

    // Calcular la dirección del movimiento en los ejes X e Y
    if (posicionObjetivo.x > posicionActual.x)
    {
        movimiento.x = velocidad;
        m_actualizarAnimacion = true;
        m_animacion.y = Derecha;
    }
    else if (posicionObjetivo.x < posicionActual.x)
    {
        movimiento.x = -velocidad;
        m_actualizarAnimacion = true;
        m_animacion.y = Izquierda;
    }
    else if (posicionObjetivo.y > posicionActual.y)
    {
        movimiento.y = velocidad;
        m_actualizarAnimacion = true;
        m_animacion.y = Abajo;
    }
    else if (posicionObjetivo.y < posicionActual.y)
    {
        movimiento.y = -velocidad;
        m_actualizarAnimacion = true;
        m_animacion.y = Arriba;
    }

    m_cuadroAnimacion++;
    std::cout << "Cuadro de Animacion: " << m_cuadroAnimacion << " Velocidad de Animacion: " << m_modelo.getVelocidad() << std::endl;

    if (m_actualizarAnimacion && m_cuadroAnimacion > m_modelo.getVelocidad())
    {
        m_animacion.x++;
        m_cuadroAnimacion = 0;
    }

    if (m_animacion.x * TAMANO_SPRITE_JUGADOR >= m_texturaJugador.getSize().x)
    {
        m_animacion.x = 0;
    }

    // Normalizar el vector de movimiento para mantener una velocidad constante en todas las direcciones
    sf::Vector2f movimientoNormalizado = movimiento;
    if (movimiento.x != 0.f || movimiento.y != 0.f)
    {
        float magnitud = std::sqrt(movimiento.x * movimiento.x + movimiento.y * movimiento.y);
        movimientoNormalizado.x /= magnitud;
        movimientoNormalizado.y /= magnitud;
    }

    sf::Vector2f desplazamiento = movimientoNormalizado * velocidad * deltaTiempo.asSeconds();
    sf::Vector2f nuevaPosicion = posicionActual + desplazamiento;

    // Verificar si el desplazamiento cruza una casilla completa antes de actualizar la posición
    if (movimiento.x > 0.f && nuevaPosicion.x > posicionObjetivo.x)
    {
        nuevaPosicion.x = posicionObjetivo.x;
    }
    else if (movimiento.x < 0.f && nuevaPosicion.x < posicionObjetivo.x)
    {
        nuevaPosicion.x = posicionObjetivo.x;
    }

    if (movimiento.y > 0.f && nuevaPosicion.y > posicionObjetivo.y)
    {
        nuevaPosicion.y = posicionObjetivo.y;
    }
    else if (movimiento.y < 0.f && nuevaPosicion.y < posicionObjetivo.y)
    {
        nuevaPosicion.y = posicionObjetivo.y;
    }

    m_spriteJugador.setPosition(nuevaPosicion);
    m_spriteJugador.setTextureRect(sf::IntRect(m_animacion.x * TAMANO_SPRITE_JUGADOR,
        m_animacion.y * TAMANO_SPRITE_JUGADOR,
        TAMANO_SPRITE_JUGADOR,
        TAMANO_SPRITE_JUGADOR));
}

void ControladorJugador::actualizarAnimacion(sf::Time& deltaTiempo, sf::Sprite& m_spriteJugador, int m_velocidadAnimacion, int m_cuadroAnimacion, sf::Texture& m_texturaJugador)
{
	ControladorJugador::moverJugador(m_spriteJugador,deltaTiempo, m_texturaJugador);
}

/*void JugadorControlador::colocarBomba(sf::Keyboard::Key key)
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
}*/

	/*for (int i = 0; i < m_modelo.getBombas().size(); i++)
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
	}*/
	// Actualizar la animación del jugador