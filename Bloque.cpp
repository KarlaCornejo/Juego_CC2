#include "Bloque.h"

Bloque::Bloque(int tipo, sf::Vector2f posicion, int numeroEnMapa)
{
	m_tipo = tipo;
	m_estaLibre = true;
    switch (m_tipo)
    {
    case TIPOMURO:
        m_esColisionable = true;
        m_posicion = posicion;
        break;
    case TIPOSUELO:
        m_esColisionable = false;
        m_posicion = posicion;
        break;
    case TYPE_BRICS:
        m_esColisionable = true;
        m_posicion = posicion;
        break;
    case TYPE_WOOD:
        m_esColisionable = true;
        m_posicion = posicion;
        break;
    }

    m_hitBox.setPosition(m_posicion);
    m_hitBox.setSize(sf::Vector2f(TAMANO_CELDA, TAMANO_CELDA));
    m_hitBox.setFillColor(sf::Color::Transparent);
    m_numeroEnMapa = numeroEnMapa;
}

bool Bloque::esSolido()
{
    return m_esColisionable;
}

sf::Vector2f Bloque::obtenerPosicion()
{
    return m_posicion;
}

sf::RectangleShape Bloque::obtenerHitBox()
{
    return m_hitBox;
}

bool Bloque::estaLibre()
{
    return m_estaLibre;
}

void Bloque::setTipo(int tipo)
{
    m_tipo = tipo;
}

void Bloque::setLibre(bool estaLibre)
{
    m_estaLibre = estaLibre;
}