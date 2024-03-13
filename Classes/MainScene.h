#pragma once

#include "cocos2d.h"
#include "GameMenu.h";
#include "GameTile.h";
#include <unordered_set>

class MainScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(MainScene);
    /*
    static HelloWorld* create()
    {
        HelloWorld* pRet = new HelloWorld();
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    */
private:
    cocos2d::Size _gameSize;
    GameMenu* _gameMenu;
    cocos2d::DrawNode* _playField;
    cocos2d::Label* _gameoverLabel;
    int _width;
    int _height;
    int _colorCount;
    std::vector<int> _map = {};
    std::queue<GameTile*> _tilePool = {};
    std::vector<GameTile*> _gameTiles = {};
    std::unordered_set<GameTile*> _closed = {};
    std::unordered_set<GameTile*> _open = {};
    std::unordered_set<GameTile*> _ceil = {};
    bool _canClick = true;
    int _score;

    void startGame(int width, int height, int colors);
    void setUpPlayField();
    void createMap();
    void createTiles();
    void onTilePressed(GameTile* tile);
    void getConnectedTiles(GameTile* tile);
    void checkNeighbour(int x, int y, int targetColor, bool isTop = false);
    void addScore();
    void fallCeiling();
    void checkForGameover();
    bool checkNeighbourForGameover(int x, int y, int targetColor);
    void displayLoseLabel();
    void displayWinLabel();
    void removeTile(GameTile* tile);
    GameTile* getTile();
    void restart();
    cocos2d::Color4F getColorByIndex(int index);
    int getFlattenIndex(int x, int y);
    bool checkBounds(int x, int y);

    const cocos2d::Color4F _colors[8] = {
        cocos2d::Color4F(1, 0, 0, 1),
        cocos2d::Color4F(0, 1, 0, 1),
        cocos2d::Color4F(0, 0, 1, 1),
        cocos2d::Color4F(1, 1, 0, 1),
        cocos2d::Color4F(0.8, 0.1, 1, 1),
        cocos2d::Color4F(0, 0.8, 0.9, 1),
        cocos2d::Color4F(1, 0.6, 0, 1),
        cocos2d::Color4F(0.9, 0.9, 0.9, 1)
    };
};
