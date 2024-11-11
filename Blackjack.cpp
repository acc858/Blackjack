#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;
using std::rand;
using std::time;
using std::srand;

class Deck {
public:
    // Enum to represent all cards with their values
    enum Card {
        Ace_of_Spades = 11, Ace_of_Clubs = 11, Ace_of_Hearts = 11, Ace_of_Diamonds = 11,
        King_of_Spades = 10, King_of_Clubs = 10, King_of_Hearts = 10, King_of_Diamonds = 10,
        Queen_of_Spades = 10, Queen_of_Clubs = 10, Queen_of_Hearts = 10, Queen_of_Diamonds = 10,
        Jack_of_Spades = 10, Jack_of_Clubs = 10, Jack_of_Hearts = 10, Jack_of_Diamonds = 10,
        Ten_of_Spades = 10, Ten_of_Clubs = 10, Ten_of_Hearts = 10, Ten_of_Diamonds = 10,
        Nine_of_Spades = 9, Nine_of_Clubs = 9, Nine_of_Hearts = 9, Nine_of_Diamonds = 9,
        Eight_of_Spades = 8, Eight_of_Clubs = 8, Eight_of_Hearts = 8, Eight_of_Diamonds = 8,
        Seven_of_Spades = 7, Seven_of_Clubs = 7, Seven_of_Hearts = 7, Seven_of_Diamonds = 7,
        Six_of_Spades = 6, Six_of_Clubs = 6, Six_of_Hearts = 6, Six_of_Diamonds = 6,
        Five_of_Spades = 5, Five_of_Clubs = 5, Five_of_Hearts = 5, Five_of_Diamonds = 5,
        Four_of_Spades = 4, Four_of_Clubs = 4, Four_of_Hearts = 4, Four_of_Diamonds = 4,
        Three_of_Spades = 3, Three_of_Clubs = 3, Three_of_Hearts = 3, Three_of_Diamonds = 3,
        Two_of_Spades = 2, Two_of_Clubs = 2, Two_of_Hearts = 2, Two_of_Diamonds = 2
    };

    // Store the deck in an array
    Card deck[52] = {
        Ace_of_Spades, Ace_of_Clubs, Ace_of_Hearts, Ace_of_Diamonds,
        King_of_Spades, King_of_Clubs, King_of_Hearts, King_of_Diamonds,
        Queen_of_Spades, Queen_of_Clubs, Queen_of_Hearts, Queen_of_Diamonds,
        Jack_of_Spades, Jack_of_Clubs, Jack_of_Hearts, Jack_of_Diamonds,
        Ten_of_Spades, Ten_of_Clubs, Ten_of_Hearts, Ten_of_Diamonds,
        Nine_of_Spades, Nine_of_Clubs, Nine_of_Hearts, Nine_of_Diamonds,
        Eight_of_Spades, Eight_of_Clubs, Eight_of_Hearts, Eight_of_Diamonds,
        Seven_of_Spades, Seven_of_Clubs, Seven_of_Hearts, Seven_of_Diamonds,
        Six_of_Spades, Six_of_Clubs, Six_of_Hearts, Six_of_Diamonds,
        Five_of_Spades, Five_of_Clubs, Five_of_Hearts, Five_of_Diamonds,
        Four_of_Spades, Four_of_Clubs, Four_of_Hearts, Four_of_Diamonds,
        Three_of_Spades, Three_of_Clubs, Three_of_Hearts, Three_of_Diamonds,
        Two_of_Spades, Two_of_Clubs, Two_of_Hearts, Two_of_Diamonds
    };

    unordered_map<int, bool> dealtCards;  // Track dealt cards

    Deck() {
        srand(time(0));  // Seed for random number generator
    }

    // Deal a card that hasn't been dealt yet
    Card deal() {
        int position;
        do {
            position = rand() % 52;  // Generate random card index
        } while (dealtCards[position]);  // Re-deal if the card was already dealt

        dealtCards[position] = true;  // Mark card as dealt
        return deck[position];
    }

    // Get the integer value of a card
    static int getCardValue(Card card) {
        return static_cast<int>(card);
    }


// Function to compute the total score (handle ace as 1 or 11)
int computeScore(const vector<int>& hand) {
    int total = 0;
    int aces = 0;

    for (int value : hand) {
        total += value;
        if (value == 11) aces++;
    }

    // Adjust ace values if total is greater than 21
    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }

    return total;
}

void play_blackjack() {
    //Initialize variables for use across loops
    char play_again; 
    int dealed = 0;
    int pwins = 0; 
    int hwins = 0;
    do  {
    // Initialize vectors to contain the cards of the dealer and player
    vector<int> playerHand;
    vector<int> dealerHand;
    // Dealer the player and dealer 2 cards
    playerHand.push_back(getCardValue(deal())); 
    playerHand.push_back(getCardValue(deal()));
    dealerHand.push_back(getCardValue(deal()));
    dealerHand.push_back(getCardValue(deal()));
    dealed = dealed + 4; //Incriment the amount of dealed cards by 4

    cout << "Your hand: " << playerHand[0] << ", " << playerHand[1] << endl;
    cout << "Dealer shows: " << dealerHand[0] << endl;
    int game;
    char choice;
    int loop;
    while (true) {
        play_again = 'a';
        int playerScore = computeScore(playerHand);
        // If your score is 21 then break the loop because why would you hit
        if (playerScore == 21) { 
            cout << "You have blackjack!" << endl;
            break;
            
        }
        // you can't hit if you already busted
        else if (playerScore > 21) {
            cout << "You bust! Score: " << playerScore << endl;
            break;
        }

        cout << "Your score: " << playerScore << ". Hit (h) or stand (s)? ";
        cin >> choice;
        // Either hit or stand 
        if (choice == 'h') {
            playerHand.push_back(getCardValue(deal()));
            cout << "You drew a " << playerHand.back() << endl;
            dealed++;
        } else if (choice == 's') {
           break;
        } else {
            cout << "Invalid choice! Please enter 'h' or 's'." << endl;
        }
        
    }

    // Dealer's turn: reveal their hidden card
    
    cout << "Dealer's turn..." << endl;
    cout << "Dealer's hole card is " << dealerHand[1] << endl;
    while (computeScore(dealerHand) < 17 && computeScore(dealerHand) < computeScore(playerHand)) {
        dealerHand.push_back(getCardValue(deal()));
        dealed++;
        cout << "Dealer drew a " << dealerHand.back() << endl;
    }
    
    
    int playerScore = computeScore(playerHand);
    int dealerScore = computeScore(dealerHand);
    

    cout << "Your score: " << playerScore << ", Dealer's score: " << dealerScore << endl;
    
    // Determine winner
    
    if (playerScore > 21) {
        cout << "You busted, dealer wins!" << endl;
        hwins++;
    }
    else if (dealerScore > 21) {
        cout << "Dealer busts, you win!" << endl;
        pwins++;
    } 
    else if (dealerScore == 21 && playerScore != 21) {
        cout << "Dealer has blackjack!" << endl;
        hwins++;
    }
    else if (playerScore > dealerScore) {
        cout << "You win!" << endl;
        pwins++;
    }
    else if (playerScore < dealerScore) {
        cout << "Dealer wins!" << endl;
        hwins++;
    } else {
        cout << "It's a push!" << endl;
    }
    if (dealed > 42) {
        cout << "Your wins: " << pwins << ", House wins: " << hwins << endl;
        cout << "Thanks for playing!" << endl;
        break;
    }
    //Ask the player if they would like to play again
    while (play_again != 'y' && play_again != 'n') {
            cout << "Please enter 'y' or 'n': ";
            cin >> play_again;
        }
    
    } 
    // Only play while there is enough cards to play a hypothetical worse case scenario
    while (dealed <= 42 && play_again == 'y');
}

};

// Play the game
int main() {
    Deck play;
    play.play_blackjack();


    return 0;
}