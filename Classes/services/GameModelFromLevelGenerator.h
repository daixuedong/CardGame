#pragma once

#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"

// 将静态配置（LevelConfig）转换为动态运行时数据（GameModel），并处理卡牌随机生成策略
class GameModelFromLevelGenerator
{
public:
    static GameModel generateGameModel(int levelId, const LevelConfig& levelConfig);
};