#ifndef CONTROLADOR_MAPA_H_INCLUDED
#define CONTROLADOR_MAPA_H_INCLUDED

#include "ModeloMapa.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
class ControladorMapa
{
public:
    ControladorMapa(ModeloMapa& modelo);

    void actualizar();
    bool cargar(sf::Vector2f posicion, const std::string& texturaCelda, sf::Vector2u tamanoCelda, unsigned int ancho, unsigned int alto);
    void cargarMapaDesdeArchivo(const std::string& rutaArchivo);
    

private:
    ModeloMapa& m_modelo;
};

#endif // CONTROLADOR_MAPA_H_INCLUDED
