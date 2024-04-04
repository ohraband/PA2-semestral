//
// Created by Andy on 7. 6. 2021.
//

#include "CHuman.h"

using namespace std;

CAction* CHuman::MakeAction(CEstablishment * source) const {

    CEstablishment* target = nullptr;
    //Get list of all establishments
    vector<CEstablishment* > targets = map->GetEstablishmentList();

    //Highlight all establishments on the map
    map->HighlightAllEst(source);

    if(!targets.empty()){
        while(true) {
            map->GetSrc()->ShowString(5,map->GetWidth() + 7,"                                                   ");
            map->GetSrc()->ShowString(5,map->GetWidth() + 7,"");

            long unsigned int num  = HumanInput();
            //check if selected establishment is attackable
            if (targets.size() > num) {
                target = targets[num];
                if(source != target){
                    CAction * action = new CAction(source, target, map);
                    //if route does not exist, ask again
                    if(action->GetRoute()->IsEmpty()){
                        ImpossibleRoute();
                        char giveup = getch();
                        if(giveup == 's'){
                            return nullptr;
                        }
                    }
                    else{
                        return action;
                        break;
                    }
                }
            }
        }
    }


    return nullptr;
}

void CHuman::ImpossibleRoute() const{
    map->GetSrc()->ShowString(3,map->GetWidth() + 7,"Impossible route, please choose another one.                ");
    map->GetSrc()->ShowString(4,map->GetWidth() + 7,"Or press \"s\" to skip."                                     );
}




int CHuman::HumanInput() const{
    map->GetSrc()->ShowString(3,map->GetWidth() + 7,"Current Establishment is \'S\' others are marked by numbers."  );
    map->GetSrc()->ShowString(4,map->GetWidth() + 7,"Press number of the Establishment you want to attack."         );
    map->GetSrc()->ShowString(5,map->GetWidth() + 7,"");

    //get input from human
    string input;
    char k = getch();
    int i = map->GetWidth() + 7;
    move(5,i);
    printw("%c",k);
    while(k != 10){ //enter key
        input += k;
        move(5,i);
        i++;
        printw("%c",k);
        k = getch();
    }

    //process human input into an integer
    int num = 0;
    if(input.empty()){
        return -1;
    }
    for(const auto a : input){
        if(a < 48 || a > 57){
            return -1;
        }
        else{
            num += a - 48;
            num *= 10;
        }
    }
    num /= 10;



    return num;
}
