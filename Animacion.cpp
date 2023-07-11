#include <vector>
#include "Animacion.h"

std::map<std::string, std::weak_ptr<sf::Texture>> Animacion::m_textures;

Animacion::Animacion(std::string const& id)
    : m_texture(load(id)){}

Animacion::~Animacion(){}

sf::Texture* Animacion::get()
{
    if (!m_texture){ return nullptr;  }
    return m_texture.get();
}

std::shared_ptr<sf::Texture> Animacion::load(std::string const& id)
{
    std::vector<std::string> idToDelette;
    std::shared_ptr<sf::Texture> returnPtr;

    /// recherche de l'element + recherche des elements a suprimer
    for (std::pair<std::string, std::weak_ptr<sf::Texture>> p : m_textures)
    {
        if (p.second.expired()){  idToDelette.push_back(p.first);    }
        else if (p.first == id)
            returnPtr = p.second.lock();
    }

    /// supression
    for (std::string id : idToDelette)
        m_textures.erase(id);

    if (returnPtr)
        return returnPtr;

    /// element inexistant - ajout si chargement reussi
    returnPtr = std::make_shared<sf::Texture>(sf::Texture());
    if (!returnPtr->loadFromFile(id))
        return std::shared_ptr<sf::Texture>();

    m_textures.insert(std::pair<std::string, std::weak_ptr<sf::Texture>>(id, std::weak_ptr<sf::Texture>(returnPtr)));

    return returnPtr;
}