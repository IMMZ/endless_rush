// todo: license

#ifndef LAYER_HPP
#define LAYER_HPP

#include <string>

namespace ibrengine
{

class Layer
{
public: // TODO: add enum class Type { Tile, Object, Image }
  Layer(const std::string &name, int w, int h);
  virtual ~Layer();

  const std::string &getName() const;

  int getW() const;
  int getH() const;
  bool isVisible() const;
  void setVisible(bool visible);
  float getOpacity() const;
  void setOpacity(float opacity);

private:
  std::string mName;
  float mOpacity = 1.0f;
  int mW, mH;
  bool mVisible = true;
};

} // namespace ibrengine

#endif // LAYER_HPP
