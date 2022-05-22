#include <string.h>
#include "GildedRose.h"
#include <stdio.h>
#include <ctype.h>

typedef struct {
    const char* name;
    int type;
} ItemTypeReg;

// Define custom item list with specific type
// for items that do not contain item type keyword in their names
ItemTypeReg itemTypeReg[1] = {
    {"sulfuras", ITEM_TYPE_LEGENDARY}
};

Item*
init_item(Item* item, const char *name, int sellIn, int quality)
{
    item->sellIn = sellIn;
    item->quality = quality;
    item->name = strdup(name);
    
    return item;
}

extern char* 
print_item_to_buffer(char* buffer, Item* item) 
{
    sprintf(buffer, "%s, %d, %d", item->name, item->sellIn, item->quality);
}

void toLowerCaseStr(char* str, char* buf) {
    int i = 0;
    for(; str[i]; i++){
        buf[i] = tolower(str[i]);
    }
    buf[i] = 0x00;
}

int getItemType(Item item) {
    int type = ITEM_TYPE_COMMON;
    char lowerName[256];
    toLowerCaseStr(item.name, lowerName);
    if (strstr(lowerName, "aged") != NULL) {
        type |= ITEM_TYPE_AGED;
    }
    if (strstr(lowerName, "legendary") != NULL) {
        type |= ITEM_TYPE_LEGENDARY;
    }
    if (strstr(lowerName, "pass") != NULL) {
        type |= ITEM_TYPE_PASS;
    }
    if (strstr(lowerName, "conjured") != NULL) {
        type |= ITEM_TYPE_CONJURED;
    }
    for (int i = 0; i < (sizeof(itemTypeReg) / sizeof(itemTypeReg[0])); i++) {
        if (strstr(lowerName, itemTypeReg[i].name) != NULL) {
            type |= itemTypeReg[i].type;
        }
    }
    return type;
}

int calcNextSellIn(Item item, int type){
    if (type & ITEM_TYPE_LEGENDARY){
        // Only legendary item does not affect sellIn value
        return item.sellIn;
    }
    return item.sellIn - 1;
}

int calcNextQuality(Item item, int type){
    // The next quality value is calculated based on 
    // current sellIn value

    int nextQuality = item.quality;
    int modifier = 0;

    // TODO: to determine what is the logic for items belong to more than one type
    // The logic below assumes every items only belong to one type
    switch (type) {
        case ITEM_TYPE_COMMON:
            modifier = (item.sellIn <= 0) ? -2 : -1;
            break;
        case ITEM_TYPE_AGED:
            modifier = (item.sellIn <= 0) ? 2 : 1;
            break;
        case ITEM_TYPE_LEGENDARY:
            modifier = 0;
            break;
        case ITEM_TYPE_PASS:
            if (item.sellIn <= 0) {
                nextQuality = 0;
            }
            else if (item.sellIn <= 5) {
                modifier = 3;
            }
            else if (item.sellIn <= 10) {
                modifier = 2;
            }
            else {
                modifier = 1;
            }
            break;
        case ITEM_TYPE_CONJURED:
            modifier = (item.sellIn <= 0) ? -4 : -2;
            break;
    }

    // Calculate next quality
    nextQuality = nextQuality + modifier;
  
    // Make sure next quality does not exceed this range, except legendary items
    if ((type & ITEM_TYPE_LEGENDARY) == 0) {
        nextQuality = (nextQuality <= 0) ? 0 : nextQuality;
        nextQuality = (nextQuality >= 50) ? 50 : nextQuality;
    }
    return nextQuality;
}

void 
update_quality(Item items[], int size) 
{
    int i;
    int itemType;
    int nextSellIn = 0;
    int nextQuality = 0;
    
    for (i = 0; i < size; i++)
    {
        itemType = getItemType(items[i]);
        nextSellIn = calcNextSellIn(items[i], itemType);
        nextQuality = calcNextQuality(items[i], itemType);
        items[i].sellIn = nextSellIn;
        items[i].quality = nextQuality;
    }
}
