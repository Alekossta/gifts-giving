#include "State/State.h"
#include "State/Object.h"
#include "State/Player.h"
#include "Math/Vector2.h"

State State::instance;

State& State::GetInstance() {
    return instance;
}

void State::InitInternal()
{
    // create santa male
    Player* SantaMale = Player::CreatePlayer("Santa Male", Vector2(0,0), Vector2(32,32), input);
    AddObjectToAll(SantaMale);
    AddObjectToColliding(SantaMale);
    // create santa female
    Player* SantaFemale = Player::CreatePlayer("Santa Female", Vector2(64,0), Vector2(32,32), input);
    AddObjectToAll(SantaFemale);
    AddObjectToColliding(SantaFemale);

    for(const auto& pair : allObjects)
    {
        pair.second->Begin();
    }
}

void State::Init()
{
    GetInstance().InitInternal();
}

void State::UpdateInternal()
{
    for(const auto& pair : allObjects)
    {
        pair.second->Update();
    }
}

void State::Update()
{
    GetInstance().UpdateInternal();
}

void State::AddObjectToAll(Object* objectToAdd)
{
    if(objectToAdd)
    {
        allObjects[objectToAdd->name] = objectToAdd;
    }
}
void State::AddObjectToColliding(Object* objectToAdd)
{
    if(objectToAdd)
    {
        collidingObjects.push_back(objectToAdd);
    }
}

State::~State()
{

}