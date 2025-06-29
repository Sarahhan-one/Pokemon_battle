#include "GameManager.h"
#include "Tools.h"

void GameManager::init()
{
}

void GameManager::menu()
{
    std::cout << "===== 게임 메뉴 =====\n";
    std::cout << "1. 전투 시작\n";
    std::cout << "2. 게임 종료\n";
    std::cout << "번호를 선택하세요: ";

    int input = 0;
    cin >> input;

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
}

void GameManager::selectCharacter()
{
}
