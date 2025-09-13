#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class Player {
public:
    string name;
    int wins;

    Player(string playerName) {
        name = playerName;
        wins = 0;
    }

    void addWin() {
        wins++;
    }
};

class Dice {
public:
    int roll() {
        return rand() % 6 + 1;
    }
};

class DiceGame {
private:
    unordered_map<string, Player> players;
    vector<string> playerOrder;
    Dice dice;

public:
    void addPlayer(string name) {
        players[name] = Player(name);
        playerOrder.push_back(name);
    }

    void playRound() {
        unordered_map<string, int> rolls;
        int highestRoll = 0;

        cout << "\nRolling dice for all players...\n";
        for (auto &p : playerOrder) {
            int rollValue = dice.roll();
            rolls[p] = rollValue;
            cout << p << " rolled: " << rollValue << endl;
            if (rollValue > highestRoll) {
                highestRoll = rollValue;
            }
        }

        vector<string> roundWinners;
        for (auto &r : rolls) {
            if (r.second == highestRoll) {
                roundWinners.push_back(r.first);
            }
        }

        if (roundWinners.size() == 1) {
            players[roundWinners[0]].addWin();
            cout << "Winner of this round: " << roundWinners[0] << "\n";
        } else {
            cout << "It's a tie between: ";
            for (auto &w : roundWinners) {
                cout << w << " ";
            }
            cout << "\n";
        }
    }

    void showGameResult() {
        cout << "\n=== Final Results ===\n";
        vector<Player> leaderboard;
        for (auto &p : players) {
            leaderboard.push_back(p.second);
        }

        sort(leaderboard.begin(), leaderboard.end(),
             [](Player &a, Player &b) {
                 return a.wins > b.wins;
             });

        for (auto &p : leaderboard) {
            cout << p.name << " - Wins: " << p.wins << endl;
        }
    }
};

int main() {
    srand(time(0));
    DiceGame game;

    int numPlayers;
    cout << "Enter number of players: ";
    cin >> numPlayers;

    for (int i = 0; i < numPlayers; i++) {
        string playerName;
        cout << "Enter player " << i + 1 << " name: ";
        cin >> playerName;
        game.addPlayer(playerName);
    }

    int numRounds;
    cout << "Enter number of rounds: ";
    cin >> numRounds;

    for (int i = 0; i < numRounds; i++) {
        cout << "\n--- Round " << i + 1 << " ---\n";
        game.playRound();
    }

    game.showGameResult();
    return 0;
}
