#include "HumanPlayer.h"

extern std::vector<int> WaitForCardSelections(int numCards);

vector<int> HumanPlayer::selectCardsForStage()
{
    cout << "<Card List>\n";

    vector<Card> cards = pokemon_->getCards();
    for (int i = 0; i < cards.size(); i++) {
        cout << "Card " << i << ": " << cards[i].getName() << '\n';
    }

    cout << "Select three different cards using WPF interface...\n";

    // Wait for card selections from WPF instead of reading from console
    return WaitForCardSelections(3);
}

vector<Position> HumanPlayer::executeCard(vector<vector<Pokemon*>>& map, int cardInd)
{
    Card card = pokemon_->getCards()[cardInd];
    return card.executeCard(map);
}

