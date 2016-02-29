// todo: license

#ifndef LAYER_HPP
#define LAYER_HPP

#include <string>

namespace ibrengine
{

class Layer
{
public:
  enum class Type
  {
    Tile,
    Object,
    Image
  };

  Layer(const std::string &name, Type type, int w, int h);
  virtual ~Layer();

  const std::string &getName() const;

  int getW() const;
  int getH() const;
  bool isVisible() const;
  void setVisible(bool visible);
  float getOpacity() const;
  void setOpacity(float opacity);
  Type getType() const;

private:
  std::string mName;
  float mOpacity = 1.0f;
  int mW, mH;
  Type mType = Type::Tile;
  bool mVisible = true;
};

} // namespace ibrengine

#endif // LAYER_HPP
