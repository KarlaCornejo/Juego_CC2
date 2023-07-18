#include "ModeloMapa.h"
#include <fstream>
#include <iostream>

int ModeloMapa::getAncho() { return this->m_ancho; }
int ModeloMapa::getAlto() { return this->m_alto; }
void ModeloMapa::setAncho(int ancho) { this->m_ancho = ancho; }
void ModeloMapa::setAlto(int alto) { this->m_alto = alto; }

void ModeloMapa::cambiarCelda(int fila, int columna, int tipo)
{
    m_celdas[fila][columna]->romperBloque();
    if (m_generarMapa[fila][columna] != TIPOMURO && m_generarMapa[fila][columna] != TIPOSUELO && m_celdas[fila][columna]->getEsDestrutible())
    {
        setNumeroCelda(fila, columna, tipo);
        int tu = tipo % (m_texturaCelda.getSize().x / m_tamanoCelda.x);
        int tv = tipo / (m_texturaCelda.getSize().x / m_tamanoCelda.x);
        sf::VertexArray& quad = m_vertices[fila][columna];
        quad[0].texCoords = sf::Vector2f(tu * m_tamanoCelda.x, tv * m_tamanoCelda.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * m_tamanoCelda.x, tv * m_tamanoCelda.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * m_tamanoCelda.x, (tv + 1) * m_tamanoCelda.y);
        quad[3].texCoords = sf::Vector2f(tu * m_tamanoCelda.x, (tv + 1) * m_tamanoCelda.y);
    }
}


sf::Texture ModeloMapa::obtenerTextura() { return m_texturaCelda; }

sf::VertexArray ModeloMapa::getVerticeArray(int fila, int columna) { return m_vertices[fila][columna];};

sf::Vector2f ModeloMapa::obtenerPosicionPunto(int fila, int columna)
{
    return m_posicionMapa[fila][columna];
}

int ModeloMapa::getNumeroCelda(int fila, int columna)
{
    return m_generarMapa[fila][columna];
}

void ModeloMapa::setNumeroCelda(int fila, int columna, int tipo)
{
    m_generarMapa[fila][columna] = tipo;
    m_celdas[fila][columna]->setTipo(tipo);
}

ModeloBloque* ModeloMapa::getCelda(int fila, int columna)
{
    return m_celdas[fila][columna];
}

void ModeloMapa::setLibre(int fila, int columna, bool estaLibre)
{
    getCelda(fila, columna)->setLibre(estaLibre);
}

bool ModeloMapa::estaLibre(int fila, int columna)
{
    return getCelda(fila, columna)->estaLibre();
}

sf::Vector2f ModeloMapa::getFilasColumnas()
{
    return sf::Vector2f(m_ancho, m_alto);
}