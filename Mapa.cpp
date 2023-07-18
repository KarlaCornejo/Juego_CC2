/*#include "Mapa.h"
#include <fstream>
#include <iostream>

bool Mapa::cargar(sf::Vector2f posicion, const std::string& texturaCelda, sf::Vector2u tamanoCelda, unsigned int ancho, unsigned int alto)
{
    m_ancho = ancho + 2;
    m_alto = alto + 2;
    cargarMapaDesdeArchivo("mapa.txt");
    int n = 0;

    if (!m_texturaCelda.loadFromFile(texturaCelda))
    {
        std::cout << "No se pudo cargar la textura: " << texturaCelda << std::endl;
        return false;
    }

    m_vertices.resize(m_ancho, std::vector<sf::VertexArray>(m_alto, sf::VertexArray(sf::Quads, 4)));
    m_celdas.resize(m_ancho, std::vector<Bloque*>(m_alto, nullptr));
    m_posicionMapa.resize(m_ancho, std::vector<sf::Vector2f>(m_alto, sf::Vector2f()));

    m_posicion = posicion;
    m_tamanoCelda = tamanoCelda;
    std::cout << "Ancho: " << m_ancho << " Alto: " << m_alto << std::endl;

    for (unsigned int i = 0; i < m_ancho; i++)
    {
        for (unsigned int j = 0; j < m_alto; j++)
        {
            int numeroCelda = m_generarMapa[i][j];
            std::cout << numeroCelda << " - ";

            m_celdas[i][j] = new Bloque(numeroCelda, sf::Vector2f(i * tamanoCelda.x + posicion.x, j * tamanoCelda.y + posicion.y), n);
            m_posicionMapa[i][j] = sf::Vector2f(i * tamanoCelda.x + posicion.x, j * tamanoCelda.y + posicion.y);

            int tu = numeroCelda % (m_texturaCelda.getSize().x / tamanoCelda.x);
            int tv = numeroCelda / (m_texturaCelda.getSize().x / tamanoCelda.x);

            sf::VertexArray& quad = m_vertices[i][j];

            quad[0].position = sf::Vector2f(j * tamanoCelda.x + posicion.x, i * tamanoCelda.y + posicion.y);
            quad[1].position = sf::Vector2f((j + 1) * tamanoCelda.x + posicion.x, i * tamanoCelda.y + posicion.y);
            quad[2].position = sf::Vector2f((j + 1) * tamanoCelda.x + posicion.x, (i + 1) * tamanoCelda.y + posicion.y);
            quad[3].position = sf::Vector2f(j * tamanoCelda.x + posicion.x, (i + 1) * tamanoCelda.y + posicion.y);

            quad[0].texCoords = sf::Vector2f(tu * tamanoCelda.x, tv * tamanoCelda.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tamanoCelda.x, tv * tamanoCelda.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tamanoCelda.x, (tv + 1) * tamanoCelda.y);
            quad[3].texCoords = sf::Vector2f(tu * tamanoCelda.x, (tv + 1) * tamanoCelda.y);


            n++;
        }std::cout << std::endl;
    }

    return true;
}

void Mapa::cargarMapaDesdeArchivo(const std::string& rutaArchivo)
{
    std::ifstream archivo(rutaArchivo);
    if (archivo.is_open())
    {
        srand(time(NULL));

        m_generarMapa.clear();
        for (int i = 0; i < m_ancho; i++)
        {
            std::vector<int> fila;
            for (int j = 0; j < m_alto; j++)
            {
                int valorCelda;
                archivo >> valorCelda;
                std::cout << valorCelda << std::endl;
                fila.push_back(valorCelda);
            }
            m_generarMapa.push_back(fila);
        }

        archivo.close();
    }
    else
    {
        std::cout << "No se pudo abrir el archivo: " << rutaArchivo << std::endl;
    }
}

sf::Vector2f Mapa::obtenerPosicionPunto(int fila, int columna)
{
    return m_posicionMapa[fila][columna];
}

int Mapa::getNumeroCelda(int fila, int columna)
{
    return m_generarMapa[fila][columna];
}

void Mapa::setNumeroCelda(int fila, int columna, int tipo)
{
    m_generarMapa[fila][columna] = tipo;
    m_celdas[fila][columna]->setTipo(tipo);
}

Bloque* Mapa::getCelda(int fila, int columna)
{
    return m_celdas[fila][columna];
}

void Mapa::setLibre(int fila, int columna, bool estaLibre)
{
    getCelda(fila, columna)->setLibre(estaLibre);
}

bool Mapa::estaLibre(int fila, int columna)
{
    return getCelda(fila, columna)->estaLibre();
}

sf::Vector2f Mapa::getFilasColumnas()
{
    return sf::Vector2f(m_ancho, m_alto);
}

void Mapa::actualizarMapa(int fila, int columna, int tipoBloque)
{
    setNumeroCelda(fila, columna, tipoBloque);

    int tu = tipoBloque % (m_texturaCelda.getSize().x / m_tamanoCelda.x);
    int tv = tipoBloque / (m_texturaCelda.getSize().x / m_tamanoCelda.x);

    sf::VertexArray& quad = m_vertices[fila][columna];
    quad[0].texCoords = sf::Vector2f(tu * m_tamanoCelda.x, tv * m_tamanoCelda.y);
    quad[1].texCoords = sf::Vector2f((tu + 1) * m_tamanoCelda.x, tv * m_tamanoCelda.y);
    quad[2].texCoords = sf::Vector2f((tu + 1) * m_tamanoCelda.x, (tv + 1) * m_tamanoCelda.y);
    quad[3].texCoords = sf::Vector2f(tu * m_tamanoCelda.x, (tv + 1) * m_tamanoCelda.y);
}

void Mapa::cambiar(int fila, int columna, int tipo, bool randomize)
{
    m_celdas[fila][columna]->romperBloque();
    if (m_generarMapa[fila][columna] != TIPOMURO && m_generarMapa[fila][columna] != TIPOSUELO && m_celdas[fila][columna]->getEsDestrutible())
    {
        if (randomize)
        {
            int random = rand() % 10;
            if (random < 4 || random > 6)
                random = TIPOSUELO;
            tipo = random;
        }
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

void Mapa::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_texturaCelda;
    for (unsigned int i = 0; i < m_ancho; ++i)
    {
        for (unsigned int j = 0; j < m_alto; ++j)
        {
            target.draw(m_vertices[i][j], states);
        }
    }
}*/