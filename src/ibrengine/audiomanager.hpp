// TODO: license text

#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include "global.hpp"

#include <SFML/Audio/Music.hpp>
#include <SFML/System/Time.hpp>

namespace ibrengine
{

/**
 * @class AudioManager
 * @brief This class contains basic functionality to work with the sound.
 * @details Manager can play audio files and has very basic functionality to handle the sound.
 * It is possible to change the speed of the music, make fade-in or fade-out and mute/unmute.
 */
class AudioManager
{
public:
  /**
   * @brief Constructor.
   */
  AudioManager();

  /**
   * @brief Plays the sound.
   * @details If some music is playing it will be stopped before to play a new one.
   * @param fileName File path to the sound file.
   * @see pause()
   * @see stop()
   */
  void play(const std::string &fileName);

  /**
   * @brief Pauses the music is it's playing.
   * @see play()
   * @see stop()
   */
  void pause();

  /**
   * @brief Stops the music if it's playing or paused.
   * @see play()
   * @see pause()
   */
  void stop();

  /**
   * @brief Mutes the sound.
   * @see unmute()
   */
  void mute();

  /**
   * @brief Unmutes the sound.
   * @see mute()
   */
  void unmute();

  /**
   * @brief Makes fade-in effect.
   * @note It is possible to make settings with setFadeStep(float step) and setFadeInterval(const sf::Time &interval).
   * @see fadeOut()
   */
  void fadeIn();

  /**
   * @brief Makes fade-out effect.
   * @note It is possible to make settings with setFadeStep(float step) and setFadeInterval(const sf::Time &interval).
   * @see fadeIn()
   */
  void fadeOut();

  /**
   * @brief Updates the manager.
   * @param time Elapsed time from last update.
   */
  void update(const sf::Time &time);

  /**
   * @brief Specifies if anything is playing now.
   * @return Value giving an information if anything is playing now.
   * @retval true Something is playing now.
   * @retval false Nothing is playing now.
   */
  bool isPlaying() const;

  /**
   * @brief Return playback speed.
   * @return Playback speed.
   */
  float getSpeed() const;

  /**
   * @brief Sets playback speed.
   * @param speed Speed to set from 0.0 to 1.0.
   */
  void setSpeed(float speed);

  /**
   * @brief Return playback volume.
   * @return Playback volume.
   */
  float getVolume() const;

  /**
   * @brief Sets playback volume.
   * @param volume Volume to set in range 0.0 (mute) - 1.0(full).
   */
  void setVolume(float volume);

  /**
   * @brief Specifies if playback is looped.
   * @return Value giving information if playback is looped.
   * @retval true Playback is looped.
   * @retval false Playback is not looped.
   */
  bool isLooped() const;

  /**
   * @brief Set playbacks's loop feature.
   * @param looped Loop state.
   */
  void setLooped(bool looped);

  /**
   * @brief Returns fade step.
   * @details Fade step is the amount of volume change by one fade interval.
   * @see setFadeStape()
   * @see getFadeInterval()
   * @return Fade step in range 0.0 - 1.0.
   */
  float getFadeStep() const;

  /**
   * @brief Sets fade step.
   * @param step Fade step.
   * @details Fade step is the amount of volume change by one fade interval.
   * @see getFadeStape()
   * @see getFadeInterval()
   */
  void setFadeStep(float step);

  /**
   * @brief Returns fade interval.
   * @details fade interval is the interval by which the volume will be changed with specified step.
   * @return Fade interval.
   * @see setFadeInterval()
   */
  const sf::Time& getFadeInterval() const;

  /**
   * @brief Sets fade interval.
   * @param interval fade interval.
   * @details fade interval is the interval by which the volume will be changed with specified step.
   * @see getFadeInterval()
   */
  void setFadeInterval(const sf::Time &interval);

private:
  DISABLE_COPY(AudioManager);
  DISABLE_MOVE(AudioManager);

  sf::Music mMusic;
  sf::Time mFadeInterval;
  float mSpeed = 1.0f, mVolume = 0.5, mOldVolume = 0.0f, mFadeStep = 0.1f;
  bool mFadingOut = false, mFadingIn = false;
};

} // namespace ibrengine

#endif // AUDIOMANAGER_HPP
