#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define TOTPOSSCARDS 81

enum Color {Red, Green, Purple};
ifstream& operator>> (ifstream &is, Color &color){
    char i;
    is >> i;
    if (i == 'r'){
        color = Red;
    }else if(i == 'g'){
        color = Green;
    }else{
        color = Purple;
    }

    return is;
}

ofstream& operator<< (ofstream &is, const Color &color){
    char i;
    if (color == Red){
        i = 'r';
    }else if(color == Green){
        i = 'g';
    }else{
        i = 'p';
    }
    is << i;

    return is;
}





enum Shape {Oval, Diamond, Squiggle};

ifstream& operator>> (ifstream &is, Shape &shape){
    char i;
    is >> i;
    if (i == 'o'){
        shape = Oval;
    }else if(i == 'd'){
        shape = Diamond;
    }else{
        shape = Squiggle;
    }

    return is;
}

ofstream& operator<< (ofstream &is, const Shape &shape){
    char i;
    if (shape == Oval){
        i = 'o';
    }else if(shape == Diamond){
        i = 'd';
    }else{
        i = 's';
    }
    is << i;

    return is;
}





enum Pattern {Empty, Lined, Full};

ifstream& operator>> (ifstream &is, Pattern &pattern){
    char i;
    is >> i;
    if (i == 'e'){
        pattern = Empty;
    }else if(i == 'l'){
        pattern = Lined;
    }else{
        pattern = Full;
    }

    return is;
}

ofstream& operator<< (ofstream &is, const Pattern &pattern){
    char i;
    if (pattern == Empty){
        i = 'e';
    }else if(pattern == Lined){
        i = 'l';
    }else{
        i = 'f';
    }
    is << i;

    return is;
}





struct Card{
        size_t cardIndex;
        int num;
        Shape shape;
        Color color;
        Pattern pattern;
        bool here = false;
};





class Set {
    public: 

    void readBoard();
    
    void printBoardandIndexVec(){
        fout << "Beginning of board \n \n";
        for(size_t i = 0; i < board.size(); ++i){
            fout << board[i].color << " ";
            fout << board[i].num << " ";
            fout << board[i].shape << " ";
            fout << board[i].pattern << "\n"; 
        }

        fout << "Beginning of Index \n  \n";
        for(size_t i = 0; i < index.size(); ++i){
            if(index[i].here){
                fout << index[i].color << " ";
                fout << index[i].num << " ";
                fout << index[i].shape << " ";
                fout << index[i].pattern << "\n";  
                fout << index[i].cardIndex << " " << i << "\n";
            }
        }
    }


    private:
    size_t hashFunctionOne(const Card &card);
    size_t hashFunctionTwo(const Card &cardOne, const Card &cardTwo);
    size_t find(size_t hashIndex);

    vector <Card> board;
    vector <Card> index;
    ofstream fout;
    string filename;
    size_t numCards;
};



/* Possible optimization Ideas:
Use parallelism to run match searches on each card instead of running in sequence

Create a hash table for the set with a hash formula such that each pair of cards 
can be indexed to the possible location of the matching third card
*/


//function to check if the card features are all the same
/*int checkSame(Card one, Card two, Card three){
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
}*/

int main(){
    Set set;
    set.readBoard();

    set.printBoardandIndexVec();
    

    return 0;
}


size_t Set::hashFunctionOne(const Card &card){
    return size_t(card.color + (card.num-1)*3 + card.pattern*9 + card.shape*27);
}

size_t Set::hashFunctionTwo(const Card &cardOne, const Card &cardTwo){
    int desiredColor = (cardOne.color + cardTwo.color)%3;
    int desiredNum = (cardOne.num + cardTwo.num)%3;
    int desiredShape = (cardOne.shape + cardTwo.shape)%3;
    int desiredPattern = (cardOne.pattern + cardTwo.pattern)%3;

    if(desiredColor == 1){
        desiredColor = 2;
    }else if(desiredColor == 2){
        desiredColor = 1;
    }

    if(desiredNum == 1){
        desiredNum = 2;
    }else if(desiredNum == 2){
        desiredNum = 1;
    }

    if(desiredShape == 1){
        desiredShape = 2;
    }else if(desiredShape == 2){
        desiredShape = 1;
    }

    if(desiredPattern == 1){
        desiredPattern = 2;
    }else if(desiredPattern == 2){
        desiredPattern = 1;
    }
    

    return size_t(desiredColor + desiredNum*3 + desiredShape*9 + desiredPattern*27);
}



void Set::readBoard(){
    filename = "exBoard.txt";
    ifstream fin(filename.c_str());
    if(!fin.is_open()){
        cout<<"Error opening file"<<endl;
        exit(1);
    }

    fout.open("output.txt");
    if(!fout.is_open()){
        cout<<"Error opening file"<<endl;
        exit(1);
    }

    fin >> numCards;
    board.resize(numCards);
    index.resize(TOTPOSSCARDS);

    Card currentCard;
    for(size_t i = 0; i < numCards; i++){
        fin >> currentCard.color; 
        fin >> currentCard.num;
        fin >> currentCard.shape;
        fin >> currentCard.pattern;
        currentCard.here = true;
        currentCard.cardIndex = i;
        
        board[i] = currentCard;
        index[hashFunctionOne(currentCard)] = currentCard;
    }
}



size_t Set::find(size_t hashIndex){
    if(index[hashIndex].here){
        return hashIndex;
    }
    return TOTPOSSCARDS + 1;
}