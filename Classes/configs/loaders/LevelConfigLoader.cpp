#include "configs/loaders/LevelConfigLoader.h"
#include <cocos2d.h>
#include <json/rapidjson.h>
#include <json/document.h>

LevelConfig LevelConfigLoader::loadLevelConfig(int id)
{
    LevelConfig levelConfig;
        
    char fileName[64];
    snprintf(fileName, sizeof(fileName), "levels/level%d.json", id);
    
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(fileName);
    std::string content = cocos2d::FileUtils::getInstance()->getStringFromFile(fullPath);
    
    if (content.empty())
    {
        CCLOG("[LevelConfigLoader] 加载失败：%s", fileName);
        return levelConfig;
    }
        
    rapidjson::Document doc;
    doc.Parse(content.c_str());
        
    if (doc.HasParseError() || !doc.IsObject())
    {
        CCLOG("[LevelConfigLoader] JSON解析错误");
        return levelConfig;
    }
        
    // 解析 playField
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray())
    {
        for (auto& item : doc["Playfield"].GetArray())
        {
            CardConfig cardConfig;
            cardConfig.cardFace = item["CardFace"].GetInt();
            cardConfig.cardSuit = item["CardSuit"].GetInt();
            cardConfig.position.x = item["Position"]["x"].GetFloat();
            cardConfig.position.y = item["Position"]["y"].GetFloat();
            levelConfig.playField.push_back(cardConfig);
        }
    }
        
    // 解析备用牌
    if (doc.HasMember("Stack") && doc["Stack"].IsArray())
    {
        for (auto& item : doc["Stack"].GetArray())
        {
            CardConfig cardConfig;
            cardConfig.cardFace = item["CardFace"].GetInt();
            cardConfig.cardSuit = item["CardSuit"].GetInt();
            levelConfig.stack.push_back(cardConfig);
        }
    }
    return levelConfig;
    
}