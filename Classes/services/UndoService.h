#pragma once
#include "models/GameModel.h"


// 回退记录构建
// 在操作发生前拍摄快照压入UndiModel

class UndoService
{
public:
    // 记录桌面牌到手牌
    static void recordPlayFieldToTray(GameModel& gameModel, int playFieldId);
    // 记录备用牌到手牌
    static void recordStackToTray(GameModel& gameModel);
};
