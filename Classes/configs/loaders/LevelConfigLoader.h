#pragma once

#include <configs/models/LevelConfig.h>

// 关卡配置加载逻辑
class LevelConfigLoader
{
public:
    static LevelConfig loadLevelConfig(int id);
};