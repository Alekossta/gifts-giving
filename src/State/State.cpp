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

    const float playersSpeed = 250.f;

    // create santa male
    Player* SantaMale = new Player("Santa Male", Vector2(0,0), Vector2(64,64), "./assets/Atlas.png",
    Vector2(0,0), Vector2(32,32), 0, playersSpeed);
    AddObjectToAll(SantaMale);
    AddObjectToColliding(SantaMale);

    // create santa female
    Player* SantaFemale = new Player("Santa Female", Vector2(64,0), Vector2(64,64), "./assets/Atlas.png",
    Vector2(32,0), Vector2(32,32), 1, playersSpeed);
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

void State::UpdateInternal(float deltatime)
{
    for(const auto& pair : allObjects)
    {
        pair.second->Update(deltatime);
    }
}

void State::Update(float deltatime)
{
    GetInstance().UpdateInternal(deltatime);
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