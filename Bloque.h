#ifndef BLOQUE_H_INCLUDED
#define BLOQUE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

#define TAMANO_CELDA 32
#define TIPOMURO 0
#define TIPOSUELO 1
#define TYPE_BRICS 2
#define TYPE_WOOD 3

class Bloque
{
public:
	Bloque(int tipo, sf::Vector2f posicion, int numeroEnMapa); /// Constructor
	bool esSolido();
	/*** Devuelve si el bloque es sólido */
	sf::Vector2f obtenerPosicion();
	/* Devuelve la posición del bloque */
	bool estaLibre();
	/* Devuelve si el bloque está libre***/
	void setTipo(int tipo);
	/*** Establece el tipo del bloque (muro, ladrillo, madera) ***/
	void setLibre(bool estaLibre);
	/*** Establece si el bloque está libre ***/

	sf::RectangleShape obtenerHitBox();
	/*** Devuelve el hitbox del bloque ***/
private:
	int m_tipo; // Diferente tipo para gestionar la textura
	bool m_esColisionable;
	int m_numeroEnMapa;
	bool m_estaLibre;
	sf::RectangleShape m_hitBox;
	sf::Vector2f m_posicion;
};

#endif // BLOQUE_H_INCLUDED