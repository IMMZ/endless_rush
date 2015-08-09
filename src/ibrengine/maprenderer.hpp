// todo: license

#ifndef MAPRENDERER_HPP
#define MAPRENDERER_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <vector>

namespace sf
{
  class Sprite;
}

namespace ibrengine
{

class ObjectLayer;
class TileLayer;
class Map;

class MapRenderer
{
public:
  explicit MapRenderer(sf::RenderTarget &renderTarget);
  ~MapRenderer();

  void renderMap(const Map *map);

private:
  void loadSprites();
  void renderTileLayer(const TileLayer *layer);
  void renderObjectLayer(const ObjectLayer *layer);
  inline sf::Sprite& getSprite(int index);

  std::vector<std::shared_ptr<sf::Texture>> mTextures;
  sf::Sprite *mSprites = nullptr;
  const Map *mMap = nullptr;
  sf::RenderTarget &mRenderTarget;
};

sf::Sprite& MapRenderer::getSprite(int index)
{
  return mSprites[index - 1]; // Sprites in tmx starts with index '1', we start with '0'.
}

} // namespace ibrengine

#endif // MAPRENDERER_HPP
