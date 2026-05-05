#pragma once
#include "2d/CCNode.h"
#include "models/CardModel.h"

// 单张卡牌视图

class CardView : public cocos2d::Node
{
public:
    using ClickCallback = std::function<void(int cardId)>;
    
    static CardView* create(const CardModel& cardModel)
    {
        auto* v = new (std::nothrow) CardView();
        if (v && v->_init(cardModel))
        {
            v->autorelease();
            return v;
        }
        CC_SAFE_DELETE(v);
        return nullptr;
    }
    
    void setClickCallback(ClickCallback clickCallback) { _clickCallback = clickCallback; }
    int getCardId() const {return _cardId; }
    
    // 平移动画
    void moveAnimation(cocos2d::Vec2 targetPosition, float duration = 0.25f, std::function<void()> onComplete = nullptr);
    
    // 切换正背面显示
    void setFaceUp(bool faceUp)
    {
        _faceUp = faceUp;
        _updateDisplay();
    }
    
    
private:
    int _cardId = -1;
    CardFaceType _face = CFT_NONE;
    CardSuitType _suit = CST_NONE;
    bool _faceUp = true;
    cocos2d::Vec2 kAnchorPoint = {0.5f, 0.5f};
    cocos2d::Vec2 kSetPosition = {0.f, 0.f};
    
    // 正面内容节点（数字+花色），整体显示/隐藏
    cocos2d::Node* _frontNode = nullptr;
    ClickCallback _clickCallback;
    bool _init(const CardModel& cardModel);
    // 构建正面
    void _buildFront(cocos2d::Size cardSize);
    void _registerTouch();
    
    // 根据_faceUp显示或隐藏正面内容
    void _updateDisplay()
    {
        if (_faceUp)
            _frontNode->setVisible(_faceUp);
    }
};
