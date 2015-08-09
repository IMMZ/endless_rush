// todo: license

#include "maprenderer.hpp"

#include "animatableobject.hpp"
#include "map.hpp"
#include "objectlayer.hpp"
#include "tilelayer.hpp"
#include "tileobject.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <SFML/Graphics/Font.hpp> // todo remove
#include <SFML/Graphics/Text.hpp> // todo remove

#include <iostream> // TODO: remove

/*
 * TODO: Render objects.
 */

namespace ibrengine
{

MapRenderer::MapRenderer(sf::RenderTarget &renderTarget):
  mRenderTarget(renderTarget)
{
}

MapRenderer::~MapRenderer()
{
  delete[] mSprites;
}

void MapRenderer::renderMap(const Map *map)
{
  if (mMap != map)
  {
    mMap = map;
    this->loadSprites(); // TODO: do it only once not here in renderMap()
  }
  for (Map::LayerConstIterator i = map->layersBegin(); i != map->layersEnd(); ++i)
  {
    TileLayer *tLayer = dynamic_cast<TileLayer*>(i->get());
    ObjectLayer *objLayer = dynamic_cast<ObjectLayer*>(i->get());
    if (tLayer != nullptr && tLayer->isVisible())
      this->renderTileLayer(tLayer);
    else if (objLayer != nullptr && objLayer->isVisible())
      this->renderObjectLayer(objLayer);
  }
}

void MapRenderer::loadSprites()
{
  // Reinitializing storage for sprites.
  delete[] mSprites;
  int spritesCount = 0;
  for (Map::TilesetConstIterator i = mMap->tilesetsBegin(); i != mMap->tilesetsEnd(); ++i)
    spritesCount += i->get()->getTilesCount();
  mSprites = new sf::Sprite[spritesCount];
  std::cout << "Loaded " << spritesCount << " tiles." << std::endl;

  for (Map::TilesetConstIterator i = mMap->tilesetsBegin(); i != mMap->tilesetsEnd(); ++i)
  {
    Tileset *tSet = i->get();
    sf::Image img;
    img.loadFromFile(tSet->getImgSrc());
    img.createMaskFromColor(tSet->getTransparentColor());
    std::shared_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromImage(img);
    mTextures.push_back(texture);
    const int wTilesCount = tSet->getImgW() / tSet->getTileW();
    const int hTilesCount = tSet->getImgH() / tSet->getTileH();

    // Setting up the sprites in our storage.
    int currentSpriteId = 0;
    for (int y = 0; y < hTilesCount; ++y)
    {
      for (int x = 0; x < wTilesCount; ++x)
      {
        sf::Sprite &sprite = this->getSprite(currentSpriteId + tSet->getFirstTileId());
        sprite.setTexture(*texture);
        sprite.setTextureRect(
          sf::IntRect(x * tSet->getTileW(), y * tSet->getTileH(), tSet->getTileW(), tSet->getTileH()));
        currentSpriteId++;
      }
    }
  }
}

void MapRenderer::renderTileLayer(const TileLayer *layer)
{
  /*
   * We should render only visible tiles to optimize rendering.
   * 1) Find out left upper tile which is in window region;
   * 2) Render a grid of tiles starting with left upper tile.
   * Rendering is done horizontally like shown below:
   * OOOOOOOOOOOOOOOOO
   * OOOOOOOOOO =>...
   */

  int windowW = mRenderTarget.getSize().x;
  int windowH = mRenderTarget.getSize().y;
  int currentX = mRenderTarget.getView().getCenter().x - windowW / 2;
  int currentY = mRenderTarget.getView().getCenter().y - windowH / 2;
  const int xTileFrom = currentX / mMap->getTileW();
  const int yTileFrom = currentY / mMap->getTileH();
  const int xTileTo = xTileFrom + windowW / mMap->getTileW();
  const int yTileTo = yTileFrom + windowH / mMap->getTileH();

  for (int y = yTileFrom; y <= yTileTo; ++y)
  {
    for (int x = xTileFrom; x <= xTileTo; ++x)
    {
      if (x >= 0 && y >= 0 && layer->getTileId(x, y) > 0)
      {
        sf::Sprite &sprite = this->getSprite(layer->getTileId(x, y));
        if (layer->getOpacity() < 1.0f)
        {
          sf::Color color = sprite.getColor();
          color.a = 255 * layer->getOpacity();
          sprite.setColor(color);
        }
        sprite.setPosition(x * mMap->getTileW(), y * mMap->getTileH());
        mRenderTarget.draw(sprite);
      }
    }
  }
}

void MapRenderer::renderObjectLayer(const ObjectLayer *layer)
{
  for (const std::shared_ptr<MapObject> &mapObj: *layer)
  {
    if (mapObj->isVisible() && dynamic_cast<DrawableObject*>(mapObj.get()) != nullptr)
    {
      AnimatableObject *animObj = dynamic_cast<AnimatableObject*>(mapObj.get());
      TileObject *tileObj = dynamic_cast<TileObject*>(mapObj.get());
      sf::Sprite *sprite = nullptr;
      if (animObj != nullptr)
      {
        sprite = &this->getSprite(animObj->getCurrentTileId());
        sprite->setPosition(animObj->getPosition().x, animObj->getPosition().y);
      }
      else if (tileObj != nullptr)
      {
        sprite = &this->getSprite(tileObj->getTileId());
        sprite->setPosition(tileObj->getPosition().x, tileObj->getPosition().y);
      }
      if (layer->getOpacity() < 1.0f)
      {
        sf::Color color = sprite->getColor();
        color.a = 255 * layer->getOpacity();
        sprite->setColor(color);
      }
      mRenderTarget.draw(*sprite);
    }
  }
}

} // namespace ibrengine
