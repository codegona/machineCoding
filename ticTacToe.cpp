#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>

using namespace std;


class Players{
    string name;
    char piece;

    public:
        Players(string name,char piece): name(name), piece(piece) {};
        string getName() {
            return name;
        }
        char getPiece() {
            return piece;
        }
};

class Board{
    vector<vector<char>> grid;
    public:
        Board(): grid(3, vector<char>(3, '-')) {}
        void getGrid() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cout << grid[i][j];
                    
                }
                cout << endl;
            }
            cout<<endl;
        }
        
        bool checkValidMove(int row,int col){
            if( row<0 || col<0 || row >2 || col> 2 || grid[row][col] != '-') return false;
            return true;
        }
        bool isFull(){

            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if( grid[i][j] == '-')
                        return false;
                }
            }
            return true;
        }
        bool checkWinner(int row,int col, char piece){
            
             // Check rows and columns
            for (int i = 0; i < 3; i++) {
                if (grid[i][0] == piece && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
                    return true;
                if (grid[0][i] == piece && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
                    return true;
            }
            // Check diagonals
            if (grid[0][0] == piece && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
                return true;
            if (grid[0][2] == piece && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
                return true;
            return false;
        }
        void placePiece(int row,int col,char piece){
            grid[row][col]= piece;

        }
};

class Game{
    Players player1,player2;
    Board grid;
    Players *currentTurn;
    public:
        Game(Players p1,Players p2,Board grid): player1(p1),player2(p2),grid(grid),currentTurn(&player1){};
        
        void play(){
            grid.getGrid();
            
            while(true){
                int row, col;
                cin>>row>>col;
                row--;
                col--;
                if(!grid.checkValidMove(row,col)){
                    cout<<"Invalid Move";
                    continue;
                }
                grid.placePiece(row,col,currentTurn->getPiece());

                grid.getGrid();
                if(grid.checkWinner( row,col, currentTurn->getPiece())){
                    cout<<currentTurn->getName()<<" wins the game"<<endl;
                    return ;
                }
                if(grid.isFull()){
                    cout<<"Game Over"<<endl;
                    return ;
                }
                currentTurn = (currentTurn == &player1) ? &player2 : &player1;
            }
        }
};

int main(){
    
    string player1,player2;
    char piece1,piece2;
    cin>>piece1>>player1;
    cin>>piece2>>player2;
    Players p1(player1,piece1);
    Players p2(player2,piece2);
    Board grid;
    Game game(p1,p2,grid);
    game.play();
  
}