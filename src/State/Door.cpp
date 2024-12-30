#include "State/Door.h"
#include "SDL2/SDL.h"
#include "State/State.h"
#include "State/Button.h"
#include "General.h"

Door::Door(const std::string& doorName, Vector2 position, Vector2 startingSize, 
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
int zIndexNew, int doorCode):
 Object(doorName, position, startingSize, newSrcName, newSourceRectanglePosition,
newSourceRectangleSize, zIndexNew, true, true, true), doorCode(doorCode)
{

}

void Door::Update(float deltatime)
{   
    
    bool bDoorOpens =  false;
	
    for (const auto &button : interactingButtons) {
        bDoorOpens = bDoorOpens || button->getIsActive();
    }

}

void Door::Begin() 
{
	// emmmm works as well
	rotation = 0.0;
    bIsOpen = false;

    for (const auto &[name, object] : State::GetAllObjects()) {
        if (startsWith(name, "Button")) {
            
            Button* button = dynamic_cast<Button*>(object);
            if (button->getOpensDoorCode() == doorCode) {
                interactingButtons.push_back(button);
            }
        }
    }
}
