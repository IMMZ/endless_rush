// todo: license

#include "tmxloader.hpp"

#include "box.hpp"
#include "chainshape.hpp"
#include "circle.hpp"
#include "global.hpp"
#include "maploadexception.hpp"
#include "objectlayer.hpp"
#include "physicobject.hpp"
#include "polygonshape.hpp"
#include "tilelayer.hpp"
#include "tileset.hpp"
#include "utils.hpp"
#include "xmlparseexception.hpp"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <memory>
#include <iostream> // todo: remove
#include "animatableobject.hpp"
#include "drawableobject.hpp"

namespace ibrengine
{

std::unique_ptr<Map> TmxLoader::loadMap(const std::string &tmxPath)
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
  std::unique_ptr<Map> m(parseMap(mXmlDoc->first_node()));
  return m;
}

/*
 * Find out the shape type of object by it's xml structure.
 * Square and Circle have 'width' and 'height' attributes. Circle also has
 * '</ellipse>' subnode.
 * Polygon has 'polygon_points' subnode.
 * Polyline has 'poline_points' subnode.
 */
void TmxLoader::parseShapeGroup(PhysicObject::ShapeGroup &shapeGrp, const XmlNode *objectNode)
{
  if (objectNode == nullptr)
    return;

  // Getting information about xml structure.
  const XmlAttribute* widthAttr = objectNode->first_attribute("width");
  const XmlAttribute* heightAttr = objectNode->first_attribute("height");
  const XmlAttribute* gidAttr = objectNode->first_attribute("gid");
  const XmlAttribute *xAttr = objectNode->first_attribute("x");
  const XmlAttribute *yAttr = objectNode->first_attribute("y");

  const XmlNode* ellipseNode = objectNode->first_node("ellipse");
  const XmlNode* polylineNode = objectNode->first_node("polyline");
  const XmlNode* polygonNode = objectNode->first_node("polygon");

  // TODO: add support for polygon, edge and chain.
  std::shared_ptr<internal::Shape> shape;
  if (widthAttr != nullptr && heightAttr != nullptr) // Box/Circle.
  {
    if (ellipseNode != nullptr) // Circle.
    {
      if (strcmp(widthAttr->value(), heightAttr->value()) != 0)
        throw MapLoadException("The width and height of a circle are not equal.");

      shape = std::make_shared<internal::Circle>(utils::stdStringToNumber<float>(widthAttr->value()));
    }
    else // Box
    {
      shape = std::make_shared<internal::Box>(
          utils::stdStringToNumber<int>(widthAttr->value()),
          utils::stdStringToNumber<int>(heightAttr->value()));
    }
  }
  else if (polylineNode != nullptr) // Polyline
  {
    internal::ChainShape *chainShape = new internal::ChainShape;
    shape.reset(chainShape);
    std::vector<std::string> coordPairs;
    std::string strToParse(polylineNode->first_attribute("points")->value());
    utils::splitString(strToParse, ' ', false, coordPairs);
    for (const std::string &coordPair: coordPairs)
    {
      // TODO: extract
      std::vector<std::string> xy;
      utils::splitString(coordPair, ',', false, xy);
      Point p = std::make_pair(utils::stdStringToNumber<int>(xy[0]), utils::stdStringToNumber<int>(xy[1]));
      chainShape->addPoint(p);
    }
  }
  else if (polygonNode != nullptr) // Polygon
  {
    internal::PolygonShape *polyShape = new internal::PolygonShape;
    shape.reset(polyShape);
    std::vector<std::string> coordPairs;
    std::string strToParse(polygonNode->first_attribute("points")->value());
    utils::splitString(strToParse, ' ', false, coordPairs);
    for (const std::string &coordPair: coordPairs)
    {
      std::vector<std::string> xy;
      utils::splitString(coordPair, ',', false, xy);
      Point p = std::make_pair(utils::stdStringToNumber<int>(xy[0]), utils::stdStringToNumber<int>(xy[1]));
      polyShape->addPoint(p);
    }
  }

    shape->setPosition(
        std::make_pair(
            utils::stdStringToNumber<int>(xAttr->value()),
            utils::stdStringToNumber<int>(yAttr->value())));
    shapeGrp.push_back(shape);
}

Map* TmxLoader::parseMap(const XmlNode *mapNode)
{
  if (strcmp(mapNode->name(), "map") != 0)
    throw new MapLoadException("No 'map' node at the beggining of the file.");

  std::string mapVersion;
  Map::Orientation mapOrient = Map::Orientation::Orthogonal; // Default orientation.
  int mapW, mapH;
  int mapTileW, mapTileH;
  XmlAttribute *attr = mapNode->first_attribute();
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
      mapW = utils::stdStringToNumber<int>(attr->value());
    }
    else if (strcmp(attr->name(), "height") == 0)
    {
      mapH = utils::stdStringToNumber<int>(attr->value());
    }
    else if (strcmp(attr->name(), "tilewidth") == 0)
    {
      mapTileW = utils::stdStringToNumber<int>(attr->value());
    }
    else if (strcmp(attr->name(), "tileheight") == 0)
    {
      mapTileH = utils::stdStringToNumber<int>(attr->value());
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
TmxLoader::parseTileset(Map *map, const XmlNode *tilesetNode)
{::std::cout << "Parsing tileset..." << ::std::endl;
  if (strcmp(tilesetNode->name(), "tileset") != 0)
    throw new MapLoadException("Wrong tileset node");

  std::string name, imgSrc;
  sf::Color transparentColor;
  int firstTileId, imgW, imgH, tileW, tileH;

  XmlAttribute *attr = tilesetNode->first_attribute();
  while (attr != nullptr)
  {
    if (strcmp(attr->name(), "firstgid") == 0)
      firstTileId = utils::stdStringToNumber<int>(attr->value());
    else if (strcmp(attr->name(), "name") == 0)
      name = attr->value();
    else if (strcmp(attr->name(), "tilewidth") == 0)
      tileW = utils::stdStringToNumber<int>(attr->value());
    else if (strcmp(attr->name(), "tileheight") == 0)
      tileH = utils::stdStringToNumber<int>(attr->value());
    attr = attr->next_attribute();
  }

  ::std::cout << "  Name: " << name << ::std::endl;
  // Parsing image.
  XmlNode *imgNode = tilesetNode->first_node("image");
  XmlAttribute *imgAttr = imgNode->first_attribute();
  while (imgAttr != nullptr)
  {
    if (strcmp(imgAttr->name(), "source") == 0)
      imgSrc = utils::extractFilenameFromPath(imgAttr->value());
    else if (strcmp(imgAttr->name(), "trans") == 0)
      transparentColor = utils::hexColorToSFMLColor(imgAttr->value());
    else if (strcmp(imgAttr->name(), "width") == 0)
      imgW = utils::stdStringToNumber<int>(imgAttr->value());
    else if (strcmp(imgAttr->name(), "height") == 0)
      imgH = utils::stdStringToNumber<int>(imgAttr->value());
    imgAttr = imgAttr->next_attribute();
  }

  // Parsing animation.
  const XmlNode *tileNode = tilesetNode->first_node("tile");
  while (tileNode != nullptr)
  {
    int tileId = utils::stdStringToNumber<int>(tileNode->first_attribute("id")->value());
    // Parsing 'anim_id' property.
    int animId = -1;
    const XmlNode *propertiesNode = tileNode->first_node("properties");
    if (propertiesNode != nullptr)
    {
      const XmlNode *propertyNode = propertiesNode->first_node("property");
      while (propertyNode != nullptr)
      {
        if (strcmp(propertyNode->first_attribute("name")->value(), "anim_id") == 0)
        {
          animId = utils::stdStringToNumber<int>(propertyNode->first_attribute("value")->value());
          break;
        }
        else
        {
          propertyNode = propertyNode->next_sibling();
        }
      }
    }
    const XmlNode *animationNode = tileNode->first_node("animation");
    if (animationNode != nullptr)
      map->addAnimation(this->parseAnimation(firstTileId, animId, animationNode));

    // Parsing collision objects.
    const XmlNode *objsNode = tileNode->first_node("objectgroup");
    if (objsNode != nullptr)
      this->parsePhysAnim(*map, firstTileId + tileId, objsNode);

    tileNode = tileNode->next_sibling();
  }

  std::shared_ptr<Tileset> tSet =
    std::make_shared<Tileset>(name, imgSrc, imgW, imgH, firstTileId, tileW, tileH);
  if (transparentColor != sf::Color::Black)
    tSet->setTransparentColor(transparentColor);
  return tSet;
}

void TmxLoader::parseTilesets(Map *map, const XmlNode *mapNode)
{
  const XmlNode *tSetNode = mapNode->first_node("tileset");
  while (tSetNode != nullptr)
  {
    map->addTileset(this->parseTileset(map, tSetNode));
    tSetNode = tSetNode->next_sibling("tileset");
  }
}

Layer* TmxLoader::parseTileLayer(const XmlNode *layerNode)
{ // TODO: parse speed
  std::string name;
  int w, h;
  bool visible = true;
  float opacity = 1.0f;
  XmlAttribute *layerAttr = layerNode->first_attribute();
  while (layerAttr != nullptr)
  {
    if (strcmp(layerAttr->name(), "name") == 0)
      name = layerAttr->value();
    else if (strcmp(layerAttr->name(), "width") == 0)
      w = utils::stdStringToNumber<int>(layerAttr->value());
    else if (strcmp(layerAttr->name(), "height") == 0)
      h = utils::stdStringToNumber<int>(layerAttr->value());
    else if (strcmp(layerAttr->name(), "opacity") == 0)
      opacity = utils::stdStringToNumber<float>(layerAttr->value());
    else if (strcmp(layerAttr->name(), "visible") == 0
      && strcmp(layerAttr->value(), "0") == 0)
      visible = false;
    layerAttr = layerAttr->next_attribute();
  }
  TileLayer *layer = new TileLayer(name, w, h);
  const XmlNode *dataNode = layerNode->first_node("data");
  if (strcmp(dataNode->first_attribute("encoding")->value(), "csv") != 0)
    throw new MapLoadException("Wrong layer encoding. Only CSV is supported");
  this->parseLayerData(layer, dataNode);
  layer->setVisible(visible);
  layer->setOpacity(opacity);
  return layer;
}

Layer* TmxLoader::parseObjectLayer(Map *map, const XmlNode *layerNode)
{// TODO: extract this
  std::string name;
  int w, h;
  bool visible = true;
  float opacity = 1.0f;
  XmlAttribute *layerAttr = layerNode->first_attribute();
  while (layerAttr != nullptr)
  {
    if (strcmp(layerAttr->name(), "name") == 0)
      name = layerAttr->value();
    else if (strcmp(layerAttr->name(), "width") == 0)
      w = utils::stdStringToNumber<int>(layerAttr->value());
    else if (strcmp(layerAttr->name(), "height") == 0)
      h = utils::stdStringToNumber<int>(layerAttr->value());
    else if (strcmp(layerAttr->name(), "opacity") == 0)
      opacity = utils::stdStringToNumber<float>(layerAttr->value());
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

void TmxLoader::parseObjects(Map *map, ObjectLayer *layer, const XmlNode *layerNode)
{
  XmlNode *objNode = layerNode->first_node("object");
  while (objNode != nullptr)
  {
    this->parseObject(map, layer, objNode);
    objNode = objNode->next_sibling("object");
  }
}

void TmxLoader::readProperties(const MapObject &mapObj, PhysicObject *physObj) const
{
  // At first finding out a type to create an object.
  if (mapObj.hasProperty("bodyType"))
  {
    sf::String bodyTypeStr = mapObj.getProperty("bodyType");
    if (bodyTypeStr == "kinematic")
      physObj->setType(PhysicObject::Type::Kinematic);
    else if (bodyTypeStr == "dynamic")
      physObj->setType(PhysicObject::Type::Dynamic);
  }

  for (auto i = mapObj.propertiesBegin(); i != mapObj.propertiesEnd(); ++i)
  {
    if (i->first == "active")
      physObj->setActive(utils::stringToBool(i->second));
    else
    if (i->first == "allowSleep")
      physObj->setAllowSleep(utils::stringToBool(i->second));
    else
    if (i->first == "awake")
      physObj->setAwake(utils::stringToBool(i->second));
    else
    if (i->first == "bullet")
      physObj->setBullet(utils::stringToBool(i->second));
    else
    if (i->first == "fixedRotation")
      physObj->setFixedRotation(utils::stringToBool(i->second));
    else
    if (i->first == "angle")
      physObj->setAngle(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "angularDamping")
      physObj->setAngularDamping(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "angularVelocity")
      physObj->setAngularVelocity(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "gravityScale")
      physObj->setGravityScale(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "linearDamping")
      physObj->setLinearDamping(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "linearVelocity")
    {
      LinearVelocity linVel;
      utils::sfStringToVector2d<float>(i->second, linVel);
      physObj->setLinearVelocity(linVel);
    }
    else
    if (i->first == "density")
      physObj->setDensity(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "friction")
      physObj->setFriction(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "sensor")
      physObj->setSensor(utils::stringToBool(i->second));
    else
    if (i->first == "restitution")
      physObj->setRestitution(utils::stdStringToNumber<float>(i->second));
  }
}

/* TODO: Maybe we can create the object from Object::Type flags?
 * 1) Create a flags from custom properties.
 * 2) Pass them to something 'this->createObjects(flags);'
 */
void TmxLoader::parseObject(Map *map, ObjectLayer *layer, const XmlNode *objNode)
{
  // All objects have name and position so we can parse them at first.
  sf::String name, type;
  XmlAttribute *nameAttr = objNode->first_attribute("name");
  XmlAttribute *typeAttr = objNode->first_attribute("type");
  XmlAttribute *xAttr = objNode->first_attribute("x");
  XmlAttribute *yAttr = objNode->first_attribute("y");
  if (nameAttr != nullptr)
    name = nameAttr->value();
  std::string std_name = name.toAnsiString();
  if (typeAttr != nullptr)
    type = typeAttr->value();

  // Setting visibility.
  bool visible = true;
  const XmlAttribute *visibleAttr = objNode->first_attribute("visible");
  if (visibleAttr != nullptr && utils::stdStringToNumber<int>(visibleAttr->value()) == 0)
    visible = false;

  PositionI pos = std::make_pair(
    utils::stdStringToNumber<int>(xAttr->value()),
    utils::stdStringToNumber<int>(yAttr->value()));

  const XmlAttribute *gidAttr = objNode->first_attribute("gid");
  MapObject *mapObj = new MapObject(name);
  mapObj->setVisible(visible);
  this->parseProperties(mapObj, objNode); // TODO: better to accept MapObject&?

  // Getting the type of the object.
  bool drawable = (gidAttr != nullptr);
  bool physical = mapObj->hasProperty("physical") ?
    utils::stringToBool(mapObj->getProperty("physical")) :
    false;
  bool animatable = mapObj->hasProperty("animatable") ?
    utils::stringToBool(mapObj->getProperty("animatable")) :
    false;

  const XmlAttribute *wAttr = objNode->first_attribute("width");
  const XmlAttribute *hAttr = objNode->first_attribute("height");
  if (wAttr != nullptr && hAttr != nullptr) // Physical/DrawableObject
  {
    int w = utils::stdStringToNumber<int>(wAttr->value());
    int h = utils::stdStringToNumber<int>(hAttr->value());

    if (drawable) // DrawableObject/AnimatableObject
    {
      // Create drawable part.
      int gid = utils::stdStringToNumber<int>(gidAttr->value());
      DrawableObject *drawObj = new DrawableObject(*mapObj);
      drawObj->setTileId(gid);
      drawObj->setPosition(pos);
      drawObj->setSize(std::make_pair(w, h));

      if (animatable)
      {
        AnimatableObject *animObj = new AnimatableObject(name, *mapObj, gid);
        animObj->mMap = map;
        for (auto i = mapObj->propertiesBegin(); i != mapObj->propertiesEnd(); ++i)
        {
          if (i->first.find("anim_") == 0) // property name starts with 'anim'
          {
            int animId = utils::stdStringToNumber<int>(i->second.toAnsiString());
            animObj->addAnimation(i->first, map->getAnimation(animId));
          }
        }
        animObj->setPosition(pos);
        animObj->setSize(std::make_pair(w, h));
      }

      // Create physical part.
      if (physical)
      {
        PhysicObject *physObj = new PhysicObject(*mapObj);
        physObj->setPosition(pos);
        physObj->setSize(std::make_pair(w, h));
        PhysicObject::ShapeGroup sg = map->getShapeGroup(gid);
        physObj->setShapeGroup(map->getShapeGroup(gid));
        readProperties(*mapObj, physObj);
      }
    }
    else
    {
      PhysicObject *physObj = new PhysicObject(*mapObj);
      physObj->setPosition(pos);
      PhysicObject::ShapeGroup shapeGrp; parseShapeGroup(shapeGrp, objNode);
      physObj->setShapeGroup(shapeGrp);
      readProperties(*mapObj, physObj);
    }
  }
  else // PhysicalObject
  {
    PhysicObject *physObj = new PhysicObject(*mapObj);
    physObj->setPosition(pos);
    PhysicObject::ShapeGroup shapeGrp; parseShapeGroup(shapeGrp, objNode);
    physObj->setShapeGroup(shapeGrp);
    readProperties(*mapObj, physObj);
  }
  mapObj->addToLayer(*layer);
  layer->addMapObject(std::shared_ptr<MapObject>(mapObj));
}

std::unique_ptr<Animation>
TmxLoader::parseAnimation(int startId, int animId,
  const XmlNode *animNode)
{
  auto anim = internal::make_unique<Animation>(animId);
  const XmlNode *frameNode = animNode->first_node("frame");
  while (frameNode != nullptr)
  {
    int tileId = startId
      + utils::stdStringToNumber<int>(frameNode->first_attribute("tileid")->value());
    int duration = utils::stdStringToNumber<int>(frameNode->first_attribute("duration")->value());
    anim->addFrame(tileId, duration);
    frameNode = frameNode->next_sibling("frame");
  }
  return std::move(anim);
}

void TmxLoader::parsePhysAnim(Map &map, int tileId, const XmlNode *objGroupNode)
{
  const XmlNode *objNode = objGroupNode->first_node("object");
  PhysicObject::ShapeGroup objGroup;
  while (objNode != nullptr)
  {
    this->parseShapeGroup(objGroup, objNode);
    objNode = objNode->next_sibling("object");
    if (!objGroup.empty())
    {
      map.addShapeGroup(tileId, objGroup);
      ::std::cout << "Added shapegroup to the map with id: " << tileId << ::std::endl;
    }
  }
}

void TmxLoader::parseLayerData(TileLayer *layer,
  const XmlNode *dataNode)
{
  const std::string dataStr(dataNode->value());
  std::vector<std::string> tileIdsVector;
  utils::splitString(dataStr, ',', false, tileIdsVector);
  if (tileIdsVector.size() != (layer->getH() * layer->getW()))
    throw new MapLoadException("Invalid tile data");

  int i = 0, j = 0;
  for (std::string &tileIdStr: tileIdsVector)
  {
    layer->setTileId(i, j, utils::stdStringToNumber<int>(tileIdStr));
    i++;
    if (i == layer->getW()) { i = 0; j++; }
  }
}

void TmxLoader::parseLayers(Map *map, const XmlNode *mapNode)
{
  const XmlNode *innerNode = mapNode->first_node();
  while (innerNode != nullptr)
  {
    if (strcmp(innerNode->name(), "layer") == 0)
      map->addLayer(this->parseTileLayer(innerNode));
    else if (strcmp(innerNode->name(), "objectgroup") == 0)
      map->addLayer(this->parseObjectLayer(map, innerNode));
    innerNode = innerNode->next_sibling();
  }
}

void TmxLoader::parseProperties(MapObject *mapObj, const XmlNode *objNode)
{
  const XmlNode *propsNode = objNode->first_node("properties");
  if (propsNode == nullptr)
    return;
  const XmlNode *propNode = propsNode->first_node("property");
  while (propNode != nullptr)
  {
    mapObj->addProperty(
      propNode->first_attribute("name")->value(),
      propNode->first_attribute("value")->value());
    propNode = propNode->next_sibling("property");
  }
}

} // namespace ibrengine
