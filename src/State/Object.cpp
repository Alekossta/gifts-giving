#include "State/Object.h"

Object::Object(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,bool bCollidesNew,
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize)
 : name(newName), position(startingPosition), size(startingSize), bCollides(bCollidesNew), srcName(newSrcName),
 sourceRectanglePosition(newSourceRectanglePosition), sourceRectangleSize(newSourceRectangleSize)
{

}

Object::~Object()
{
    
}

void Object::Begin()
{

}

void Object::Update(float deltatime)
{

}

Object* Object::CreateObject(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,
bool bCollidesNew,const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize)
{
    return new Object(newName, startingPosition, startingSize, bCollidesNew,
    newSrcName, newSourceRectanglePosition, newSourceRectangleSize);
}

void Object::DeleteObject(Object* object)
{
    delete object;
}