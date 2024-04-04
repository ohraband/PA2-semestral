//
// Created by Andy on 7. 6. 2021.
//

#ifndef SEMESTRAL_CCOMPUTER_H
#define SEMESTRAL_CCOMPUTER_H


#include "CPlayer.h"
/**
 * Implementation of the Player class controlled by Computer.
 */
class CComputer : public CPlayer{
public:
    /**
     * Create a new CComputer player
     * @param map - map of the level
     * @param playername - single character name of the player
     * @param difficulty - player difficulty
     */
    CComputer(CMap *map, char playername, int difficulty = 1): CPlayer(map, playername), difficulty(difficulty){

    };
    /**
     * Defualt destructor
     */
    ~CComputer() override = default;

    /**
     * Creates a new action based on the difficulty.
     * @param source
     * @return new action of the player
     */
    CAction* MakeAction(CEstablishment * source) const override;

    /**
     * Easiest difficulty, selects the first available establishment to attack.
     * @param source establishment
     * @return computer's action
     */
    CAction* SuperEasy(CEstablishment * source) const;

    /**
     * Second easiest difficulty, selects the establishment with lowest health.
     * @param source establishment
     * @return computer's action
     */
    CAction* Easy(CEstablishment * source) const;

    /**
     * Third difficulty, if it has more than 12 health, tries to heal other establishments
     * of the same player, otherwise attacks the establishment with lowest health.
     * @param source establishment
     * @return computer's action
     */
    CAction* Healer(CEstablishment * source) const;

private:
    int difficulty;
};















#endif //SEMESTRAL_CCOMPUTER_H
