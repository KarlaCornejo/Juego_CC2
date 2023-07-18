#include "ControladorMapa.h"

ControladorMapa::ControladorMapa(ModeloMapa& modelo)
    : m_modelo(modelo)
{}


void ControladorMapa::actualizar()
{
    // No se necesita lógica de actualización en este caso
}



bool ControladorMapa::cargar(sf::Vector2f posicion, const std::string& texturaCelda, sf::Vector2u tamanoCelda, unsigned int ancho, unsigned int alto) {
    int m_ancho = ancho + 2;
    int m_alto = alto + 2;
    m_modelo.setAlto(m_alto);
    m_modelo.setAncho(m_ancho);
    cargarMapaDesdeArchivo("mapa.txt");
    int n = 0;

    if (!(m_modelo.m_texturaCelda.loadFromFile(texturaCelda)))
    {
        std::cout << "No se pudo cargar la textura: " << texturaCelda << std::endl;
        return false;
    }

    m_modelo.m_vertices.resize(m_ancho, std::vector<sf::VertexArray>(m_alto, sf::VertexArray(sf::Quads, 4)));
    m_modelo.m_celdas.resize(m_ancho, std::vector<ModeloBloque*>(m_alto, nullptr));
    m_modelo.m_posicionMapa.resize(m_ancho, std::vector<sf::Vector2f>(m_alto, sf::Vector2f()));

    m_modelo.m_posicion = posicion;
    m_modelo.m_tamanoCelda = tamanoCelda;
    std::cout << "Ancho: " << m_ancho << " Alto: " << m_alto << std::endl;

    for (unsigned int i = 0; i < m_ancho; i++)
    {
        for (unsigned int j = 0; j < m_alto; j++)
        {
            int numeroCelda = m_modelo.m_generarMapa[i][j];
            std::cout << numeroCelda << " - ";

            m_modelo.m_celdas[i][j] = new ModeloBloque(numeroCelda, sf::Vector2f(i * tamanoCelda.x + posicion.x, j * tamanoCelda.y + posicion.y), n);
            m_modelo.m_posicionMapa[i][j] = sf::Vector2f(i * tamanoCelda.x + posicion.x, j * tamanoCelda.y + posicion.y);

            int tu = numeroCelda % (m_modelo.m_texturaCelda.getSize().x / tamanoCelda.x);
            int tv = numeroCelda / (m_modelo.m_texturaCelda.getSize().x / tamanoCelda.x);

            sf::VertexArray& quad = m_modelo.m_vertices[i][j];

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
void ControladorMapa::cargarMapaDesdeArchivo(const std::string& rutaArchivo)
{

    std::ifstream archivo(rutaArchivo);
    if (archivo.is_open())
    {
        srand(time(NULL));

        m_modelo.m_generarMapa.clear();
        for (int i = 0; i < m_modelo.getAncho(); i++)
        {
            std::vector<int> fila;
            for (int j = 0; j < m_modelo.getAlto(); j++)
            {
                int valorCelda;
                archivo >> valorCelda;
                std::cout << valorCelda << std::endl;
                fila.push_back(valorCelda);
            }
            m_modelo.m_generarMapa.push_back(fila);
        }
        archivo.close();
    }
    else
    {
        std::cout << "No se pudo abrir el archivo: " << rutaArchivo << std::endl;
    }
}