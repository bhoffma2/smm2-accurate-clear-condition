#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <stdio.h>
#include <stdint.h>


enum LevelThemes {
    GROUND,
    UNDERGROUND,
    CASTLE,
    AIRSHIP,
    UNDERWATER,
    GHOST_HOUSE,
    SNOW,
    DESERT,
    SKY,
    FOREST
};


/**
 * int IsCCLeastAll(FILE *leveldata, int magnitude);
 *      Determines if a level will produce "at least" or "all" in a clear condition
 * 
 * Parameters:
 *      FILE *leveldata: the binary level file
 * 
 * returns: int
 *      Returns the difference between the number of objects that exist or may spawn in the level and clear condition 
 *      magnitude. If the return value is < 0, then the clear condition will be "at least". if the return value is = 0,
 *      then the clear condition will be "all".
 *      
 *      This function will return 0 when the clear condition doesn't have a magnitude. This includes all clear
 *      conditions in the actions and status categories. Will also return 0 if there isn't a clear condition
 * 
 *      This function returns -1 if there is an error.
 */
int IsCCLeastAll(FILE *leveldata);

/**
 * FUNCTION: objectCount
 * Finds how many given objects are in a level file
 * 
 * Parameters:
 *      [IN] FILE *level: the level file, opened in rb mode.
 *      [IN] uint16_t id: the id of the object to find
 *      [IN] uint32_t flags: the flags of the object to find. if a flag bit is 1, will only find objects with that flag set, else ignore
 *      [IN] uint32_t flags_ex: the flags of the object to exclude from the search.
 *      [IN] uint32_t world: the world you want to seach (MAINWORLD, SUBWORLD)
 * 
 * returns: 
 *      >=0: The count of all objects with the correct flags in a level.
 *      -1: if there is an error
 */
int objectCount(FILE *level, uint16_t id, uint32_t flags, uint32_t flags_ex, uint32_t world);

/**
 * FUNCTION: objectCountCID
 * Finds how many given objects are a child id to a given object id
 * 
 * Parameters:
 *      [IN] FILE *level: the level file, opened in rb mode
 *      [IN] uint16_t id: the id of the object that contains the object to find
 *      [IN] uint16_t cid: the id of the object to find
 *      [IN] uint32_t cflags: the flags of the object to find
 *      [IN] uint32_t cflags_ex: the flags of the objects to exclude
 *      [IN] uint32_t world: the world to check (MAINWORLD, SUBWORLD)
 * 
 * returns:
 *      >=0: the count of all objects with the correct flags in a level.
 *           NOTE: All instances will increment the count by 1, even if the object to find can spawn multiple times from that object
 *      -1: if there is an error
 */
int objectCountCID(FILE *level, uint16_t id, uint16_t cid, uint32_t cflags, uint32_t cflags_ex, uint32_t world);

/**
 * FUNCTION: findTotalPossibleObjects
 * A wrapper function for combinations of objectCount and objectCountCID functions that will calculate how many total objects exist 
 * and spawn in a level. This function is intended for objects that spawn once from blocks, and spawn from pipes, bill blasters, 
 * and lakitus. Will also work on objects that cannot be a CID (bosses and big enemies). This function will check one world for the 
 * object in the following states:
 *  - standalone
 *  - blocks
 *  - ? blocks
 *  - pipes
 *  - bill blasters
 *  - note blocks
 *  - hidden blocks
 *  - lakitus
 * 
 * NOTE: Be careful with making sure that the object you are looking for doesn't have special cases unique to it or not universally 
 * applicable. Sometimes this function can be used with additional cases of objectCount or objectCountCID covering those special cases, 
 * other times this function cannot be used to properly count the object, and the user must implement the checks manually.
 * 
 * Parameters:
 *      [IN] FILE *level: the level file, open in rb mode
 *      [IN] uint16_t obj: the id of the object to find
 *      [IN] uint32_t objFlags: the flags you want set on the object you want to find.
 *      [IN] uint32_t objFlags_ex: the flags you want to be excluded on the object to find.
 *      [IN] uint32_t world: the world you want to check (MAINWORLD, SUBWORLD)
 *      [IN] int mag: the magnitude which the object spawns from pipes, bill blasters, and lakitus.
 * 
 * Returns:
 *      The count of the object in that world. 
 *      
 */
int findTotalPossibleObjects(FILE *level, uint16_t obj, uint32_t objFlags, uint32_t objFlags_ex, uint32_t world, int mag);

/**
 * FUNCTION: assignObjectValues
 * Will assign the values for an object. File pointer must be set first to MAINWORLD or SUBWORLD before invoking this function for
 * the first time. If some [OUT] parameters are unneeded, set to NULL.
 * 
 * Parameters:
 *      [IN] FILE *level: the level file, opened in rb mode
 *      [OUT] uint16_t *id: the pointer to a variable to populate with the id value.
 *      [OUT] uint16_t *cid: the pointer to a variable to populate with the cid value.
 *      [OUT] uint16_t *lid: the pointer to a variable to populate with the lid value.
 *      [OUT] uint32_t *flags: the pointer to a variable to populate with the flags value.
 *      [OUT] uint32_t *cflags: the pointer to a variable to populate with the cflags value.
 * 
 * Returns:
 *  Nothing. All [OUT] values not equal to NULL will be populated with their respective values.
 */
void assignObjectValues(FILE *level, uint16_t *id, uint16_t *cid, uint16_t *lid, uint32_t *flags, uint32_t *cflags);

uint16_t getStyle(FILE *level);
uint8_t getTheme(FILE *level, uint32_t world);
uint8_t isNighttime(FILE *level, uint32_t world);

#endif