//
// Created by Andy on 4. 6. 2021.
//

#ifndef SEMESTRAL_CNOTHING_H
#define SEMESTRAL_CNOTHING_H


#include <utility>

#include "CViewableItem.h"

/**
 * Implementation of CViewableItem as an empty block.
 */
class CNothing : public CViewableItem {
public:
    /**
     * Create a new CNothing object
     * @param pos - position
     * @param name - playername
     */
    CNothing(Position pos, char name) : CViewableItem(pos, name){
    };

    /**
     * Default CNothing destructor.
     */
    ~CNothing() override = default;

    /**
     * Checks if position is walkable.
     * @return  true
     */
    bool Walkable() const override {
        return true;
    }

    /**
     * Shows an empty block.
     * @param src - display screen
     */
    void Show(CScreen *src) const override {
        src->QuickShow(pos.y(),pos.x(),Playername(),1);
    }

private:
};

#endif //SEMESTRAL_CNOTHING_H
