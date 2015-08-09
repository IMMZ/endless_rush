// todo: license

#include "tmxloader.hpp"

#include "animatableobject.hpp"
#include "complexshape.hpp"
#include "map.hpp"
#include "maploadexception.hpp"
#include "objectlayer.hpp"
#include "simpleshape.hpp"
#include "tilelayer.hpp"
#include "tileobject.hpp"
#include "tileset.hpp"
#include "utils.hpp"
#include "xmlparseexception.hpp"

#include <cstring>
#include <fstream>
#include <memory>
#include <iostream> // todo: remove

namespace ibrengine
{

Map* TmxLoader::loadMap(const std::string &tmxPath)
{
  std::ifstream tmxFile(tmxPath);
  if (tmxFile.is_open())
  {
    tmxFile.seekg(0, tmxFile.end);
    int fileSize = tmxFile.tellg();
    tmxFile.seekg(0, tmxFile.beg);
    mFileBytes.reset(new char[fileSize + 1]);
    mFileBytes[fileSize] = '\0';
    tmxFile.read(mFileBytes.get(), fileSize);
    tmxFile.close();
    mXmlDoc.reset(new rapidxml::xml_document<char>());
  }
  try
  {
    mXmlDoc->parse<rapidxml::parse_default>(mFileBytes.get());
  }
  catch (rapidxml::parse_error &exc)
  {
    throw new XmlParseException(exc.what(), exc.where<char>());
  }
  return parseMap(mXmlDoc->first_node());
}

Map* TmxLoader::parseMap(const rapidxml::xml_node<char> *mapNode)
{
  if (strcmp(mapNode->name(), "map") != 0)
    throw new MapLoadException("No 'map' node at the beggining of the file.");

  std::string mapVersion;
  Map::Orientation mapOrient = Map::Orientation::Orthogonal; // Default orientation.
  int mapW, mapH;
  int mapTileW, mapTileH;
  rapidxml::xml_attribute<char> *attr = mapNode->first_attribute();
  while (attr != nullptr)
  {
    if (strcmp(attr->name(), "version") == 0)
      mapVersion = attr->value();
    else if (strcmp(attr->name(), "orientation") == 0)
    {
      std::string orientStr(attr->value());
      if (orientStr == "orthogonal")
        mapOrient = Map::Orientation::Orthogonal;
      else if (orientStr == "isometric")
        mapOrient = Map::Orientation::Isometric;
      else if (orientStr == "hexagonal")
        mapOrient = Map::Orientation::Hexagonal;
      else
        throw new MapLoadException("Unknown orientation type");
    }
    else if (strcmp(attr->name(), "width") == 0)
    {
      mapW = utils::stdStringToInt(attr->value());
    }
    else if (strcmp(attr->name(), "height") == 0)
    {
      mapH = utils::stdStringToInt(attr->value());
    }
    else if (strcmp(attr->name(), "tilewidth") == 0)
    {
      mapTileW = utils::stdStringToInt(attr->value());
    }
    else if (strcmp(attr->name(), "tileheight") == 0)
    {
      mapTileH = utils::stdStringToInt(attr->value());
    }
    attr = attr->next_attribute();
  }
  Map *map = new Map(mapW, mapH, mapTileW, mapTileH);
  map->setVersion(mapVersion);
  map->setOrientation(mapOrient);
  // TODO: parse map name and author
  this->parseTilesets(map, mapNode);
  this->parseLayers(map, mapNode);
  return map;
}

std::shared_ptr<Tileset>
TmxLoader::parseTileset(Map *map, const rapidxml::xml_node<char> *tilesetNode)
{
  if (strcmp(tilesetNode->name(), "tileset") != 0)
    throw new MapLoadException("Wrong tileset node");

  std::string name, imgSrc;
  sf::Color transparentColor;
  int firstTileId, imgW, imgH, tileW, tileH;

  rapidxml::xml_attribute<char> *attr = tilesetNode->first_attribute();
  while (attr != nullptr)
  {
    if (strcmp(attr->name(), "firstgid") == 0)
      firstTileId = utils::stdStringToInt(attr->value());
    else if (strcmp(attr->name(), "name") == 0)
      name = attr->value();
    else if (strcmp(attr->name(), "tilewidth") == 0)
      tileW = utils::stdStringToInt(attr->value());
    else if (strcmp(attr->name(), "tileheight") == 0)
      tileH = utils::stdStringToInt(attr->value());
    attr = attr->next_attribute();
  }

  // Parsing image.
  rapidxml::xml_node<char> *imgNode = tilesetNode->first_node("image");
  rapidxml::xml_attribute<char> *imgAttr = imgNode->first_attribute();
  while (imgAttr != nullptr)
  {
    if (strcmp(imgAttr->name(), "source") == 0)
      imgSrc = utils::extractFilenameFromPath(imgAttr->value());
    else if (strcmp(imgAttr->name(), "trans") == 0)
      transparentColor = utils::hexColorToSFMLColor(imgAttr->value());
    else if (strcmp(imgAttr->name(), "width") == 0)
      imgW = utils::stdStringToInt(imgAttr->value());
    else if (strcmp(imgAttr->name(), "height") == 0)
      imgH = utils::stdStringToInt(imgAttr->value());
    imgAttr = imgAttr->next_attribute();
  }

  // Parsing animation.
  const rapidxml::xml_node<char> *tileNode = tilesetNode->first_node("tile");
  if (tileNode != nullptr)
  {
    int tileId = utils::stdStringToInt(tileNode->first_attribute("id")->value());
    // Parsing 'anim_id' property.
    int animId = -1;
    const rapidxml::xml_node<char> *propertiesNode = tileNode->first_node("properties");
    if (propertiesNode != nullptr)
    {
      const rapidxml::xml_node<char> *propertyNode = propertiesNode->first_node("property");
      if (propertiesNode != nullptr)
        animId = utils::stdStringToInt(propertyNode->first_attribute("value")->value());
    }
    const rapidxml::xml_node<char> *animationNode = tileNode->first_node("animation");
    if (animationNode != nullptr)
      map->addAnimation(this->parseAnimation(firstTileId, animId, animationNode));

    // Parsing collision objects.
    const rapidxml::xml_node<char> *objsNode = tileNode->first_node("objectgroup");
    if (objsNode != nullptr)
    {
      const rapidxml::xml_node<char> *objNode = objsNode->first_node("object");
      while (objNode != nullptr)
      {
        // TODO add it somewhere this->parseObject(objNode));
        objNode = objNode->next_sibling("object");
      }
    }
  }

  std::shared_ptr<Tileset> tSet =
    std::make_shared<Tileset>(name, imgSrc, imgW, imgH, firstTileId, tileW, tileH);
  if (transparentColor != sf::Color::Black)
    tSet->setTransparentColor(transparentColor);
  return tSet;
}

void TmxLoader::parseTilesets(Map *map, const rapidxml::xml_node<char> *mapNode)
{
  const rapidxml::xml_node<char> *tSetNode = mapNode->first_node("tileset");
  while (tSetNode != nullptr)
  {
    map->addTileset(this->parseTileset(map, tSetNode));
    tSetNode = tSetNode->next_sibling("tileset");
  }
}

Layer* TmxLoader::parseTileLayer(const rapidxml::xml_node<char> *layerNode)
{ // TODO: parse speed
  std::string name;
  int w, h;
  bool visible = true;
  float opacity = 1.0f;
  rapidxml::xml_attribute<char> *layerAttr = layerNode->first_attribute();
  while (layerAttr != nullptr)
  {
    if (strcmp(layerAttr->name(), "name") == 0)
      name = layerAttr->value();
    else if (strcmp(layerAttr->name(), "width") == 0)
      w = utils::stdStringToInt(layerAttr->value());
    else if (strcmp(layerAttr->name(), "height") == 0)
      h = utils::stdStringToInt(layerAttr->value());
    else if (strcmp(layerAttr->name(), "opacity") == 0)
      opacity = utils::stdStringToFloat(layerAttr->value());
    else if (strcmp(layerAttr->name(), "visible") == 0
      && strcmp(layerAttr->value(), "0") == 0)
      visible = false;
    layerAttr = layerAttr->next_attribute();
  }
  TileLayer *layer = new TileLayer(name, w, h);
  const rapidxml::xml_node<char> *dataNode = layerNode->first_node("data");
  if (strcmp(dataNode->first_attribute("encoding")->value(), "csv") != 0)
    throw new MapLoadException("Wrong layer encoding. Only CSV is supported");
  this->parseLayerData(layer, dataNode);
  layer->setVisible(visible);
  layer->setOpacity(opacity);
  return layer;
}

Layer* TmxLoader::parseObjectLayer(Map *map, const rapidxml::xml_node<char> *layerNode)
{// TODO: extract this
  std::string name;
  int w, h;
  bool visible = true;
  float opacity = 1.0f;
  rapidxml::xml_attribute<char> *layerAttr = layerNode->first_attribute();
  while (layerAttr != nullptr)
  {
    if (strcmp(layerAttr->name(), "name") == 0)
      name = layerAttr->value();
    else if (strcmp(layerAttr->name(), "width") == 0)
      w = utils::stdStringToInt(layerAttr->value());
    else if (strcmp(layerAttr->name(), "height") == 0)
      h = utils::stdStringToInt(layerAttr->value());
    else if (strcmp(layerAttr->name(), "opacity") == 0)
      opacity = utils::stdStringToFloat(layerAttr->value());
    else if (strcmp(layerAttr->name(), "visible") == 0
      && strcmp(layerAttr->value(), "0") == 0)
      visible = false;
    layerAttr = layerAttr->next_attribute();
  }
  ObjectLayer *layer = new ObjectLayer(name, w, h);
  this->parseObjects(map, layer, layerNode);
  layer->setVisible(visible);
  layer->setOpacity(opacity);
  return layer;
}

void TmxLoader::parseObjects(Map *map, ObjectLayer *layer,
  const rapidxml::xml_node<char> *layerNode)
{
  rapidxml::xml_node<char> *objNode = layerNode->first_node("object");
  while (objNode != nullptr)
  {
    layer->addObject(this->parseObject(map, objNode));
    objNode = objNode->next_sibling("object");
  }
}

std::unique_ptr<MapObject>
TmxLoader::parseObject(Map *map, const rapidxml::xml_node<char> *objNode)
{
  // All objects have name and position so we can parse them at first.
  sf::String name, type; sf::Vector2i pos; bool visible = true;
  rapidxml::xml_attribute<char> *nameAttr = objNode->first_attribute("name");
  rapidxml::xml_attribute<char> *typeAttr = objNode->first_attribute("type");
  rapidxml::xml_attribute<char> *xAttr = objNode->first_attribute("x");
  rapidxml::xml_attribute<char> *yAttr = objNode->first_attribute("y");
  if (nameAttr != nullptr)
    name = nameAttr->value();
  if (typeAttr != nullptr)
    type = typeAttr->value();
  pos.x = utils::stdStringToInt(xAttr->value());
  pos.y = utils::stdStringToInt(yAttr->value());

  /*
   * Find out the type of object by it's xml structure.
   * Square and Circle have 'width' and 'height' attributes. Circle also has
   * '</ellipse>' subnode.
   * Polygon has 'polygon_points' subnode.
   * Polyline has 'poline_points' subnode.
   */
  rapidxml::xml_attribute<char> *wAttr = objNode->first_attribute("width");
  rapidxml::xml_attribute<char> *hAttr = objNode->first_attribute("height"); // TODO: make const
  const rapidxml::xml_attribute<char> *gidAttr = objNode->first_attribute("gid");
  if (wAttr != nullptr && hAttr != nullptr) // Square/Circle/TileObject/AnimatableObject.
  {
    if (gidAttr != nullptr) // TileObject/AnimatableObject
    {
      int w = utils::stdStringToInt(wAttr->value());
      int h = utils::stdStringToInt(hAttr->value());
      int gid = utils::stdStringToInt(gidAttr->value());
      if (type == "animatable") // AnimatableObject
      {
        std::unique_ptr<AnimatableObject> animObj(new AnimatableObject(name, gid));
        this->parseProperties(animObj.get(), objNode); // TODO: EXTRACT
        AnimatableObject::PropertyConstIterator i = animObj->propertiesBegin();
        while (i != animObj->propertiesEnd())
        {
          if (i->first.find("anim_") == 0) // property name starts with 'anim'
          {
            int animId = utils::stdStringToInt(i->second.toAnsiString());
            animObj->addAnimation(i->first, map->getAnimation(animId));
          }
          ++i;
        }
        animObj->setPosition(pos);
        animObj->setSize(sf::Vector2i(w, h));
        return std::move(animObj);
      }
      std::unique_ptr<TileObject> tileObj(new TileObject(name, gid));
      this->parseProperties(tileObj.get(), objNode); // TODO: EXTRACT
      tileObj->setPosition(pos);
      tileObj->setSize(sf::Vector2i(w, h));
      return std::move(tileObj);
    }
    SimpleShape::Type shapeType = SimpleShape::Type::Square;
    int w = utils::stdStringToInt(wAttr->value());
    int h = utils::stdStringToInt(hAttr->value());
    if (objNode->first_node("ellipse") != nullptr)
      shapeType = SimpleShape::Type::Circle;
    std::unique_ptr<SimpleShape> shape(new SimpleShape(name, shapeType));
    this->parseProperties(shape.get(), objNode); // TODO: EXTRACT
    shape->setPosition(pos);
    shape->setSize(sf::Vector2i(w, h));
    shape->setType(type);
    return std::move(shape);
  }

  rapidxml::xml_node<char> *objInnerNode = objNode->first_node("polygon");
  ComplexShape::Type shapeType = ComplexShape::Type::Polygon;
  if (objInnerNode == nullptr)
  {
    objInnerNode = objNode->first_node("polyline");
    shapeType = ComplexShape::Type::Polyline;
  }
  std::unique_ptr<ComplexShape> shape(new ComplexShape(name, shapeType));
  this->parseProperties(shape.get(), objNode);
  this->parsePoints(objInnerNode, shape.get());
  shape->setType(type);
  return std::move(shape);
}

std::unique_ptr<Animation>
TmxLoader::parseAnimation(int startId, int animId,
  const rapidxml::xml_node<char> *animNode)
{
  std::unique_ptr<Animation> anim(new Animation(animId));
  const rapidxml::xml_node<char> *frameNode = animNode->first_node("frame");
  while (frameNode != nullptr)
  {
    int tileId = startId
      + utils::stdStringToInt(frameNode->first_attribute("tileid")->value());
    int duration = utils::stdStringToInt(frameNode->first_attribute("duration")->value());
    anim->addFrame(tileId, duration);
    frameNode = frameNode->next_sibling("frame");
  }
  return std::move(anim);
}

void TmxLoader::parsePoints(const rapidxml::xml_node<char> *polygonNode,
  ComplexShape *shape)
{
  std::vector<std::string> coordPairs;
  std::string strToParse(polygonNode->first_attribute("points")->value());
  utils::splitString(strToParse, ' ', false, coordPairs);
  for (const std::string &coordPair: coordPairs)
  {
    sf::Vector2i point;
    std::vector<std::string> xy;
    utils::splitString(coordPair, ',', false, xy);
    point.x = utils::stdStringToInt(xy[0]);
    point.y = utils::stdStringToInt(xy[1]);
    shape->addPoint(point);
    std::cout << "parsed point " << point.x << ", " << point.y << std::endl;
  }
}

void TmxLoader::parseLayerData(TileLayer *layer,
  const rapidxml::xml_node<char> *dataNode)
{
  std::string dataStr(dataNode->value());
  std::vector<std::string> tileIdsVector;
  utils::splitString(dataStr, ',', false, tileIdsVector);
  if (tileIdsVector.size() != (layer->getH() * layer->getW()))
    throw new MapLoadException("Invalid tile data");

  int i = 0, j = 0;
  for (std::string &tileIdStr: tileIdsVector)
  {
    layer->setTileId(i, j, utils::stdStringToInt(tileIdStr));
    i++;
    if (i == layer->getW())
    {
      i = 0; j++;
    }
  }
}

void TmxLoader::parseLayers(Map *map, const rapidxml::xml_node<char> *mapNode)
{
  rapidxml::xml_node<char> *innerNode = mapNode->first_node();
  while (innerNode != nullptr)
  {
    if (strcmp(innerNode->name(), "layer") == 0)
      map->addLayer(this->parseTileLayer(innerNode));
    else if (strcmp(innerNode->name(), "objectgroup") == 0)
      map->addLayer(this->parseObjectLayer(map, innerNode));
    innerNode = innerNode->next_sibling();
  }
}

void TmxLoader::parseProperties(MapObject *mapObj, const rapidxml::xml_node<char> *objNode)
{
  const rapidxml::xml_node<char> *propsNode = objNode->first_node("properties");
  if (propsNode == nullptr)
    return;
  const rapidxml::xml_node<char> *propNode = propsNode->first_node("property");
  while (propNode != nullptr)
  {
    mapObj->addProperty(
      propNode->first_attribute("name")->value(),
      propNode->first_attribute("value")->value());
    propNode = propNode->next_sibling("property");
  }
}

} // namespace ibrengine
