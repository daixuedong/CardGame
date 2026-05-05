#pragma once
#include "cocos2d.h"
#include "views/CardView.h"
#include <functional>
#include <unordered_map>

// 游戏主视图
// 持有所有CardView
class GameView : public cocos2d::Node
{
public:
    using UndoClickCallback = std::function<void()>;
    
    static GameView* create()
    {
        auto view = new (std::nothrow) GameView();
        if (view && view->init())
        {
            view->autorelease();
            return view;
        }
        CC_SAFE_DELETE(view);
        return nullptr;
    }
    
    bool init() override
    {
        if (!Node::init())
            return false;
        _buildUndoButton();
        return true;
    }
    
    // CardView管理
    void addCardView(CardView* cardView, int zOrder = 0)
    {
        if (!cardView)
            return;
        addChild(cardView, zOrder);
        _cardViews[cardView->getCardId()] = cardView;
    }
    
    void removeCardView(int cardId)
    {
        auto it = _cardViews.find(cardId);
        if (it != _cardViews.end())
        {
            it->second->removeFromParent();
            _cardViews.erase(it);
        }
    }
    
    CardView* getCardView(int cardId)
    {
        auto it = _cardViews.find(cardId);
        return it != _cardViews.end() ? it->second : nullptr;
    }
    
    // ---- 动画接口 ----
    
    // 匹配动画：卡牌平移到手牌区
    void playMoveAnimation(int movingCardId, cocos2d::Vec2 targetPosition, std::function<void()> onComplete = nullptr);
    
    // 回退动画
    void playUndoAnimation(int cardId, cocos2d::Vec2 targetPosition, bool faceUp);
    
    // 回退按钮
    void setUndoClickCallback(UndoClickCallback callback)
    {
        _undoClickCallback = callback;
    }
    
    
private:
    std::unordered_map<int, CardView*> _cardViews;
    UndoClickCallback _undoClickCallback;
    void _buildUndoButton();
};
