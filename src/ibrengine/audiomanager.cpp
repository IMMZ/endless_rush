// TODO: license text

#include "audiomanager.hpp"

namespace ibrengine
{

AudioManager::AudioManager()
{
  mMusic.setVolume(mVolume * 100.0f);
  mMusic.setLoop(false);
}

void AudioManager::play(const std::string& fileName)
{
  if (mMusic.openFromFile(fileName))
  {
    if (mMusic.getStatus() == sf::Music::Playing)
      mMusic.stop();
    mMusic.play();
  }
}

void AudioManager::pause()
{
  if (mMusic.getStatus() == sf::Music::Playing)
    mMusic.pause();
}

void AudioManager::stop()
{
  if (mMusic.getStatus() != sf::Music::Stopped)
    mMusic.stop();
}

void AudioManager::mute()
{
  mOldVolume = mVolume;
  setVolume(0.0f);
}

void AudioManager::unmute()
{
  setVolume(mOldVolume);
}

void AudioManager::fadeOut()
{
  mFadingIn = false;
  mFadingOut = true;
  mOldVolume = getVolume();
}

void AudioManager::fadeIn()
{
  if (mVolume == 0.0f)
  {
    mFadingOut = false;
    mFadingIn = true;
  }
}

void AudioManager::update(const sf::Time &time)
{
  if (mFadingIn || mFadingOut)
  {
    float timeCoef = static_cast<float>(time.asSeconds()) / static_cast<float>(mFadeInterval.asSeconds());
    if (mFadingOut)
    {
      setVolume(getVolume() - mFadeStep * timeCoef);
      if (getVolume() == 0.0f)
        mFadingOut = false;
    }
    else if (mFadingIn)
    {
      setVolume(getVolume() + mFadeStep * timeCoef);
      if (getVolume() >= mOldVolume)
        mFadingIn = false;
    }
  }
}

bool AudioManager::isPlaying() const
{
  return (mMusic.getStatus() == sf::Music::Playing);
}

float AudioManager::getSpeed() const
{
  return mSpeed;
}

void AudioManager::setSpeed(float speed)
{
  mSpeed = speed;
  mMusic.setPitch(speed);
}

float AudioManager::getVolume() const
{
  return mVolume;
}

void AudioManager::setVolume(float volume)
{
  if (volume < 0.0f)
    mVolume = 0.0f;
  else if (volume > 1.0f)
    mVolume = 1.0f;
  else
    mVolume = volume;

  mMusic.setVolume(mVolume * 100.0f);
}

bool AudioManager::isLooped() const
{
  return mMusic.getLoop();
}

void AudioManager::setLooped(bool looped)
{
  mMusic.setLoop(looped);
}

float AudioManager::getFadeStep() const
{
  return mFadeStep;
}

void AudioManager::setFadeStep(float step)
{
  mFadeStep = step;
}

const sf::Time& AudioManager::getFadeInterval() const
{
  return mFadeInterval;
}

void AudioManager::setFadeInterval(const sf::Time &interval)
{
  mFadeInterval = interval;
}

} // namespace ibrengine
