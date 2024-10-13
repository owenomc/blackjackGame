#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;

// Function to generate a random card value between 1 and 11
int getRandomCard() {
    return rand() % 11 + 1;
}

// Function to calculate the total value of a hand
int calculateHandValue(const vector<int>& hand) {
    int sum = 0;
    int numAces = 0;

    for (int card : hand) {
        if (card == 11) {
            numAces++;
        }
        sum += card;
    }

    while (sum > 21 && numAces > 0) {
        sum -= 10;
        numAces--;
    }

    return sum;
}

// Function to initialize and shuffle the deck
list<int> initializeDeck() {
    list<int> deck;
    for (int i = 1; i <= 13; ++i) {
        for (int j = 0; j < 4; ++j) {
            deck.push_back(i);
        }
    }
    srand(static_cast<unsigned int>(time(nullptr)));

    // Shuffle the deck using the shuffle function
    vector<int> deckVector(deck.begin(), deck.end());
    shuffle(deckVector.begin(), deckVector.end(), mt19937{random_device{}()});
    deck.assign(deckVector.begin(), deckVector.end());

    return deck;
}

// Function to draw a card from the deck
int drawCard(list<int>& deck) {
    if (deck.empty()) {
        cout << "Out of cards. Shuffling a new deck." << endl;
        deck = initializeDeck();
    }
    int card = deck.front();
    deck.pop_front();
    return card;
}

int main() {
    list<int> deck = initializeDeck();

    while (true) {
        vector<int> playerHand;
        vector<int> dealerHand;

        playerHand.push_back(getRandomCard());
        playerHand.push_back(getRandomCard());

        dealerHand.push_back(getRandomCard());
        dealerHand.push_back(getRandomCard());

        cout << "Welcome to Blackjack!" << endl;

        // Display player's initial hand
        cout << "Your hand: " << playerHand[0] << " " << playerHand[1] << endl;
        cout << "Dealer's face-up card: " << dealerHand[0] << endl;

        while (true) {
            int playerTotal = calculateHandValue(playerHand);

            if (playerTotal == 21) {
                cout << "Blackjack! You win!" << endl;
                break;
            } else if (playerTotal > 21) {
                cout << "Bust! You lose." << endl;
                break;
            }

            cout << "Do you want to (1) Hit or (2) Stand? ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                playerHand.push_back(getRandomCard());
                cout << "Your hand: ";
                for (int card : playerHand) {
                    cout << card << " ";
                }
                cout << endl;
            } else if (choice == 2) {
                while (calculateHandValue(dealerHand) < 17) {
                    dealerHand.push_back(getRandomCard());
                }
                cout << "Dealer's hand: ";
                for (int card : dealerHand) {
                    cout << card << " ";
                }
                cout << endl;

                int dealerTotal = calculateHandValue(dealerHand);

                if (dealerTotal > 21 || dealerTotal < playerTotal) {
                    cout << "You win!" << endl;
                } else if (dealerTotal == playerTotal) {
                    cout << "It's a tie!" << endl;
                } else {
                    cout << "You lose." << endl;
                }
                break;
            }
        }

        cout << "Do you want to play again? (y/n): ";
        char playAgain;
        cin >> playAgain;

        if (playAgain != 'y' && playAgain != 'Y') {
            break;
        }

        cout << " " << endl;

    }

    cout << "Thanks for playing! Goodbye." << endl;

    return 0;
}
