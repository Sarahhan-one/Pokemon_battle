#include "GameManager.h"
#include "Tools.h"

void GameManager::init()
{
    gameState_ = GameState::MENU; 
    stageNumber_ = 1; 
    battleManager_.init();
}

void GameManager::menu()
{
    std::cout << "===== 게임 메뉴 =====\n";
    std::cout << "1. 전투 시작\n";
    std::cout << "2. 게임 종료\n";
    std::cout << "번호를 선택하세요: ";

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
        std::cout << "잘못된 입력입니다.\n";
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
        battleManager_.printMap();
        //battle loop logic
        battleManager_.selectCardsForStage();
        battleManager_.executeCurrentCard();
        if (battleManager_.getIsBattleEnd()) {
            endBattle();
        }
        (void)_getch();
        system("cls");
        break;

    case GameState::EXIT:
        std::cout << "게임을 종료합니다.\n";
        exit(0);  // 프로그램 종료
        break;
    }
}

void GameManager::endBattle()
{
    std::cout << "전투가 종료되었습니다.\n";
}

void skill1() {}
void skill2() {}
void skill3() {}
void skill4() {}

void GameManager::selectCharacter()
{
    std::cout << "캐릭터를 선택하세요.\n";
    std::cout << "1. Pikachu \n";

    int choice; 
    std::cin >> choice; 


    void(*skills[4])(void) = { skill1, skill2, skill3, skill4 };


    Pokemon pokemon;
    if (choice == 1) {
        Pokemon pokemon;
        pokemon.setPos(Position(0, 5));
    }
    
    // assign to the player
    battleManager_.setHumanUnit(pokemon);

    // assign a random unit to the opponent
    Pokemon opponent;
    opponent.setPos(Position(9, 5));
    battleManager_.setComputerUnit(opponent);
}
