#pragma once
#ifndef BOMBE_H_INCLUDED
#define BOMBE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "VistaMapa.h"
#include "ControladorAnimacion.h"
#include "ModeloBloque.h"

#define SIZE_BOMB 32
#define PATH_TO_BOMB_TEXTURE "./Media/Image/Bomb/classicBomb.png"
#define PATH_TO_EXPLOSION_TEXTURE "./Media/Image/Bomb/classicExplosion.png"
#define PATH_TO_EXPLOSION_SOUND "./Media/Sound/explosion.wav"
#define DELAY_EXPLOSION 3
#define DELAY_DISPLAY 1

class ModeloBomba : public sf::Drawable
{
private:
	ControladorAnimacion m_texturaBomba;
	sf::Sprite m_spriteBomba;

	ControladorAnimacion m_texturaExplosion;
	std::vector<sf::Sprite> m_spritesExplosion;

	sf::Time m_retrasoExplosion;
	sf::Clock m_temporizador;
	sf::Time m_mostrarExplosion;

	sf::Vector2f m_posicionBomba;
	sf::Vector2f m_casilleroBomba;

	sf::SoundBuffer m_bufferExplosion;
	sf::Sound m_sonidoExplosion;

	std::vector<sf::Vector2f> m_casillerosExplosion;

	int m_potenciaBomba;

	bool m_esExplosion;
	bool m_causarDa�o;
	bool m_destruir;
	bool m_esUso;
	bool m_esS�lida;
	bool m_lanzamiento;


public:
	ModeloBomba(); ///Constructor de bomba
	void actualizar(VistaMapa& mapaGenerado);
	/*****Permite actualizar la bomba en cada fotograma
	verificando si el tiempo transcurrido desde la
	creaci�n de la bomba es mayor al tiempo de explosi�n,
	si es as�, se crean los casilleros donde explota la bomba
	y si el tiempo es mayor al tiempo de destrucci�n de la
	bomba, esta se destruye.
	****/
	void crearBomba(sf::Vector2f posicionBomba, sf::Vector2f posicionCasillero, int potenciaBomba, VistaMapa& mapa);
	/*****Activa la bomba con una determinada posici�n
	y una cierta potencia.
	****/
	bool obtenerUsoBomba();
	/*****Devuelve si la bomba est� activa
	****/
	int obtenerNumeroCasillerosExplotados();
	/*****Devuelve la cantidad de casilleros donde hubo una explosi�n
	****/
	bool da�arJugador(sf::Vector2f posicionJugador);
	/*****Devuelve si el jugador est� vivo despu�s de haber sido golpeado
	en un casillero donde hubo una explosi�n.
	***/
	bool danarBomba(ModeloBomba* bombas);
	/*****Devuelve si la bomba pasada como par�metro fue golpeada por una explosi�n.
	Si es as�, la bomba explotar� al mismo tiempo.
	****/
	sf::Vector2f obtenerPosicionBombaTocada(sf::Vector2f posicion);
	/*****Devuelve la posici�n pasada como par�metro ??? (no s� por qu�)
	****/
	void da�arCasillero(VistaMapa& mapaGenerado);
	/*****Si un ladrillo o madera es golpeado, se transforma en tierra o en un bonus.
	Si un bonus es golpeado, se transforma en tierra.
	****/
	sf::Vector2f obtenerCasilleroExplotado(int numero);
	/*****Si un ladrillo o madera es golpeado, se transforma en tierra o en un bonus.
	Si un bonus es golpeado, se transforma en tierra.
	****/
	void lanzarBomba();
	/*****Establece el valor de lanzamiento de m_launch a true
	****/
	bool obtenerLanzamiento();
	/*****Devuelve el valor de m_launch
	****/
	sf::Vector2f obtenerPosicionBomba();
	/*****Devuelve la posici�n de la bomba
	****/

	bool getUsoBomba() const;
	virtual void draw(sf::RenderTarget& targets, sf::RenderStates states) const
	{

		if (m_esUso == true)
		{
			targets.draw(m_spriteBomba, states);
			if (m_esExplosion == true)
			{
				for (int i = 0; i < m_spritesExplosion.size(); i++)
				{
					targets.draw(m_spritesExplosion[i], states);
				}
			}
		}
	}
	/*****Permite dibujar la bomba y dibujar las explosiones cuando existan. ****/
};

#endif // BOMBE_HPP_INCLUDED


