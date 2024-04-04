//
// Created by Andy on 7. 6. 2021.
//

#ifndef SEMESTRAL_CPLAYER_H
#define SEMESTRAL_CPLAYER_H


#include "CAction.h"

/**
 * Abstract class represents a single player on the game.
 */
class CPlayer{
public:

    /**
     * Creates a new player.
     * @param map - map the player is on
     * @param playername - name of the player
     */
    CPlayer(CMap *map, char playername): map(map), playername(playername){
    };

    /**
     * Default CPlayer desctructor.
     */
    virtual ~CPlayer() = default;

    /**
     * Creates an action of the player in the game.
     * @param source - establishment creating the action from
     * @return new action
     */
    virtual CAction* MakeAction(CEstablishment* source) const = 0;

    /**
     * @return playername
     */
    char GetPlayername() const{
        return playername;
    }

protected:
    CMap *map;
    char playername;
};































#endif //SEMESTRAL_CPLAYER_H
