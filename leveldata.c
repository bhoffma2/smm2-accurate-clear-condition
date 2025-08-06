#include <stdint.h>
#include <stdio.h>

#include "leveldata.h"

#define MAINWORLD 0x248
#define SUBWORLD 0x2e128


int IsCCLeastAll(FILE *level)
{
    if (!level){
        return -1;
    }

    fseek(level, 0, SEEK_END);
    size_t size = ftell(level);
    if (size != 0x5bfc0) {return -1;}

    // Finding the clear condition from the level file
    unsigned char cc_bin[4]; // the 4-byte clear condition code
    fseek(level, 0x10, SEEK_SET);
    fread(cc_bin, 1, 4, level);
    uint32_t cc_val = cc_bin[0] | cc_bin[1] << 8 | cc_bin[2] << 16 | cc_bin[3] << 24;

    // Finding the CC magnitude
    int cc_mag;
    fseek(level, 0x6, SEEK_SET);
    fread(&cc_mag, 1, 1, level);
    
    int count = 0;
    
    switch (cc_val){
        // Clear Conditions without a magnitude
        case 0x0:           // None        
        case 0x08327ae6:    // Reach the goal without landing after leaving the ground.
        case 0x1664515a:    // Reach the goal without taking damage.
        case 0x196743a3:    // Reach the goal as Boomerang Mario.
        case 0x1a098d50:    // Reach the goal while wearing a Shoe.
        case 0x2a8e77bb:    // Reach the goal as Fire Mario.
        case 0x2c66b03e:    // Reach the goal as Frog Mario.
        case 0x35a5af47:    // Reach the goal as Raccoon Mario.
        case 0x3a2f3996:    // Reach the goal as Propellor Mario.
        case 0x3b49b792:    // Reach the goal while wearing a Propellor Box.
        case 0x3eab9aa1:    // Reach the goal while holding a Koopa Shell.
        case 0x449eb152:    // Reach the goal while wearing a Goomba Mask.
        case 0x4c8772a3:    // Reach the goal on a Lakitu's Cloud.
        case 0x553a9590:    // Reach the goal while holding a Trampoline.
        case 0x6a1ce415:    // Reach the goal as Superball Mario.
        case 0x7bc4d388:    // Reach the goal while wearing a Bullet Bill Mask.
        case 0x7c8612d5:    // Reach the goal as Big Mario.
        case 0x7ddb5d7f:    // Reach the goal as Cat Mario.
        case 0x97f8a309:    // Reach the goal while wearing a Dry Bones Shell.
        case 0xaa2f7449:    // Reach the goal as Flying Squirrel Mario.
        case 0xb4fa3d4b:    // Reach the goal as Buzzy Mario.
        case 0xb7402052:    // Reach the goal as Builder Mario.
        case 0xbb926013:    // Reach the goal as Cape Mario.
        case 0xbf1b11c3:    // Reach the goal while wearing a Cannon Box.
        case 0xc5963651:    // Reach the goal as Link.
        case 0xc73be7ec:    // Reach the goal while you have Super Star Invincibility.
        case 0xd16f4c4e:    // Reach the goal as SMB2 Mario.
        case 0xd9893249:    // Reach the goal in a Koopa Clown Car/Junior Clown Car.
        case 0xde0abfc6:    // Reach the goal as Spiny Mario.
        case 0xde56ffb5:    // Reach the goal in Koopa Troopa Car.
        case 0xed1023ea:    // Reach the goal as Super Mario.
        case 0xf7967ebd:    // Reach the goal as Balloon Mario.
        case 0xf8ad45c4:    // Reach the goal while wearing a Red POW Box.
        case 0xfae86a49:    // Reach the goal while riding Yoshi.
            return 0;
        
        // Clear conditions that have a magnitude
        case 0x0be56f93:    // Reach the goal after defeating at least/all (n) Mechakoopa(s).
            count += findTotalPossibleObjects(level, 111, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 111, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x103bba8c:    // Reach the goal after defeating at least/all (n) Cheep Cheep(s).
            count += findTotalPossibleObjects(level, 56, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 56, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x2cc36aab:   // Reach the goal after defeating at least/all (n) Larry(s).
            count += findTotalPossibleObjects(level, 122, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 122, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0x387c22ca:    // Reach the goal after defeating at least/all (n) Blooper(s).
            count += findTotalPossibleObjects(level, 48, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 48, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x3b8a1111:    // Reach the goal after defeating at least/all (n) Spike(s). [FLAGS]
            count += findTotalPossibleObjects(level, 74, 0, 0x4, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 74, 0, 0x4, SUBWORLD, 10);
            return count - cc_mag;
        case 0x3c164eb1:    // Reach the goal after defeating at least/all (n) Boom Boom(s). (SPECIAL CASE) [FLAGS]
            count += findTotalPossibleObjects(level, 77, 0, 0x4, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 77, 0, 0x4, SUBWORLD, 0);
            return count - cc_mag;
        case 0x3f4124e8:    // Reach the goal after defeating at least/all (n) Porcupuffer(s).
            count += findTotalPossibleObjects(level, 114, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 114, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0x3f50b513:    // Reach the goal after defeating at least/all (n) Charvaargh(s).
            count += findTotalPossibleObjects(level, 86, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 86, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0x405dce65:    // Reach the goal after defeating at least/all (n) Bullet Bill(s). (SPECIAL CASE)
            count += 10*objectCountCID(level, 13, 0xffff, 0, 0, MAINWORLD);
            count += 10*objectCountCID(level, 13, 0xffff, 0, 0, SUBWORLD);
            return count - cc_mag;
        case 0x4067ab4e:    // Reach the goal after defeating at least/all (n) Bully/Bullies.
            count += findTotalPossibleObjects(level, 117, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 117, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0x467afb58:    // Reach the goal after defeating at least/all (n) Hop-Chop(s).
            count += findTotalPossibleObjects(level, 50, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 50, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x48b4157b:    // Reach the goal while holding a Red POW Block. OR Reach the goal after activating at least/all (n) Red POW Block(s). (SPECIAL CASE) [FLAGS]
            if (cc_mag == 0) {return 0;}
            count += findTotalPossibleObjects(level, 19, 0x4, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 19, 0x4, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x48d111e0:    // Reach the goal after defeating at least/all (n) Bob-omb(s).
            count += findTotalPossibleObjects(level, 15, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 15, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x4b115542:    // Reach the goal after defeating at least/all (n) Spiny/Spinies. (SPECIAL CASE) [FLAGS]
            count += findTotalPossibleObjects(level, 25, 0, 0x4, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 25, 0, 0x4, SUBWORLD, 10);
            count += 10*objectCountCID(level, 30, 0xffff, 0, 0x4, MAINWORLD); // lakitus throw spinys by default
            count += 10*objectCountCID(level, 30, 0xffff, 0, 0x4, SUBWORLD);
            return count - cc_mag;
        case 0x4b980b7f:    // Reach the goal after defeating at least/all (n) Bowser(s)/Meowser(s).
            count += findTotalPossibleObjects(level, 62, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 62, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0x4c44da92:    // Reach the goal after defeating at least/all (n) Ant Trooper(s).
            count += findTotalPossibleObjects(level, 96, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 96, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x501c7c00:    // Reach the goal after defeating at least/all (n) Boo(s). (SPECIAL CASE) [FLAGS]
            count += findTotalPossibleObjects(level, 41, 0, 0x4, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 41, 0, 0x4, SUBWORLD, 10);
            if (getStyle(level) != 0x5733){ // not 3D world (peepas) vs other styles (boo rings)
                count += findTotalPossibleObjects(level, 41, 0x4, 0, MAINWORLD, 8);
                count += findTotalPossibleObjects(level, 41, 0x4, 0, SUBWORLD, 8);
            }
            return count - cc_mag;
        case 0x54fea275:    // Reach the goal after defeating at least/all (n) Roy(s).
            count += findTotalPossibleObjects(level, 125, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 125, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0x5559be79:    // Reach the goal after defeating at least/all (n) Morton(s).
            count += objectCount(level, 121, 0, 0, MAINWORLD);
            count += objectCount(level, 121, 0, 0, SUBWORLD);
            return count - cc_mag;
        case 0x563755f2:    // Reach the goal after defeating at least/all (n) Fish Bone(s).
            count += findTotalPossibleObjects(level, 103, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 103, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x5a085610:    // Reach the goal after defeating at least/all (n) Monty Mole(s).
            count += findTotalPossibleObjects(level, 102, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 102, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x62b74a93:    // Reach the goal after picking up at least/all (n) 1-Up Mushroom(s). (SPECIAL CASE)
            if (!((getTheme(level, MAINWORLD) == 0x0) && (isNighttime(level, MAINWORLD) == 0x2))){
                count += findTotalPossibleObjects(level, 33, 0, 0, MAINWORLD, 3);
                count += objectCountCID(level, 106, 33, 0, 0, MAINWORLD);
            }
            if ((getTheme(level, SUBWORLD) == 0x0) && (isNighttime(level, SUBWORLD) == 0x2)){
                count += findTotalPossibleObjects(level, 33, 0, 0, SUBWORLD, 3);
                count += objectCountCID(level, 106, 33, 0, 0, SUBWORLD);
            }
            return count - cc_mag;
        case 0x634a6671:    // Reach the goal after defeating at least/all (n) Hammer Bro(s.). [FLAGS]
            count += findTotalPossibleObjects(level, 3, 0, 0x4000,MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 3, 0, 0x4000, SUBWORLD, 10);
            return count - cc_mag;
        case 0x63f3d532:    // Reach the goal after hitting at least/all (n) P Switch(es). OR Reach the goal while holding a P Switch. (SPECIAL CASE)
            if (cc_mag == 0) {return 0;}
            count += findTotalPossibleObjects(level, 18, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 18, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x66477be4:    // Reach the goal after activating at least/all (n) POW Block(s). OR Reach the goal while holding a POW Block. (SPECIAL CASE) [FLAGS]
            if (cc_mag == 0) {return 0;}
            count += findTotalPossibleObjects(level, 19, 0, 0x4, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 19, 0, 0x4, SUBWORLD, 10);
            return count - cc_mag;
        case 0x66c2b75e:    // Reach the goal after defeating at least/all (n) Angry Sun(s). [FLAGS]
            count += findTotalPossibleObjects(level, 104, 0, 0x4, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 104, 0, 0x4, SUBWORLD, 0);
            return count - cc_mag;
        case 0x671f29b5:    // Reach the goal after defeating at least/all (n) Pokey(s).
            count += findTotalPossibleObjects(level, 78, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 78, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0x6daa9a3f:    // Reach the goal after defeating at least/all (n) Pom Pom(s). [FLAGS]
            count += findTotalPossibleObjects(level, 77, 0x4, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 77, 0x4, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0x756120ee:    // Reach the goal after defeating at least/all (n) Peepa(s). [FLAGS]
            count += findTotalPossibleObjects(level, 41, 0x4, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 41, 0x4, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x794c6eb3:    // Reach the goal after defeating at least/all (n) Lakitu(s).
            count += findTotalPossibleObjects(level, 30, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 30, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0x7981172f:    // Reach the goal after defeating at least/all (n) Lemmy(s).
            count += findTotalPossibleObjects(level, 120, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 120, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0x7a128199:    // Reach the goal after defeating at least/all (n) Lava Bubble(s).
            count += findTotalPossibleObjects(level, 60, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 60, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0x7f07acbf:    // Reach the goal after defeating at least/all (n) Goomba(s)/Galoomba(s). (SPECIAL CASE) [FLAGS]
            count += findTotalPossibleObjects(level, 0, 0, 0x4, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 0, 0, 0x4, SUBWORLD, 10);
            uint16_t style = getStyle(level);
            if (style == 0x314d || style == 0x334d){
                count += findTotalPossibleObjects(level, 45, 0, 0, MAINWORLD, 4); // shoe goombas
                count += findTotalPossibleObjects(level, 45, 0, 0, SUBWORLD, 4);
            }
            return count - cc_mag;
        case 0x7f88648a:    // Reach the goal after defeating at least/all (n) Thwomp(s).
            count += findTotalPossibleObjects(level, 12, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 12, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0x86aae3fd:    // Reach the goal after defeating at least/all (n) Iggy(s).
            count += findTotalPossibleObjects(level, 124, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 124, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0xa09bb51f:    // Reach the goal after defeating at least/all (n) Sledge Bro(s.). [FLAGS]
            count += findTotalPossibleObjects(level, 3, 0x4000, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 3, 0x4000, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0xa3aec34a:    // Reach the goal after defeating at least/all (n) Rocky Wrench(es).
            count += findTotalPossibleObjects(level, 58, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 58, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0xa3e39544:    // Reach the goal after grabbing at least/all (n) 50-Coin(s). [FLAGS]
            count += findTotalPossibleObjects(level, 70, 0x80000, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 70, 0x80000, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0xbd35b4ac:    // Reach the goal after defeating at least/all (n) Wendy(s).
            count += findTotalPossibleObjects(level, 123, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 123, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0xc77685e8:    // Reach the goal after defeating at least/all (n) Goombrat(s)/Goombud(s). [FLAGS]
            count += findTotalPossibleObjects(level, 0, 0x4, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 0, 0x4, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0xc78f5040:    // Reach the goal after grabbing at least/all (n) 10-Coin(s). [FLAGS]
            count += findTotalPossibleObjects(level, 70, 0, 0xc0000, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 70, 0, 0xc0000, SUBWORLD, 0);
            return count - cc_mag;
        case 0xc7dad20f:    // Reach the goal after defeating at least/all (n) Buzzy Beetle(s). [FLAGS]
            count += findTotalPossibleObjects(level, 28, 0, 0x4, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 28, 0, 0x4, SUBWORLD, 10);
            return count - cc_mag;
        case 0xca315249:    // Reach the goal after defeating at least/all (n) Bowser Jr.(s).
            count += findTotalPossibleObjects(level, 98, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 98, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0xcce12a46:    // Reach the goal after defeating at least/all (n) Koopa Troopa(s). (SPECIAL CASE)
            count += findTotalPossibleObjects(level, 1, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 1, 0, 0, SUBWORLD, 10);
            count += findTotalPossibleObjects(level, 72, 0, 0, MAINWORLD, 0); // koopa troopa car included
            count += findTotalPossibleObjects(level, 72, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0xce2e5a15:    // Reach the goal after defeating at least/all (n) Chain Chomp(s).
            count += findTotalPossibleObjects(level, 61, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 61, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0xce9a707b:    // Reach the goal after defeating at least/all (n) Muncher(s). (SPECIAL)
            count += objectCount(level, 57, 0, 0, MAINWORLD);                      // standalone
            count += objectCountCID(level, 4, 57, 0, 0, MAINWORLD);                // blocks
            count += objectCountCID(level, 5, 57, 0, 0, MAINWORLD);                // ? blocks
            count += objectCount(level, 57, 0x1, 0, MAINWORLD);                    // pipes
            count += 10 * objectCountCID(level, 13, 57, 0, 0, MAINWORLD);          // bill blasters
            count += objectCountCID(level, 23, 57, 0, 0, MAINWORLD);               // note blocks
            count += objectCountCID(level, 29, 57, 0, 0, MAINWORLD);               // hidden blocks
            count += 10 * objectCountCID(level, 30, 57, 0, 0, MAINWORLD);          // lakitus
            count += objectCount(level, 57, 0, 0, SUBWORLD);                       // standalone
            count += objectCountCID(level, 4, 57, 0, 0, SUBWORLD);                 // blocks
            count += objectCountCID(level, 5, 57, 0, 0, SUBWORLD);                 // ? blocks
            count += objectCount(level, 57, 0x1, 0, SUBWORLD);                     // pipes
            count += 10 * objectCountCID(level, 13, 57, 0, 0, SUBWORLD);           // bill blasters
            count += objectCountCID(level, 23, 57, 0, 0, SUBWORLD);                // note blocks
            count += objectCountCID(level, 29, 57, 0, 0, SUBWORLD);                // hidden blocks
            count += 10 * objectCountCID(level, 30, 57, 0, 0, SUBWORLD);           // lakitus
            return count - cc_mag;
        case 0xcf81610a:    // Reach the goal after defeating at least/all (n) Wiggler(s).
            count += findTotalPossibleObjects(level, 52, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 52, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0xdf6717de:    // Reach the goal after defeating at least/all (n) Piranha Plant(s)/Jumping Piranha Plant(s). (SPECIAL CASE) [FLAGS]
            uint32_t flags_ex = 0x0;
            if (getStyle(level) == 0x574d){flags_ex = 0x4;}
            count += objectCount(level, 2, 0, flags_ex, MAINWORLD);                      // standalone
            count += objectCountCID(level, 4, 2, 0, flags_ex, MAINWORLD);                // blocks
            count += objectCountCID(level, 5, 2, 0, flags_ex, MAINWORLD);                // ? blocks
            count += objectCount(level, 2, 0x1, flags_ex, MAINWORLD);                    // pipes
            count += 10 * objectCountCID(level, 13, 2, 0, flags_ex, MAINWORLD);          // bill blasters
            count += objectCountCID(level, 23, 2, 0, flags_ex, MAINWORLD);               // note blocks
            count += objectCountCID(level, 29, 2, 0, flags_ex, MAINWORLD);               // hidden blocks
            count += 10 * objectCountCID(level, 30, 2, 0, flags_ex, MAINWORLD);          // lakitus
            count += objectCount(level, 2, 0, flags_ex, SUBWORLD);                       // standalone
            count += objectCountCID(level, 4, 2, 0, flags_ex, SUBWORLD);                 // blocks
            count += objectCountCID(level, 5, 2, 0, flags_ex, SUBWORLD);                 // ? blocks
            count += objectCount(level, 2, 0x1, flags_ex, SUBWORLD);                     // pipes
            count += 10 * objectCountCID(level, 13, 2, 0, flags_ex, SUBWORLD);           // bill blasters
            count += objectCountCID(level, 23, 2, 0, flags_ex, SUBWORLD);                // note blocks
            count += objectCountCID(level, 29, 2, 0, flags_ex, SUBWORLD);                // hidden blocks
            count += 10 * objectCountCID(level, 30, 2, 0, flags_ex, SUBWORLD);           // lakitus
            return count - cc_mag;
        case 0xe25c5f60:    // Reach the goal after defeating at least/all (n) Dry Bones. [FLAGS]
            count += findTotalPossibleObjects(level, 46, 0, 0x4, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 46, 0, 0x4, SUBWORLD, 10); 
            return count - cc_mag;
        case 0xe3f62c75:    // Reach the goal after defeating at least/all (n) Stingby/Stingbies.
            count += findTotalPossibleObjects(level, 65, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 65, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0xe47c2be8:    // Reach the goal after defeating at least/all (n) Piranha Creeper(s).
            count += findTotalPossibleObjects(level, 107, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 107, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0xe50302f7:    // Reach the goal after defeating at least/all (n) Fire Piranha Plant(s). (SPECIAL CASE) [FLAGS]
            count += objectCount(level, 2, 0x4, 0, MAINWORLD);                      // standalone
            count += objectCountCID(level, 4, 2, 0x4, 0, MAINWORLD);                // blocks
            count += objectCountCID(level, 5, 2, 0x4, 0, MAINWORLD);                // ? blocks
            count += objectCount(level, 2, 0x5, 0, MAINWORLD);                      // pipes
            count += 10 * objectCountCID(level, 13, 2, 0x4, 0, MAINWORLD);          // bill blasters
            count += objectCountCID(level, 23, 2, 0x4, 0, MAINWORLD);               // note blocks
            count += objectCountCID(level, 29, 2, 0x4, 0, MAINWORLD);               // hidden blocks
            count += 10 * objectCountCID(level, 30, 2, 0x4, 0, MAINWORLD);          // lakitus
            count += objectCount(level, 2, 0x4, 0, SUBWORLD);                       // standalone
            count += objectCountCID(level, 4, 2, 0x4, 0, SUBWORLD);                 // blocks
            count += objectCountCID(level, 5, 2, 0x4, 0, SUBWORLD);                 // ? blocks
            count += objectCount(level, 2, 0x5, 0, SUBWORLD);                       // pipes
            count += 10 * objectCountCID(level, 13, 2, 0x4, 0, SUBWORLD);           // bill blasters
            count += objectCountCID(level, 23, 2, 0x4, 0, SUBWORLD);                // note blocks
            count += objectCountCID(level, 29, 2, 0x4, 0, SUBWORLD);                // hidden blocks
            count += 10 * objectCountCID(level, 30, 2, 0x4, 0, SUBWORLD);           // lakitus
            return count - cc_mag;
        case 0xe6f2eebe:    // Reach the goal after breaking at least/all (n) Crate(s).
            count += findTotalPossibleObjects(level, 112, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 112, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0xece74bc7:    // Reach the goal after defeating at least/all (n) Ludwig(s).
            count += findTotalPossibleObjects(level, 126, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 126, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0xf0f35cba:    // Reach the goal after defeating at least/all (n) Skipsqueak(s).
            count += findTotalPossibleObjects(level, 51, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 51, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0xf55b3863:    // Reach the goal after grabbing at least/all (n) Coin(s). (SPECIAL CASE) [FLAGS]
            int isPSwitchPresent = 0;    
            isPSwitchPresent += findTotalPossibleObjects(level, 18, 0, 0, MAINWORLD, 2);
            isPSwitchPresent += findTotalPossibleObjects(level, 18, 0, 0, SUBWORLD, 2);
            count += objectCount(level, 8, 0, 0, MAINWORLD);                      // standalone
            count += objectCount(level, 8, 0, 0, SUBWORLD);                       
            count += 10 * objectCountCID(level, 4, 8, 0, 0, MAINWORLD);           // blocks w/ coin
            count += 10 * objectCountCID(level, 4, 8, 0, 0, SUBWORLD);            
            count += objectCountCID(level, 5, 0xffff, 0, 0, MAINWORLD);           // ? blocks
            count += objectCountCID(level, 5, 0xffff, 0, 0, SUBWORLD);
            count += 10 * objectCountCID(level, 5, 8, 0, 0, MAINWORLD);           // ? blocks w/ coin
            count += 10 * objectCountCID(level, 5, 8, 0, 0, SUBWORLD);            
            count += 30 * objectCount(level, 8, 0x1, 0, MAINWORLD);               // pipes
            count += 30 * objectCount(level, 8, 0x1, 0, SUBWORLD);                
            count += 30 * objectCountCID(level, 13, 8, 0, 0, MAINWORLD);          // bill blasters
            count += 30 * objectCountCID(level, 13, 8, 0, 0, SUBWORLD);           
            count += objectCountCID(level, 23, 8, 0, 0, MAINWORLD);               // note blocks
            count += objectCountCID(level, 23, 8, 0, 0, SUBWORLD);                
            count += objectCountCID(level, 29, 0xffff, 0, 0, MAINWORLD);          // hidden blocks
            count += objectCountCID(level, 29, 0xffff, 0, 0, SUBWORLD);
            count += 10 * objectCountCID(level, 29, 8, 0, 0, MAINWORLD);          // hidden blocks w/ coin (Known bug, only gives 1 coin)
            count += 10 * objectCountCID(level, 29, 8, 0, 0, SUBWORLD);           
            count += 30 * objectCountCID(level, 30, 8, 0, 0, MAINWORLD);          // lakitus 
            count += 30 * objectCountCID(level, 30, 8, 0, 0, SUBWORLD);           
            count += objectCountCID(level, 106, 8, 0, 0, MAINWORLD);              // trees
            count += objectCountCID(level, 106, 8, 0, 0, SUBWORLD);             
            count += objectCountCID(level, 112, 8, 0, 0, MAINWORLD);              // crates
            count += objectCountCID(level, 112, 8, 0, 0, SUBWORLD);
            count += 10 * objectCount(level, 70, 0, 0xc0000, MAINWORLD);          // 10-coins
            count += 10 * objectCount(level, 70, 0, 0xc0000, SUBWORLD);
            count += 30 * objectCount(level, 70, 0x40000, 0, MAINWORLD);          // 30-coins
            count += 30 * objectCount(level, 70, 0x40000, 0, SUBWORLD);
            count += 50 * objectCount(level, 70, 0x80000, 0, MAINWORLD);          // 50-coins
            count += 50 * objectCount(level, 70, 0x80000, 0, SUBWORLD);
            count += objectCount(level, 92, 0, 0, MAINWORLD);                     // pink coins
            count += objectCount(level, 92, 0, 0, SUBWORLD);
            if (isPSwitchPresent){
                count += objectCountCID(level, 4, 0xffff, 0, 0, MAINWORLD);       // blocks (can turn into coins via p-switch, but only count if pswitch exists)
                count += objectCountCID(level, 4, 0xffff, 0, 0, SUBWORLD);
            }
            return count - cc_mag;
        case 0xf571d608:    // Reach the goal after defeating at least/all (n) Magikoopa(s).
            count += findTotalPossibleObjects(level, 39, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 39, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0xf5b932c2:    // Reach the goal after grabbing at least/all (n) 30-Coin(s). [FLAGS]
            count += findTotalPossibleObjects(level, 70, 0x40000, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 70, 0x40000, 0, SUBWORLD, 0);
            return count - cc_mag;
        case 0xfe75363e:    // Reach the goal after defeating at least/all (n) Spike Top(s).
            count += findTotalPossibleObjects(level, 40, 0, 0, MAINWORLD, 10);
            count += findTotalPossibleObjects(level, 40, 0, 0, SUBWORLD, 10);
            return count - cc_mag;
        case 0xffe76309:    // Reach the goal after defeating at least/all (n) Banzai Bill(s).
            count += findTotalPossibleObjects(level, 32, 0, 0, MAINWORLD, 0);
            count += findTotalPossibleObjects(level, 32, 0, 0, SUBWORLD, 0);
            return count - cc_mag;
        default:
            return -1;
    }
    return 0;
}


int findTotalPossibleObjects(FILE *level, uint16_t obj, uint32_t objFlags, uint32_t objFlags_ex, uint32_t world, int mag)
{
    int count = 0;
    count += objectCount(level, obj, objFlags, objFlags_ex, world);                      // standalone
    count += objectCountCID(level, 4, obj, objFlags, objFlags_ex, world);                // blocks
    count += objectCountCID(level, 5, obj, objFlags, objFlags_ex, world);                // ? blocksd
    count += (mag-1) * objectCount(level, obj, (objFlags | 0x1), objFlags_ex, world);    // pipes
    count += mag * objectCountCID(level, 13, obj, objFlags, objFlags_ex, world);         // bill blasters
    count += objectCountCID(level, 23, obj, objFlags, objFlags_ex, world);               // note blocks
    count += objectCountCID(level, 29, obj, objFlags, objFlags_ex, world);               // hidden blocks
    count += mag * objectCountCID(level, 30, obj, objFlags, objFlags_ex, world);         // lakitus
    return count;
}


int objectCount (FILE *level, uint16_t id, uint32_t flags, uint32_t flags_ex, uint32_t worldPtr)
{
    if (!level) {return -1;}

    int count = 0;
    uint16_t id_f = 0x0;
    uint32_t flags_f = 0x0;

    fseek(level, worldPtr, SEEK_SET);
    while (ftell(level) < (worldPtr + 0x14500) ){
        assignObjectValues(level, &id_f, NULL, NULL, &flags_f, NULL);
        if (flags_f == 0x0) {break;}     // if we reached end of objects (all values will be 0)
        if ((id_f == id) && ((flags_f & flags) == flags) && ((flags_f & flags_ex) == 0)) {count++;} 
        // If an object in the file matches our parameters, increment by 1
    }
    return count;
}


int objectCountCID(FILE *level, uint16_t id, uint16_t cid, uint32_t cflags, uint32_t cflags_ex, uint32_t world)
{
    if (!level) {return -1;}

    int count = 0;
    uint16_t id_f = 0x0;
    uint16_t cid_f = 0x0;
    uint32_t cflags_f = 0x0;

    fseek(level, world, SEEK_SET);
    while (ftell(level) < (world + 0x14500)){
        assignObjectValues(level, &id_f, &cid_f, NULL, NULL, &cflags_f);
        if (cflags_f == 0x0 && id == 0x0) {break;}  // if there are no more objects (all fields will be 0)
        if ((id_f == id) && (cid_f == cid) && ((cflags_f & cflags) == cflags) && ((cflags_f & cflags_ex) == 0)) {count++;} // if the file obj matches our parameters
    }
    return count;
}


void assignObjectValues(FILE *level, uint16_t *id, uint16_t *cid, uint16_t *lid, uint32_t *flags, uint32_t *cflags)
{
    fseek(level, 0xc, SEEK_CUR);                            // x, y, reserved, width, height (NOT NEEDED)
    if (flags)  {fread(flags, sizeof(*flags), 1, level);}   // object flags
    else        {fseek(level, 0x4, SEEK_CUR);}
    if (cflags) {fread(cflags, sizeof(*cflags), 1, level);} // child flags
    else        {fseek(level, 0x4, SEEK_CUR);}
    fseek(level, 0x4, SEEK_CUR);                            // extended data (NOT NEEDED)
    if (id)     {fread(id, sizeof(*id), 1, level);}         // object id
    else        {fseek(level, 0x2, SEEK_CUR);}
    if (cid)    {fread(cid, sizeof(*cid), 1, level);}       // child id
    else        {fseek(level, 0x2, SEEK_CUR);}
    if (lid)    {fread(lid, sizeof(*lid), 1, level);}       // link id
    else        {fseek(level, 0x2, SEEK_CUR);} 
    fseek(level, 0x2, SEEK_CUR);                            // sound id (NOT NEEDED)
    return;
}


uint16_t getStyle(FILE *level)
{
    // SMB1:  0x314d (1M)
    // SMB3:  0x334d (3M)
    // SMW:   0x574d (WM)
    // NSMBU: 0x5557 (UW)
    // SM3DW: 0x5733 (W3)
    uint16_t style = 0x0;
    fseek(level, 0xf1, SEEK_SET);
    fread(&style, sizeof(style), 1, level);
    return style;
}


uint8_t getTheme(FILE *level, uint32_t world)
{
    // Ground = 0x0
    uint8_t worldval = 0;
    fseek(level, world-0x48, SEEK_SET);
    fread(&worldval, sizeof(worldval), 1, level);
    return worldval;
}


uint8_t isNighttime(FILE *level, uint32_t world)
{
    // DAY = 0x0
    // NIGHT = 0x2
    uint8_t worldval = 0;
    fseek(level, world-0x30, SEEK_SET);
    fread(&worldval, sizeof(worldval), 1, level);
    return worldval;
}

