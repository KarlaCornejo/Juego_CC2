#ifndef JUGADOR_MODELO_H_INCLUDED
#define JUGADOR_MODELO_H_INCLUDED

#include <string>
#include <vector>
#include "ModeloBomba.h"

#define TAMANO_SPRITE_JUGADOR 32

enum Direccion { Abajo, Derecha, Arriba, Izquierda };

class ModeloJugador
{
public:
    ModeloJugador();
    //JugadorModelo(int id, std::string nombre, int vidaInicial);

    void setID(int id);
    int getID() const;

    void setNombre(const std::string& nombre);
    std::string getNombre() const;

    void setVida(int vida);
    int getVida() const;

    void setVelocidad(float velocidad);
    float getVelocidad();

    void addBomba(const ModeloBomba& bomba);
    std::vector<ModeloBomba>& getBombas();

    const std::vector<ModeloBomba>& getBombas() const;

    int getPosicionX();
    int getPosicionY();
    int m_poderBomba = 1;
    int m_posicionX;
    int m_posicionY;
    void setPosicionX(int PoX);
    void setPosicionY(int PoY);
private:
    int m_id = 1;
    std::string m_nombre = "Jugador01";
    int m_vida = 3;
    float m_velocidad = 0;
    std::vector<ModeloBomba> m_bombas;

};

#endif // JUGADOR_MODELO_H_INCLUDED