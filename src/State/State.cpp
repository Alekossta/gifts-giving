#include "State/State.h"
#include "Game.h"
#include "Math/Vector2.h"
#include "State/Object.h"
#include "State/Player.h"

State State::instance;

State &State::GetInstance() { return instance; }

void State::InitInternal() {

  const float playersSpeed = 250.f;

  // create santa male
  Player *SantaMale = new Player("Santa Male", Vector2(0, 0), Vector2(64, 64),
                                 "./assets/Atlas.png", Vector2(0, 0),
                                 Vector2(32, 32), 0, 0, playersSpeed);
  AddObjectToAll(SantaMale);
  AddObjectToColliding(SantaMale);

  // create santa female
  Player *SantaFemale = new Player(
      "Santa Female", Vector2(64, 0), Vector2(64, 64), "./assets/Atlas.png",
      Vector2(32, 0), Vector2(32, 32), 0, 1, playersSpeed);
  AddObjectToAll(SantaFemale);
  AddObjectToColliding(SantaFemale);

  // create ground tiles
  float tileSize = 80;
  unsigned tilesHorizontal = Game::GetWidth() / tileSize; // 32x32 tiles
  unsigned tilesVertical = Game::GetHeight() / tileSize;
  for (unsigned i = 0; i < tilesHorizontal; i++) {
    for (unsigned j = 0; j < tilesVertical; j++) {
      float xOffset = i * tileSize;
      float yOffset = j * tileSize;
      Vector2 tilePosition(xOffset, yOffset);
      std::string tileName = "Tile" + std::to_string(i) + std::to_string(j);
      Object *GroundTileMap =
          new Object(tileName, tilePosition, Vector2(tileSize, tileSize), false,
                     "./assets/Atlas.png", Vector2(64, 0), Vector2(32, 32), -1);
      AddObjectToAll(GroundTileMap);
    }
  }

  Object *Wall = new Object(
      "Wall", Vector2(100, 100), Vector2(tileSize, tileSize), true, "./assets/Atlas.png",
      Vector2(64 + 32, 0), Vector2(32, 32), 1);
  AddObjectToAll(Wall);
  AddObjectToColliding(Wall);


  for (const auto &pair : allObjects) {
    pair.second->Begin();
  }
}

void State::Init() { GetInstance().InitInternal(); }

void State::UpdateInternal(float deltatime) {
  for (const auto &pair : allObjects) {
    pair.second->Update(deltatime);
  }
}

void State::Update(float deltatime) { GetInstance().UpdateInternal(deltatime); }

void State::AddObjectToAll(Object *objectToAdd) {
  if (objectToAdd) {
    allObjects[objectToAdd->name] = objectToAdd;
  }
}
void State::AddObjectToColliding(Object *objectToAdd) {
  if (objectToAdd) {
    collidingObjects.push_back(objectToAdd);
  }
}

void State::MoveObjectInternal(Object *object, Vector2 newPosition) {
  double dx = newPosition.x - object->position.x;
  double dy = newPosition.y - object->position.y;

  // Maximum x, y player can move to
  double maxX = fmax(object->position.x + dx, object->position.x);
  double maxY = fmax(object->position.y + dy, object->position.y);

  // Minimum x, y player can move to
  double minX = fmin(object->position.x + dx, object->position.x);
  double minY = fmin(object->position.y + dy, object->position.y);

  for (const auto &[name, collidingObject] : State::GetAllObjects()) {
    if (!collidingObject->bCollides)
      continue;
    // If player is just under or above the wall
    if (collidingObject->position.x <= object->position.x + object->size.x &&
        object->position.x <=
            collidingObject->position.x + collidingObject->size.x) {
      // If player is above the wall
      if (collidingObject->position.y >= object->position.y + object->size.y) {
        // Player can move up to the upper side of the wall
        maxY = fmin(maxY, collidingObject->position.y - object->size.y);
      } else if (collidingObject->position.y + collidingObject->size.y <=
                 object->position.y) { // If player is under the wall
        // Player can move up to the lower side of the wall
        minY =
            fmax(minY, collidingObject->position.y + collidingObject->size.y);
      }
    }
    // If player is just on the left or on the right of the wall
    if (collidingObject->position.y <= object->position.y + object->size.y &&
        object->position.y <=
            collidingObject->position.y + collidingObject->size.y) {
      // If player is on the left of the wall
      if (collidingObject->position.x >= object->position.x + object->size.x) {
        // The player can move up to the left side of the wall
        maxX = fmin(maxX, collidingObject->position.x - object->size.x);
      } else if (collidingObject->position.x + collidingObject->size.x <=
                 object->position.x) { // If player is on the right of the wall
        // The player can move up to the right side of the wall
        minX =
            fmax(minX, collidingObject->position.x + collidingObject->size.x);
      }
    }
  }

  // Move the player
  object->position.x = fmin(maxX, object->position.x + dx);
  object->position.x = fmax(minX, object->position.x);

  object->position.y = fmin(maxY, object->position.y + dy);
  object->position.y = fmax(minY, object->position.y);
}

void State::MoveObject(Object *object, Vector2 newPosition) {
  State::GetInstance().MoveObjectInternal(object, newPosition);
}
State::~State() {}