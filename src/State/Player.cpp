#include "State/Player.h"
#include "SDL2/SDL.h"
#include "State/State.h"
#include "State/Button.h"

Player::Player(const std::string& playerName, Vector2 startingPosition, Vector2 startingSize,
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
int zIndexNew,bool bIsVisibleNew, unsigned newPlayerIndex, float newPlayerSpeed) :
Object(playerName, startingPosition, startingSize, false, newSrcName,newSourceRectanglePosition,
 newSourceRectangleSize, zIndexNew, bIsVisibleNew),  playerIndex(newPlayerIndex), playerSpeed(newPlayerSpeed)
{

}

Player::~Player()
{
    
}

void Player::Begin()
{

}

bool CollidesHelper(Object* object1, Object* object2) {
    return object1->position.x < object2->position.x + object2->size.x &&
           object1->position.x + object1->size.x > object2->position.x &&
           object1->position.y < object2->position.y + object2->size.y &&
           object1->position.y + object1->size.y > object2->position.y;
}

bool Collides(Object *object1, Object *object2) {
    return CollidesHelper(object1, object2) || CollidesHelper(object2, object1);
}

bool starts_with(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() && 
           str.compare(0, prefix.size(), prefix) == 0;
}

void Player::CheckButtonCollision() {
    for (auto &[name, object] : State::GetAllObjects()) {
        if (starts_with(name, "ButtonNotPressed") || starts_with(name, "ButtonPressed")) {
            bool collides = Collides(this, object);
          //  std::cout << "calling\n";
            object->setBIsVisible(starts_with(name, "ButtonPressed") == collides);
          //  std::cout << "called\n";
        }
    }
}


void Player::Update(float deltatime)
{
    Vector2 movementDirection;

    if((Input::IsKeyPressed(SDL_SCANCODE_D) && playerIndex == 0) ||
    (Input::IsKeyPressed(SDL_SCANCODE_RIGHT) && playerIndex == 1))
    {
        movementDirection.x = 1;
    }

    if((Input::IsKeyPressed(SDL_SCANCODE_A) && playerIndex == 0) ||
    (Input::IsKeyPressed(SDL_SCANCODE_LEFT) && playerIndex == 1))
    {
        movementDirection.x = -1;
    }

    if((Input::IsKeyPressed(SDL_SCANCODE_S) && playerIndex == 0) ||
    (Input::IsKeyPressed(SDL_SCANCODE_DOWN) && playerIndex == 1))
    {
        movementDirection.y = 1;
    }

    if((Input::IsKeyPressed(SDL_SCANCODE_W) && playerIndex == 0) ||
    (Input::IsKeyPressed(SDL_SCANCODE_UP) && playerIndex == 1))
    {
        movementDirection.y = -1;
    }

    
    movementDirection.Normalize();
    
    Vector2 newPosition = position + movementDirection * deltatime * playerSpeed;
    State::MoveObject(this, newPosition);
    CheckButtonCollision();
}