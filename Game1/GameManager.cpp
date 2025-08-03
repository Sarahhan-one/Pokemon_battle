#include "GameManager.h"
#include "Pokemon/Pikachu.h"
#include "Pokemon/Kkobugi.h"
#include "Pokemon/Pairi.h"
#include "Pokemon/Naong.h"
#include "Pokemon/Majayong.h"
#include "Pokemon/Ttodogas.h"
#include "Tools.h"
#include <thread>

void GameManager::init()
{
    gameState_ = GameState::MENU;
    stageNumber_ = 1;
    battleManager_.init();
}

void GameManager::menu()
{
    std::cout << "===== Game Menu =====\n";
    std::cout << "1. Battle Starts\n";
    std::cout << "2. End the Game\n";
    std::cout << "Select the number: ";

    int input = 0;
    std::cin >> input;

    switch (input) {
    case 1:
        gameState_ = GameState::BATTLE;
        selectCharacter();
        startBattle();
        system("cls");
        break;
    case 2:
        gameState_ = GameState::EXIT;
        break;
    default:
        std::cout << "Not a valid input.\n";
        break;
    }
}

void GameManager::startBattle()
{
    battleManager_.init();
}

void GameManager::update()
{
    switch (gameState_) {
    case GameState::MENU:
        system("cls");
        menu();
        break;

    case GameState::BATTLE:
        std::cout << "Battle Starts!!\n";
        Sleep(1000);
        battleManager_.executeBattle();
        if (battleManager_.getLastResult() == BattleResult::COMPUTER_WIN) {
            std::cout << "Game Over! You lost.\n";
            Sleep(2000);
            gameState_ = GameState::MENU;
        }
        else if (battleManager_.getLastResult() == BattleResult::PLAYER_WIN) {
            stageNumber_++; // Advance to next stage
            if (stageNumber_ == 3) { // FINAL WIN
                std::cout << "You Won all the stages!!! Congrats!!! \n";
                Sleep(2000);
                gameState_ = GameState::MENU;

            }
            else { // WIN PER STAGE
                std::cout << "You Won! Proceeding to next stage... \n";
                Sleep(2000);

                // Restore HP and reset map for next stage
                // Player's Pokemon stays, only opponent changes
                Pokemon& playerPokemon = battleManager_.getHumanPlayer()->getPokemon();
                playerPokemon.setPos(Position(1, 0));

                //while (playerPokemon.getHp() < playerPokemon.getMaxHp()) {
                //    playerPokemon.takeDamage(-1); // Heal by 1 until full
                //}

                Pokemon* nextOpponent = createOpponentForStage(stageNumber_);
                nextOpponent->setPos(Position(1, 3));
                battleManager_.setComputerPokemon(nextOpponent);

                battleManager_.init();
                gameState_ = GameState::BATTLE;
                return;
            }
        }
        break;

    case GameState::EXIT:
        std::cout << "End the Game.\n";
        Sleep(2000);
        exit(0);
        break;
    }
}

void GameManager::selectCharacter()
{
    Pokemon* playerPokemon = nullptr;
    Pokemon* opponentPokemon = new Naong(Position(1, 3));

    unsigned int choice = 3;
    while (choice > 2) {

        system("cls");
        cout << "Select you character.\n";
        cout << "\
0. Pikachu\n\
1. Kkobugi\n\
2. Pairi\n";
        cin >> choice;

        Position playerStPos = Position(1, 0);

        switch (choice) {
        case 0:
            playerPokemon = new Pikachu(playerStPos);
            break;
        case 1:
            playerPokemon = new Kkobugi(playerStPos);
            break;
        case 2:
            playerPokemon = new Pairi(playerStPos);
            break;
        default:
            system("cls");
            cout << "Not a valid input.\n";
            Sleep(2000);
            break;
        }
    }

    string name = typeid(*playerPokemon).name();
    cout << "\nSelected Pokemon : " << name << endl;
    Sleep(1000);

    battleManager_.setHumanPokemon(playerPokemon);
    battleManager_.setComputerPokemon(opponentPokemon);
}

Pokemon* GameManager::createOpponentForStage(int stage) {
    Position OpponentStPos = Position(1, 3);
    switch (stage) {
    case 1:
        return new Majayong(OpponentStPos);
    case 2:
        return new Ttodogas(OpponentStPos);
    default:
        return new Naong(OpponentStPos); // Fallback to ensure there's always an opponent
    }
}

void GameManager::main()
{
    GameManager gameManager;

    //cout << "계속하려면 아무 키나 누르세요...";
    //(void)_getch();

    while (true) {
        gameManager.update();
    }
}

void GameManager::exitGame()
{
    exit(0);
}

void GameManager::SelectCharacterProgrammatically(int characterId)
{
    Pokemon* playerPokemon = nullptr;
    Pokemon* opponentPokemon = new Naong(Position(1, 3));
    Position playerStPos = Position(1, 0);

    // Select character based on ID passed from WPF
    switch (characterId) {
    case 0:
        playerPokemon = new Pikachu(playerStPos);
        break;
    case 1:
        playerPokemon = new Kkobugi(playerStPos);
        break;
    case 2:
        playerPokemon = new Pairi(playerStPos);
        break;
    default:
        playerPokemon = new Pikachu(playerStPos); // Default to Pikachu
        break;
    }

    // Set the selected Pokemon
    battleManager_.setHumanPokemon(playerPokemon);
    battleManager_.setComputerPokemon(opponentPokemon);

    // Set up for battle
    gameState_ = GameState::BATTLE;
    startBattle();

    // This loop will continue until all stages are complete or player loses
    while (gameState_ == GameState::BATTLE) {
        // Execute battle for current stage
        battleManager_.executeBattle();

        // Process battle results
        if (battleManager_.getLastResult() == BattleResult::COMPUTER_WIN) {
            std::cout << "Game Over! You lost.\n";
            Sleep(2000);
            gameState_ = GameState::MENU;
            break; // Exit the loop to return to menu
        }
        else if (battleManager_.getLastResult() == BattleResult::PLAYER_WIN) {
            stageNumber_++; // Advance to next stage
            if (stageNumber_ > 2) { // FINAL WIN
                std::cout << "You Won all the stages!!! Congrats!!! \n";
                Sleep(2000);
                gameState_ = GameState::MENU;
                break; // Exit the loop to return to menu
            }
            else { // WIN PER STAGE
                std::cout << "You Won! Proceeding to next stage... \n";
                Sleep(2000);

                // Prepare for next stage
                Pokemon& playerPokemon = battleManager_.getHumanPlayer()->getPokemon();
                playerPokemon.setPos(Position(1, 0));

                Pokemon* nextOpponent = createOpponentForStage(stageNumber_);
                nextOpponent->setPos(Position(1, 3));
                battleManager_.setComputerPokemon(nextOpponent);

                battleManager_.init();
                // Continue to next iteration of the loop
            }
        }
    }
    
    // Reset stage number when returning to menu
    if (gameState_ == GameState::MENU) {
        stageNumber_ = 1;
    }
}