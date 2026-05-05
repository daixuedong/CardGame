#include "CardView.h"

void CardView::moveAnimation(cocos2d::Vec2 targetPosition, float duration, std::function<void()> onComplete)
{
    stopAllActions();
    auto move = cocos2d::MoveTo::create(duration, targetPosition);
    
    if (onComplete)
    {
        auto seq = cocos2d::Sequence::create(
            move,
            cocos2d::CallFunc::create(onComplete),
            nullptr
            );
        runAction(seq);
    }
    else
    {
        runAction(move);
    }
}

bool CardView::_init(const CardModel& cardModel)
{
    if (!Node::init())
        return false;
    
    _cardId = cardModel.id;
    _face = cardModel.face;
    _suit = cardModel.suit;
    _faceUp = cardModel.faceUp;
    
    // 卡牌底板
    auto base = cocos2d::Sprite::create(CardResConfig::getCardBase());
    if (base)
    {
        base->setAnchorPoint(kAnchorPoint);
        base->setPosition(kSetPosition);
        addChild(base, 0);
        
        setContentSize(base->getContentSize());
    }
    
    // 正面内容
    _frontNode = cocos2d::Node::create();
    _buildFront(base ? base->getContentSize() : cocos2d::Size(140, 200));
    addChild(_frontNode, 1);
    
    _updateDisplay();
    setPosition(cardModel.position);
    _registerTouch();
    
    return true;
}

void CardView::_buildFront(cocos2d::Size cardSize)
{
    // 中央大数字
    auto bigNum = cocos2d::Sprite::create(CardResConfig::getBigImage(_face, _suit));
    if (bigNum)
    {
        bigNum->setAnchorPoint(kAnchorPoint);
        bigNum->setPosition(kSetPosition);
        _frontNode->addChild(bigNum);
    }

    // 左上角小数字
    auto smallNumTL = cocos2d::Sprite::create(CardResConfig::getSmallImage(_face, _suit));
    if (smallNumTL)
    {
        smallNumTL->setAnchorPoint(kAnchorPoint);
        smallNumTL->setPosition(cocos2d::Vec2(kSetPosition.x - 80, kSetPosition.y + 130));
        _frontNode->addChild(smallNumTL);
    }

    // 右上角花色
    auto suitTR = cocos2d::Sprite::create(CardResConfig::getSuitImage(_suit));
    if (suitTR)
    {
        suitTR->setAnchorPoint(kAnchorPoint);
        suitTR->setPosition(cocos2d::Vec2(kSetPosition.x + 80, kSetPosition.y + 130));
        _frontNode->addChild(suitTR);
    }
}

void CardView::_registerTouch()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event*) -> bool
    {
        cocos2d::Vec2 local = convertToNodeSpace(touch->getLocation());
        cocos2d::Size size = getContentSize();
        cocos2d::Rect rect(0, 0, size.width, size.height);
        return rect.containsPoint(local);
    };
    
    listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event*)
    {
        cocos2d::Vec2 local = convertToNodeSpace(touch->getLocation());
        cocos2d::Size size = getContentSize();
        cocos2d::Rect rect(0, 0, size.width, size.height);
        if (rect.containsPoint(local) && _clickCallback)
            _clickCallback(_cardId);
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
