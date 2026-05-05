#include "GameController.h"

#include "configs/loaders/LevelConfigLoader.h"
#include "configs/models/LevelConfig.h"
#include "services/GameModelFromLevelGenerator.h"
#include "services/MatchService.h"
#include "services/UndoService.h"

void GameController::startGame(int levelId, cocos2d::Node* parent)
{
    // 加载关卡配置
    LevelConfig levelConfig = LevelConfigLoader::loadLevelConfig(levelId);
    
    // GameModel
    _gameModel = GameModelFromLevelGenerator::generateGameModel(levelId, levelConfig);
    
    // 创建GameView
    _gameView = GameView::create();
    parent->addChild(_gameView);
    
    // 初始化UndoManager
    _undoManager.init(&_gameModel, [this](int cardId, cocos2d::Vec2 position, bool faceUp)
    {
        _onUndoAnimRequest(cardId, position, faceUp);
    });
    
    // 注册回退按钮
    _gameView->setUndoClickCallback([this]()
    {
        _undoManager.undo();
    });
    
    // 初始化所有CardView
    _initCardViews();
}

void GameController::handlePlayFieldCardClick(int cardId)
{
    CardModel* playCard = _gameModel.findCard(cardId);
    CardModel* trayTop = _gameModel.topTrayCard();
    if (!playCard || !trayTop) return;
    if (!playCard->faceUp) return;
    if (!MatchService::canMatch(*playCard, *trayTop)) return;

    // 先保存拷贝，避免指针失效
    CardModel cardCopy = *playCard;
    cocos2d::Vec2 trayPosition = trayTop->position;
    cardCopy.position = trayPosition;

    // 记录回退
    UndoService::recordPlayFieldToTray(_gameModel, cardId);

    // 更新 Model
    _removeFromPlayField(cardId);
    _gameModel.trayCards.push_back(cardCopy); 
    _gameModel.rebuildIndex();

    // 播放动画
    _gameView->playMoveAnimation(cardId, trayPosition);
}

void GameController::handleStackClick()
{
    CardModel* stackTop = _gameModel.topStackCard();    
    if (!stackTop) return;
    
    // 记录回退
    UndoService::recordStackToTray(_gameModel);
    
    // 目标位置
    CardModel* trayTop = _gameModel.topTrayCard();
    cocos2d::Vec2 trayPosition = trayTop ? trayTop->position : cocos2d::Vec2(700, 400);
    
    // 更新Model
    CardModel drawn = *stackTop;
    _gameModel.stackCards.pop_back();
    drawn.faceUp = true;
    drawn.position = trayPosition;
    _gameModel.trayCards.push_back(drawn);
    _gameModel.rebuildIndex();
    
    // 播放动画
    _gameView->playMoveAnimation(drawn.id, trayPosition);
}

void GameController::_initCardViews()
{
    // 桌面牌
    for (const auto& card : _gameModel.playfieldCards)
    {
        _createCardView(card, false);
    }
    
    // 备用牌
    if (!_gameModel.stackCards.empty())
    {
        for (auto& card : _gameModel.stackCards)
        {
            card.position = cocos2d::Vec2(300+index, 400);
            index += 100;
            _createCardView(card, true);
        }
    }
    
    // 手牌区
    if (!_gameModel.trayCards.empty())
    {
        _gameModel.trayCards.back().position = cocos2d::Vec2(700, 400);
        _createCardView(_gameModel.trayCards.back(), false);
    }
}

void GameController::_createCardView(const CardModel& cardModel, bool isStack)
{
    auto* cardView = CardView::create(cardModel);
    if (!cardView) return;
    
    if (isStack)
    {
        // 点击备用堆
        cardView->setClickCallback([this](int)
        {
            handleStackClick();
        });
    }
    else
    {
        cardView->setClickCallback([this](int cardId)
        {
            // 判断是桌面牌还是手牌区顶牌
            bool isPlayField = false;
            for (const auto& card : _gameModel.playfieldCards)
            {
                if (card.id == cardId)
                {
                    isPlayField = true;
                    break;
                }
            }
            if (isPlayField)
            {
                handlePlayFieldCardClick(cardId);
            }
        });
    }
    
    _gameView->addCardView(cardView, 0);
}
