#pragma once
#include "2d/CCScene.h"
#include "controllers/GameController.h"


// 游戏主场景
// 游戏入口
class GameScene : public cocos2d::Scene
{
public:
    static GameScene* create(int levelId = 1)
    {
        auto scene = new (std::nothrow) GameScene();
        if (scene && scene->_init(levelId))
        {
            scene->autorelease();
            return scene;
        }
        CC_SAFE_DELETE(scene);
        return nullptr;
    }
    
private:
    GameController _gameController;

    bool _init(int levelId)
    {
        if (!Scene::init())
            return false;
        
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        auto bgLayer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 165, 0, 255));
        this->addChild(bgLayer);
        
        auto drawNode = cocos2d::DrawNode::create();
        drawNode->drawSolidRect(
            cocos2d::Vec2(100, 200),                    // 左下角
            cocos2d::Vec2(980, 600),                // 右上角
            cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f) // 红色 (R=1, G=0, B=0, A=1)
        );
        this->addChild(drawNode);
        
        _gameController.startGame(levelId, this);
        return true;
    }
};