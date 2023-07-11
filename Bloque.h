#ifndef BLOQUE_H_INCLUDED
#define BLOQUE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

#define TAMANO_CELDA 32
#define TIPOMURO 0
#define TIPOSUELO 1
#define TIPOLADRILLO 2
#define TIPOMADERA 3
#define BONUS_AGREGAR_BOMBA 4
#define BONUS_AUMENTAR_EXPLOSIÓN 5
#define BONUS_AUMENTAR_VELOCIDAD 6
#define TIPO_BOMBA 7

class Bloque
{
public:
	Bloque(int tipo, sf::Vector2f posicion, int numeroEnMapa); /// Constructor
	bool esSolido();
	sf::Vector2f obtenerPosicion();
	bool estaLibre();
	void setTipo(int tipo);
	void setLibre(bool estaLibre);
	bool getEsDestrutible();
	bool estaDestruidoElBloque();
	void romperBloque();
	sf::RectangleShape obtenerHitBox();

	/*** Funciones adicionales ***/
	int getTipo();
	int getVida();
	bool esColisionable();
	bool estaDestructible();

private:
	int m_tipo;
	int m_vida;
	bool m_esColisionable;
	bool m_estaDestructible;
	int m_numeroEnMapa;
	bool m_estaLibre;
	sf::RectangleShape m_hitBox;
	sf::Vector2f m_posicion;
};


#endif // BLOQUE_H_INCLUDED