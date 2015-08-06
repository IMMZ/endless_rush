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
  explicit Animation(int id);

  int getId() const;
  int getCurrentTileId() const;
  void addFrame(int tileId, int duration);
  int getFramesCount() const;
  int getDurationForFrame(int frame);
  void setDurationForFrame(int frame, int duration);
  float getSpeed() const;
  void setSpeed(float speed);
  void play();
  void stop();
  void reset();
  void update();

private:
  void updateDurations(); // used after changing speed

  std::vector<std::pair<int /* tileId */, int /* duration */ >> mFrames;
  sf::Clock mTimer;
  float mSpeed = 1.0f, mOldSpeed = 1.0f;
  int mCurrentFrame = 0;
  int mId = -1;
  bool mPlaying = true; // TODO: make false
};

} // namespace ibrengine

#endif // ANIMATION_HPP
