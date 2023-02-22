#include <ai/math/Vector2.h>

int main()
{
  Vector2 vec{10.f, 10.f};
  auto    mag  = vec.Magnitude();
  auto    mag2 = Vector2::Magnitude({10, 10});

  std::cout << vec;
  std::cout << mag << "\n";
  std::cout << mag2 << "\n";

  auto a = Vector2::MoveTowards({10, 10}, {0, 0}, 1);
  std::cout << a << "\n";

  auto angle = Vector2::GetAngleBetween({768, 384}, {768, 712});
  std::cout << angle << "\n";

  auto angle2 = Vector2::GetAngleBetween({0, 712 - 384}, {0, 0});
  std::cout << angle2 << "\n";

  return 0;
}