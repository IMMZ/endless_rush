// todo: license

#include "maprenderer.hpp"

#include "drawableobject.hpp"
#include "map.hpp"
#include "objectlayer.hpp"
#include "tilelayer.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

/*
 * TODO: Render objects.
 */

namespace ibrengine
{

MapRenderer::MapRenderer(sf::RenderTarget &renderTarget):
  mRenderTarget(renderTarget)
{
}

void MapRenderer::renderMap(const Map &map)
{
  if (mMap != &map)
  {
    mMap = &map;
    this->loadSprites(); // TODO: do it only once not here in renderMap()
  }
  for (auto layer = map.layersBegin(); layer != map.layersEnd(); ++layer)
  {
    if ((*layer)->getType() == Layer::Type::Tile && (*layer)->isVisible())
      renderTileLayer(static_cast<TileLayer&>(*(*layer)));
    else if ((*layer)->getType() == Layer::Type::Object && (*layer)->isVisible())
      renderObjectLayer(static_cast<ObjectLayer&>(*(*layer)));
    else if ((*layer)->getType() == Layer::Type::Image and (*layer)->isVisible())
      renderImageLayer(static_cast<ImageLayer&>(*(*layer)));
  }
}

bool MapRenderer::isObjectInView(const DrawableObject &mapObj) const
{
  const int screenW = mRenderTarget.getSize().x;
  const int screenH = mRenderTarget.getSize().y;
  const int screenX = mRenderTarget.getView().getCenter().x - screenW / 2;
  const int screenY = mRenderTarget.getView().getCenter().y - screenH / 2;
  const int objW = mapObj.getSize().first;
  const int objH = mapObj.getSize().second;
  const int objOffsetX = mapObj.getPosition().first - screenX + objW;
  const int objOffsetY = mapObj.getPosition().second - screenY + objH;

  if (objOffsetX < -10 || objOffsetX > (screenX + screenW + objW + 10))
    return false;
  if (objOffsetY < -10 || objOffsetY > (screenY + screenH + objH + 10))
    return false;

  return true;
}

void MapRenderer::loadSprites()
{
  int spritesCount = 0;
  for (auto tileset = mMap->tilesetsBegin(); tileset != mMap->tilesetsEnd(); ++tileset)
    spritesCount += tileset->get()->getTilesCount();
  mSprites.reset(new sf::Sprite[spritesCount]);
  std::cout << "Loaded " << spritesCount << " tiles." << std::endl;

  for (auto tileset = mMap->tilesetsBegin(); tileset != mMap->tilesetsEnd(); ++tileset)
  {
    Tileset *tSet = tileset->get();
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

  // Loading sprites for image layers.
  for (auto it = mMap->layersBegin(); it != mMap->layersEnd(); ++it)
  {
    if ((*it)->getType() == Layer::Type::Image)
    {
      const ImageLayer &imgLayer = static_cast<ImageLayer&>(*(*it));
      std::shared_ptr<sf::Texture> imgTexture(new sf::Texture);
      imgTexture->loadFromFile(imgLayer.getImgPath());
      sf::Sprite imgSprite(*imgTexture);
      imgSprite.setPosition(0.0f, 0.0f);
      if (imgLayer.getOpacity() < 1.0f)
      {
        sf::Color color = imgSprite.getColor();
        color.a = 255 * imgLayer.getOpacity();
        imgSprite.setColor(color);
      }
      mImgSprites.insert(std::make_pair(imgLayer.getName(), imgSprite));
      mTextures.push_back(imgTexture);
    }
  }
}

void MapRenderer::renderImageLayer(const ImageLayer &imgLayer)
{
  mRenderTarget.draw(mImgSprites.at(imgLayer.getName()));
}

void MapRenderer::renderTileLayer(const TileLayer &layer)
{
  /*
   * We should render only visible tiles to optimize rendering.
   * 1) Find out left upper tile which is in window region;
   * 2) Render a grid of tiles starting with left upper tile.
   * Rendering is done horizontally like shown below:
   * OOOOOOOOOOOOOOOOO
   * OOOOOOOOOO =>...
   */

  const int windowW = mRenderTarget.getSize().x;
  const int windowH = mRenderTarget.getSize().y;
  const int currentX = mRenderTarget.getView().getCenter().x - windowW / 2;
  const int currentY = mRenderTarget.getView().getCenter().y - windowH / 2;
  const int xTileFrom = currentX / mMap->getTileW();
  const int yTileFrom = currentY / mMap->getTileH();
  int xTileTo = xTileFrom + windowW / mMap->getTileW();
  if (xTileTo >= mMap->getW())
    xTileTo = mMap->getW() - 1;
  int yTileTo = yTileFrom + windowH / mMap->getTileH();
  if (yTileTo >= mMap->getH())
    yTileTo = mMap->getH() - 1;
  for (int y = yTileFrom; y <= yTileTo; ++y)
  {
    for (int x = xTileFrom; x <= xTileTo; ++x)
    {
      if (x >= 0 && y >= 0 && layer.getTileId(x, y) > 0)
      {
        sf::Sprite &sprite = this->getSprite(layer.getTileId(x, y));
        //TODO: extract this
        //TODO: should we set the rotation here?
        if (layer.getOpacity() < 1.0f)
        {
          sf::Color color = sprite.getColor();
          color.a = 255 * layer.getOpacity();
          sprite.setColor(color);
        }

        sprite.setPosition(x * mMap->getTileW(), y * mMap->getTileH());
        mRenderTarget.draw(sprite);
      }
    }
  }
}

void MapRenderer::renderObjectLayer(const ObjectLayer &layer)
{
  for (auto i = layer.beginDrawableObjs(); i != layer.endDrawableObjs(); ++i)
  {
    if ((*i)->isVisible())
    {
      sf::Sprite &sprite = this->getSprite((*i)->getTileId());
      sprite.setPosition((*i)->getPosition().first, (*i)->getPosition().second);
      sprite.setRotation((*i)->getRotation());
      if (layer.getOpacity() < 1.0f)
      {
        sf::Color color = sprite.getColor();
        color.a = 255 * layer.getOpacity();
        sprite.setColor(color);
      }
      mRenderTarget.draw(sprite);
    }
  }
}

} // namespace ibrengine
