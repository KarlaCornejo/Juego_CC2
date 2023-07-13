#include "JugadorModelo.h"

JugadorModelo::JugadorModelo()
    : m_id(0), m_vida(0), m_velocidad(0)
{
}

JugadorModelo::JugadorModelo(int id, std::string nombre, int vidaInicial, int velocidadInicial)
    : m_id(id), m_nombre(nombre), m_vida(vidaInicial), m_velocidad(velocidadInicial)
{
}

void JugadorModelo::setID(int id)
{
    m_id = id;
}

int JugadorModelo::getID() const
{
    return m_id;
}

void JugadorModelo::setNombre(const std::string& nombre)
{
    m_nombre = nombre;
}

std::string JugadorModelo::getNombre() const
{
    return m_nombre;
}

void JugadorModelo::setVida(int vida)
{
    m_vida = vida;
}

int JugadorModelo::getVida() const
{
    return m_vida;
}

void JugadorModelo::setVelocidad(float velocidad)
{
    m_velocidad = velocidad;
}

float JugadorModelo::getVelocidad() const
{
    return m_velocidad;
}

void JugadorModelo::addBomba(const Bomba& bomba)
{
    m_bombas.push_back(bomba);
}

std::vector<Bomba>& JugadorModelo::getBombas()
{
    return m_bombas;
}




const std::vector<Bomba>& JugadorModelo::getBombas() const
{
    return m_bombas;
}


int JugadorModelo::getPosicionX() {
    return m_posicionX; 
}

int JugadorModelo::getPosicionY() { 
    return m_posicionY; 
}

void JugadorModelo::setPosicionX(int PoX) { 
    m_posicionX = PoX; 
}

void JugadorModelo::setPosicionY(int PoY) { 
    m_posicionY = PoY; 
}
