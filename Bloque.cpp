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
        m_vida = 1;
        m_estaDestructible = false;
        break;
    case TIPOSUELO:
        m_esColisionable = false;
        m_posicion = posicion;
        m_vida = 1;
        m_estaDestructible = false;
        break;
    case TIPOLADRILLO:
        m_esColisionable = true;
        m_posicion = posicion;
        m_vida = 2;
        m_estaDestructible = true;
        break;
    case TIPOMADERA:
        m_esColisionable = true;
        m_posicion = posicion;
        m_vida = 1;
        m_estaDestructible = true;
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

/*bool Bloque::esSolido()
{
    return m_esColisionable;
}

sf::Vector2f Bloque::obtenerPosicion()
{
    return this->m_posicion;
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
}*/

bool Bloque::getEsDestrutible()
{
    return m_estaDestructible;
}

bool Bloque::estaDestruidoElBloque()
{
    return m_vida <= 0;
}

void Bloque::romperBloque()
{
    m_vida--;
}
/*
sf::RectangleShape Bloque::obtenerHitBox()
{
    return m_hitBox;
}*/

int Bloque::getTipo()
{
    return m_tipo;
}

int Bloque::getVida()
{
    return m_vida;
}

bool Bloque::esColisionable()
{
    return m_esColisionable;
}

bool Bloque::estaDestructible()
{
    return m_estaDestructible;
}
