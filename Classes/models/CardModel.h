#pragma once

#include "configs/models/CardResConfig.h"
#include "cocos2d.h"

// 单张卡牌运行时的数据
struct CardModel
{
    int id = -1;
    CardFaceType face = CFT_NONE;  // 牌正面数字
    CardSuitType suit = CST_NONE;  // 花型
    bool faceUp = true;       // 是否为正面
    cocos2d::Vec2 position;  // 牌位置
};
