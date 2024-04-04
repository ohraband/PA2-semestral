//
// Created by Andy on 4. 6. 2021.
//

#ifndef SEMESTRAL_MAPOBJECT_H
#define SEMESTRAL_MAPOBJECT_H



#include <string>

#include "Position.h"
#include "CScreen.h"


using namespace std;

/**
 * Abstract class for items that can be viewed on the map.
 */
class CViewableItem{
public:
    /**
     * Create a new item.
     * @param pos - position of the item
     * @param playername - name of the player item belongs to
     */
    CViewableItem(Position pos, char playername) : pos(pos), playername(playername)
    {};

    /**
     * Virtual destructor.
     */
    virtual ~CViewableItem() = default;

    /**
     * Method to display the item on screen.
     * @param src - screen
     */
    virtual void Show(CScreen *src) const = 0;

    /**
     * Method to check if given item can be passed through.
     * @return true if item can be passed through, false otherwise.
     */
    virtual bool Walkable() const = 0;

    /**
     * @return name of the player item belongs to
     */
    char Playername() const{
        return playername;
    }

    /**
     * @return position of the item
     */
    Position GetPosition() const {
        return pos;
    }

    /**
     * Assign color to be displayed based on the playername.
     * @return
     */
    int AssignColorPair() const{
        int colorpair = 1;
        if(Playername() == 'M'){
            colorpair = 2;
        }
        else if(Playername() == 'P'){
            colorpair = 6;
        }
        else if(Playername() == 'K'){
            colorpair = 7;
        }
        else if(Playername() == 'S'){
            colorpair = 8;
        }
        else if(Playername() == 'D'){
            colorpair = 9;
        }
        return colorpair;
    }

protected:
    Position pos;
    char playername;
};


#endif //SEMESTRAL_MAPOBJECT_H

