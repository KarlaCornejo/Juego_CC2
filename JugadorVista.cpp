#include "JugadorVista.h"

JugadorVista::JugadorVista(const JugadorModelo& modelo, JugadorControlador& controlador)
    : m_modelo(modelo), m_controlador(controlador)
{
    // Cargar la textura del jugador
    if (!m_texturaJugador.loadFromFile("ruta_de_la_textura.png"))
    {
        // Manejar el error de carga de la textura
    }

    // Configurar el sprite del jugador
    m_spriteJugador.setTexture(m_texturaJugador);
}

void JugadorVista::dibujar(sf::RenderWindow& ventana)
{
    for (int i = 0; i < m_modelo.getBombas().size(); i++)
    {
        if (m_modelo.getBombas()[i].getUsoBomba() == true)
            ventana.draw(m_modelo.getBombas()[i]);
    }

    if (m_modelo.getVida() != 0)
    {
        ventana.draw(m_spriteJugador);
    }
}

void JugadorVista::actualizarSprite()
{
    // L�gica para actualizar el sprite del jugador en funci�n del modelo
    // Por ejemplo, cambiar el frame de animaci�n seg�n la direcci�n o estado del jugador

    // Ejemplo de c�mo obtener la posici�n del jugador desde el controlador
    sf::Vector2f posicion = m_controlador.getPosition();

    // Ejemplo de c�mo obtener la animaci�n del jugador desde el modelo
    int animacion = m_modelo.getAnimacion();

    // Actualizar el sprite del jugador con la posici�n y animaci�n correspondientes
    m_spriteJugador.setPosition(posicion);
    m_spriteJugador.setAnimacion(animacion);
}
