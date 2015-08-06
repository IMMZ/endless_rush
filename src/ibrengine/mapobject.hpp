// license text

#ifndef MAPOBJECT_HPP
#define MAPOBJECT_HPP

#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

#include <map>

namespace ibrengine
{

class MapObject
{
public:
  MapObject(); // TODO: extra?
  explicit MapObject(const sf::String &name);
  virtual ~MapObject();

  const sf::String& getName() const;
  void setName(const sf::String &name);
  const sf::Vector2i& getPosition() const;
  void setPosition(const sf::Vector2i &pos);
  bool isVisible() const;
  void setVisible(bool visible);
  const sf::String& getType() const;
  void setType(const sf::String &type);

  // Properties.
  void addProperty(const sf::String &propertyName, const sf::String &propertyValue);
  const sf::String& getProperty(const sf::String &propertyName) const;
  bool hasProperty(const sf::String &propertyName) const;


private:
  std::map<sf::String /* name */, sf::String /* value */> mProperties;
  sf::String mName, mType;
  sf::Vector2i mPosition;
  bool mVisible = true;
};

} // namespace ibrengine

#endif // MAPOBJECT_HPP
