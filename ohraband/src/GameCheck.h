//
// Created by Andy on 10. 6. 2021.
//

#ifndef SEMESTRAL_GAMECHECK_H
#define SEMESTRAL_GAMECHECK_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

/**
 * Checks if all lines are the same width.
 * @param filename - map file name
 * @return true if all lines are the same width, false otherwise
 */
bool CheckLines(const string & filename) {
    ifstream MapFile(filename);
    if(!MapFile.good()){
        cout << "Bad Mapfile" << endl;
        return false;
    }

    char c;
    int linelength = 0;
    int correctlinelength = 0;
    while (MapFile.get(c)) {
        if(c == '\n'){
            if(!correctlinelength){
                correctlinelength = linelength;
            }
            else{
                if(correctlinelength != linelength) {
                    MapFile.close();
                    return false;
                }
            }
            linelength = 0;
        }
        else{
            linelength++;
        }
    }
    MapFile.close();
    return true;
}

/**
 * Checks if all map has the corect format
 * @param filename - map filename
 * @return true if all map has the corect format, false otherwise
 */
bool CheckViewItems(const string & filename) {
    //get number of lines
    ifstream LineCount(filename);
    string line;
    bool open = LineCount.is_open();
    if(!open){
        cout << "Bad MapFile name" << endl;
        return false;
    }
    if(!LineCount.good()){
        cout << "Bad MapFile name" << endl;
        return false;
    }
    int lines=0;
    while (getline(LineCount, line)) {
        lines++;
    }

    //check if terminal has correct size and supports colors
    int col, row;
    initscr();
    getmaxyx(stdscr,row,col);

    if (!has_colors())
    {
        endwin();
        cout << "Sorry, your terminal does not support colors." << endl;
        cout << "This game is not worth playing without them." << endl;
        return false;
    }


    endwin();
    cout << "Rows avaliable: " << row << endl;
    cout << "Number of lines in text file: " << lines << endl;
    cout << "Columns avaliable: " << col << endl;
    cout << "Line length: " << line.length() + 70<< endl;

    if(lines < 4 || line.length() < 4){
        cout << "This file is too small to even be a map." << endl;
        return false;
    }

    if(row < lines || col < (int)line.length() + 70 ){
        cout << "Too small window." << endl;
        return false;
    }


    //checks empty spaces, obstacles and establishments
    ifstream ViewItem(filename);
    string itemline;
    int seclines=0;
    set<int> eststart; //set of positions where establishments start
    //iterate over every line
    while (getline(ViewItem, itemline)) {
        //check if edges are all obstacles
        if(seclines == 0 || seclines == (lines-1) ){
            for(char i : itemline){
                if(i == ' ' || (i > 'A' && i < 'V') || i == 'Y' || i == 'Z'){
                    return false;
                }
            }
        }
        if(itemline[0] == ' ' || (itemline[0] > 'A' && itemline[0] < 'V') || itemline[0] == 'Y' || itemline[0] == 'Z'){
            return false;
        }
        if(itemline[itemline.size()-1] == ' ' || (itemline[itemline.size()-1] >= 'A' && itemline[itemline.size()-1] <= 'V') ||
           itemline[itemline.size()-1] == 'Y' || itemline[itemline.size()-1] == 'Z'){
            return false;
        }

        //check if establishments are correct
        for(long unsigned int i = 0 ; i < itemline.size() ; i++){

            if(eststart.find(i) != eststart.end()){
                if(itemline[i] != 'n' || itemline[i+1] != 'n' || itemline[i+2] != 'n'){
                    return false;
                }
                eststart.erase(i);
            }

            if((itemline[i] > 'A' && itemline[i] < 'V') || itemline[i] == 'Y' || itemline[i] == 'Z'){
                eststart.insert(i);
                if( i+3 >= itemline.size()-1 || seclines + 2 >= lines ){
                    return false;
                }
                else{
                    if(itemline[i+1] != 'n' || itemline[i+2] != 'n'){
                        return false;
                    }
                }
            }
        }

        seclines++;
    }
    return true;
}

/**
 * Count number of the establishments on the map.
 * @param filename - - map file name
 * @return number of establishments
 */
int CountEst(const string& filename){
    ifstream LineCount(filename);
    string line;
    int est = 0;
    while (getline(LineCount, line)) {
        for(auto l : line){
            if((l > 'A' && l < 'V') || l == 'Y' || l == 'Z'){
                est++;
            }
        }
    }
    LineCount.close();
    return est;
}

/**
 * Checks if map can be successfully created from a save file.
 * @param filename - save file name
 * @return true if it can, false otherwise
 */
bool CheckLoadMap(const string& filename){
    cout << filename << endl;
    ifstream file(filename);
    if(!file.good()){
        cout << "Bad Savefile" << endl;
        return false;
    }

    string mapname;
    int diff = -1;
    int estnum = -1;
    if ( !(getline(file,mapname))){
        cout << mapname << endl;
        return false;
    }


    if(mapname[mapname.size()-1] == '\r'){
        mapname.pop_back();
    }
    if ( !CheckLines(mapname) || !CheckViewItems(mapname)){
        cout << mapname << endl;
        return false;
    }
    cout << "loadmap" << mapname << endl;

    if(!(file >> diff) || !(file >> estnum)){
        cout << diff << endl;
        cout << estnum << endl;
        return false;
    }

    if(estnum != CountEst(mapname)){
        cout << "Wrong estnum" << endl;
        return false;
    }

    if(diff < 0 || diff > 3){
        cout << "Wrong diff" << endl;
        return false;
    }

    char name = 'A';
    int reps = -1;
    int maxreps = -1;
    for(int i = 0 ; i < estnum ; i++){
        if(!(file >> name) || !(file >> reps) || !(file >> maxreps) ){
            return false;
        }

        if(name < 'A' || (name >= 'V' && name != 'Y' && name == 'Z') ){
            return false;
        }
        if(reps > maxreps){
            return false;
        }
    }

    file.close();
    return true;
}


#endif //SEMESTRAL_GAMECHECK_H
