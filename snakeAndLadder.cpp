#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class Snake {
public:
    Snake(int head, int tail) : head(head), tail(tail) {}
    int getHead() const { return head; }
    int getTail() const { return tail; }

private:
    int head;
    int tail;
};

class Ladder {
public:
    Ladder(int start, int end) : start(start), end(end) {}
    int getStart() const { return start; }
    int getEnd() const { return end; }

private:
    int start;
    int end;
};

class Board {
public:
    Board(int size, const vector<Snake>& snakes, const vector<Ladder>& ladders)
        : size(size) {
        for (const auto& snake : snakes) {
            snakesMap[snake.getHead()] = snake.getTail();
        }
        for (const auto& ladder : ladders) {
            laddersMap[ladder.getStart()] = ladder.getEnd();
        }
    }

    int getSize() const {
        return size;
    }

    int getNewPosition(int position) const {
        if (snakesMap.find(position) != snakesMap.end()) {
            return snakesMap.at(position);
        }
        if (laddersMap.find(position) != laddersMap.end()) {
            return laddersMap.at(position);
        }
        return position;
    }

private:
    int size;
    unordered_map<int, int> snakesMap;
    unordered_map<int, int> laddersMap;
};

class Player {
public:
    Player(const string& name) : name(name), position(0) {}

    const string& getName() const {
        return name;
    }

    int getPosition() const {
        return position;
    }

    void setPosition(int pos) {
        position = pos;
    }

private:
    string name;
    int position;
};

class Dice {
public:
    Dice(int noOfDice) : noOfDice(noOfDice) {
        std::srand(std::time(nullptr));
    }

    int roll() const {
        return (rand() % (6*noOfDice)) + 1;
    }

private:
    int noOfDice;
};

class Game {
public:
    Game(Board board, vector<Player> players) 
        : board(board), players(players), dice(1) {}

    void play() {
        bool gameWon = false;
        while (!gameWon) {
            for (Player& player : players) {
                int diceValue = dice.roll();
                int initialPosition = player.getPosition();
                int newPosition = initialPosition + diceValue;

                if (newPosition > board.getSize()) {
                    newPosition = initialPosition;
                } else {
                    newPosition = board.getNewPosition(newPosition);
                }

                player.setPosition(newPosition);
                cout << player.getName() << " rolled a " << diceValue 
                          << " and moved from " << initialPosition << " to " << newPosition <<endl;

                if (newPosition == board.getSize()) {
                    cout << player.getName() << " wins the game!" << endl;
                    gameWon = true;
                    break;
                }
            }
        }
    }

private:
    Board board;
    vector<Player> players;
    Dice dice;
};

int main() {
    
    // vector<Snake> snakes = {Snake(14, 7), Snake(22, 5), Snake(36, 20)};
    // vector<Ladder> ladders = {Ladder(2, 23), Ladder(8, 34), Ladder(40, 89)};
    // vector<Player> players = {Player("Alice"), Player("Bob"), Player("Charlie")};
    vector<Snake> snakes;
    vector<Ladder> ladders;
    vector<Player> players;
    int totalSnakes,totalLadders,TotalPlayers;
    cin>>totalSnakes;
    for(int i=0;i<totalSnakes;i++){
        int head,tail;
        cin>>head>>tail;
        Snake s(head,tail);
        snakes.push_back(s);
    }
    cin>>totalLadders;
    for(int i=0;i<totalLadders;i++){
        int start,end;
        cin>>start>>end;
        Ladder l(start,end);
        ladders.push_back(l);
    }
    cin>>TotalPlayers;
    for(int i=0;i<TotalPlayers;i++){
        string name;
        cin>>name;
        Player p(name);
        players.push_back(p);
    }
    Board board(100, snakes, ladders);
    Game game(board, players);
    game.play();

    return 0;
}
