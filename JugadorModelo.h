#ifndef JUGADOR_MODELO_H_INCLUDED
#define JUGADOR_MODELO_H_INCLUDED

#include <string>
#include <vector>
#include "Bomba.h"

#define TAMANO_SPRITE_JUGADOR 32

enum Direccion { Abajo, Derecha, Arriba, Izquierda };

class JugadorModelo
{
public:
    JugadorModelo();
    JugadorModelo(int id, std::string nombre, int vidaInicial, int velocidadInicial);

    void setID(int id);
    int getID() const;

    void setNombre(const std::string& nombre);
    std::string getNombre() const;

    void setVida(int vida);
    int getVida() const;

    void setVelocidad(float velocidad);
    float getVelocidad() const;

    void addBomba(const Bomba& bomba);
    std::vector<Bomba>& getBombas();

    const std::vector<Bomba>& getBombas() const;

    int getPosicionX();
    int getPosicionY();


    void setPosicionX(int);
    void setPosicionY(int);
private:
    int m_id;
    std::string m_nombre;
    int m_vida;
    float m_velocidad;
    std::vector<Bomba> m_bombas;
    int m_posicionX;
    int m_posicionY;
};

#endif // JUGADOR_MODELO_H_INCLUDED