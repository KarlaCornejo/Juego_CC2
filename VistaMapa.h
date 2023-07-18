#ifndef VISTA_MAPA_H_INCLUDED
#define VISTA_MAPA_H_INCLUDED

#include "ModeloMapa.h"
#include <SFML/Graphics.hpp>

class VistaMapa : public sf::Drawable, public sf::Transformable
{
public:
    VistaMapa();
    VistaMapa(std::unique_ptr<ModeloMapa> modeloMapa);
    sf::Vector2f getFilasColumnas();
    void cargarMapa(std::unique_ptr<ModeloMapa> modeloMapa);
    ModeloMapa* getModeloMapa();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::unique_ptr<ModeloMapa> m_modelo; // Puntero inteligente al modelo

};

#endif // VISTA_MAPA_H_INCLUDED
