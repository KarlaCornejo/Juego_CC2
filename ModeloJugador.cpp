#include "ModeloJugador.h"

ModeloJugador::ModeloJugador()
    : m_id(0), m_vida(3), m_velocidad(30)
{
    m_bombas.push_back(ModeloBomba());
}

/*JugadorModelo::JugadorModelo(int id, std::string nombre, int vidaInicial)
    : m_id(id), m_nombre(nombre), m_vida(vidaInicial)
{
}*/

void ModeloJugador::setID(int id)
{
    m_id = id;
}

int ModeloJugador::getID() const
{
    return m_id;
}

void ModeloJugador::setNombre(const std::string& nombre)
{
    m_nombre = nombre;
}

std::string ModeloJugador::getNombre() const
{
    return m_nombre;
}

void ModeloJugador::setVida(int vida)
{
    m_vida = vida;
}

int ModeloJugador::getVida() const
{
    return m_vida;
}

void ModeloJugador::setVelocidad(float velocidad)
{
    m_velocidad = velocidad;
}

float ModeloJugador::getVelocidad()
{
    return m_velocidad;
}

void ModeloJugador::addBomba(const ModeloBomba& bomba)
{
    m_bombas.push_back(bomba);
}

std::vector<ModeloBomba>& ModeloJugador::getBombas()
{
    return m_bombas;
}




const std::vector<ModeloBomba>& ModeloJugador::getBombas() const
{
    return m_bombas;
}


int ModeloJugador::getPosicionX() {
    return m_posicionX; 
}

int ModeloJugador::getPosicionY() { 
    return m_posicionY; 
}

void ModeloJugador::setPosicionX(int PoX) {
    m_posicionX = PoX; 
}

void ModeloJugador::setPosicionY(int PoY) { 
    m_posicionY = PoY; 
}
