#include "HumanPlayer.h"

vector<int> HumanPlayer::selectCardsForStage()
{
	cout << "<Card List>\n";

	vector<Card> cards = pokemon_->getCards();
	for (int i = 0; i < cards.size(); i++) {
		cout << "Card "<< i << ": " << cards[i].getName() << '\n';
	}
	

	cout << "Select three cards !!\n";

	int in;
	vector<int> selectedCardInds(3, 0);

	for (int i = 0; i < 3; i++) {
		cin >> in;
		if (in < 0 && in >= cards.size()) {
			cout << "Invalid card index !!!\n";
			i -= 1;
			continue;
		}
		selectedCardInds[i] = in;
	}
	
	return selectedCardInds;
}

void HumanPlayer::executeCard(vector<vector<Pokemon*>> map, int cardInd)
{
	Card card = pokemon_->getCards()[cardInd];
	cout << "Player Use Card \"" << card.getName() << "\"" << endl;
	card.executeCard(map);
}

