// todo: license

#ifndef MAPRENDERER_HPP
#define MAPRENDERER_HPP

#include "imagelayer.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <unordered_map>
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
class DrawableObject;

class MapRenderer
{
public:
  explicit MapRenderer(sf::RenderTarget &renderTarget);

  void renderMap(const Map *map);

private:
  bool isObjectInView(const DrawableObject &obj) const;
  void loadSprites();
  void renderImageLayer(const ImageLayerSharedPtr &imgLayer);
  void renderTileLayer(const TileLayer *layer);
  void renderObjectLayer(const ObjectLayer *layer);
  inline sf::Sprite& getSprite(int index);

  std::unordered_map<std::string /* layerName */, sf::Sprite> mImgSprites;
  std::vector<std::shared_ptr<sf::Texture>> mTextures;
  std::unique_ptr<sf::Sprite[]> mSprites;

  const Map *mMap = nullptr;
  sf::RenderTarget &mRenderTarget;
};

sf::Sprite& MapRenderer::getSprite(int index)
{
  return mSprites[index - 1]; // Sprites in tmx starts with index '1', we start with '0'.
}

} // namespace ibrengine

#endif // MAPRENDERER_HPP
