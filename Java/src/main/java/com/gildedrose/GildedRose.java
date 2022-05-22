package com.gildedrose;

class GildedRose {
    Item[] items;

    public GildedRose(Item[] items) {
        this.items = items;
    }

    private int calcNextSellIn(Item item, int type){
        if ((type & ItemType.ITEM_TYPE_LEGENDARY) != 0){
            // Only legendary item does not affect sellIn value
            return item.sellIn;
        }
        return (int)(item.sellIn - 1);
    }

    private int calcNextQuality(Item item, int type){
        // The next quality value is calculated based on 
        // current sellIn value

        int nextQuality = item.quality;
        int modifier = 0;

        // TODO: to determine what is the logic for items belong to more than one type
        // The logic below assumes every items only belong to one type
        switch (type) {
            case ItemType.ITEM_TYPE_COMMON:
                modifier = (item.sellIn <= 0) ? -2 : -1;
                break;
            case ItemType.ITEM_TYPE_AGED:
                modifier = (item.sellIn <= 0) ? 2 : 1;
                break;
            case ItemType.ITEM_TYPE_LEGENDARY:
                modifier = 0;
                break;
            case ItemType.ITEM_TYPE_PASS:
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
            case ItemType.ITEM_TYPE_CONJURED:
                modifier = (item.sellIn <= 0) ? -4 : -2;
                break;
        }

        // Calculate next quality
        nextQuality = nextQuality + modifier;
      
        // Make sure next quality does not exceed this range, except legendary items
        if ((type & ItemType.ITEM_TYPE_LEGENDARY) == 0) {
            nextQuality = (nextQuality <= 0) ? 0 : nextQuality;
            nextQuality = (nextQuality >= 50) ? 50 : nextQuality;
        }
        return nextQuality;
    }

    public void updateQuality() {
        int itemType;
        int nextSellIn = 0;
        int nextQuality = 0;
        for (int i = 0; i < items.length; i++) {
            itemType = ItemType.getItemType(items[i]);
            nextSellIn = calcNextSellIn(items[i], itemType);
            nextQuality = calcNextQuality(items[i], itemType);
            items[i].sellIn = nextSellIn;
            items[i].quality = nextQuality;
        }
    }
}