// TODO: license

#ifndef INPUT_HPP
#define INPUT_HPP

class Input
{
public:
  enum class Action
  {
    NoAction,
    Up,
    Down,
    Right,
    Left,
    Jump,
    Fire,
    SuperMove,
    Start,
    Enter = Start,
    Pause = Start,
    Back
  };
};

#endif // INPUT_HPP
