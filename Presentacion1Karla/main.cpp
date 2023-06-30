#include <SFML/Graphics.hpp>
#include <iostream>

#define UI_WIDTH 788
#define UI_HEIGHT 500
#define SPRITE_PLAYER_SIZE 32

using namespace sf;

void pantallaPrincipalDelMenu(RenderWindow& fenetre, bool colorGame, bool colorSettings);

Font menufont;

int main()
{
    menufont.loadFromFile("font.ttf");

    RenderWindow ventanaJuego(VideoMode(UI_WIDTH, UI_HEIGHT), "Bomberman", Style::Close);

    pantallaPrincipalDelMenu(ventanaJuego, false, false);

    Texture personajeTexture;
    Sprite personajeSprite;
    Vector2f personajePosicion(400.0f, 300.0f);
    float personajeVelocidad = 200.0f;

    if (!personajeTexture.loadFromFile("player.png"))
    {
        std::cerr << "Error al cargar la textura del personaje." << std::endl;
        return EXIT_FAILURE;
    }

    personajeSprite.setTexture(personajeTexture);
    personajeSprite.setPosition(personajePosicion);

    Clock clock;

    while (ventanaJuego.isOpen())
    {
        Event evento;
        while (ventanaJuego.pollEvent(evento))
        {
            switch (evento.type)
            {
            case Event::Closed:
                ventanaJuego.close();
                break;
            case Event::MouseMoved:
                if (evento.mouseMove.x >= 50 && evento.mouseMove.x <= 300 && evento.mouseMove.y >= 350 && evento.mouseMove.y < 430)
                    pantallaPrincipalDelMenu(ventanaJuego, true, false);
                else if (evento.mouseMove.x >= (UI_WIDTH - 300) && evento.mouseMove.x <= (UI_WIDTH - 50) && evento.mouseMove.y >= 350 && evento.mouseMove.y < 430)
                    pantallaPrincipalDelMenu(ventanaJuego, false, true);
                else
                    pantallaPrincipalDelMenu(ventanaJuego, false, false);

                break;
            case Event::MouseButtonPressed:
                if (evento.mouseButton.x >= (UI_WIDTH - 300) && evento.mouseButton.x <= (UI_WIDTH - 50) && evento.mouseButton.y >= 350 && evento.mouseButton.y < 430)
                    ventanaJuego.close();
                else if (evento.mouseButton.x >= 50 && evento.mouseButton.x <= 300 && evento.mouseButton.y >= 350 && evento.mouseButton.y < 430)
                {
                    while (ventanaJuego.isOpen())
                    {

                        float deltaTime = clock.restart().asSeconds();

                        if (Keyboard::isKeyPressed(Keyboard::W))
                        {
                            personajePosicion.y -= personajeVelocidad * deltaTime;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::S))
                        {
                            personajePosicion.y += personajeVelocidad * deltaTime;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::A))
                        {
                            personajePosicion.x -= personajeVelocidad * deltaTime;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::D))
                        {
                            personajePosicion.x += personajeVelocidad * deltaTime;
                        }

                        personajeSprite.setPosition(personajePosicion);
                        personajeSprite.setTextureRect(IntRect(SPRITE_PLAYER_SIZE, SPRITE_PLAYER_SIZE, SPRITE_PLAYER_SIZE, SPRITE_PLAYER_SIZE));

                        ventanaJuego.clear();

                        ventanaJuego.draw(personajeSprite);

                        ventanaJuego.display();
                    }
                }
                    break;
            }
        }

    }

    return 0;
}

void pantallaPrincipalDelMenu(RenderWindow& fenetre, bool colorGame, bool colorSettings)
{
    Texture background;
    if (!background.loadFromFile("Menu6.png"))
    {
        std::cerr << "Error al cargar la textura del fondo del menú." << std::endl;
        return;
    }

    Sprite fondo;
    fondo.setTexture(background);
    fondo.setPosition(0, 0);

    Text playText;
    playText.setString("JUGAR");
    playText.setFont(menufont);
    playText.setPosition(120, 380);
    playText.setCharacterSize(22);
    if (colorGame)
        playText.setFillColor(Color(0, 0, 0));

    Text exitText;
    exitText.setString("SALIR");
    exitText.setFont(menufont);
    exitText.setPosition(475, 380);
    exitText.setCharacterSize(22);
    if (colorSettings)
        exitText.setFillColor(Color(241, 196, 15));

    fenetre.setSize(Vector2u(UI_WIDTH, UI_HEIGHT));
    fenetre.clear(Color::Black);
    fenetre.draw(fondo);
    fenetre.draw(playText);
    fenetre.draw(exitText);
    fenetre.display();
}