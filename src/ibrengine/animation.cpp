// license text

#include "animation.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/String.hpp>

namespace ibrengine
{

Animation::Animation(int id):
  mId(id)
{
}

int Animation::getId() const
{
  return mId;
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

void Animation::setDurationForFrame(int frame, int duration)
{
  mFrames[frame].second = duration;
}

float Animation::getSpeed() const
{
  return mSpeed;
}

void Animation::setSpeed(float speed)
{
  mOldSpeed = mSpeed;
  if (speed > 10.0f)
    mSpeed = 10.0f;
  else if (speed < 1.0f)
    mSpeed = 1.0f;
  else
    mSpeed = speed;
  this->updateDurations();
}

void Animation::play()
{
  mPlaying = true;
  mTimer.restart();
}

void Animation::stop()
{
  mPlaying = false;
}

void Animation::reset()
{
  mCurrentFrame = 0;
}

void Animation::update()
{
  if (mPlaying && mTimer.getElapsedTime().asMilliseconds() > mFrames[mCurrentFrame].second)
  {
    (mCurrentFrame == mFrames.size() - 1) ? mCurrentFrame = 0: mCurrentFrame++;
    mTimer.restart();
  }
}

void Animation::updateDurations()
{
  float coefficient = mSpeed / mOldSpeed;
  for(std::pair<int, int> &frame: mFrames)
    frame.second *= coefficient;
}

} // namespace ibrengine
