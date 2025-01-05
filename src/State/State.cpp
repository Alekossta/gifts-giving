#include "State/State.h"
#include "Game.h"
#include "LevelManager/LevelManager.h"
#include "Math/Vector2.h"
#include "State/Object.h"
#include "State/Player.h"
#include "State/Button.h"
#include "State/Door.h"
#include "State/Child.h"
#include "General.h"
#include "Graphics/Graphics.h"
#include <algorithm>

bool elementOf(std::vector<std::string> &vec, std::string element) {
  for (size_t i = 0; i < vec.size(); i++)
  {
    if (vec[i] == element) return true;
  }
  return false;
}

State State::instance;

State &State::GetInstance() { return instance; }

std::vector<std::string> introText = {"Gifts-Giving",
"Spread joy, one gift at a time! It's Christmas Eve!",
" Santa Claus and Mrs. Claus need your help to deliver gifts to all the children before time runs out.",
"Instructions:",
"1. Move Around:",
"- Player 1 (Mrs. Claus): Use the arrow keys.",
"- Player 2 (Santa): Use WASD.",
"2. Deliver Gifts:",
"- Approach a child together.",
" - Player 1 presses Enter, and Player 2 presses Space at the same time to deliver a gift.",
"3. Don't Delay!:",
"- Each child has a limited time to wait before receiving their gift.",
"- If a child waits too long, you lose 1 life.",
"4. Win the Game:",
"- Deliver as many gifts as you can before you run out of lives!",
"Press Space to Start!"
};

std::vector<std::string> gameOverText = {
  "Game Over!",
  "Press Space to Play Again!"
};

void State::setupTileCodeToTextureIndex()
{
  tileCodeToTextureIndex["MA0"] = 0;
  tileCodeToTextureIndex["FE0"] = 1;
  tileCodeToTextureIndex["TB0"] = 2;
  tileCodeToTextureIndex["WV0"] = 3;
  tileCodeToTextureIndex["VB0"] = 4;
  tileCodeToTextureIndex["VT0"] = 5;
  tileCodeToTextureIndex["WH0"] = 6;
  tileCodeToTextureIndex["HL0"] = 7;
  tileCodeToTextureIndex["HR0"] = 8;
  tileCodeToTextureIndex["T10"] = 9;
  tileCodeToTextureIndex["C10"] = 10;
  tileCodeToTextureIndex["C20"] = 11;
  tileCodeToTextureIndex["C30"] = 12;
  tileCodeToTextureIndex["C40"] = 13;
}

void State::setupWallCodes()
{
  wallCodes.push_back("VB0");
  wallCodes.push_back("VT0");
  wallCodes.push_back("WV0");
  wallCodes.push_back("WH0");
  wallCodes.push_back("HL0");
  wallCodes.push_back("HR0");
  wallCodes.push_back("C10");
  wallCodes.push_back("C20");
  wallCodes.push_back("C30");
  wallCodes.push_back("C40");
  wallCodes.push_back("T10");
  wallCodes.push_back("T20");
  wallCodes.push_back("T30");
  wallCodes.push_back("T40");
}

void State::setupGifts()
{
  gifts.push_back(" a bike!");
  gifts.push_back(" a dall!");
  gifts.push_back(" a ball!");
  gifts.push_back(" a plane!");
  gifts.push_back(" a car!");
  gifts.push_back(" a kite!");
  gifts.push_back(" a yo-yo!");
  gifts.push_back(" a dog!");
  gifts.push_back(" a cat!");
  gifts.push_back(" a fish!");
}

void State::InitInternal()
{

  // constants
  const float playersSpeed = 250.f;

  // initialize variables
  goalNumOfActiveChildren = 3;
  initSecondsToGiveGift = 2;
  lives = 3;
  score = 0;
  lastSpawnTime = -1000000;

  // init level manager and open level 0
  LevelManager::Init();
  currentLevel = LevelManager::GetLevels()["Level0"];

  // setup for logic
  setupTileCodeToTextureIndex();
  setupWallCodes();
  setupGifts();

  srand(time(NULL));

  for (int y = 0; y < NUM_OF_TILES_COL; y++)
  {
    for (int x = 0; x < NUM_OF_TILES_ROW; x++)
    {
      float xOffset = x * TILE_SIZE;
      float yOffset = y * TILE_SIZE;
      Vector2 tilePosition(xOffset, yOffset);
      Vector2 tileSize, srcRectangle, srcRectangleSize(32, 32);
      int zIndex;
      bool bCollides;
      std::string src = Game::GetAssetPath("Atlas.png");

      // Draw Background Tile
      std::string tileName = "Tile" + std::to_string(x) + std::to_string(y);
      tileSize = Vector2(TILE_SIZE, TILE_SIZE);
      srcRectangle = Vector2(64, 0);
      bCollides = false;
      zIndex = -1;
      Object *GroundTileMap = new Object(
            tileName, tilePosition, tileSize,
            src, srcRectangle, srcRectangleSize, zIndex, bCollides);
      AddObjectToAll(GroundTileMap);
      bool isNoWallPosition = true;
      if (currentLevel->grid[y][x] == "MA0")
      {
        tileSize = Vector2(64, 64);
        srcRectangle = Vector2(1, 0);
        srcRectangleSize = Vector2(26, 32);
        zIndex = 2;
        Player *SantaMale =
            new Player("Santa Male", tilePosition,
                       tileSize, src,
                       srcRectangle, srcRectangleSize, zIndex, 0, playersSpeed);
        SantaMale->Tags.push_back("Player");
        SantaMale->CollisionIgnoreTags.push_back("Player");
        AddObjectToAll(SantaMale);
      }
      else if (currentLevel->grid[y][x] == "FE0")
      {
        tileSize = Vector2(64, 64);
        srcRectangle = Vector2(33, 0);

        zIndex = 2;
        srcRectangleSize = Vector2(26, 32);
        Player *SantaFemale =
            new Player("Santa Female", tilePosition, tileSize, src, srcRectangle,
                       srcRectangleSize, zIndex, 1, playersSpeed);
        SantaFemale->Tags.push_back("Player");
        SantaFemale->CollisionIgnoreTags.push_back("Player");
        AddObjectToAll(SantaFemale);
        noWallPositions.push_back(tilePosition);
      }
      else if (elementOf(wallCodes, currentLevel->grid[y][x])) {
        std::string tileName = "Wall" + std::to_string(x) + std::to_string(y);
        tileSize = Vector2(TILE_SIZE, TILE_SIZE);
        srcRectangle = Vector2(tileCodeToTextureIndex[currentLevel->grid[y][x]] * 32, 0);
        zIndex = 1;
        bCollides = true;
        Object *Wall = new Object(
            tileName, tilePosition, tileSize,
           src, srcRectangle, srcRectangleSize, zIndex);
        AddObjectToAll(Wall);
        isNoWallPosition = false;
      } else if (currentLevel->grid[y][x][0] == 'B' && currentLevel->grid[y][x] != "BT0") {
        int opensDoorCode = (currentLevel->grid[y][x][1] - '0');
        tilePosition = Vector2(xOffset, yOffset);
        tileSize = Vector2(64, 64);
        bCollides = false;
        srcRectangle = Vector2(15*32, 0);
        zIndex = 1;
        std::string tileName = "Button" + std::to_string(x) + std::to_string(y);
        Button* Button1 = new Button(
            tileName, tilePosition, tileSize,
            src, srcRectangle, srcRectangleSize, zIndex, opensDoorCode);
        AddObjectToAll(Button1);
        isNoWallPosition = false;
      } else if (currentLevel->grid[y][x][0] == 'D') {
        int doorCode = (currentLevel->grid[y][x][1] - '0');
        bool bIsVertical = (currentLevel->grid[y][x][2] == 'V');
        tilePosition = Vector2(xOffset, yOffset);
        tileSize = Vector2(TILE_SIZE, TILE_SIZE);
        bCollides = true;
        srcRectangle = Vector2(17*32, 0);
        zIndex = 2;
        std::string tileName = "Door" + std::to_string(x) + std::to_string(y);
        Door* Door1 = new Door(
            tileName, tilePosition, tileSize,
            src, srcRectangle, srcRectangleSize, zIndex, doorCode, bIsVertical);
        AddObjectToAll(Door1);
        isNoWallPosition = false;
      }

      if (isNoWallPosition) {
        noWallPositions.push_back(tilePosition);
      }
    }
  }



  Vector2 positionLivesText(25, 25);
  livesText = new TextBox("LivesText", positionLivesText, {}, 2, "3");
  AddObjectToAll(livesText);

  Vector2 positionScoreText(Game::GetWidth() - 25, 25);
  scoreText = new TextBox("ScoreText", positionScoreText, {}, 2, "1");
  AddObjectToAll(scoreText);

  // create a child for the start

  // call begin for all objects
  for (const auto &pair : allObjects)
  {
    pair.second->Begin();
  }
  int yOffset = 0;
  int index = 0;
  for (auto intro : introText) {
     TextBox* introTextBox = new TextBox("intro" + std::to_string(index++), {60, 80 + yOffset}, {}, 2, intro, true,{255, 255, 255});
     AddObjectToAll(introTextBox);
     yOffset += 40;
  }
  yOffset = Game::GetHeight() * 0.5 - 20;
  index = 0;
  for (auto gameOver : gameOverText) {
     TextBox* gameOverTextBox = new TextBox("gameOver" + std::to_string(index++), {60, yOffset}, {}, 2, gameOver, true,{255, 255, 255});
     AddObjectToAll(gameOverTextBox);
     yOffset += 40;
  }
  bDisplayIntro = true;
  bGameOver = false;
}

void State::Init() { GetInstance().InitInternal(); }

bool State::isPositionValid(Object* object) {
  Object* player1 = GetAllObjects()["Santa Male"];
  if (AreObjectsOverlapping(object, player1)) return false;
  Object* player2 = GetAllObjects()["Santa Female"];
  if (AreObjectsOverlapping(object, player2)) return false;

  for (const auto &child : activeChildren) {
    if (AreObjectsOverlapping(object, child)) return false;
  }

  if (object->position.x + 50 + 2.5*TILE_SIZE > Game::GetWidth() || object->position.y - 55 - TILE_SIZE < 0) return false;
  return true;
}

void State::DestroyObjectInternal(const std::string& objectName)
{
  if (allObjects.find(objectName) == allObjects.end()) return;
  Object* objectToDestroy = allObjects[objectName];
  if(objectToDestroy)
  {
    for(Object* child : objectToDestroy->children)
    {
      if (!child) continue;
      DestroyObjectInternal(child->name);
    }
    Graphics::DestroySprite(objectName);
    allObjects[objectName] = NULL;
    allObjects.erase(objectName);
  }
}

void State::CreateChild(bool bStateOnly) {
    if(kidsSpawnInterval > 7 * 1000 )
    {
      kidsSpawnInterval -= 250;
    }

    std::string tileName = "Child" + std::to_string(rand() % (10000000));
    while (State::GetAllObjects().find(tileName) != State::GetAllObjects().end()) {
      tileName = "Child" + std::to_string(rand() % (10000000));
    } 
    Vector2 position;
    Vector2 tileSize = Vector2(40, 48);
    bool bCollides = true;
    Vector2 srcRectangle = Vector2(16*32 + 6, 8 + 32 * (rand() % 4));
    Vector2 srcRectangleSize = Vector2(20, 24);
    int zIndex = 1;
    std::string src = Game::GetAssetPath("Atlas.png");

    Object* testerObject = new Object("testObject", {}, tileSize, src, srcRectangle, srcRectangleSize, zIndex);
    do {
      int size = noWallPositions.size();
      position = testerObject->position = noWallPositions[rand() % size];
    } while (!isPositionValid(testerObject));
    delete testerObject;

    Object* textBackground = new Object(tileName + "textBoxBackground", position + (Vector2){30, -80},
     {2.5*TILE_SIZE, TILE_SIZE}, src, {19*32, 0}, {64, 32}, 3, false);
    TextBox* textBox = new TextBox(tileName + "textBox", position + (Vector2){50, -55}, {}, 4,
     "I want " + gifts[rand() % gifts.size()], true);
    TextBox* timeTextBox = new TextBox(tileName + "timeTextBox", position + (Vector2){8, -35}, {}, 4, "");

    Child* child = new Child(
        tileName, position, tileSize,
        src, srcRectangle, srcRectangleSize, zIndex, textBackground, textBox, timeTextBox, initSecondsToGiveGift);
    AddObjectToAll(child);
    AddObjectToAll(textBox);
    AddObjectToAll(textBackground);
    AddObjectToAll(timeTextBox);
    child->children.push_back(timeTextBox);
    child->children.push_back(textBackground);
    textBackground->children.push_back(textBox);
    activeChildren.insert(child);

    if(!bStateOnly)
    {
      Graphics::GetInstance().createSprite(tileName, child);
      Graphics::GetInstance().createTextSprite(tileName + "textBox", textBox);
      Graphics::GetInstance().createTextSprite(tileName + "timeTextBox", timeTextBox);
      Graphics::GetInstance().createSprite(tileName + "textBoxBackground", textBackground);
    }
}

void State::UpdateInternal(float deltatime)
{
  if (bDisplayIntro) {
    if(Input::IsKeyPressed(SDL_SCANCODE_SPACE)) {
      bDisplayIntro = false;
    }
  } else if (bGameOver) {
    for (auto& [name, object] : allObjects) {
      if (!startsWith(name, "gameOver")) object->setIsVisible(false);
      else object->setIsVisible(true);
    }
    if(Input::IsKeyPressed(SDL_SCANCODE_SPACE)) {
        State::Init();
        for (auto &[name, object] : State::GetAllObjects()) 
        {   
          TextBox* text = dynamic_cast<TextBox*>(object);    
          if (text) 
          {
              Graphics::GetInstance().createTextSprite(name, text);
          } 
          else // is normal object
          {
              Graphics::GetInstance().createSprite(name, object);
          }
        }
    }
  } else {
    for (auto& [name, object] : allObjects) {
      if (startsWith(name, "intro") || startsWith(name, "gameOver")) object->setIsVisible(false);
    }
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastSpawnTime >= kidsSpawnInterval) {
      // create also the sprite for the kid so false
      CreateChild(false);
      lastSpawnTime = currentTime;
    }
    for(auto& objectPair : allObjects)
    {
      objectPair.second->Update(deltatime);
    }
    if(livesText) livesText->setText(std::to_string(lives));
    if(scoreText) scoreText->setText(std::to_string(score));

    if (lives == 0) {
      bGameOver = true;
    }
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

bool State::AreObjectsOverlapping(Object* object1, Object* object2)
{
  // check x
  float object1EndX = object1->position.x + object1->size.x;
  float object2EndX = object2->position.x + object2->size.x;

  if(object1->position.x >= object2EndX || object2->position.x >= object1EndX) return false;


  // check y
  float object1EndY = object1->position.y + object1->size.y;
  float object2EndY = object2->position.y + object2->size.y;

  if(object1->position.y >= object2EndY || object2->position.y >= object1EndY) return false;

  return true;
}

bool State::AreObjectsClose(Object* object1, Object* object2) 
{
  return fabs(object1->position.x + object1->size.x - object2->position.x) < 10 && 
         fabs(object1->position.y + object1->size.y - object2->position.y) < 10;
}

bool hasCommonElement(const std::vector<std::string>& vec1, const std::vector<std::string>& vec2) {
    for (const auto& item : vec1) {
        if (std::find(vec2.begin(), vec2.end(), item) != vec2.end()) {
            return true;
        }
    }
    return false;
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
    if (!collidingObject->bCollides ||
     hasCommonElement(collidingObject->Tags, object->CollisionIgnoreTags))
    {
      continue;
    }

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
State::~State() {
  
}