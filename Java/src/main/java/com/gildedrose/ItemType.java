package com.gildedrose;

public class ItemType {
    public static final int ITEM_TYPE_COMMON =     (int)0x00;
    public static final int ITEM_TYPE_AGED =       (int)0x01;
    public static final int ITEM_TYPE_LEGENDARY =  (int)0x02;
    public static final int ITEM_TYPE_PASS =       (int)0x04;
    public static final int ITEM_TYPE_CONJURED =   (int)0x08;
    
    private static class ItemTypeReg {
        String name;
        int type;
        ItemTypeReg (String name, int type) {
            this.name = name;
            this.type = type;
        }
    }
    
    private static final ItemTypeReg[] itemTypeReg = {
        new ItemTypeReg("sulfuras", ITEM_TYPE_LEGENDARY)
    };
    
    public static int getItemType(Item item) {
        int type = ITEM_TYPE_COMMON;
        String lowerName = item.name.toLowerCase();
        if (lowerName.contains("aged")) {
            type |= ITEM_TYPE_AGED;
        }
        if (lowerName.contains("legendary")) {
            type |= ITEM_TYPE_LEGENDARY;
        }
        if (lowerName.contains("pass")) {
            type |= ITEM_TYPE_PASS;
        }
        if (lowerName.contains("conjured")) {
            type |= ITEM_TYPE_CONJURED;
        }
        for (int i = 0; i < itemTypeReg.length; i++) {
            if (lowerName.contains(itemTypeReg[i].name)) {
                type |= itemTypeReg[i].type;
            }
        }
        return type;
    }
    
}