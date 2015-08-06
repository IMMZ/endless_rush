// todo: license

#ifndef MAP_HPP
#define MAP_HPP

#include "animation.hpp"
#include "layer.hpp"
#include "tileset.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace ibrengine
{

class Map
{
public:
  typedef std::vector<std::shared_ptr<Tileset>>::iterator TilesetIterator;
  typedef std::vector<std::shared_ptr<Tileset>>::const_iterator TilesetConstIterator;
  typedef std::vector<std::shared_ptr<Layer>>::iterator LayerIterator;
  typedef std::vector<std::shared_ptr<Layer>>::const_iterator LayerConstIterator;

  enum class Orientation
  {
    Orthogonal,
    Isometric,
    Hexagonal
  };

  Map(int w, int h, int tileW, int tileH);

  const std::string& getAuthor() const;
  void setAuthor(const std::string &author);
  int getH() const;
  int getW() const;
  int getTileH() const;
  int getTileW() const;
  Orientation getOrientation() const;
  void setOrientation(Orientation orient);
  const std::string& getVersion() const;
  void setVersion(const std::string &version);

  // Tileset funcs.
  void addTileset(const std::shared_ptr<Tileset> &tSet);
  TilesetIterator tilesetsBegin();
  TilesetConstIterator tilesetsBegin() const;
  TilesetIterator tilesetsEnd();
  TilesetConstIterator tilesetsEnd() const;
  const Tileset* getTilesetAt(int i) const;
  int getTilesetsCount() const;

  // Layer funcs.
  void addLayer(Layer *layer); // TODO: replace by const std::shared<>
  LayerIterator layersBegin();
  LayerConstIterator layersBegin() const;
  LayerIterator layersEnd();
  LayerConstIterator layersEnd() const;
  const Layer* getLayerAt(int i) const;
  int getLayersCount() const;

  // Animation funcs.
  void addAnimation(const std::shared_ptr<Animation> &anim);
  const Animation* getAnimation(int animId) const;

private:
  std::vector<std::shared_ptr<Tileset>> mTilesets;
  std::vector<std::shared_ptr<Layer>> mLayers;
  std::map<int /* id */, std::shared_ptr<Animation>> mAnimations;
  std::string mVersion;
  std::string mAuthor;
  int mW, mH;
  int mTileW, mTileH;
  Orientation mOrientation;
};

} // namespace ibrengine

#endif // MAP_HPP
