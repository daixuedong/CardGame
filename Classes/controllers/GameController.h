#pragma once
#include "managers/UndoManager.h"
#include "models/GameModel.h"
#include "views/GameView.h"

// 游戏控制器
// 协调GameModel, GameView, UndoManager
class GameController
{
public:
    // 开始游戏
    void startGame(int levelId, cocos2d::Node* parent);
    // 处理桌面牌点击
    void handlePlayFieldCardClick(int cardId);
    // 处理备用牌点击
    void handleStackClick();
    
private:
    GameModel _gameModel;
    GameView* _gameView = nullptr;
    UndoManager _undoManager;
    float index;
    
    void _initCardViews();
    void _createCardView(const CardModel& cardModel, bool isStack);
    void _removeFromPlayField(int cardId)
    {
        auto& playField = _gameModel.playfieldCards;
        playField.erase(std::remove_if(
            playField.begin(),
            playField.end(), 
            [cardId](const CardModel& cardModel) { return cardModel.id == cardId; }), 
            playField.end()
            );
    }
    
    void _onUndoAnimRequest(int cardId, cocos2d::Vec2 position, bool faceUp)
    {
        _gameView->playUndoAnimation(cardId, position, faceUp);
    }
};
