#include <bits/stdc++.h>

using namespace std;

class board {
    public:
        vector<vector<int>> boardCardsMatrix;
        vector<vector<int>> boardCardsMatrixCopy;

        void Initialize() {
            boardCardsMatrix = {{0, 0, 1, 0},  // 0
                                {0, 0, 1, 0},  // 1
                                {0, 0, 1, 0},  // 2
                                {0, 0, 1, 0},  // 3
                                {0, 0, 0, 0},  // 4
                                {0, 0, 0, 0},  // 5
                                {0, 0, 0, 0},  // 6
                                {0, 0, 1, 0},  // 7
                                {0, 0, 0, 0},  // 8
                                {0, 0, 0, 0},  // 9
                                {0, 0, 0, 0},  // 10
                                {0, 0, 0, 0},  // 11
                                {0, 0, 0, 0}}; // 12
        }

        void update() {
            boardCardsMatrixCopy = boardCardsMatrix;
        }

        void display() {
            for (auto row : boardCardsMatrix) {
                for (auto e : row) {
                    cout << e << " ";
                }
                cout << endl;
            }
        }
        
        void displayCopy() {
            for (auto row : boardCardsMatrixCopy) {
                for (auto e : row) {
                    cout << e << " ";
                }
                cout << endl;
            }
        }

        void putCard(string card_string) {
            pair<int, int>cardIndex = convertCardtoIndex(card_string);
            boardCardsMatrixCopy[cardIndex.first][cardIndex.second]++;
        }

        void eraseCard(string card_string) {
            pair<int, int>cardIndex = convertCardtoIndex(card_string);
            boardCardsMatrixCopy[cardIndex.first][cardIndex.second]--;
        }

        vector<string> solve(vector<string> playerDeck) {
            vector<string> playerDeckRevised = playerDeck;
            for (int iter=0; iter < playerDeck.size(); iter++){
                pair<int, int>playerCardIndex = convertCardtoIndex(playerDeck[iter]);
                int playerCard_j = playerCardIndex.first; //number...up and down.
                int playerCard_i = playerCardIndex.second; //color..right and left.

                if (UpDownCheck(playerCard_i, playerCard_j)){
                    playerDeckRevised[iter] += "_is_placed!";
                }
            }
            return playerDeckRevised;
        }

    private:
        bool UpDownCheck(int x, int y){
            return ((boardCardsMatrixCopy[y+1][x] >= 1) && (boardCardsMatrixCopy[y+2][x] >= 1)) || ((boardCardsMatrixCopy[y-1][x] >= 1) && (boardCardsMatrixCopy[y-2][x] >= 1));
        }

        pair<int, int> convertCardtoIndex(string s){
            map<string, int> m1{{"red", 1}, {"blue", 2}, {"black", 3}, {"orange", 4}};

            size_t i = 0;

            // Extract letters
            string card_color, card_number;
            while (i < s.size() && isalpha(s[i])) {
            card_color += s[i];
            i++;
            }
            int card_colorIndex = m1[card_color];

            // Extract numbers
            while (i < s.size() && isdigit(s[i])) {
            card_number += s[i];
            i++;
            }
            int card_numberIndex = stoi(card_number);

            return pair<int, int> (card_numberIndex-1, card_colorIndex-1);
        }
};


class boardCopy {

}

//"red 1", "blue 2", "black 3", "orange 4"

int main() {
    vector<string> playerDeck = {"red5",  "black5", "orange5", "black6",
                                "blue7", "black7", "orange7"};
    board boardCards;
    boardCards.Initialize();
    boardCards.display();
    boardCards.update();

    for (const auto &card : playerDeck) {
        boardCards.putCard(card);
    }
    boardCards.displayCopy();
    vector<string>playerDeckRevised = boardCards.solve(playerDeck);
    for(const auto &card : playerDeckRevised){
        cout << card << endl;
    }

}
