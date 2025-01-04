#include "State/Child.h"
#include "SDL2/SDL.h"
#include "State/State.h"

Child::Child(const std::string& childName, Vector2 position, Vector2 startingSize, 
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
int zIndexNew, Object* newTextHolder, TextBox* textBox, TextBox* timeTextBox, int secondsLeft):
 Object(childName, position, startingSize, newSrcName, newSourceRectanglePosition,
newSourceRectangleSize, zIndexNew, false, true, true),
 bAsksGift(false), textHolder(newTextHolder), textBox(textBox), timeTextBox(timeTextBox), timeToGiveGift(secondsLeft), timeToDisappear(2)
{
	timeToGiveGift.startTimer(1000);
}

void Child::Update(float deltatime)
{	
	Object* santaMale = State::GetAllObjects()["Santa Male"];
	Object* santaFemale = State::GetAllObjects()["Santa Female"];
	float distanceFromPlayerMale = 0;
	float distanceFromPlayerFemale = 0;
	if(santaFemale && santaMale)
	{
		distanceFromPlayerMale = santaMale->position.DistanceTo(position);
		distanceFromPlayerFemale = santaFemale->position.DistanceTo(position);
	}

	const float distanceThreshold = 100;

	bool bothPlayersClose = distanceFromPlayerFemale <= distanceThreshold && distanceFromPlayerMale <= distanceThreshold;
	
	if(textHolder)
	{
		if (bothPlayersClose) 
		{
			textHolder->setIsVisible(true);
		} else {
			textHolder->setIsVisible(false);
		}
	}

	if(timeTextBox)
	{
		timeTextBox->setText(std::to_string(timeToGiveGift.secondsLeft));
	}

	// if(Input::IsKeyPressed(SDL_SCANCODE_SPACE) && Input::IsKeyPressed(SDL_SCANCODE_RETURN) && bothPlayersClose)
	// {	
	// 	if(textBox)
	// 	{
	// 		textBox->setText("Thank you!");
	// 	}
	// 	// textBox->setIsVisible(true);
	// 	// timeTextBox->bIsVisible = false;
	// 	// bIsActive = false;
	// 	timeToDisappear.startTimer(1000);
	// }
}

void Child::Begin() 
{
	
}

