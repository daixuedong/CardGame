#pragma once
#include <string>

// 花色类型
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // 梅花
    CST_DIAMONDS,   // 方块
    CST_HEARTS,     // 红桃
    CST_SPADES,     // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};

// 正面类型
enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

// 配置卡牌图片路径等静态资源映射
class CardResConfig
{
public:
    // 判断是否是桃花和方片
    static bool isRedSuit(CardSuitType suit) { return suit == CST_HEARTS || suit == CST_DIAMONDS; }
    
    // 大数字图片
    static std::string getBigImage(CardFaceType face, CardSuitType suit)
    {
        if (face < 0 || face >= CFT_NUM_CARD_FACE_TYPES) return "";
        std::string prefix = isRedSuit(suit) ? "res/number/big_red_" : "res/number/big_black_";
        return prefix + _getKNames()[face] + ".png";
    }
    
    // 小数字图片
    static std::string getSmallImage(CardFaceType face, CardSuitType suit)
    {
        if (face < 0 || face >= CFT_NUM_CARD_FACE_TYPES) return "";
        std::string prefix = isRedSuit(suit) ? "res/number/small_red_" : "res/number/small_black_";
        return prefix + _getKNames()[face] + ".png";
    }
    
    // 花色
    static std::string getSuitImage(CardSuitType suit)
    {
        if (suit < 0 || suit >= CST_NUM_CARD_SUIT_TYPES) return "";
        return "res/suits/" + std::string(_getKSuitNames()[suit]) + ".png";
    }
    
    // 底板
    static  std::string getCardBase()
    {
        return "res/card_general.png";
    }
    
private:
    static const char** _getKNames()
    {
        static const char* kNames[] = {
            "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
        };
        return kNames;
    }
    
    static const char** _getKSuitNames()
    {
        static const char* kSuitNames[] = {
            "club", "diamond", "heart", "spade"
        };
        return kSuitNames;
    }
};