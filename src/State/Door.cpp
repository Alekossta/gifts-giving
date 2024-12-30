#include "State/Door.h"
#include "SDL2/SDL.h"
#include "State/State.h"
#include "State/Button.h"
#include "General.h"
#include "Math/Vector2.h"

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
void Door::Close()
{
    if(bIsOpen)
    {
        sourceRectanglePosition = Vector2(32 * 17,0);
        bIsOpen = false;
        bCollides = true;
    }
}