#include "State/Child.h"
#include "SDL2/SDL.h"
#include "State/State.h"

Child::Child(const std::string& childName, Vector2 position, Vector2 startingSize, 
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
int zIndexNew):
 Object(childName, position, startingSize, newSrcName, newSourceRectanglePosition,
newSourceRectangleSize, zIndexNew, false, true, true),
 bIsActive(false)
{

}

void Child::Update(float deltatime)
{
	Object* player1 = State::GetAllObjects()["Santa Male"];
	bool bIsCloseToPlayer1 = State::AreObjectsClose(this, player1);

	Object* player2 = State::GetAllObjects()["Santa Female"];
	bool bIsCloseToPlayer2 = State::AreObjectsClose(this, player2);

	if(bIsCloseToPlayer1 && bIsCloseToPlayer2)
	{
		AskGift();
	}
	else
	{
		DontAskGift();
	}
}

void Child::AskGift() {

}


void Child::DontAskGift() {

}


void Child::Begin() 
{
	
}

