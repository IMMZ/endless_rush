// TODO: license text

#ifndef DRAWABLEOBJECTT_HPP_
#define DRAWABLEOBJECTT_HPP_

#include "object.hpp"

namespace ibrengine
{

class DrawableObjectt: public Object
{
public:
  explicit DrawableObjectt(MapObject &director);

  int getTileId() const;
  void setTileId(int tileId);

private:
    int mTileId = -1;
};

} // namespace ibrengine

#endif // DRAWABLEOBJECTT_HPP_
