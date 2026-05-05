#pragma once

#include "models/CardModel.h"

// 回退类型
enum class UndoType
{
    UT_PLAY_FIELD_TO_TRAY, // 桌面牌到手牌区
    UT_BACKUP_TO_HANLD, // 备用牌到手牌区
};

// 单步回退记录
// 存储操作之前的卡牌快照
struct UndoRecord
{
    UndoType type;
    std::vector<CardModel> snapshots;
};

// 以栈的形式存储回退记录
struct UndoModel
{
    std::vector<UndoRecord> records;
    bool canUndo() const { return !records.empty(); }
    void push(const UndoRecord& record) { records.push_back(record); }
    
    UndoRecord pop()
    {
        UndoRecord record = records.back();
        records.pop_back();
        return record;
    }
    
    void clear() { records.clear(); }
};
