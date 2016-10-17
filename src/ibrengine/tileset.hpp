// todo: license

#ifndef TILESET_HPP
#define TILESET_HPP

#include "global.hpp"

#include <SFML/Graphics/Color.hpp>

#include <string>

namespace ibrengine
{

class Tileset
{
public:
  Tileset(const std::string &name,
    const std::string &imgSrc, int imgW, int imgH,
    int firstTileId, int tileW, int tileH);

  int getImgH() const;
  int getImgW() const;
  int getFirstTileId() const;
  const std::string& getImgSrc() const;
  const std::string& getName() const;
  int getTileH() const;
  int getTileW() const;
  int getTilesCount() const;
  const sf::Color& getTransparentColor() const;
  void setTransparentColor(const sf::Color &color);

private:
  sf::Color mTransparentColor;
  std::string mName;
  std::string mImgSrc;
  int mFirstTileId;
  int mTileW, mTileH;
  int mImgW, mImgH;
};

DECLARE_SMART_PTRS(Tileset);

} // namespace ibrengine

#endif // TILESET_HPP
