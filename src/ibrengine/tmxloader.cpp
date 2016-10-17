// todo: license

#include "tmxloader.hpp"

#include "box.hpp"
#include "chainshape.hpp"
#include "circle.hpp"
#include "global.hpp"
#include "imagelayer.hpp"
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

template <typename T>
struct IsPointContainer
{
  static constexpr bool Value = false;
};

template <>
struct IsPointContainer<internal::ChainShape>
{
  static constexpr bool Value = true;
};

template <>
struct IsPointContainer<internal::PolygonShape>
{
  static constexpr bool Value = true;
};

template <typename T>
void parsePointContainer(internal::ShapeSharedPtr &shape, const TmxLoader::XmlNode *xmlNode)
{
  static_assert(IsPointContainer<T>::Value, "Type is not a point container");
  T *chainShape = new T;
  shape.reset(chainShape);
  std::string strToParse(xmlNode->first_attribute("points")->value());
  std::vector<std::string> coordPairs = utils::splitString(strToParse, ' ', false);
  for (const std::string &coordPair: coordPairs)
  {
    std::vector<std::string> xy = utils::splitString(coordPair, ',', false);
    chainShape->addPoint(
        std::make_pair(
            utils::stdStringToNumber<int>(xy[0]),
            utils::stdStringToNumber<int>(xy[1])));
  }
}

MapUniquePtr TmxLoader::loadMap(const std::string &tmxPath)
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
    mXmlDoc.reset(new XmlDoc);
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

/*
 * Find out the shape type of object by it's xml structure.
 * Square and Circle have 'width' and 'height' attributes. Circle also has
 * '</ellipse>' subnode.
 * Polygon has 'polygon_points' subnode.
 * Polyline has 'polyline_points' subnode.
 */
PhysicObject::ShapeGroup
TmxLoader::parseShapeGroup(const XmlNode *objectNode, TileLinkage tileLinkage)
{
  PhysicObject::ShapeGroup shapeGrp;
  if (objectNode == nullptr)
    return std::move(shapeGrp);

  // Getting information about xml structure.
  const XmlAttribute *widthAttr = objectNode->first_attribute("width");
  const XmlAttribute *heightAttr = objectNode->first_attribute("height");
  const XmlAttribute *gidAttr = objectNode->first_attribute("gid");
  const XmlAttribute *xAttr = objectNode->first_attribute("x");
  const XmlAttribute *yAttr = objectNode->first_attribute("y");

  const XmlNode *ellipseNode = objectNode->first_node("ellipse");
  const XmlNode *polylineNode = objectNode->first_node("polyline");
  const XmlNode *polygonNode = objectNode->first_node("polygon");

  // TODO: add support for polygon, edge and chain.
  internal::ShapeSharedPtr shape;
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
    parsePointContainer<internal::ChainShape>(shape, polylineNode);
  }
  else if (polygonNode != nullptr) // Polygon
  {
    parsePointContainer<internal::PolygonShape>(shape, polygonNode);
  }

  shape->setPosition(
    std::make_pair(
      utils::stdStringToNumber<int>(xAttr->value()),
      utils::stdStringToNumber<int>(yAttr->value())));
  shape->setLinkedToTile(tileLinkage == TileLinkage::LinkedToTiled ? true : false);
  shapeGrp.push_back(shape);
  return std::move(shapeGrp);
}

MapUniquePtr TmxLoader::parseMap(const XmlNode *mapNode)
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
  MapUniquePtr map = internal::make_unique<Map>(mapW, mapH, mapTileW, mapTileH);
  map->setVersion(mapVersion);
  map->setOrientation(mapOrient);
  // TODO: parse map name and author
  this->parseTilesets(*map, mapNode);
  this->parseLayers(*map, mapNode);
  return std::move(map);
}

TilesetUniquePtr
TmxLoader::parseTileset(Map &map, const XmlNode *tilesetNode)
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
  const XmlNode *imgNode = tilesetNode->first_node("image");
  const XmlAttribute *imgAttr = imgNode->first_attribute();
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
    const int tileId = utils::stdStringToNumber<int>(tileNode->first_attribute("id")->value());
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
      map.addAnimation(this->parseAnimation(firstTileId, animId, animationNode));

    // Parsing collision objects.
    const XmlNode *objsNode = tileNode->first_node("objectgroup");
    if (objsNode != nullptr)
      parseShapeGroups(map, firstTileId + tileId, objsNode);

    tileNode = tileNode->next_sibling();
  }

  TilesetUniquePtr tSet =
    internal::make_unique<Tileset>(name, imgSrc, imgW, imgH, firstTileId, tileW, tileH);
  if (transparentColor != sf::Color::Black)
    tSet->setTransparentColor(transparentColor);
  return std::move(tSet);
}

void TmxLoader::parseTilesets(Map &map, const XmlNode *mapNode)
{
  const XmlNode *tSetNode = mapNode->first_node("tileset");
  while (tSetNode != nullptr)
  {
    map.addTileset(parseTileset(map, tSetNode));
    tSetNode = tSetNode->next_sibling("tileset");
  }
}

LayerUniquePtr TmxLoader::parseImageLayer(const XmlNode *layerNode)
{
  const XmlNode *imageNode = layerNode->first_node("image");
  XmlAttribute *layerAttr = layerNode->first_attribute();
  std::string layerName;
  float opacity = 1.0f;
  bool visible = true;

  while (layerAttr != nullptr)
  {
    if (strcmp(layerAttr->name(), "name") == 0)
      layerName = layerAttr->value();
    else if (strcmp(layerAttr->name(), "opacity") == 0)
      opacity = utils::stdStringToNumber<float>(layerAttr->value());
    else if (strcmp(layerAttr->name(), "visible") == 0 and strcmp(layerAttr->value(), "0") == 0)
      visible = false;
    layerAttr = layerAttr->next_attribute();
  }

  if (imageNode != nullptr)
  {
    std::string imgPath;
    int w = 0, h = 0;

    // Attributes
    XmlAttribute *imgAttr = imageNode->first_attribute();
    while (imgAttr != nullptr)
    {
      if (strcmp(imgAttr->name(), "source") == 0)
        imgPath = imgAttr->value();
      else if (strcmp(imgAttr->name(), "width") == 0)
        w = utils::stdStringToNumber<int>(imgAttr->value());
      else if (strcmp(imgAttr->name(), "heigth") == 0)
        h = utils::stdStringToNumber<int>(imgAttr->value());
      imgAttr = imgAttr->next_attribute();
    }

    ImageLayerUniquePtr imgLayer =
      internal::make_unique<ImageLayer>(layerName, w, h, imgPath);
    imgLayer->setVisible(visible);
    imgLayer->setOpacity(opacity);
    return std::move(imgLayer);
  }
  return nullptr;
}

LayerUniquePtr TmxLoader::parseTileLayer(const XmlNode *layerNode)
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
  TileLayerUniquePtr layer = internal::make_unique<TileLayer>(name, w, h);
  const XmlNode *dataNode = layerNode->first_node("data");
  if (strcmp(dataNode->first_attribute("encoding")->value(), "csv") != 0)
    throw new MapLoadException("Wrong layer encoding. Only CSV is supported");
  this->parseLayerData(*layer, dataNode);
  layer->setVisible(visible);
  layer->setOpacity(opacity);
  return std::move(layer);
}

LayerUniquePtr TmxLoader::parseObjectLayer(Map &map, const XmlNode *layerNode)
{// TODO: extract this
  std::string name;
  int w = 0, h = 0;
  bool visible = true;
  float opacity = 1.0f;
  const XmlAttribute *layerAttr = layerNode->first_attribute();
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
  ObjectLayerUniquePtr layer = internal::make_unique<ObjectLayer>(name, w, h);
  this->parseObjects(map, *layer, layerNode);
  layer->setVisible(visible);
  layer->setOpacity(opacity);
  return std::move(layer);
}

void TmxLoader::parseObjects(Map &map, ObjectLayer &layer, const XmlNode *layerNode)
{
  XmlNode *objNode = layerNode->first_node("object");
  while (objNode != nullptr)
  {
    this->parseObject(map, layer, objNode);
    objNode = objNode->next_sibling("object");
  }
}

void TmxLoader::readProperties(const MapObject &mapObj, PhysicObject &physObj) const
{
  // At first finding out a type to create an object.
  if (mapObj.hasProperty("bodyType"))
  {
    sf::String bodyTypeStr = mapObj.getProperty("bodyType");
    if (bodyTypeStr == "kinematic")
      physObj.setType(PhysicObject::Type::Kinematic);
    else if (bodyTypeStr == "dynamic")
      physObj.setType(PhysicObject::Type::Dynamic);
  }

  for (auto i = mapObj.propertiesBegin(); i != mapObj.propertiesEnd(); ++i)
  {
    if (i->first == "active")
      physObj.setActive(utils::stringToBool(i->second));
    else
    if (i->first == "allowSleep")
      physObj.setAllowSleep(utils::stringToBool(i->second));
    else
    if (i->first == "awake")
      physObj.setAwake(utils::stringToBool(i->second));
    else
    if (i->first == "bullet")
      physObj.setBullet(utils::stringToBool(i->second));
    else
    if (i->first == "fixedRotation")
      physObj.setFixedRotation(utils::stringToBool(i->second));
    else
    if (i->first == "angle")
      physObj.setAngle(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "angularDamping")
      physObj.setAngularDamping(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "angularVelocity")
      physObj.setAngularVelocity(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "gravityScale")
      physObj.setGravityScale(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "linearDamping")
      physObj.setLinearDamping(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "linearVelocity")
    {
      LinearVelocity linVel = utils::sfStringToVector2d<float>(i->second);
      physObj.setLinearVelocity(linVel);
    }
    else
    if (i->first == "density")
      physObj.setDensity(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "friction")
      physObj.setFriction(utils::stdStringToNumber<float>(i->second));
    else
    if (i->first == "sensor")
      physObj.setSensor(utils::stringToBool(i->second));
    else
    if (i->first == "restitution")
      physObj.setRestitution(utils::stdStringToNumber<float>(i->second));
  }
}

/* TODO: Maybe we can create the object from Object::Type flags?
 * 1) Create a flags from custom properties.
 * 2) Pass them to something 'this->createObjects(flags);'
 */
void TmxLoader::parseObject(Map &map, ObjectLayer &layer, const XmlNode *objNode)
{
  // All objects have name and position so we can parse them at first.
  const XmlAttribute *idAttr = objNode->first_attribute("id");
  const int id = utils::stdStringToNumber<int>(idAttr->value());
  sf::String name, type;
  const XmlAttribute *nameAttr = objNode->first_attribute("name");
  const XmlAttribute *typeAttr = objNode->first_attribute("type");
  const XmlAttribute *xAttr = objNode->first_attribute("x");
  const XmlAttribute *yAttr = objNode->first_attribute("y");
  if (nameAttr != nullptr)
    name = nameAttr->value();
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
  MapObjectSharedPtr pMapObj = std::make_shared<MapObject>(name, map);
  pMapObj->setVisible(visible);
  this->parseProperties(*pMapObj, objNode);

  // Getting the type of the object.
  bool drawable = (gidAttr != nullptr);
  bool physical = pMapObj->hasProperty("physical") ?
    utils::stringToBool(pMapObj->getProperty("physical")) :
    false;
  bool animatable = pMapObj->hasProperty("animatable") ?
    utils::stringToBool(pMapObj->getProperty("animatable")) :
    false;

  const XmlAttribute *wAttr = objNode->first_attribute("width");
  const XmlAttribute *hAttr = objNode->first_attribute("height");
  if (wAttr != nullptr && hAttr != nullptr) // Physical/DrawableObject
  {
    const int w = utils::stdStringToNumber<int>(wAttr->value());
    const int h = utils::stdStringToNumber<int>(hAttr->value());

    if (drawable) // DrawableObject/AnimatableObject
    {
      // Create drawable part.
      const int gid = utils::stdStringToNumber<int>(gidAttr->value());
      DrawableObject *drawObj = new DrawableObject(pMapObj, id);
      drawObj->setTileId(gid);

      /*
       * Tiled map editor uses bottom-left point as the base point,
       * when SFML draws based on top-left one. It means that we
       * should subtract the height of the object for all drawable objects.
       */
      PositionI newPos(pos); newPos.second -= h;
      drawObj->setPosition(newPos);
      drawObj->setSize(std::make_pair(w, h));
      layer.addObject(ObjectUniquePtr(drawObj));

      if (animatable)
      {
        AnimatableObjectUniquePtr animObj = internal::make_unique<AnimatableObject>(name, pMapObj, gid, id);
        for (auto i = pMapObj->propertiesBegin(); i != pMapObj->propertiesEnd(); ++i)
        {
          if (i->first.find("anim_") == 0) // property name starts with 'anim'
          {
            const int animId = utils::stdStringToNumber<int>(i->second.toAnsiString());
            animObj->addAnimation(i->first, &map.getAnimation(animId));
          }
        }
        animObj->setPosition(pos);
        animObj->setSize(std::make_pair(w, h));
        layer.addObject(std::move(animObj));
      }

      // Create physical part.
      if (physical)
      {
        PhysicObjectUniquePtr physObj = internal::make_unique<PhysicObject>(pMapObj, id);
        physObj->setPosition(pos);
        physObj->setSize(std::make_pair(w, h));
        physObj->setShapeGroup(map.getShapeGroup(gid));
        readProperties(*pMapObj, *physObj);
        layer.addObject(std::move(physObj));
      }
    }
  }
  if ((wAttr == nullptr || hAttr == nullptr) || !drawable) // PhysicalObject
  {
    PhysicObjectUniquePtr physObj = internal::make_unique<PhysicObject>(pMapObj, id);
    physObj->setPosition(pos);
    physObj->setShapeGroup(parseShapeGroup(objNode, TileLinkage::NotLinkedToTile));
    readProperties(*pMapObj, *physObj);
    layer.addObject(std::move(physObj));
  }
}

AnimationUniquePtr
TmxLoader::parseAnimation(int startId, int animId,
  const XmlNode *animNode)
{
  auto anim = internal::make_unique<Animation>(animId);
  const XmlNode *frameNode = animNode->first_node("frame");
  while (frameNode != nullptr)
  {
    const int tileId = startId
      + utils::stdStringToNumber<int>(frameNode->first_attribute("tileid")->value());
    const int duration = utils::stdStringToNumber<int>(frameNode->first_attribute("duration")->value());
    anim->addFrame(tileId, duration);
    frameNode = frameNode->next_sibling("frame");
  }
  return std::move(anim);
}

void TmxLoader::parseShapeGroups(Map &map, int tileId, const XmlNode *objGroupNode)
{
  const XmlNode *objNode = objGroupNode->first_node("object");
  PhysicObject::ShapeGroup objGroup;
  while (objNode != nullptr)
  {
    objGroup = parseShapeGroup(objNode, TileLinkage::LinkedToTiled);
    objNode = objNode->next_sibling("object");
  }
  if (!objGroup.empty())
  {
    map.addShapeGroup(tileId, std::move(objGroup));
    ::std::cout << "Added shapegroup to the map with id: " << tileId << ::std::endl;
  }
}

void TmxLoader::parseLayerData(TileLayer &layer, const XmlNode *dataNode)
{
  const std::string dataStr(dataNode->value());
  const std::vector<std::string> tileIdsVector = utils::splitString(dataStr, ',', false);
  if (tileIdsVector.size() != (layer.getH() * layer.getW()))
    throw new MapLoadException("Invalid tile data");

  int i = 0, j = 0;
  for (const std::string &tileIdStr: tileIdsVector)
  {
    layer.setTileId(i, j, utils::stdStringToNumber<int>(tileIdStr));
    i++;
    if (i == layer.getW()) { i = 0; j++; }
  }
}

void TmxLoader::parseLayers(Map &map, const XmlNode *mapNode)
{
  const XmlNode *innerNode = mapNode->first_node();
  while (innerNode != nullptr)
  {
    if (strcmp(innerNode->name(), "layer") == 0)
      map.addLayer(this->parseTileLayer(innerNode));
    else if (strcmp(innerNode->name(), "objectgroup") == 0)
      map.addLayer(this->parseObjectLayer(map, innerNode));
    else if (strcmp(innerNode->name(), "imagelayer") == 0)
      map.addLayer(this->parseImageLayer(innerNode));
    innerNode = innerNode->next_sibling();
  }
}

void TmxLoader::parseProperties(MapObject &mapObj, const XmlNode *objNode)
{
  const XmlNode *propsNode = objNode->first_node("properties");
  if (propsNode == nullptr)
    return;
  const XmlNode *propNode = propsNode->first_node("property");
  while (propNode != nullptr)
  {
    mapObj.addProperty(
      propNode->first_attribute("name")->value(),
      propNode->first_attribute("value")->value());
    propNode = propNode->next_sibling("property");
  }
}

} // namespace ibrengine
