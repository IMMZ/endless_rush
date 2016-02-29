// TODO: license text

#ifndef TITLESSTATE_HPP
#define TITLESSTATE_HPP

#include"igamestate.hpp"

#include <list>

namespace internal
{

class TitlesState: public internal::IGameState
{
public:
  void draw(sf::RenderTarget &target); // TODO: remove rendertarget parameter - use getRenderTarget() instead
  void handleInput(Input::Action act);
  void update(const sf::Time &time);

private:
  using Participant = std::pair<sf::String /* role */, sf::String /* name */>;
  using Participants = std::list<Participant>;

  /* The container below is used for storing pairs like role - name.
   * In the titles they are shown as next:
   * ========================
   *        programmer
   *     Ibrahimov Mamed
   *
   *          music
   *     Goryn Doroshenko
   * ========================
   * The name should have a bigger font size than the role.
   */
  Participants mParticipants;
};

} // namespace ibrengine

#endif // TITLESSTATE_HPP
