#include "State/Object.h"

Object::Object(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,bool bCollidesNew,
const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize, int zIndexNew)
 : name(newName), position(startingPosition), size(startingSize), bCollides(bCollidesNew), srcName(newSrcName),
 sourceRectanglePosition(newSourceRectanglePosition), sourceRectangleSize(newSourceRectangleSize), zIndex(zIndexNew)
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