#include "State/Child.h"
#include "SDL2/SDL.h"
#include "State/State.h"

Child::Child(const std::string& childName, Vector2 position, Vector2 startingSize, 
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
int zIndexNew, TextBox* textBox, TextBox* timeTextBox, int secondsLeft):
 Object(childName, position, startingSize, newSrcName, newSourceRectanglePosition,
newSourceRectangleSize, zIndexNew, false, true, true),
 bAsksGift(false), textBox(textBox), timeTextBox(timeTextBox), timeToGiveGift(secondsLeft), timeToDisappear(2)
{
	timeToGiveGift.startTimer(1000);
}

void Child::Update(float deltatime)
{	
	Object* santaMale = State::GetAllObjects()["Santa Male"];
	Object* santaFemale = State::GetAllObjects()["Santa Female"];

	float distanceFromPlayerMale = santaMale->position.DistanceTo(position);
	float distanceFromPlayerFemale = santaFemale->position.DistanceTo(position);

	const float distanceThreshold = 100;

	bool bothPlayersClose = distanceFromPlayerFemale <= distanceThreshold && distanceFromPlayerMale <= distanceThreshold;
	
	if (bothPlayersClose) 
	{
		textHolder->setIsVisible(true);
	} else {
		textHolder->setIsVisible(false);
	}

	timeTextBox->setText(std::to_string(timeToGiveGift.secondsLeft));
	if(Input::IsKeyPressed(SDL_SCANCODE_SPACE) && Input::IsKeyPressed(SDL_SCANCODE_RETURN) && bothPlayersClose)
	{	
		textBox->setText("Thank you!");
		// textBox->setIsVisible(true);
		// timeTextBox->bIsVisible = false;
		// bIsActive = false;
		timeToDisappear.startTimer(1000);
	}
}

void Child::Begin() 
{
	
}

