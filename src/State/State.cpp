#include "State/State.h"
#include "Game.h"
#include "LevelManager/LevelManager.h"
#include "Math/Vector2.h"
#include "State/Object.h"
#include "State/Player.h"
#include "State/Button.h"

bool elementOf(std::vector<std::string> &vec, std::string element) {
  for (size_t i = 0; i < vec.size(); i++)
  {
    if (vec[i] == element) return true;
  }
  return false;
}

State State::instance;

State &State::GetInstance() { return instance; }

void State::InitInternal()
{

  const float playersSpeed = 250.f;

  LevelManager::Init();

  currentLevel = LevelManager::GetLevels()["Level0"];
  tileCodeToTextureIndex["MA"] = 0;
  tileCodeToTextureIndex["FE"] = 1;
  tileCodeToTextureIndex["TB"] = 2;
  tileCodeToTextureIndex["WV"] = 3;
  tileCodeToTextureIndex["VB"] = 4;
  tileCodeToTextureIndex["VT"] = 5;
  tileCodeToTextureIndex["WH"] = 6;
  tileCodeToTextureIndex["HL"] = 7;
  tileCodeToTextureIndex["HR"] = 8;
  tileCodeToTextureIndex["T1"] = 9;
  tileCodeToTextureIndex["C1"] = 10;
  tileCodeToTextureIndex["C2"] = 11;
  tileCodeToTextureIndex["C3"] = 12;
  tileCodeToTextureIndex["C4"] = 13;

  wallCodes.push_back("VB");
  wallCodes.push_back("VT");
  wallCodes.push_back("WV");
  wallCodes.push_back("WH");
  wallCodes.push_back("HL");
  wallCodes.push_back("HR");
  wallCodes.push_back("C1");
  wallCodes.push_back("C2");
  wallCodes.push_back("C3");
  wallCodes.push_back("C4");
  wallCodes.push_back("T1");
  wallCodes.push_back("T2");
  wallCodes.push_back("T3");
  wallCodes.push_back("T4");

  for (int y = 0; y < NUM_OF_TILES_COL; y++)
  {
    for (int x = 0; x < NUM_OF_TILES_ROW; x++)
    {
      if (currentLevel->grid[y][x] == "MA")
      {
        float xOffset = x * TILE_SIZE;
        float yOffset = y * TILE_SIZE;
        Vector2 tilePosition(xOffset, yOffset);
        std::string tileName = "Tile" + std::to_string(x) + std::to_string(y);
        Object *GroundTileMap = new Object(
            tileName, tilePosition, Vector2(TILE_SIZE, TILE_SIZE), false,
            "./assets/Atlas.png", Vector2(64, 0), Vector2(32, 32), -1, true);
        AddObjectToAll(GroundTileMap);
        Player *SantaMale =
            new Player("Santa Male", Vector2(TILE_SIZE * x, TILE_SIZE * y),
                       Vector2(64, 64), "./assets/Atlas.png",
                       Vector2(0, 0), Vector2(32, 32), 0, true, 0, playersSpeed);
        AddObjectToAll(SantaMale);
      }
      else if (currentLevel->grid[y][x] == "FE")
      {
        float xOffset = x * TILE_SIZE;
        float yOffset = y * TILE_SIZE;
        Vector2 tilePosition(xOffset, yOffset);
        std::string tileName = "Tile" + std::to_string(x) + std::to_string(y);
        Object *GroundTileMap = new Object(
            tileName, tilePosition, Vector2(TILE_SIZE, TILE_SIZE), false,
            "./assets/Atlas.png", Vector2(64, 0), Vector2(32, 32), -1, true);
        AddObjectToAll(GroundTileMap);
        Player *SantaFemale =
            new Player("Santa Female", Vector2(TILE_SIZE * x, TILE_SIZE * y),
                       Vector2(64, 64), "./assets/Atlas.png", Vector2(32, 0),
                       Vector2(32, 32), 0, true, 1, playersSpeed);
        AddObjectToAll(SantaFemale);
      }
      else if (currentLevel->grid[y][x] == "BT")
      {
        float xOffset = x * TILE_SIZE;
        float yOffset = y * TILE_SIZE;
        Vector2 tilePosition(xOffset, yOffset);
        std::string tileName = "Tile" + std::to_string(x) + std::to_string(y);
        Object *GroundTileMap = new Object(
            tileName, tilePosition, Vector2(TILE_SIZE, TILE_SIZE), false,
            "./assets/Atlas.png", Vector2(64, 0), Vector2(32, 32), -1, true);
        AddObjectToAll(GroundTileMap);
      } else if (elementOf(wallCodes, currentLevel->grid[y][x])) {
        float xOffset = x * TILE_SIZE;
        float yOffset = y * TILE_SIZE;
        Vector2 tilePosition(xOffset, yOffset);
        std::string tileName = "Wall" + std::to_string(x) + std::to_string(y);
        Object *Wall = new Object(
            tileName, Vector2(TILE_SIZE * x, TILE_SIZE * y), Vector2(TILE_SIZE, TILE_SIZE), true,
            "./assets/Atlas.png", Vector2(tileCodeToTextureIndex[currentLevel->grid[y][x]] * 32, 0), Vector2(32, 32), 0, true);
        AddObjectToAll(Wall);
        AddObjectToColliding(Wall);
      } else if (currentLevel->grid[y][x][0] == 'B') {
        std::cout << "Button" << std::endl;
        float xOffset = x * TILE_SIZE;
        float yOffset = y * TILE_SIZE;
        int opensDoorCode = (currentLevel->grid[y][x][1] - '0');
        Vector2 tilePosition(xOffset, yOffset);
        std::string tileName = "ButtonPressed" + std::to_string(x) + std::to_string(y);
        Button* PressedButton = new Button(
            tileName, Vector2(TILE_SIZE * x, TILE_SIZE * y), Vector2(TILE_SIZE, TILE_SIZE), true,
            "./assets/Atlas.png", Vector2(15 * 32, 0), Vector2(32, 32), 0, false,true, opensDoorCode);
        AddObjectToAll(PressedButton);
        AddObjectToColliding(PressedButton);

        tileName = "ButtonNotPressed" + std::to_string(x) + std::to_string(y);
        Button* NotPressedButton =  new Button(
            tileName, Vector2(TILE_SIZE * x, TILE_SIZE * y), Vector2(TILE_SIZE, TILE_SIZE), true,
            "./assets/Atlas.png", Vector2(14 * 32, 0), Vector2(32, 32), 1, true, false, opensDoorCode);
        AddObjectToAll(NotPressedButton);
        AddObjectToColliding(NotPressedButton);

        tileName = "Tile" + std::to_string(x) + std::to_string(y);
        Object *GroundTileMap = new Object(
            tileName, tilePosition, Vector2(TILE_SIZE, TILE_SIZE), false,
            "./assets/Atlas.png", Vector2(64, 0), Vector2(32, 32), -1, true);
        AddObjectToAll(GroundTileMap);
      }
    }
  }

  for (const auto &pair : allObjects)
  {
    pair.second->Begin();
  }
}

void State::Init() { GetInstance().InitInternal(); }

void State::UpdateInternal(float deltatime)
{
  for (const auto &pair : allObjects)
  {
    pair.second->Update(deltatime);
  }
}

void State::Update(float deltatime) { GetInstance().UpdateInternal(deltatime); }

void State::AddObjectToAll(Object *objectToAdd)
{
  if (objectToAdd)
  {
    allObjects[objectToAdd->name] = objectToAdd;
  }
}
void State::AddObjectToColliding(Object *objectToAdd)
{
  if (objectToAdd)
  {
    collidingObjects.push_back(objectToAdd);
  }
}

void State::MoveObjectInternal(Object *object, Vector2 newPosition)
{
  double dx = newPosition.x - object->position.x;
  double dy = newPosition.y - object->position.y;

  // Maximum x, y player can move to
  double maxX = fmax(object->position.x + dx, object->position.x);
  double maxY = fmax(object->position.y + dy, object->position.y);

  // Minimum x, y player can move to
  double minX = fmin(object->position.x + dx, object->position.x);
  double minY = fmin(object->position.y + dy, object->position.y);

  for (const auto &[name, collidingObject] : State::GetAllObjects())
  {
    if (!collidingObject->bCollides)
      continue;
    // If player is just under or above the wall
    if (collidingObject->position.x < object->position.x + object->size.x &&
        object->position.x <
            collidingObject->position.x + collidingObject->size.x)
    {
      // If player is above the wall
      if (collidingObject->position.y >= object->position.y + object->size.y)
      {
        // Player can move up to the upper side of the wall
        maxY = fmin(maxY, collidingObject->position.y - object->size.y);
      }
      else if (collidingObject->position.y + collidingObject->size.y <=
               object->position.y)
      { // If player is under the wall
        // Player can move up to the lower side of the wall
        minY =
            fmax(minY, collidingObject->position.y + collidingObject->size.y);
      }
    }
    // If player is just on the left or on the right of the wall
    if (collidingObject->position.y < object->position.y + object->size.y &&
        object->position.y <
            collidingObject->position.y + collidingObject->size.y)
    {
      // If player is on the left of the wall
      if (collidingObject->position.x >= object->position.x + object->size.x)
      {
        // The player can move up to the left side of the wall
        maxX = fmin(maxX, collidingObject->position.x - object->size.x);
      }
      else if (collidingObject->position.x + collidingObject->size.x <=
               object->position.x)
      { // If player is on the right of the wall
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

void State::MoveObject(Object *object, Vector2 newPosition)
{
  State::GetInstance().MoveObjectInternal(object, newPosition);
}
State::~State() {}