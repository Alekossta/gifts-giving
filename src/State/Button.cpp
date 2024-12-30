#include "State/Button.h"
#include "SDL2/SDL.h"
#include "State/State.h"

Button::Button(const std::string& buttonName, Vector2 position, Vector2 startingSize, 
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
int zIndexNew, int opensDoorCode):
 Object(buttonName, position, startingSize, newSrcName, newSourceRectanglePosition,
newSourceRectangleSize, zIndexNew, false, true, true, 0.0),
 bIsActive(false), opensDoorCode(opensDoorCode) 
{

}

void Button::Update(float deltatime)
{
	Object* player1 = State::GetAllObjects()["Santa Male"];
	bool bHasPlayer1 = State::AreObjectsOverlapping(this, player1);

	Object* player2 = State::GetAllObjects()["Santa Female"];
	bool bHasPlayer2 = State::AreObjectsOverlapping(this, player2);

	if(bHasPlayer1 || bHasPlayer2)
	{
		Activate();
	}
	else
	{
		DeActivate();
	}
}

void Button::Begin() 
{
	// emmmm works
	bIsActive = true;
	DeActivate();
}

void Button::Activate()
{
    if(!bIsActive)
    {
        bIsActive = true;
		sourceRectanglePosition = Vector2(15*32,0);
    }
}

void Button::DeActivate()
{
	if(bIsActive)
	{
		bIsActive = false;
		sourceRectanglePosition = Vector2(14*32,0);
	}
}