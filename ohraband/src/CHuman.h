//
// Created by Andy on 7. 6. 2021.
//

#ifndef SEMESTRAL_CHUMAN_H
#define SEMESTRAL_CHUMAN_H

#include "CPlayer.h"

/**
 * Implementation of class CPlayer intended for Humans.
 */
class CHuman : public CPlayer{
public:
    /**
     * Create one Human player.
     * @param map - map of the game
     * @param playername - name of the player
     */
    CHuman(CMap *map, char playername): CPlayer(map, playername){
    };

    /**
     * Default destructor.
     */
    ~CHuman() override = default;

    /**
     * Make an action based on humans input.
     * @param source - establishment a player is attacking from
     * @return CAction* if successful, nullptr otherwise.
     */
    CAction* MakeAction(CEstablishment * source) const override;

    /**
     * Ask human for establishment to attack.
     * @return number of establishment to be attacked
     */
    int HumanInput() const;

    /**
     * Warn human that such move cannot be made because
     * a route from the source to the target does not exist.
     */
    void ImpossibleRoute() const;

private:
};

#endif //SEMESTRAL_CHUMAN_H
