#ifndef RESOURCESIDENTIFIERS_H
#define RESOURCESIDENTIFIERS_H
// Forward declaration of SFML classes
namespace sf
{
    class Texture;
}

namespace Textures
{
    enum ID
    {
        Galile,
        Bleuton,
        Picard
    };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;


#endif // RESOURCESIDENTIFIERS_H
