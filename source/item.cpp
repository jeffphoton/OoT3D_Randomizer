#include "item.hpp"

#include <array>

#include "logic.hpp"
#include "random.hpp"
#include "../code/src/item_override.h"

Item::Item(std::string name_, ItemType type_, int getItemId_, bool advancement_, bool* logicVar_, u16 price_)
    : name(std::move(name_)),
      type(type_),
      getItemId(getItemId_),
      advancement(advancement_),
      logicVar(logicVar_),
      price(price_) {}

Item::Item(std::string name_, ItemType type_, int getItemId_, bool advancement_, u8* logicVar_, u16 price_)
    : name(std::move(name_)),
      type(type_),
      getItemId(getItemId_),
      advancement(advancement_),
      logicVar(logicVar_),
      price(price_) {}

Item::~Item() = default;

void Item::ApplyEffect() {
    if (std::holds_alternative<bool*>(logicVar)) {
        *std::get<bool*>(logicVar) = true;
    } else {
        *std::get<u8*>(logicVar) += 1;
    }
    Logic::UpdateHelpers();
}

void Item::UndoEffect() {
    if (std::holds_alternative<bool*>(logicVar)) {
        *std::get<bool*>(logicVar) = false;
    } else {
        *std::get<u8*>(logicVar) -= 1;
    }
    Logic::UpdateHelpers();
}

ItemOverride_Value Item::Value() const {
    //just a random list of progression items
    static constexpr std::array<u16, 10> items = {
        GI_BOOMERANG,
        GI_HAMMER,
        GI_ARROW_LIGHT,
        0x80,
        0x81,
        0x82,
        0x83,
        0x84,
        0x85,
        0x8A,
    };

    ItemOverride_Value val;
    val.all = 0;
    val.itemId = getItemId;
    if (getItemId == GI_ICE_TRAP) {
        val.looksLikeItemId = RandomElement(items);
    }
    return val;
}
