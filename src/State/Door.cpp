#include "State/Door.h"
#include "SDL2/SDL.h"
#include "State/State.h"
#include "State/Button.h"
#include "General.h"
#include "Math/Vector2.h"
#include "State/Player.h"

Door::Door(const std::string& doorName, Vector2 position, Vector2 startingSize, 
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
int zIndexNew, int doorCode, bool bIsVertical):
 Object(doorName, position, startingSize, newSrcName, newSourceRectanglePosition,
newSourceRectangleSize, zIndexNew, true, true, true, bIsVertical ? 0 : 90), doorCode(doorCode)
{

}

void Door::Update(float deltatime)
{   
    
    bool bDoorOpens =  false;
	
    for (const auto &button : interactingButtons) {
        bDoorOpens = bDoorOpens || button->getIsActive();
    }

    if(bDoorOpens)
    {   
        Open();
    }
    else
    {
        Close();
    }

}

void Door::Begin() 
{
	// emmmm works as well
    bIsOpen = false;
    for (const auto &[name, object] : State::GetAllObjects()) {
        if (startsWith(name, "Button")) {
            
            Button* button = dynamic_cast<Button*>(object);
            if (button->getOpensDoorCode() == doorCode) {
                interactingButtons.push_back(button);
                std::cout << "Adding button " << button->name << "to door " << doorCode << std::endl;
            }
        }
    }
}

void Door::Open()
{
    if(!bIsOpen)
    {
        sourceRectanglePosition = Vector2(32 * 18,0);
        bIsOpen = true;
        bCollides = false;
    }
}

bool isPositionValid(Object* player) {
    for (const auto &[name, object] : State::GetAllObjects()) {
        if (object != player && object->bCollides && State::AreObjectsOverlapping(object, player)) {
            return false;
        }
    }
    return true;
}

void Door::Close()
{
    if(bIsOpen)
    {
        sourceRectanglePosition = Vector2(32 * 17,0);
        bIsOpen = false;
        bCollides = true;
    }

    Object* player1 = State::GetAllObjects()["Santa Male"];
    Object* player2 = State::GetAllObjects()["Santa Female"];
    Object* player = NULL;
    
    if (State::AreObjectsOverlapping(this, player1)) {
        player = player1;
    } 
    
    if (State::AreObjectsOverlapping(this, player2)) {
        player = player2;
    }

    if (player == NULL) return;
    
    float oldY = player->position.y;

    player->position.y = position.y - player->size.y;
    if (isPositionValid(player)) {
        return;
    }

    player->position.y = position.y + size.y;
    if (isPositionValid(player)) {
        return;
    }

    player->position.y = oldY;
    player->position.x = position.x - player->size.x;
    if (isPositionValid(player)) {
        return;
    }

    player->position.x = position.x + size.x;
    if (isPositionValid(player)) {
        return;
    }

    
}