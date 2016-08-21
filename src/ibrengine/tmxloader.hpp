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
  std::unique_ptr<Map> loadMap(const std::string &tmxPath);

private:
  using XmlNode = rapidxml::xml_node<char>;
  using XmlAttribute = rapidxml::xml_attribute<char>;

  void parseShapeGroup(PhysicObject::ShapeGroup &shapeGrp, const XmlNode *objectNode); // TODO: parseShape rename
  Map* parseMap(const XmlNode *mapNode);
  std::shared_ptr<Tileset>
  parseTileset(Map *map, const XmlNode *tilesetNode);
  void parseTilesets(Map *map, const XmlNode *mapNode);
  Layer* parseImageLayer(const XmlNode *layerNode);
  Layer* parseTileLayer(const XmlNode *layerNode);
  Layer* parseObjectLayer(Map *map, const XmlNode *layerNode);
  void parseObjects(Map *map, ObjectLayer *layer, const XmlNode *layerNode);
  void parseObject(Map *map, ObjectLayer *layer, const XmlNode *objNode);
  std::unique_ptr<Animation>
  parseAnimation(int startId, int animId, const XmlNode *animNode);
  void parsePhysAnim(Map &map, int tileId, const XmlNode *objGroupNode); // TODO: rename parseShapeGroups
  void parseLayerData(TileLayer *layer, const XmlNode *dataNode);
  void parseLayers(Map *map, const XmlNode *mapNode);
  void parseProperties(const MapUnitPtr &mapObj, const XmlNode *objNode);
  void readProperties(const MapObject &mapObj, PhysicObject* physObj) const;

  std::unique_ptr<rapidxml::xml_document<char>> mXmlDoc;
  std::unique_ptr<char[]> mFileBytes; // The bytes should exist while parsing.
};

} // namespace ibrengine

#endif // TMXLOADER_HPP
