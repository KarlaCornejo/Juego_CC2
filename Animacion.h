#ifndef ANIMACION_H_INCLUDED
#define ANIMACION_H_INCLUDED

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <map>

class Animacion
{
public:
    Animacion(std::string const& id);
    virtual ~Animacion();

    /* retourne la texture r�f�renc�e par l'objet
     * retourne nullptr si la texture n'a pas ete load correctement
     */
    sf::Texture* get();

protected:
    std::shared_ptr<sf::Texture> m_texture;

    static std::map<std::string, std::weak_ptr<sf::Texture>> m_textures;
    static std::shared_ptr<sf::Texture> load(std::string const& id);

private:
};

#endif 