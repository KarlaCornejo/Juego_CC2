#include "VentanaInicio.h"

using namespace sf;
Font menuFont;

VentanaInicio::VentanaInicio(int l, int a) {
    lar = l;
    anc = a;
}

void VentanaInicio::mostrarPantallaInicio(RenderWindow& ventana, bool resaltarJuego, bool resaltarConfiguracion) {
    // Implementación de mostrarPantallaInicio
    menuFont.loadFromFile("./Media/Font/font.ttf");

    sf::Texture fondoTextura;
    if (!fondoTextura.loadFromFile("Media/Image/Menu6.png"))
    {

    }

    Sprite fondo;
    fondo.setTexture(fondoTextura);
    fondo.setPosition(0, 0);

    Text textoJugar;
    textoJugar.setString("JUGAR");
    textoJugar.setFont(menuFont);
    textoJugar.setPosition(120, 380);
    textoJugar.setCharacterSize(22);
    if (resaltarJuego)
        textoJugar.setFillColor(Color(0, 0, 0));

    Text textoSalir;
    textoSalir.setString("SALIR");
    textoSalir.setFont(menuFont);
    textoSalir.setPosition(475, 380);
    textoSalir.setCharacterSize(22);
    if (resaltarConfiguracion)
        textoSalir.setFillColor(Color(241, 196, 15));


    ventana.setSize(Vector2u(UI_WIDTH, UI_HEIGHT));
    ventana.clear(Color::Black);
    ventana.draw(fondo);
    ventana.draw(textoJugar);
    ventana.draw(textoSalir);
    ventana.display();
}

void VentanaInicio::ejecutar() {
    RenderWindow ventana(VideoMode(UI_WIDTH, UI_HEIGHT), "Bomberman", Style::Close);

    mostrarPantallaInicio(ventana, false, false);

    while (ventana.isOpen()) {
        Event evento;
        while (ventana.pollEvent(evento)) {
            switch (evento.type) {
            case Event::Closed:
                ventana.close();
                break;
            case Event::MouseMoved:
                if (evento.mouseMove.x >= 50 && evento.mouseMove.x <= 300 && evento.mouseMove.y >= 350 && evento.mouseMove.y < 430)
                    mostrarPantallaInicio(ventana, true, false);
                else if (evento.mouseMove.x >= (UI_WIDTH - 300) && evento.mouseMove.x <= (UI_WIDTH - 50) && evento.mouseMove.y >= 350 && evento.mouseMove.y < 430)
                    mostrarPantallaInicio(ventana, false, true);
                else
                    mostrarPantallaInicio(ventana, false, false);

                break;
            case Event::MouseButtonPressed:
                if (evento.mouseButton.x >= (UI_WIDTH - 300) && evento.mouseButton.x <= (UI_WIDTH - 50) && evento.mouseButton.y >= 350 && evento.mouseButton.y < 430)
                    ventana.close();
                else if (evento.mouseButton.x >= 50 && evento.mouseButton.x <= 300 && evento.mouseButton.y >= 350 && evento.mouseButton.y < 430)
                {
                    VentanaJuego ventanaJuego;
                    ventanaJuego.ejecutar();
                }
                break;
            }
        }
    }
}
