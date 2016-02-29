// license text

#include "tilelayer.hpp"

namespace ibrengine
{

TileLayer::TileLayer(const std::string& name, int w, int h):
  Layer(name, Layer::Type::Tile, w, h)
{
  mTileIds = new int*[this->getW()];
  for (int i = 0; i < this->getW(); ++i)
    mTileIds[i] = new int[this->getH()];
}

TileLayer::~TileLayer()
{
  for (int i = 0; i < this->getW(); ++i)
    delete[] mTileIds[i];
  delete[] mTileIds;
}

int TileLayer::getTileId(int x, int y) const
{
  return mTileIds[x][y];
}

void TileLayer::setTileId(int x, int y, int tileId)
{
  mTileIds[x][y] = tileId;
}

float TileLayer::getSpeed() const
{
  return mSpeed;
}

void TileLayer::setSpeed(float speed)
{
  if (speed > 10.0f)
    mSpeed = 10.0f;
  else if (speed < 0.1f)
    mSpeed = 0.1f;
  else
    mSpeed = speed;
}

} // namespace ibrengine
