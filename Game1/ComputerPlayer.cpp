#include "ComputerPlayer.h"

vector<int> ComputerPlayer::selectCardsForStage()
{
	vector<int> selectedCardInds(3, 0);

    random_device rd;                           // seed generator
    mt19937 gen(rd());                          // Mersenne Twister Engine
    uniform_int_distribution<int> dist(0, pokemon_->getCards().size() - 1); // 0부터 max card ind 까지 랜덤
    

    for (int i = 0; i < 3; ++i) {
        int randomNumber = dist(gen);
        
        selectedCardInds[i] = randomNumber;
    }

    return selectedCardInds;
}

vector<Position> ComputerPlayer::executeCard(vector<vector<Pokemon*>>& map, int cardInd)
{
    Card card = pokemon_->getCards()[cardInd];
    return card.executeCard(map);
}