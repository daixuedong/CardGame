#include "UndoManager.h"

bool UndoManager::undo()
{
    if (!canUndo())
        return false;
    
    UndoRecord undoRecord = _gameModel->undoModel.pop();

    switch (undoRecord.type)
    {
    case UndoType::UT_PLAY_FIELD_TO_TRAY:
        _undoPlayFieldToTray(undoRecord);
        break;
    case UndoType::UT_BACKUP_TO_HANLD:
        _undoStackToTray(undoRecord);
        break;
    default:
        CCLOG("[UndoManager] 不知到什么类型");
        break;
    }
    return true;
}

void UndoManager::_undoPlayFieldToTray(const UndoRecord& undoRecord)
{
    if (undoRecord.snapshots.size() < 2)
        return;
    
    const CardModel& pfSnap = undoRecord.snapshots[0];
    const CardModel& traySnap = undoRecord.snapshots[1];
    CCLOG("[Undo] pfSnap id=%d face=%d", pfSnap.id, pfSnap.face);
    CCLOG("[Undo] traySnap id=%d face=%d", traySnap.id, traySnap.face);
    
    // 把手牌移回桌面
    if (!_gameModel->trayCards.empty())
    {
        CardModel moved = _gameModel->trayCards.back();
        _gameModel->trayCards.pop_back();
        
        moved.position = pfSnap.position;
        moved.faceUp = pfSnap.faceUp;
        _gameModel->playfieldCards.push_back(moved);
        _gameModel->rebuildIndex();
        
        if (_animCallback)
            _animCallback(moved.id, moved.position, moved.faceUp);
    }
}


void UndoManager::_undoStackToTray(const UndoRecord& undoRecord)
{
    if (undoRecord.snapshots.size() < 2)
        return;

    const CardModel& stackSnap = undoRecord.snapshots[0];
    const CardModel& traySnap  = undoRecord.snapshots[1];

    // 把手牌顶牌移回备用堆
    if (!_gameModel->trayCards.empty())
    {
        CardModel moved = _gameModel->trayCards.back();
        _gameModel->trayCards.pop_back();

        moved.faceUp   = false;
        moved.position = stackSnap.position;  
        _gameModel->stackCards.push_back(moved);
        _gameModel->rebuildIndex();

        if (_animCallback)
            _animCallback(moved.id, stackSnap.position, false);
    }
}