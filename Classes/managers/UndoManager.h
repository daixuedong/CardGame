#pragma once
#include <functional>

#include "cocos2d.h"
#include "models/GameModel.h"


// 回退管理器
class UndoManager
{
public:
    // 动画回调
    using UndoAnimCallback = std::function<void(int cardId, cocos2d::Vec2 targetPos, bool faceUp)>;
    
    void init(GameModel* gameModel, UndoAnimCallback callback)
    {
        _gameModel = gameModel;
        _animCallback = callback;
    }
    
    bool canUndo() const
    {
        return _gameModel && _gameModel->undoModel.canUndo();
    }
    
    // 执行一步回退，返回false表示无可回退记录
    bool undo();
    
private:
    GameModel* _gameModel = nullptr;
    UndoAnimCallback _animCallback;
    
    // 回退“桌面牌 -> 手牌"
    // snapshots[0] = 桌面牌快照
    // snapshots[1] = 手牌快照
    void _undoPlayFieldToTray(const UndoRecord& undoRecord);
    
    // 回退“备用牌 -> 手牌”
    // snapshots[0] = 备用牌
    // snapshots[1] = 手牌
    void _undoStackToTray(const UndoRecord& undoRecord);
};
