#include "Mapa.h"
#include <fstream>
#include <iostream>

bool Mapa::cargar(sf::Vector2f posicion, const std::string& texturaCelda, sf::Vector2u tamanoCelda, unsigned int ancho, unsigned int alto)
{
    if (m_recargar == true)
    {
        m_celdas.clear();
        m_generarMapa.clear();
        m_posicionMapa.clear();
    }
    m_ancho = ancho + 2;
    m_alto = alto + 2;
    Mapa::cargarMapaDesdeArchivo("mapa.txt");
    int n = 0;
    if (!m_texturaCelda.loadFromFile(texturaCelda))
        return false; m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize((m_ancho) * (m_alto) * 4);
    m_posicion = posicion;
    m_tamanoCelda = tamanoCelda;

    for (unsigned int i = 0; i < m_ancho; ++i)
    {
        for (unsigned int j = 0; j < m_alto; ++j)
        {
            int numeroCelda = m_generarMapa[i + (j * m_ancho)];
            std::cout << "i: " << i << "j: " << j << "  M: " << i + (j * m_ancho) << " : " << numeroCelda << std::endl;

            m_celdas.push_back(new Bloque(numeroCelda, sf::Vector2f(i * tamanoCelda.x + posicion.x,
                +j * tamanoCelda.y + posicion.y), n));
            m_posicionMapa.push_back(sf::Vector2f(i * tamanoCelda.x + posicion.x
                , j * tamanoCelda.y + posicion.y));

            int tu = numeroCelda % (m_texturaCelda.getSize().x / tamanoCelda.x);
            int tv = numeroCelda / (m_texturaCelda.getSize().x / tamanoCelda.x);

            sf::Vertex* quad = &m_vertices[(i + j * m_ancho) * 4];

            quad[0].position = sf::Vector2f(i * tamanoCelda.x + posicion.x, j * tamanoCelda.y + posicion.y);
            quad[1].position = sf::Vector2f((i + 1) * tamanoCelda.x + posicion.x, j * tamanoCelda.y + posicion.y);
            quad[2].position = sf::Vector2f((i + 1) * tamanoCelda.x + posicion.x, (j + 1) * tamanoCelda.y + posicion.y);
            quad[3].position = sf::Vector2f(i * tamanoCelda.x + posicion.x, (j + 1) * tamanoCelda.y + posicion.y);

            quad[0].texCoords = sf::Vector2f(tu * tamanoCelda.x, tv * tamanoCelda.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tamanoCelda.x, tv * tamanoCelda.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tamanoCelda.x, (tv + 1) * tamanoCelda.y);
            quad[3].texCoords = sf::Vector2f(tu * tamanoCelda.x, (tv + 1) * tamanoCelda.y);

            n++;
        }
    }
}
    void Mapa::draw(sf::RenderTarget & target, sf::RenderStates states) const    {
        states.transform *= getTransform();
        states.texture = &m_texturaCelda;
        target.draw(m_vertices, states);
    }

    void Mapa::cargarMapaDesdeArchivo(const std::string & rutaArchivo)
    {
        std::ifstream archivo(rutaArchivo); if (archivo.is_open())
        {
            srand(time(NULL));

            m_generarMapa.clear();
            for (int i = 0; i < m_alto; i++)
            {
                for (int j = 0; j < m_ancho; j++)
                {
                    int valorCelda;
                    archivo >> valorCelda;
                    std::cout << valorCelda << std::endl;
                    m_generarMapa.push_back(valorCelda);
                }
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
        return m_posicionMapa[fila * m_alto + columna];
    }

    int Mapa::getNumeroCelda(int fila, int columna)
    {
        return m_generarMapa[fila * m_ancho + columna];
    }

    sf::Vector2f Mapa::getFilasColumnas()
    {
        return sf::Vector2f(m_ancho, m_alto);
    }

    Bloque* Mapa::getCelda(int fila, int columna)
    {
        return m_celdas[fila * m_ancho + columna];
    }

    void Mapa::setNumeroCelda(int fila, int columna, int tipo)
    {
        m_generarMapa[fila * m_ancho + columna] = tipo;
        m_celdas[fila * m_ancho + columna]->setTipo(tipo);
    }

    void Mapa::setLibre(int fila, int columna, bool estaLibre)
    {
        getCelda(fila, columna)->setLibre(estaLibre);
    }

    bool Mapa::estaLibre(int fila, int columna)
    {
        return getCelda(fila, columna)->estaLibre();
    }
