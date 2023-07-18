#include "VistaJugador.h"

VistaJugador::VistaJugador(ModeloJugador& modelo, ControladorJugador& controlador, std::string& rutaArchivo, sf::Time& deltasTime)
    : m_modelo(modelo), m_controlador(controlador), m_rutaArchivo(rutaArchivo), deltaTime(deltasTime)
{
    // Cargar la textura del jugador
    if (!m_texturaJugador.loadFromFile(rutaArchivo))
    {
        std::cout << "error" << std::endl;
    }
    m_spriteJugador.setTexture(m_texturaJugador);
    m_spriteJugador.setPosition(sf::Vector2f(modelo.getPosicionX() * TAMANO_CELDA, modelo.getPosicionY() * TAMANO_CELDA));
    // Configurar el sprite del jugador
    
    m_spriteJugador.setTextureRect(sf::IntRect
    (m_controlador.m_animacion.x * TAMANO_SPRITE_JUGADOR
        , m_controlador.m_animacion.y * TAMANO_SPRITE_JUGADOR
        , TAMANO_SPRITE_JUGADOR, TAMANO_SPRITE_JUGADOR));
}

void VistaJugador::dibujar(sf::RenderWindow& ventana)
{
    /*for (int i = 0; i < m_modelo.getBombas().size(); i++)
    {
        if (m_modelo.getBombas()[i].getUsoBomba() == true)
            ventana.draw(m_modelo.getBombas()[i]);
    }*/

    if (m_modelo.getVida() != 0)
    {
        ventana.draw(m_spriteJugador);
    }
}

void VistaJugador::manejarJugador() {
    m_controlador.manejarEntradaJugador(m_spriteJugador);
}

void VistaJugador::actualizarSprite(sf::Time& TiempoPorFrame)
{
    deltaTime = TiempoPorFrame;
    // Lógica para actualizar el sprite del jugador en función del modelo
    // Por ejemplo, cambiar el frame de animación según la dirección o estado del jugador

    // Ejemplo de cómo obtener la posición del jugador desde el controlador
    sf::Vector2f posicion = m_controlador.getPosition();
    //sf::Time deltaTiempo, sf::Sprite m_spriteJugador, int m_velocidadAnimacion, int m_cuadroAnimacion, bool m_actualizarAnimacion, sf::Texture m_texturaJugador
    // Ejemplo de cómo obtener la animación del jugador desde el modelo
    m_controlador.actualizarAnimacion(TiempoPorFrame,m_spriteJugador,m_velocidadAnimacion,m_cuadroAnimacion,m_texturaJugador);
}
