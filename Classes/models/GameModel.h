#pragma once

#include <vector>
#include <unordered_map>
#include "models/CardModel.h"
#include "models/UndoModel.h"

// 游戏数据来源
struct GameModel
{
    int levelId = 0;
    
    std::vector<CardModel> playfieldCards; // 桌面牌
    std::vector<CardModel> trayCards; // 手牌区
    std::vector<CardModel> stackCards;  // 备用牌区
    
    std::unordered_map<int, CardModel*> cardMap; // 快速索引 ID -> CardModel*
    
    UndoModel undoModel;
    int _nextId = 0;
    
    // 重建CardMap索引
    void rebuildIndex()
    {
        cardMap.clear();
        for (auto& cardModel : playfieldCards) cardMap[cardModel.id] = &cardModel;
        for (auto& cardModel : trayCards) cardMap[cardModel.id] = &cardModel;
        for (auto& cardModel : stackCards) cardMap[cardModel.id] = &cardModel;
    }
    
    // 生成唯一ID
    int generateId() { return _nextId++; }
    
    // 获取手牌区顶牌
    CardModel* topTrayCard() { return trayCards.empty() ? nullptr : &trayCards.back(); }
    
    // 获取备用牌区顶牌
    CardModel* topStackCard() { return stackCards.empty() ? nullptr : &stackCards.back(); }
    
    // 通过ID查找卡牌
    CardModel* findCard(int cardId)
    {
        auto it = cardMap.find(cardId);
        return it != cardMap.end() ? it->second : nullptr;
    }
};
