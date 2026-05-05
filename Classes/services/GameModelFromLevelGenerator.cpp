#include "services/GameModelFromLevelGenerator.h"

GameModel GameModelFromLevelGenerator::generateGameModel(int levelId, const LevelConfig& levelConfig)
{
    GameModel gameModel;
    gameModel.levelId = levelId;
    
    // 生成桌面牌
    for (const auto& cardId : levelConfig.playField)
    {
        CardModel cardModel;
        cardModel.id = gameModel.generateId();
        cardModel.face = (CardFaceType)cardId.cardFace;
        cardModel.suit = (CardSuitType)cardId.cardSuit;
        cardModel.faceUp = true;
        cardModel.position = cardId.position;
        gameModel.playfieldCards.push_back(cardModel);
    }
    
    // 生成备用牌
    for (const auto& cardId : levelConfig.stack)
    {
        CardModel cardModel;    
        cardModel.id = gameModel.generateId();
        cardModel.face = (CardFaceType)cardId.cardFace;
        cardModel.suit = (CardSuitType)cardId.cardSuit;
        cardModel.faceUp = false;
        gameModel.stackCards.push_back(cardModel);
    }
    
    if (!gameModel.stackCards.empty())
    {
        CardModel top = gameModel.stackCards.back();
        gameModel.stackCards.pop_back();
        top.faceUp = true;
        gameModel.trayCards.push_back(top);
    }
    
    gameModel.rebuildIndex();
    return gameModel;
}
