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
   
void Mapa::actualizarMapa(int fila, int columna, int tileNumber)
{


    Mapa::setNumeroCelda(fila, columna, tileNumber);
    int tu = tileNumber % (m_texturaCelda.getSize().x / m_tamanoCelda.x);
    int tv = tileNumber / (m_texturaCelda.getSize().x / m_tamanoCelda.x);

    sf::Vertex* quad = &m_vertices[(columna + fila * m_ancho) * 4];
    // on définit ses quatre coins
    quad[0].position = sf::Vector2f(columna * m_tamanoCelda.x + m_posicion.x, fila * m_tamanoCelda.y + m_posicion.y);
    quad[1].position = sf::Vector2f((columna + 1) * m_tamanoCelda.x + m_posicion.x, fila * m_tamanoCelda.y + m_posicion.y);
    quad[2].position = sf::Vector2f((columna + 1) * m_tamanoCelda.x + m_posicion.x, (fila + 1) * m_tamanoCelda.y + m_posicion.y);
    quad[3].position = sf::Vector2f(columna * m_tamanoCelda.x + m_posicion.x, (fila + 1) * m_tamanoCelda.y + m_posicion.y);

    // on définit ses quatre coordonnées de texture
    // on définit ses quatre coordonnées de texture
    quad[0].texCoords = sf::Vector2f(tu * m_tamanoCelda.x, tv * m_tamanoCelda.y);
    quad[1].texCoords = sf::Vector2f((tu + 1) * m_tamanoCelda.x, tv * m_tamanoCelda.y);
    quad[2].texCoords = sf::Vector2f((tu + 1) * m_tamanoCelda.x, (tv + 1) * m_tamanoCelda.y);
    quad[3].texCoords = sf::Vector2f(tu * m_tamanoCelda.x, (tv + 1) * m_tamanoCelda.y);
}


void Mapa::cambiar(int line, int column, int type, bool randomize)
{
    m_celdas[column * m_alto + line]->romperBloque();
    if (m_generarMapa[line * m_ancho + column] != TIPOMURO
        && m_generarMapa[line * m_ancho + column] != TIPOSUELO
        && m_celdas[column * m_alto + line]->getEsDestrutible())
    {

        //if(m_tile[line*m_widht+column].DestructTile()==true)
        //{
        if (randomize)
        {
            int random = rand() % 10;
            if (random < 4 || random>6)
                random = TIPOSUELO;
            type = random;//random;
        }
        m_generarMapa[line * m_ancho + column] = type;
        int tu = type % (m_texturaCelda.getSize().x / TAMANO_CELDA);
        int tv = type / (m_texturaCelda.getSize().x / TAMANO_CELDA);
        sf::Vertex* quad = &m_vertices[(line * m_ancho + column) * 4];
        quad[0].position = sf::Vector2f(column * TAMANO_CELDA, line * TAMANO_CELDA);
        quad[1].position = sf::Vector2f((column + 1) * TAMANO_CELDA, line * TAMANO_CELDA);
        quad[2].position = sf::Vector2f((column + 1) * TAMANO_CELDA, (line + 1) * TAMANO_CELDA);
        quad[3].position = sf::Vector2f(column * TAMANO_CELDA, (line + 1) * TAMANO_CELDA);
        quad[0].texCoords = sf::Vector2f(tu * TAMANO_CELDA, tv * TAMANO_CELDA);
        quad[1].texCoords = sf::Vector2f((tu + 1) * TAMANO_CELDA, tv * TAMANO_CELDA);
        quad[2].texCoords = sf::Vector2f((tu + 1) * TAMANO_CELDA, (tv + 1) * TAMANO_CELDA);
        quad[3].texCoords = sf::Vector2f(tu * TAMANO_CELDA, (tv + 1) * TAMANO_CELDA);
        //}
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
