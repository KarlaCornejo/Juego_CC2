#include "Bomba.h"

Bomba::Bomba()
	: m_texturaBomba(PATH_TO_BOMB_TEXTURE)
	, m_texturaExplosion(PATH_TO_EXPLOSION_TEXTURE)
{
	m_esUso = false;
	m_destruir = false;
	m_esSólida = false;
	m_lanzamiento = false;
	m_causarDaño = false;
}

void Bomba::lanzarBomba()
{
	m_lanzamiento = true;
}

bool Bomba::dañarJugador(sf::Vector2f posJugador)
{
	bool fueTocado = false;
	if (m_causarDaño == true)
	{
		if (m_casilleroBomba == posJugador)
		{
			fueTocado = true;
		}
		for (int i = 0; i < m_spritesExplosion.size() && fueTocado == false; i++)
		{
			if (sf::Vector2f(m_spritesExplosion[i].getPosition().x / TAMANO_CELDA, m_spritesExplosion[i].getPosition().y / TAMANO_CELDA) == posJugador)
			{
				fueTocado = true;
			}
		}
	}
	return fueTocado;
}

sf::Vector2f Bomba::obtenerPosicionBomba()
{
	return m_casilleroBomba;
}

bool Bomba::danarBomba(Bomba* bombas)
{
	for (int i = 0; i < m_casillerosExplosion.size(); i++)
	{
		if (bombas->obtenerPosicionBomba() == m_casillerosExplosion[i])
		{
			bombas->lanzarBomba();
			return true;
		}
	}
	return false;
}

bool Bomba::obtenerLanzamiento()
{
	return m_lanzamiento;
}

void Bomba::actualizar(Mapa& mapaGen)
{
    if (m_esUso == true)
    {
        std::cout << "Explosion" << std::endl;
        if (m_temporizador.getElapsedTime().asSeconds() >= m_retrasoExplosion.asSeconds() || (m_lanzamiento == true && m_causarDaño == false))
        {
            /***************Gestionar la posición del sprite de la explosión*********************/

            int n = 0;
            m_spriteBomba.setTextureRect(sf::IntRect(SIZE_BOMB, 0, SIZE_BOMB, SIZE_BOMB));
            bool puede_continuar = true;
            int cpt = 0;
            int cptTour = 0;
            sf::Vector2f bombaTocada;
            m_causarDaño = true;
            /**********Explosión a la izquierda***************/
            for (int i = 0; i <= m_potenciaBomba - 1 && puede_continuar == true; i++)
            {
                n++;
                if (mapaGen.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x - n) == TIPOLADRILLO)
                    puede_continuar = false;
                else
                {

                    cpt++;
                    m_spritesExplosion.push_back(sf::Sprite());
                    m_spritesExplosion[i].setPosition(sf::Vector2f(m_posicionBomba.x - n * SIZE_BOMB, m_posicionBomba.y));
                    m_spritesExplosion[i].setTexture(*m_texturaExplosion.get());
                    m_spritesExplosion[i].setTextureRect(sf::IntRect(SIZE_BOMB, 0, SIZE_BOMB, SIZE_BOMB));
                    m_casillerosExplosion.push_back(sf::Vector2f(m_casilleroBomba.x - n, m_casilleroBomba.y));
                    if (mapaGen.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x - n) != TIPOSUELO
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x - n) != BONUS_AGREGAR_BOMBA
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x - n) != BONUS_AUMENTAR_EXPLOSIÓN
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x - n) != BONUS_AUMENTAR_VELOCIDAD)
                        puede_continuar = false;
                }

            }
            n = 0;
            puede_continuar = true;
            cptTour = cpt;
            /**********Explosión a la derecha***************/
            for (int i = cpt; i <= cptTour + m_potenciaBomba - 1 && puede_continuar == true; i++)
            {
                n++;
                if (mapaGen.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x + n) == TIPOMURO)
                    puede_continuar = false;
                else
                {
                    cpt++;
                    m_spritesExplosion.push_back(sf::Sprite());
                    m_spritesExplosion[i].setTexture(*m_texturaExplosion.get());
                    m_spritesExplosion[i].setPosition(sf::Vector2f(m_posicionBomba.x + n * SIZE_BOMB, m_posicionBomba.y));
                    m_spritesExplosion[i].setTextureRect(sf::IntRect(SIZE_BOMB, 0, SIZE_BOMB, SIZE_BOMB));
                    m_casillerosExplosion.push_back(sf::Vector2f(m_casilleroBomba.x + n, m_casilleroBomba.y));
                    if (mapaGen.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x + n) != TIPOSUELO
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x + n) != BONUS_AGREGAR_BOMBA
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x + n) != BONUS_AUMENTAR_EXPLOSIÓN
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x + n) != BONUS_AUMENTAR_VELOCIDAD)
                        puede_continuar = false;
                }


            }
            n = 0;
            puede_continuar = true;
            cptTour = cpt;
            /**********Explosión hacia arriba***************/
            for (int i = cpt; i <= cptTour + m_potenciaBomba - 1 && puede_continuar == true; i++)
            {
                n++;
                if (mapaGen.getNumeroCelda(m_casilleroBomba.y - n, m_casilleroBomba.x) == TIPOMURO)
                    puede_continuar = false;
                else
                {
                    cpt++;
                    m_spritesExplosion.push_back(sf::Sprite());
                    m_spritesExplosion[i].setTexture(*m_texturaExplosion.get());
                    m_spritesExplosion[i].setPosition(sf::Vector2f(m_posicionBomba.x, m_posicionBomba.y - n * SIZE_BOMB));
                    m_spritesExplosion[i].setTextureRect(sf::IntRect(0, 0, SIZE_BOMB, SIZE_BOMB));
                    m_casillerosExplosion.push_back(sf::Vector2f(m_casilleroBomba.x, m_casilleroBomba.y - n));
                    if (mapaGen.getNumeroCelda(m_casilleroBomba.y - n, m_casilleroBomba.x) != TIPOSUELO
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y - n, m_casilleroBomba.x) != BONUS_AGREGAR_BOMBA
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y - n, m_casilleroBomba.x) != BONUS_AUMENTAR_EXPLOSIÓN
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y - n, m_casilleroBomba.x) != BONUS_AUMENTAR_VELOCIDAD)
                        puede_continuar = false;
                }

            }
            n = 0;
            puede_continuar = true;
            cptTour = cpt;
            /**********Explosión hacia abajo***************/
            for (int i = cpt; i <= cptTour + m_potenciaBomba - 1 && puede_continuar == true; i++)
            {
                n++;
                bombaTocada = sf::Vector2f(0, 0);
                if (mapaGen.getNumeroCelda(m_casilleroBomba.y + n, m_casilleroBomba.x) == TIPOMURO)
                    puede_continuar = false;
                else if (mapaGen.getNumeroCelda(m_casilleroBomba.y + n, m_casilleroBomba.x) == TIPO_BOMBA)
                {
                    bombaTocada = sf::Vector2f(m_casilleroBomba.y + n, m_casilleroBomba.x);
                    m_casillerosExplosion.push_back(sf::Vector2f(m_casilleroBomba.x, m_casilleroBomba.y + n));
                }
                else
                {

                    cpt++;
                    m_spritesExplosion.push_back(sf::Sprite());
                    m_spritesExplosion[i].setTexture(*m_texturaExplosion.get());
                    m_spritesExplosion[i].setPosition(sf::Vector2f(m_posicionBomba.x, m_posicionBomba.y + n * SIZE_BOMB));
                    m_spritesExplosion[i].setTextureRect(sf::IntRect(0, 0, SIZE_BOMB, SIZE_BOMB));
                    m_casillerosExplosion.push_back(sf::Vector2f(m_casilleroBomba.x, m_casilleroBomba.y + n));
                    if (mapaGen.getNumeroCelda(m_casilleroBomba.y + n, m_casilleroBomba.x) != TIPOSUELO
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y + n, m_casilleroBomba.x) != BONUS_AGREGAR_BOMBA
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y + n, m_casilleroBomba.x) != BONUS_AUMENTAR_EXPLOSIÓN
                        && mapaGen.getNumeroCelda(m_casilleroBomba.y + n, m_casilleroBomba.x) != BONUS_AUMENTAR_VELOCIDAD)
                        puede_continuar = false;
                }

            }

            m_esExplosion = true;
            m_temporizador.restart();
            Bomba::dañarCasillero(mapaGen);
            Bomba::obtenerPosicionBombaTocada(bombaTocada);


        }

        if (m_temporizador.getElapsedTime().asSeconds() >= m_mostrarExplosion.asSeconds() && m_esExplosion == true)
        {
            m_destruir = true;
            m_esUso = false;
            m_esSólida = false;
            m_causarDaño = false;
            m_spritesExplosion.clear();
            m_casillerosExplosion.clear();
            mapaGen.setNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x, TIPOSUELO);
        }
    }
 }

sf::Vector2f Bomba::obtenerPosicionBombaTocada(sf::Vector2f posicion){return posicion;}

 int Bomba::obtenerNumeroCasillerosExplotados()
 {
     return m_casillerosExplosion.size();
 }

 sf::Vector2f Bomba::obtenerCasilleroExplotado(int numero)
 {
     return m_casillerosExplosion[numero];
 }

 bool Bomba::obtenerUsoBomba()
 {
     return m_esUso;
 }

 void Bomba::dañarCasillero(Mapa& mapaGen)
 {
     for (int i = 0; i < m_casillerosExplosion.size(); i++)
     {
         if (mapaGen.getNumeroCelda(m_casillerosExplosion[i].y, m_casillerosExplosion[i].x) == TIPOLADRILLO
             || mapaGen.getNumeroCelda(m_casillerosExplosion[i].y, m_casillerosExplosion[i].x) == TIPOMADERA)
             mapaGen.cambiar(m_casillerosExplosion[i].y, m_casillerosExplosion[i].x, TIPOSUELO, true);
         else if (mapaGen.getNumeroCelda(m_casillerosExplosion[i].y, m_casillerosExplosion[i].x) == BONUS_AGREGAR_BOMBA
             || mapaGen.getNumeroCelda(m_casillerosExplosion[i].y, m_casillerosExplosion[i].x) == BONUS_AUMENTAR_EXPLOSIÓN
             || mapaGen.getNumeroCelda(m_casillerosExplosion[i].y, m_casillerosExplosion[i].x) == BONUS_AUMENTAR_VELOCIDAD)
             mapaGen.cambiar(m_casillerosExplosion[i].y, m_casillerosExplosion[i].x, TIPOSUELO, false);
     }
 }

 void Bomba::crearBomba(sf::Vector2f posicionBomba
     , sf::Vector2f posicionCasillero, int potenciaBomba, Mapa& mapa)
 {
     std::cout << "Crear Bomba" << std::endl;
     m_casillerosExplosion.clear();
     m_casilleroBomba = posicionCasillero;
     if (mapa.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x) ==     TIPOSUELO
         || mapa.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x) ==  BONUS_AGREGAR_BOMBA
         || mapa.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x) ==  BONUS_AUMENTAR_EXPLOSIÓN
         || mapa.getNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x) ==  BONUS_AUMENTAR_VELOCIDAD)
     {
         mapa.setNumeroCelda(m_casilleroBomba.y, m_casilleroBomba.x, TIPO_BOMBA);
         m_potenciaBomba = potenciaBomba;
         m_esExplosion = false;
         m_destruir = false;
         m_esUso = true;
         m_esSólida = true;
         m_lanzamiento = false;
         m_posicionBomba = posicionBomba;
         m_retrasoExplosion = sf::seconds(DELAY_EXPLOSION);
         m_mostrarExplosion = sf::seconds(DELAY_DISPLAY);
         /* cambiar si agregamos un paquete de texturas */
         m_spriteBomba.setTexture(*m_texturaBomba.get());
         m_spriteBomba.setTextureRect(sf::IntRect(0, 0, SIZE_BOMB, SIZE_BOMB));
         m_spriteBomba.setPosition(m_posicionBomba);
        
         m_temporizador.restart();
     }
 }