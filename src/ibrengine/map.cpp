// todo: license

#include "map.hpp"

namespace ibrengine
{

Map::Map(int w, int h, int tileW, int tileH):
  mW(w), mH(h), mTileW(tileW), mTileH(tileH),
  mOrientation(Orientation::Orthogonal)
{
}

const std::string& Map::getAuthor() const
{
  return mAuthor;
}

void Map::setAuthor(const std::string &author)
{
  mAuthor = author;
}

int Map::getH() const
{
  return mH;
}

int Map::getW() const
{
  return mW;
}

int Map::getTileH() const
{
  return mTileH;
}

int Map::getTileW() const
{
  return mTileW;
}

Map::Orientation Map::getOrientation() const
{
  return mOrientation;
}

void Map::setOrientation(Orientation orient)
{
  mOrientation = orient;
}

const std::string& Map::getVersion() const
{
  return mVersion;
}

void Map::setVersion(const std::string &version)
{
  mVersion = version;
}

void Map::addTileset(const std::shared_ptr<Tileset> &tSet)
{
  mTilesets.push_back(tSet);
}

Map::TilesetIterator Map::tilesetsBegin()
{
  return mTilesets.begin();
}

Map::TilesetConstIterator Map::tilesetsBegin() const
{
  return mTilesets.cbegin();
}

Map::TilesetIterator Map::tilesetsEnd()
{
  return mTilesets.end();
}

Map::TilesetConstIterator Map::tilesetsEnd() const
{
  return mTilesets.cend();
}

const Tileset* Map::getTilesetAt(int i) const
{
  return mTilesets.at(i).get();
}

int Map::getTilesetsCount() const
{
  return mTilesets.size();
}

void Map::addLayer(Layer *layer)
{
  mLayers.push_back(std::shared_ptr<Layer>(layer));
}

Map::LayerIterator Map::layersBegin()
{
  return mLayers.begin();
}

Map::LayerConstIterator Map::layersBegin() const
{
  return mLayers.cbegin();
}

Map::LayerIterator Map::layersEnd()
{
  return mLayers.end();
}

Map::LayerConstIterator Map::layersEnd() const
{
  return mLayers.cend();
}

const Layer* Map::getLayerAt(int i) const
{
  return mLayers.at(i).get();
}

int Map::getLayersCount() const
{
  return mLayers.size();
}

void Map::addAnimation(const std::shared_ptr<Animation> &anim)
{
  mAnimations.insert(std::make_pair(anim.get()->getId(), anim));
}

const Animation* Map::getAnimation(int animId) const
{
  return mAnimations.at(animId).get();
}

} // namespace ibrengine
