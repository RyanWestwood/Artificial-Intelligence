#include <ai/math/Vector2.h>

int main()
{
  Vector2 vec{10.f, 10.f};

  float magnitude = Vector2::Magnitude({10, 10});
  //if(!AreSame(magnitude, 14.1421f)) return 1;

  auto movement = Vector2::MoveTowards({10, 10}, {0, 0}, 1);
  //if(movement != Vector2{9.29289f, 9.29289f}) return 1;

  auto angle = Vector2::GetAngleBetween({0, 10}, {0, 0});
  if(angle != 180) return 1;

  return 0;
}