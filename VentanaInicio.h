#pragma once
#ifndef _VENTANAINICIO_H_
#define _VENTANAINICIO_H_
#include <SFML/Graphics.hpp>
#include "VentanaJuego.h"

class VentanaInicio {
public:
    VentanaInicio(int l, int a);

    void mostrarPantallaInicio(sf::RenderWindow& ventana, bool resaltarJuego, bool resaltarConfiguracion);
    void ejecutar();
private:
    int lar;
    int anc;

};
#endif