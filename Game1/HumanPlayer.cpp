#include "HumanPlayer.h"

vector<int> HumanPlayer::selectCardsForStage()
{
    cout << "<Card List>\n";

    vector<Card> cards = pokemon_->getCards();
    for (int i = 0; i < cards.size(); i++) {
        cout << "Card " << i << ": " << cards[i].getName() << '\n';
    }

    cout << "Select three different cards !!\n";

    vector<int> selectedCardInds;
    while (selectedCardInds.size() < 3) {
        int in;
        cin >> in;
        if (in < 0 || in >= cards.size()) {
            cout << "Invalid card index !!!\n";
            continue;
        }
        if (find(selectedCardInds.begin(), selectedCardInds.end(), in) != selectedCardInds.end()) {
            cout << "You already selected this card. Choose another one!\n";
            continue;
        }
        selectedCardInds.push_back(in);
    }

    return selectedCardInds;
}

vector<Position> HumanPlayer::executeCard(vector<vector<Pokemon*>> map, int cardInd)
{
	Card card = pokemon_->getCards()[cardInd];
	return card.executeCard(map);
}

