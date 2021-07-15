#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct card {
    char shape;
    int num;
    char color;
    char pattern;
};


//function to check if the card features are all the same
int checkSame(card one, card two, card three){
    int sum = 0; 
    if (one.shape==two.shape&&two.shape==three.shape){
        ++sum;
    }
    if(one.num==two.num&&two.num==three.num){
        ++sum;
    }
    if(one.color==two.color&&two.color==three.color){
        ++sum;
    }
    if(one.pattern==two.pattern&&two.pattern==three.pattern){
        ++sum;
    }
    return sum;
}

//function to check if the card features are all different
int checkDifferent(card one, card two, card three){
    int sum = 0; 
    if (one.shape!=two.shape&&two.shape!=three.shape&&one.shape!=three.shape){
        ++sum;
    }
    if(one.num!=two.num&&two.num!=three.num&&one.num!=three.num){
        ++sum;
    }
    if(one.color!=two.color&&two.color!=three.color&&one.color!=three.color){
        ++sum;
    }
    if(one.pattern!=two.pattern&&two.pattern!=three.pattern&&one.pattern!=three.pattern){
        ++sum;
    }
    return sum;
}

//Checks all combos for possible sets
void solveSets (const vector<card> &board){
    for(int x=0; x<board.size()-2; ++x){
        for(int y=x+1; y<board.size()-1;++y){
            for(int z=y+1; z<board.size();++z){
                int sum1=checkSame(board[x],board[y],board[z]);
                int sum2=checkDifferent(board[x],board[y],board[z]);
                if(sum1+sum2==4){
                    cout<<"Cards: "<< x+1<<" "<<y+1<<" "<<z+1<<" are a Set!"<<endl;
                }
            }

        }

    }
}

int main(){
    string filename;
    cout<<"Type in filename containing cards: ";
    cin>>filename;
    ifstream fin(filename.c_str());
    if(!fin.is_open()){
        cout<<"Error opening file"<<endl;
        return 1;
    }
    
    //read in the data from file
    card cards;
    vector<card> board;
    while (fin>> cards.shape>> cards.num>>cards.color>>cards.pattern){
        board.push_back(cards);
    }
    //solves sets
    solveSets(board);
    return 0;
}

