// todo: license

#include "tileset.hpp"

namespace ibrengine
{

Tileset::Tileset(const std::string &name, const std::string &imgSrc, int imgW, int imgH,
  int firstTileId, int tileW, int tileH):
  mName(name),
  mImgSrc(imgSrc),
  mFirstTileId(firstTileId),
  mTileW(tileW), mTileH(tileH),
  mImgW(imgW), mImgH(imgH)
{
}

int Tileset::getImgH() const
{
  return mImgH;
}

int Tileset::getImgW() const
{
  return mImgW;
}

int Tileset::getFirstTileId() const
{
  return mFirstTileId;
}

const std::string& Tileset::getImgSrc() const
{
  return mImgSrc;
}

const std::string& Tileset::getName() const
{
  return mName;
}

int Tileset::getTileH() const
{
  return mTileH;
}

int Tileset::getTileW() const
{
  return mTileW;
}

int Tileset::getTilesCount() const
{
  return (this->getImgW() / this->getTileW()) * (this->getImgH() / this->getTileH());
}

const sf::Color& Tileset::getTransparentColor() const
{
  return mTransparentColor;
}

void Tileset::setTransparentColor(const sf::Color &color)
{
  mTransparentColor = color;
}

} // namespace ibrengine
