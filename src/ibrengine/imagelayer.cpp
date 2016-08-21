// TODO: license text

#include "imagelayer.hpp"

namespace ibrengine
{

ImageLayer::ImageLayer(const std::string& name, int w, int h, const std::string& imgPath):
  Layer(name, Type::Image, -1, -1),
  mImgPath(imgPath), mWidth(w), mHeight(h)
{
}

const std::string& ImageLayer::getImgPath() const
{
  return mImgPath;
}

int ImageLayer::getW() const
{
  return mWidth;
}

int ImageLayer::getH() const
{
  return mHeight;
}

} // namespace ibrengine
