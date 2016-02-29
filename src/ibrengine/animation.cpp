// license text

#include "animation.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/String.hpp>

namespace ibrengine
{

Animation::Animation()
{
}

Animation::Animation(int id):
  mId(id)
{
}

int Animation::getId() const
{
  return mId;
}

void Animation::setId(int id)
{
  mId = id;
}

int Animation::getCurrentTileId() const
{
  return mFrames[mCurrentFrame].first;
}

void Animation::addFrame(int tileId, int duration)
{
  mFrames.push_back(std::make_pair(tileId, duration));
}

int Animation::getFramesCount() const
{
  return mFrames.size();
}

int Animation::getDurationForFrame(int frame)
{
  return mFrames[frame].second;
}

bool Animation::isCycled() const
{
  return mIsCycled;
}

void Animation::play()
{
  mPlaying = true;
}

void Animation::stop()
{
  mPlaying = false;
}

void Animation::reset()
{
  mElapsedTime = 0;
  mCurrentFrame = 0;
}

void Animation::update(const sf::Time &time)
{
  if (mPlaying)
  {
    mElapsedTime += time.asMilliseconds();
    int currentFrameDuration = this->getDurationForFrame(mCurrentFrame);
    while (mElapsedTime > currentFrameDuration)
    {
      mElapsedTime -= currentFrameDuration;
      // Check for last frame.
      if ((mCurrentFrame + 1) == mFrames.size())
      {
        if (mIsCycled)
          mCurrentFrame = 0;
      }
      else
      {
        mCurrentFrame++;
      }
    }
  }
}

} // namespace ibrengine
