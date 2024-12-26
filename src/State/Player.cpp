#include "State/Player.h"
#include "SDL2/SDL.h"

Player::Player(const std::string& playerName, Vector2 startingPosition, Vector2 startingSize,
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize) :
Object(playerName, startingPosition, startingSize, true, newSrcName,newSourceRectanglePosition, newSourceRectangleSize)
{

}

Player::~Player()
{
    
}

void Player::Begin()
{

}

void Player::Update()
{
    if(Input::IsKeyPressed(SDL_SCANCODE_D))
    {
        
    }
}

Player* Player::CreatePlayer(const std::string& newName,
Vector2 startingPosition, Vector2 startingSize,
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize)
{
    return new Player(newName, startingPosition, startingSize, newSrcName, newSourceRectanglePosition,
    newSourceRectangleSize);
}