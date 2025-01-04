#include "State/Object.h"

Object::Object(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,
    const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
    int zIndexNew,bool bCollidesNew, bool bOverlapsNew, bool bIsVisibleNew, float rotation)
 : name(newName), position(startingPosition), size(startingSize), srcName(newSrcName),
 sourceRectanglePosition(newSourceRectanglePosition), sourceRectangleSize(newSourceRectangleSize), zIndex(zIndexNew), 
bCollides(bCollidesNew), bIsVisible(bIsVisibleNew), rotation(rotation)
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

void Object::setIsVisible(bool newbIsVisible)
{
    bIsVisible = newbIsVisible;
    for(Object* child : children)
    {
        child->setIsVisible(newbIsVisible);
    }
}
