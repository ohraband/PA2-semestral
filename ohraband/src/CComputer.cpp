//
// Created by Andy on 7. 6. 2021.
//

#include "CComputer.h"

CAction* CComputer::Healer(CEstablishment * source) const{

    //creates a list of possible targets
    vector<CEstablishment* > targets = map->GetEstablishmentList();

    //try to heal other establishments
    if(source->GetAvailableRepresentatives() > 12){
        for(auto t : targets){
            if(t != source && t->Playername() == source->Playername()){
                CAction * action = new CAction(source, t, map);
                if(action->GetRoute()->IsEmpty()){
                    delete action;
                }
                else{
                    return action;
                }
            }
        }
    }

    //sort establishments by their health
    sort(targets.begin(), targets.end(), [](CEstablishment* lhs, CEstablishment* rhs) {
        return lhs->GetAvailableRepresentatives() < rhs->GetAvailableRepresentatives();
    });


    //attack the one with the lowest health
    for(auto t : targets){
        if(t != source && t->Playername() != source->Playername()){
            CAction * action = new CAction(source, t, map);
            if(action->GetRoute()->IsEmpty()){
                delete action;
            }
            else{
                return action;
            }
        }
    }
    return nullptr;
}

CAction* CComputer::SuperEasy(CEstablishment * source) const{

    //creates a list of possible targets
    vector<CEstablishment* > targets = map->GetEstablishmentList();

    //attack the first one
    for(auto t : targets){
        if(t != source && t->Playername() != source->Playername()){
            CAction * action = new CAction(source, t, map);
            if(action->GetRoute()->IsEmpty()){
                delete action;
            }
            else{
                return action;
            }
        }
    }
    return nullptr;
}



CAction* CComputer::Easy(CEstablishment* source) const{

    //creates a list of possible targets
    vector<CEstablishment* > targets = map->GetEstablishmentList();

    //sort establishments by their health
    sort(targets.begin(), targets.end(), [](CEstablishment* lhs, CEstablishment* rhs) {
        return lhs->GetAvailableRepresentatives() < rhs->GetAvailableRepresentatives();
    });


    //attack the one with the lowest health
    for(auto t : targets){
        if(t != source && t->Playername() != source->Playername()){
            CAction * action = new CAction(source, t, map);
            if(action->GetRoute()->IsEmpty()){
                delete action;
            }
            else{
                return action;
            }
        }
    }
    return nullptr;
}



CAction* CComputer::MakeAction(CEstablishment * source) const {

    vector<CEstablishment* > sources = map->PlayerEstablishments(playername);
    vector<CEstablishment* > targets = map->GetEstablishmentList();


        if(difficulty == 1){
            return SuperEasy(source);
        }
        else if(difficulty == 2){
            return Easy(source);
        }
        else if(difficulty == 3){
            return Healer(source);
        }

    return nullptr;
}
