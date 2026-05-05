#include "UndoService.h"

void UndoService::recordPlayFieldToTray(GameModel& gameModel, int playFieldId)
{
    UndoRecord undoRecord;
    
    undoRecord.type = UndoType::UT_PLAY_FIELD_TO_TRAY;
    
    // 快照：被移动的桌面牌 + 当前手牌顶牌
    // 桌面牌快照
    CardModel* pfCard = gameModel.findCard(playFieldId);
    if (pfCard)
        undoRecord.snapshots.push_back(*pfCard);
    
    // 手牌快照
    CardModel* trayCard = gameModel.topTrayCard();
    if (trayCard)
        undoRecord.snapshots.push_back(*trayCard);
    
    gameModel.undoModel.push(undoRecord);
}

void UndoService::recordStackToTray(GameModel& gameModel)
{
    UndoRecord undoRecord;
    
    undoRecord.type = UndoType::UT_BACKUP_TO_HANLD;
    
    // 备用牌快照
    CardModel* stackCard = gameModel.topStackCard();
    if (stackCard)
        undoRecord.snapshots.push_back(*stackCard);
    
    // 手牌快照
    CardModel* trayCard = gameModel.topTrayCard();
    if (trayCard)
        undoRecord.snapshots.push_back(*trayCard);
    
    gameModel.undoModel.push(undoRecord);
}
