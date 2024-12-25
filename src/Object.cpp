#include "Object.h"

Object::Object(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,bool bCollidesNew)
 : name(newName), position(startingPosition), size(startingSize), bCollides(bCollidesNew)
{

}

Object::~Object()
{
    
}

void Object::Begin()
{

}

void Object::Update()
{

}

Object* Object::CreateObject(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,
bool bCollidesNew)
{
    return new Object(newName, startingPosition, startingSize, bCollidesNew);
}

void Object::DeleteObject(Object* object)
{
    delete object;
}