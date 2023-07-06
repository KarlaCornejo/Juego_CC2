#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "Bloque.h"
#include <vector>
#include <time.h>
#include <iostream>

#define ALTO_MAPA 15
#define ANCHO_MAPA 19

class Mapa : public sf::Drawable, public sf::Transformable
{
public:
	bool cargar(sf::Vector2f posicion, const std::string& texturaCelda, sf::Vector2u tamanoCelda, unsigned int ancho, unsigned int alto);
	void cargarMapaDesdeArchivo(const std::string& rutaArchivo);

	sf::Vector2f obtenerPosicionPunto(int fila, int columna);
	int getNumeroCelda(int fila, int columna);
	void setNumeroCelda(int fila, int columna, int tipo);
	Bloque* getCelda(int fila, int columna);
	void setLibre(int fila, int columna, bool estaLibre);
	bool estaLibre(int fila, int columna);
	sf::Vector2f getFilasColumnas();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_texturaCelda;
	sf::Vector2u m_tamanoCelda;
	std::vector<Bloque*> m_celdas;
	std::vector<int> m_generarMapa;
	std::vector<sf::Vector2f> m_posicionMapa;
	sf::Vector2f m_posicion;
	bool m_recargar = false;
	int m_ancho;
	int m_alto;
};

#endif // MAPA_H_INCLUDED