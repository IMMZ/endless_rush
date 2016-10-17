// TODO: license text

#ifndef IMAGELAYER_HPP
#define IMAGELAYER_HPP

#include "layer.hpp"

namespace ibrengine
{

class ImageLayer: public Layer
{
public:
  ImageLayer(const std::string &name, int w, int h, const std::string &imgPath);

  const std::string &getImgPath() const;
  int getW() const;
  int getH() const;

private:
  std::string mImgPath;
  int mWidth = 0, mHeight = 0;
};

DECLARE_SMART_PTRS(ImageLayer);

} // namespace ibrengine

#endif // IMAGELAYER_HPP
