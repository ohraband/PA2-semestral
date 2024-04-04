//
// Created by Andy on 7. 6. 2021.
//

#include "CGame.h"


void CGame::OneTurn() {

    //Create actions for each player.
    for(auto p : players){
        vector<CEstablishment* > est = map.PlayerEstablishments(p->GetPlayername());
        for(auto establishment : est){
            CAction * action = p->MakeAction(establishment);
            if(action == nullptr){
                delete action;
            }
            else{
                actions.push_back(action);
            }
        }
    }



    //Run each action while it is not finished.
    while(!actions.empty()){
        for (auto it = actions.begin(); it != actions.end(); ) {
            (*it)->Do();
            if((*it)->Finished()){
                delete (*it);
                //remove finished action
                it = actions.erase(it);
            }
            else {
                ++it;
            }
        }
        //display state of the map after each run
        map.ShowRoutes();
        map.ShowReps();
        map.ShowEstablishments();
    }

    //Increase number of representatives in each Establishment
    map.HireRepresentatives();
    //Show the whole map
    map.Show();


}

void CGame::RefreshScreen() const {
    map.GetSrc()->DeleteAll();
}

void CGame::AddPlayers() {

    //Human player
    if(map.CheckPlayer('P')){
        auto* a = new CHuman(&map, 'P');
        players.push_back(a);
    }

    //Computer players
    for(char i = 'A' ; i < 'Z' ; i++){
        if(map.CheckPlayer(i) && i != 'P'){
            auto* a = new CComputer(&map, (signed char)i, difficulty);
            players.push_back(a);
        }
    }
}

bool CGame::Win() const{
    //Check if a player has all the establishments on the map
    for(auto p : players){
        if( (int)map.GetEstablishmentList().size() == map.PlayerEstablishmentsNum(p->GetPlayername()) ){
            RefreshScreen();
            char name = p->GetPlayername();
            string winner(1,name);
            winner += " wins!! yay";
            map.GetSrc()->ShowString(2,5, winner);
            //wait for character input to continue
            getch();
            return true;
        }
    }
    return false;
}

void CGame::RunGame() {
    AddPlayers();
    while(!Win()){
        OneTurn();

        map.GetSrc()->ShowString(3,map.GetWidth() + 7,"Round ended. Press \"s\" to save the game,\"q\" to quit.       ");
        map.GetSrc()->ShowString(4,map.GetWidth() + 7,"Press any other key to continue.                          ");
        map.GetSrc()->ShowString(5,map.GetWidth() + 7,"                                                          ");
        map.GetSrc()->ShowString(5,map.GetWidth() + 7,"");
        char save = getch();
        if(save == 's'){
            map.GetSrc()->ShowString(3,map.GetWidth() + 7,"                                                           ");
            map.GetSrc()->ShowString(4,map.GetWidth() + 7,"Please enter the savefile name.                            ");
            map.GetSrc()->ShowString(5,map.GetWidth() + 7,"                                                           ");
            map.GetSrc()->ShowString(5,map.GetWidth() + 7,"");

            SaveGame(savedir);

            map.GetSrc()->ShowString(3,map.GetWidth() + 7,"Game saved.                                               ");
            map.GetSrc()->ShowString(4,map.GetWidth() + 7,"Press \"q\" to quit or any other key to continue.         ");
            map.GetSrc()->ShowString(5,map.GetWidth() + 7,"                                                           ");
            map.GetSrc()->ShowString(5,map.GetWidth() + 7,"");
            save = getch();
        }

        if(save == 'q'){
            //quit the game
            return;
        }


    }
}

void CGame::SaveGame(const string& directoryname) const{

    bool ok = false;
    string filename;
    while(!ok) {
        string savename;
        char k = getch();
        int i = map.GetWidth() + 7;
        move(5, i);
        printw("%c", k);
        while (k != 10) { //enter key
            savename += k;
            move(5, i);
            i++;
            printw("%c", k);
            k = getch();
        }

        filename = directoryname + savename;
        ifstream exists(filename);
        if(exists.good()){
            map.GetSrc()->ShowString(3,map.GetWidth() + 7,"File alredy exists.                                        ");
            map.GetSrc()->ShowString(4,map.GetWidth() + 7,"Please enter different savefile name.                      ");
            map.GetSrc()->ShowString(5,map.GetWidth() + 7,"                                                           ");
            map.GetSrc()->ShowString(5,map.GetWidth() + 7,"");
            savename = "";
        }
        else{
            ok = true;
        }
    }

    ofstream file(filename);
    bool open = file.is_open();
    if(!open){
        map.GetSrc()->ShowString(3,map.GetWidth() + 7,"Error saving game.                                         ");
        map.GetSrc()->ShowString(4,map.GetWidth() + 7,"Please enter different savefile name.                      ");
        map.GetSrc()->ShowString(5,map.GetWidth() + 7,"                                                           ");
        map.GetSrc()->ShowString(5,map.GetWidth() + 7,"");
        return;
    }
    if(!file.good()){
        map.GetSrc()->ShowString(3,map.GetWidth() + 7,"Error saving game.                                         ");
        map.GetSrc()->ShowString(4,map.GetWidth() + 7,"Please enter different savefile name.                      ");
        map.GetSrc()->ShowString(5,map.GetWidth() + 7,"                                                           ");
        map.GetSrc()->ShowString(5,map.GetWidth() + 7,"");
        return;
    }

    file << map.GetFilename() << endl;
    file << difficulty << " " <<  map.GetEstablishmentList().size() << endl;
    for(auto est : map.GetEstablishmentList()){
        file << est->Playername() << " " << est->GetAvailableRepresentatives() << " " << est->GetMaxRepresentatives() << " ";
    }

    file.close();
}

void CGame::LoadGame(const string& filename) const{

    ifstream file(filename);
    string mapname;
    getline(file,mapname);
    getline(file,mapname);

    string establishments;
    char name;
    int reps;
    int maxreps;

    for(auto est : map.GetEstablishmentList()){
        file >> name;
        file >> reps;
        file >> maxreps;
        est->LoadSet(name,reps,maxreps);
    }

}


pair<string,int> CGame::LoadMap(const string& filename) const{

    ifstream file(filename);
    string mapname;
    int diff;
    getline(file,mapname);
    file >> diff;
    pair<string,int> data;
    data.first = mapname;
    data.second = diff;
    return data;
}

