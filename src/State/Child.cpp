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
	Object* santaMale = State::GetAllObjects()["Santa Male"];
	Object* santaFemale = State::GetAllObjects()["Santa Female"];

	float distanceFromPlayerMale = santaMale->position.DistanceTo(position);
	float distanceFromPlayerFemale = santaFemale->position.DistanceTo(position);

	const float distanceThreshold = 100;

	bool bothPlayersClose = distanceFromPlayerFemale <= distanceThreshold && distanceFromPlayerMale <= distanceThreshold;

	if(Input::IsKeyPressed(SDL_SCANCODE_SPACE) && Input::IsKeyPressed(SDL_SCANCODE_RETURN) && bothPlayersClose)
	{
		std::cout << "give gift" << std::endl;
	}
}

void Child::Begin() 
{
	
}

