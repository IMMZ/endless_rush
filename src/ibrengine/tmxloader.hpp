// todo: license

#ifndef TMXLOADER_HPP
#define TMXLOADER_HPP

#include "animation.hpp"
#include "mapobject.hpp"

#include <rapidxml.hpp>

#include <memory>
#include <string>

namespace ibrengine
{

class ComplexShape;
class Layer;
class Map;
class ObjectLayer;
class TileLayer;
class Tileset;

class TmxLoader
{
public:
  Map* loadMap(const std::string &tmxPath);

private:
  Map* parseMap(const rapidxml::xml_node<char> *mapNode);
  std::shared_ptr<Tileset>
  parseTileset(Map *map, const rapidxml::xml_node<char> *tilesetNode);
  void parseTilesets(Map *map, const rapidxml::xml_node<char> *mapNode);
  Layer* parseTileLayer(const rapidxml::xml_node<char> *layerNode);
  Layer* parseObjectLayer(Map *map, const rapidxml::xml_node<char> *layerNode);
  void parseObjects(Map *map, ObjectLayer *layer, const rapidxml::xml_node<char> *layerNode);
  std::unique_ptr<MapObject> parseObject(Map *map, const rapidxml::xml_node<char> *objNode);
  std::unique_ptr<Animation>
  parseAnimation(int startId, int animId, const rapidxml::xml_node<char> *animNode);
  void parsePoints(const rapidxml::xml_node<char> *polygonNode, ComplexShape *shape);
  void parseLayerData(TileLayer *layer, const rapidxml::xml_node<char> *dataNode);
  void parseLayers(Map *map, const rapidxml::xml_node<char> *mapNode);
  void parseProperties(MapObject *mapObj, const rapidxml::xml_node<char> *objNode);

  std::unique_ptr<rapidxml::xml_document<char>> mXmlDoc;
  std::unique_ptr<char[]> mFileBytes; // The bytes should exist while parsing.
};

} // namespace ibrengine

#endif // TMXLOADER_HPP
