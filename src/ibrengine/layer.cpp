// todo: license

#include "layer.hpp"

namespace ibrengine
{

Layer::Layer(const std::string &name, int w, int h):
  mName(name),
  mW(w), mH(h)
{
}

Layer::~Layer()
{
}

const std::string& Layer::getName() const
{
  return mName;
}

int Layer::getW() const
{
  return mW;
}

int Layer::getH() const
{
  return mH;
}

bool Layer::isVisible() const
{
  return mVisible;
}

void Layer::setVisible(bool visible)
{
  mVisible = visible;
}

float Layer::getOpacity() const
{
  return mOpacity;
}

void Layer::setOpacity(float opacity)
{
  if (opacity < 0.0f)
    mOpacity = 0.0f;
  else if (opacity > 1.0f)
    mOpacity = 1.0f;
  else
    mOpacity = opacity;
}

} // namespace ibrengine
