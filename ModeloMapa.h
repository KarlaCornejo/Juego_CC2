#ifndef MODELO_MAPA_H_INCLUDED
#define MODELO_MAPA_H_INCLUDED
#include "Bloque.h"
#include <SFML/Graphics.hpp>
#include <vector>
#define ALTO_MAPA 19
#define ANCHO_MAPA 19
class ModeloMapa
{
public:
    sf::Vector2f obtenerPosicionPunto(int fila, int columna);
    int getNumeroCelda(int fila, int columna);
    void setNumeroCelda(int fila, int columna, int tipo);
    ModeloBloque* getCelda(int fila, int columna);
    void setLibre(int fila, int columna, bool estaLibre);
    bool estaLibre(int fila, int columna);
    sf::Vector2f getFilasColumnas();
    int getAncho();
    int getAlto();
    void setAncho(int);
    void setAlto(int);
    void cambiarCelda(int fila, int columna, int tipo);
    sf::Texture obtenerTextura();
    sf::VertexArray getVerticeArray(int fila, int columna);
   

    std::vector<std::vector<sf::VertexArray>> m_vertices;
    sf::Texture m_texturaCelda;
    sf::Vector2u m_tamanoCelda;
    std::vector<std::vector<ModeloBloque*>> m_celdas;
    std::vector<std::vector<int>> m_generarMapa;
    std::vector<std::vector<sf::Vector2f>> m_posicionMapa;
    sf::Vector2f m_posicion;
private:    
    bool m_recargar = false;
    int m_ancho;
    int m_alto;
};

#endif // MODELO_MAPA_H_INCLUDED
