#include "VistaMapa.h"

/*VistaMapa::VistaMapa(ModeloMapa& modelo)
    : m_modelo(modelo)
{
}*/
VistaMapa::VistaMapa()
{
    // Constructor por defecto
    m_modelo = std::make_unique<ModeloMapa>();
}

VistaMapa::VistaMapa(std::unique_ptr<ModeloMapa> modeloMapa)
{
    // Constructor que recibe un puntero inteligente al modelo
    m_modelo = std::move(modeloMapa);
}

void VistaMapa::cargarMapa(std::unique_ptr<ModeloMapa> modeloMapa)
{
    // Cargar un nuevo mapa a partir de un puntero inteligente al modelo
    m_modelo = std::move(modeloMapa);
    
}

sf::Vector2f VistaMapa::getFilasColumnas(){
    return m_modelo.get()->getFilasColumnas();
}

ModeloMapa* VistaMapa::getModeloMapa() { return m_modelo.get(); }

void VistaMapa::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &(m_modelo->m_texturaCelda);
    for (unsigned int i = 0; i < m_modelo->getAncho(); ++i)
    {
        for (unsigned int j = 0; j < m_modelo->getAlto(); ++j)
        {
            target.draw(m_modelo->getVerticeArray(i, j), states);
        }
    }
}
