// todo: license

#ifndef MAP_HPP
#define MAP_HPP

#include "animation.hpp"
#include "layer.hpp"
#include "mapobject.hpp"
#include "physicobject.hpp"
#include "tileset.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace ibrengine
{

class Map
{
public:
  using CollisionShapeMap = std::map<int /*tileId */, PhysicObject::ShapeGroup>;

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
  void update(const sf::Time &time);

  // Tileset funcs.
  void addTileset(TilesetUniquePtr tSet);

  using TilesetIterator = std::vector<TilesetUniquePtr>::iterator;
  using TilesetConstIterator = std::vector<TilesetUniquePtr>::const_iterator;
  TilesetIterator tilesetsBegin();
  TilesetConstIterator tilesetsBegin() const;
  TilesetIterator tilesetsEnd();
  TilesetConstIterator tilesetsEnd() const;
  const Tileset& getTilesetAt(int i) const;
  int getTilesetsCount() const;

  // Layer funcs.
  void addLayer(LayerUniquePtr layer);

  using LayerIterator = std::vector<LayerUniquePtr>::iterator;
  using LayerConstIterator = std::vector<LayerUniquePtr>::const_iterator;
  LayerIterator layersBegin();
  LayerConstIterator layersBegin() const;
  LayerIterator layersEnd();
  LayerConstIterator layersEnd() const;
  const Layer& getLayerAt(int i) const;
  int getLayersCount() const;

  // Animation funcs. TODO: make only 2 funcs with template!
  void addAnimation(AnimationUniquePtr anim);
  Animation& getAnimation(int animId);

  // Collision shape group funcs.
  void addShapeGroup(int tileId, const PhysicObject::ShapeGroup &&shapeGrp);
  const PhysicObject::ShapeGroup& getShapeGroup(int tileId) const;

private:
  CollisionShapeMap mCollisionShapeGroups;
  std::vector<TilesetUniquePtr> mTilesets;
  std::vector<LayerUniquePtr> mLayers;
  std::map<int /* id */, AnimationUniquePtr> mAnimations; // TODO: replace by unordered
  std::unordered_multimap<int /* tileId */, std::shared_ptr<MapObject>> mCollisionObjs;
  std::string mVersion;
  std::string mAuthor;
  int mW, mH;
  int mTileW, mTileH;
  Orientation mOrientation;
};

DECLARE_SMART_PTRS(Map);

} // namespace ibrengine

#endif // MAP_HPP
