#include "ModeloBloque.h"
#ifndef BLOQUE_H_INCLUDED
#define BLOQUE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

#define TAMANO_CELDA 32
#define TIPOMURO 0
#define TIPOSUELO 1
#define TIPOLADRILLO 2
#define TIPOMADERA 3
#define BONUS_AGREGAR_BOMBA 4
#define BONUS_AUMENTAR_EXPLOSIÓN 5
#define BONUS_AUMENTAR_VELOCIDAD 6
#define TIPO_BOMBA 7

class ModeloBloque
{
public:
    ModeloBloque(int tipo, sf::Vector2f posicion, int numeroEnMapa); /// Constructor
    bool esSolido();
    sf::Vector2f obtenerPosicion();
    bool estaLibre();
    void setTipo(int tipo);
    void setLibre(bool estaLibre);
    bool getEsDestrutible();
    bool estaDestruidoElBloque();
    void romperBloque();
    sf::RectangleShape obtenerHitBox();

    /*** Funciones adicionales ***/
    int getTipo();
    int getVida();
    bool esColisionable();
    bool estaDestructible();

private:
    int m_tipo;
    int m_vida;
    bool m_esColisionable;
    bool m_estaDestructible;
    int m_numeroEnMapa;
    bool m_estaLibre;
    sf::RectangleShape m_hitBox;
    sf::Vector2f m_posicion;
};



#endif // BLOQUE_H_INCLUDED
ModeloBloque::ModeloBloque(int tipo, sf::Vector2f posicion, int numeroEnMapa)
    : m_tipo(tipo), m_vida(1), m_numeroEnMapa(numeroEnMapa), m_estaLibre(true)
{
    m_posicion = posicion;
    m_hitBox.setSize(sf::Vector2f(TAMANO_CELDA, TAMANO_CELDA));
    m_hitBox.setPosition(m_posicion);
    m_hitBox.setFillColor(sf::Color::Transparent);

    switch (tipo)
    {
    case TIPOMURO:
        m_esColisionable = true;
        m_estaDestructible = false;
        break;
    case TIPOSUELO:
        m_esColisionable = false;
        m_estaDestructible = false;
        break;
    case TIPOLADRILLO:
        m_esColisionable = true;
        m_estaDestructible = true;
        break;
    case TIPOMADERA:
        m_esColisionable = true;
        m_estaDestructible = true;
        break;
    default:
        m_esColisionable = false;
        m_estaDestructible = false;
        break;
    }
}

bool ModeloBloque::esSolido()
{
    return m_esColisionable;
}

sf::Vector2f ModeloBloque::obtenerPosicion()
{
    return m_posicion;
}

bool ModeloBloque::estaLibre()
{
    return m_estaLibre;
}

void ModeloBloque::setTipo(int tipo)
{
    m_tipo = tipo;
}

void ModeloBloque::setLibre(bool estaLibre)
{
    m_estaLibre = estaLibre;
}

bool ModeloBloque::getEsDestrutible()
{
    return m_estaDestructible;
}

bool ModeloBloque::estaDestruidoElBloque()
{
    return m_vida <= 0;
}

void ModeloBloque::romperBloque()
{
    m_vida--;
}

sf::RectangleShape ModeloBloque::obtenerHitBox()
{
    return m_hitBox;
}

int ModeloBloque::getTipo()
{
    return m_tipo;
}

int ModeloBloque::getVida()
{
    return m_vida;
}

bool ModeloBloque::esColisionable()
{
    return m_esColisionable;
}

bool ModeloBloque::estaDestructible()
{
    return m_estaDestructible;
}
