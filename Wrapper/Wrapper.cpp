#include "pch.h"

#include "Wrapper.h"

CppCliWrapper::Wrapper::Wrapper() {
	gameManager = new GameManager();
}

CppCliWrapper::Wrapper::~Wrapper() {
	delete gameManager;
}

void CppCliWrapper::Wrapper::StartGame() {
	gameManager->main();
}

void CppCliWrapper::Wrapper::EndGame() {
	gameManager->exitGame();
}