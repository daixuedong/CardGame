#pragma once

#include "models/CardModel.h"

// 卡牌匹配规则
class MatchService
{
public:
    // 判断candidate是否匹配trayTop
    static bool canMatch(const CardModel& candidate, const CardModel& trayTop)
    {
        if (candidate.face == CFT_NONE || trayTop.face == CFT_NONE) return false;
        int diff = (int)candidate.face - (int)trayTop.face;
        return diff == 1 || diff == -1;
    }
};