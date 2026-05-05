#pragma once

#include <vector>
#include "cocos2d.h"

// 单张卡牌的关卡配置数据
struct CardConfig
{
    int cardFace = 0;
    int cardSuit = 0;
    cocos2d::Vec2 position;
};

// 存储解析出的静态数据
struct LevelConfig
{
    std::vector<CardConfig> playField; // 桌面牌布局
    std::vector<CardConfig> stack; // 备用牌
};