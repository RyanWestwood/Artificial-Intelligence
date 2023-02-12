#define SDL_MAIN_HANDLED
#include <engine/Collision.h>

int main() {
  
    Circle circle1{{0,0}, 10};
    Circle circle2{{5,5}, 10};

    SDL_Rect box1{0,0,10,10};
    SDL_Rect box2{5,5,10,10};

    if(!collision::SphereCollision(circle1, circle2)) return 1;
    if(!collision::BoxCollision(box1, box2)) return 1;
    if(!collision::ComplexCollision(circle1, box2)) return 1;

	return 0;
}