#ifndef ROSE_INCLUDED
#define ROSE_INCLUDED

// Define item types here, this is to handle items that 
// might belong to more than one type e.g. Legendary aged cheese, or conjured backstage pass
#define ITEM_TYPE_COMMON           0x00
#define ITEM_TYPE_AGED             0x01
#define ITEM_TYPE_LEGENDARY        0x02
#define ITEM_TYPE_PASS             0x04 
#define ITEM_TYPE_CONJURED         0x08   

typedef struct
{
    char *name;
    int sellIn;
    int quality;
} Item;

extern Item* init_item(Item* item, const char *name, int sellIn, int quality);
extern void update_quality(Item items[], int size);
extern char* print_item_to_buffer(char* buffer, Item* item);
int getItemType(Item item);
int getItemTypeFromRegistry(Item item);
#endif