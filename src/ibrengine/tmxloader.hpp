// todo: license

#ifndef TMXLOADER_HPP
#define TMXLOADER_HPP

#include "animation.hpp"
#include "map.hpp"
#include "mapobject.hpp"

#include <rapidxml.hpp>

#include <memory>
#include <string>

namespace ibrengine
{

class Layer;
class ObjectLayer;
class TileLayer;
class Tileset;

class TmxLoader
{
public:
  MapUniquePtr loadMap(const std::string &tmxPath);

private:
  using XmlDoc = rapidxml::xml_document<char>;
  using XmlNode = rapidxml::xml_node<char>;
  using XmlAttribute = rapidxml::xml_attribute<char>;

  enum class TileLinkage
  {
    NotLinkedToTile,
    LinkedToTiled
  };

  PhysicObject::ShapeGroup parseShapeGroup(const XmlNode *objectNode, TileLinkage linkage);
  MapUniquePtr parseMap(const XmlNode *mapNode);
  TilesetUniquePtr parseTileset(Map &map, const XmlNode *tilesetNode);
  void parseTilesets(Map &map, const XmlNode *mapNode);
  LayerUniquePtr parseImageLayer(const XmlNode *layerNode);
  LayerUniquePtr parseTileLayer(const XmlNode *layerNode);
  LayerUniquePtr parseObjectLayer(Map &map, const XmlNode *layerNode);
  void parseObjects(Map &map, ObjectLayer &layer, const XmlNode *layerNode);
  void parseObject(Map &map, ObjectLayer &layer, const XmlNode *objNode);
  AnimationUniquePtr parseAnimation(int startId, int animId, const XmlNode *animNode);
  void parseShapeGroups(Map &map, int tileId, const XmlNode *objGroupNode);
  void parseLayerData(TileLayer &layer, const XmlNode *dataNode);
  void parseLayers(Map &map, const XmlNode *mapNode);
  void parseProperties(MapObject &mapObj, const XmlNode *objNode);
  void readProperties(const MapObject &mapObj, PhysicObject &physObj) const;

  std::unique_ptr<XmlDoc> mXmlDoc;
  std::unique_ptr<char[]> mFileBytes; // The bytes should exist while parsing.
};

} // namespace ibrengine

#endif // TMXLOADER_HPP
