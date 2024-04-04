//
// Created by Andy on 4. 6. 2021.
//
#include <iostream>
#include <curses.h>

#include "CMap.h"



using namespace std;

vector<vector<char>> CMap::LoadMap(const string & mapfilename) const{
    //count lines
    ifstream LineCount(mapfilename);
    string line;
    int lines=0;
    while (getline(LineCount, line)) {
        lines++;
    }

    //create a 2D vector
    ifstream MapFile(mapfilename);
    vector<vector<char>> tmpobjects;
    tmpobjects.resize(lines);

    char c;
    int i=0;
    while (MapFile.get(c)) {
        if(c == '\n'){
            i++;
        }
        else if(c == '\r'){

        }
        else {
            tmpobjects[i].push_back(c);
        }
    }

    return tmpobjects;
}

vector<CEstablishment*> CMap::PlayerEstablishments(char name) const{
    vector<CEstablishment*> PlayerEst;

    for (const auto& est : EstablishmentList){
        if(name == est->Playername()){
            PlayerEst.push_back(est);
        }
    }
    return PlayerEst;
}

int CMap::PlayerEstablishmentsNum(char name) const{
    int PlayerEst = 0;

    for (const auto& est : EstablishmentList){
        if(name == est->Playername()){
            PlayerEst++;
        }
    }
    return PlayerEst;
}

void CMap::HireRepresentatives() const{
    for (const auto& est : EstablishmentList){
        for(int i = 0; i < 3; i++) {
            est->Hire();
        }
    }
}


void CMap::AddRoute(CRoute * road){
    routes.push_back(road);
}

void CMap::RemoveRoute(CRoute * road){
    routes.erase(remove(routes.begin(), routes.end(), road), routes.end());
}

vector<Position> CMap::PossibleMoves(Position pos, CEstablishment *store1, CEstablishment *store2) const{
    vector<Position> moves;

    //???
    //?X?
    //???

    //middle row
    if(IsWalkable(Position(pos.y(),pos.x()+1),store1,store2)){
        moves.emplace_back(pos.y(),pos.x()+1);}

    if(IsWalkable(Position(pos.y(),pos.x()-1),store1,store2)){
        moves.emplace_back(pos.y(),pos.x()-1);}


    //bottom row
    if(IsWalkable(Position(pos.y()+1,pos.x()),store1,store2)){
        moves.emplace_back(pos.y()+1,pos.x());}

    if(IsWalkable(Position(pos.y()+1,pos.x()-1),store1,store2)){
        moves.emplace_back(pos.y()+1,pos.x()-1);}

    if(IsWalkable(Position(pos.y()+1,pos.x()+1),store1,store2)){
        moves.emplace_back(pos.y()+1,pos.x()+1);}

    //upper row
    if(IsWalkable(Position(pos.y()-1,pos.x()-1),store1,store2)){
        moves.emplace_back(pos.y()-1,pos.x()-1);}

    if(IsWalkable(Position(pos.y()-1,pos.x()),store1,store2)){
        moves.emplace_back(pos.y()-1,pos.x());}

    if(IsWalkable(Position(pos.y()-1,pos.x()+1),store1,store2)){
        moves.emplace_back(pos.y()-1,pos.x()+1);}

    return moves;
}

bool CMap::IsWalkable(Position pos, CEstablishment *store1, CEstablishment *store2) const{

    if(pos.y() >= height || pos.x() >= width ){
        return false;
    }
    else{
        if( GetItem(pos) == store1 || GetItem(pos) == store2 || GetItem(pos)->Walkable()){
            return true;
        }
        return false;
    }

}


void CMap::Show() const{
    src->Sleep();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            PosItems[i][j]->Show(src);
        }
    }


    for (const auto& est : EstablishmentList){
        est->Show(src);
    }

    src->Sleep();
}

void CMap::ShowSingleRoute(CRoute* road) const{
    road->ShowRoute(src);
}


void CMap::ShowReps() const{
    for(auto x : routes){
        x->ShowReps(src);
    }
    src->Sleep();
}

void CMap::ShowRoutes() const{
    for(auto x : routes){
        x->ShowRoute(src);
    }
}

void CMap::ShowEstablishments() const{
    for (const auto& est : EstablishmentList){
        est->Show(src);
    }
}


void CMap::HighlightAllEst(CEstablishment* source) const{
    for(unsigned int i = 0 ; i < EstablishmentList.size(); i++){
        EstablishmentList[i]->Show(src);
        if(source == EstablishmentList[i]){
            EstablishmentList[i]->Highlight(src,'S');
        }
        else {
            EstablishmentList[i]->Highlight(src, i);
        }
    }
}

const string &CMap::GetFilename() const {
    return filename;
}

int CMap::GetWidth() const {
    return width;
}

const vector<CEstablishment *> &CMap::GetEstablishmentList() const {
    return EstablishmentList;
}

const CScreen* CMap::GetSrc() const {
    return src;
}


CViewableItem* CMap::GetItem(Position pos) const{
    if(pos.y() < height && pos.x() < width){
        return PosItems[pos.y()][pos.x()];
    }
    else{
        return nullptr;
    }
}

vector<vector<CViewableItem*>> CMap::MakePosItems(vector<vector<char>> Coordinates , int height, int width){
    vector<vector<CViewableItem*>> PosItems;
    PosItems.resize(height);
    //make PosItems correct size
    for(auto & PosItem : PosItems){
        PosItem.resize(width);
    }
    //for each coordinate create a corresponding positem
    for (unsigned int i = 0 ; i < Coordinates.size(); i++)
    {
        for (unsigned int j = 0 ; j < Coordinates[i].size(); j++)
        {
            if(PosItems[i][j] == nullptr) {

                Position pos((int)i, (int)j);

                if (Coordinates[i][j] == ' '){
                    NothingList.push_back(new CNothing(pos, Coordinates[i][j]));
                    PosItems[i][j] = NothingList[NothingList.size()-1];
                }

                else if ( (Coordinates[i][j] >= 'A' && Coordinates[i][j] <= 'V') ||  Coordinates[i][j] == 'Y'
                          || Coordinates[i][j] == 'Z') {          //'X' is used as a map block and i don't want to change that
                    EstablishmentList.push_back(new CEstablishment(pos, Coordinates[i][j]));
                    PosItems[i][j] = EstablishmentList[EstablishmentList.size()-1];
                    //make all establishments positions point to the same item
                    PosItems[i][j+1] = PosItems[i][j];
                    PosItems[i][j+2] = PosItems[i][j];
                    PosItems[i+1][j] = PosItems[i][j];
                    PosItems[i+1][j+1] = PosItems[i][j];
                    PosItems[i+1][j+2] = PosItems[i][j];
                    players.insert(Coordinates[i][j]);
                }

                else {
                    ObstacleList.push_back(new CObstacle(pos, Coordinates[i][j]));
                    PosItems[i][j] = ObstacleList[ObstacleList.size()-1];
                }

            }
        }
    }
    return PosItems;
}


bool CMap::CheckPlayer(char playername){
    if(players.count(playername) > 0){
        return true;
    }
    else{
        return false;
    }
}