#include "State/Player.h"
#include "SDL2/SDL.h"
#include "State/State.h"
#include "State/Button.h"

Player::Player(const std::string& playerName, Vector2 startingPosition, Vector2 startingSize,
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
int zIndexNew, unsigned newPlayerIndex, float newPlayerSpeed) :
Object(playerName, startingPosition, startingSize, newSrcName,newSourceRectanglePosition,
 newSourceRectangleSize, zIndexNew),  playerIndex(newPlayerIndex), playerSpeed(newPlayerSpeed)
{

}

Player::~Player()
{
    
}

void Player::Begin()
{
    startingSourceRectanglePosition = sourceRectanglePosition;
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

    if(movementDirection.GetMagnitude() == 0) // we are not moving
    {
        sourceRectanglePosition = Vector2(startingSourceRectanglePosition.x, 0);
    }
    else
    {
        sourceRectanglePosition.y = 32 + 32 * ((SDL_GetTicks() / 100) % 2);
    }
    
    movementDirection.Normalize();
    
    Vector2 newPosition = position + movementDirection * deltatime * playerSpeed;
    State::MoveObject(this, newPosition);
}