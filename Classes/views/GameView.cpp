#include "GameView.h"

void GameView::playMoveAnimation(int movingCardId, cocos2d::Vec2 targetPosition, std::function<void()> onComplete)
{
    auto* cardView = getCardView(movingCardId);
    
    if (!cardView)
    {
        if (onComplete)
            onComplete();
        return;
    }
    
    cardView->setLocalZOrder(10);
    cardView->moveAnimation(targetPosition, 0.25f, [this, movingCardId, onComplete]()
    {
        auto* cardView2 = getCardView(movingCardId);
        if (cardView2)
            cardView2->setLocalZOrder(1);
        if (onComplete)
            onComplete();
    });
}


void GameView::playUndoAnimation(int cardId, cocos2d::Vec2 targetPosition, bool faceUp)
{
    auto* cardView = getCardView(cardId);
    if (!cardView)
        return;
    
    cardView->setLocalZOrder(10);
    cardView->moveAnimation(targetPosition, 0.2f, [cardView, faceUp]()
    {
        cardView->setFaceUp(faceUp);
        cardView->setLocalZOrder(0);
    });
}


void GameView::_buildUndoButton()
{
    auto dict = cocos2d::__Dictionary::createWithContentsOfFile("strings/strings.xml");
    const char* rollback = ((cocos2d::__String*)dict->objectForKey("rollback"))->getCString();
    auto label = cocos2d::Label::createWithSystemFont(rollback, "fonts/arial.ttf", 36);
    label->setColor(cocos2d::Color3B::BLACK);
    auto item = cocos2d::MenuItemLabel::create(label, [this](cocos2d::Ref*)
    {
        if (_undoClickCallback)
            _undoClickCallback();
    });
    
    auto menu = cocos2d::Menu::create(item, nullptr);
    menu->setPosition(cocos2d::Vec2(900, 400));
    addChild(menu, 100);
}
