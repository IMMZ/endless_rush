// license text

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>


#include <vector>

namespace sf
{

class String;

}

namespace ibrengine
{

class Animation
{
public:
  Animation();
  explicit Animation(int id);

  int getId() const;
  void setId(int id);
  int getCurrentTileId() const;
  void addFrame(int tileId, int duration);
  int getFramesCount() const;
  int getDurationForFrame(int frame);
  bool isCycled() const;
  void play();
  void stop();
  void reset();
  void update(const sf::Time &time);

private:
  std::vector<std::pair<int /* tileId */, int /* duration */ >> mFrames;
  int mCurrentFrame = 0;
  int mElapsedTime = 0;
  int mId = -1;
  bool mPlaying = true; // TODO: make false
  bool mIsCycled = true;
};

} // namespace ibrengine

#endif // ANIMATION_HPP
