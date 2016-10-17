// license text

#ifndef TILELAYER_HPP
#define TILELAYER_HPP

#include "layer.hpp"

namespace ibrengine
{

class TileLayer: public Layer
{
public:
  TileLayer(const std::string &name, int w, int h);
  ~TileLayer();

  int getTileId(int x, int y) const;
  void setTileId(int x, int y, int tileId);
  float getSpeed() const;
  void setSpeed(float speed);

private:
  float mSpeed = 1.0f;
  int **mTileIds = nullptr;
};

DECLARE_SMART_PTRS(TileLayer);

} // namespace ibrengine

#endif // TILELAYER_HPP
