#include "Player.h"

Player::Player(const std::string& playerName, Vector2 startingPosition, Vector2 startingSize, Input* newInput) :
Object(playerName, startingPosition, startingSize, true), input(newInput)
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

}

Player* Player::CreatePlayer(const std::string& newName,
Vector2 startingPosition, Vector2 startingSize, Input* newInput)
{
    return new Player(newName, startingPosition, startingSize, newInput);
}