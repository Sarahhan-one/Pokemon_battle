#pragma once
#include "../Game1/GameManager.h" // GameLogic 경로에 맞게 조정

using namespace System;

namespace CppCliWrapper {
	public ref class Wrapper {
	private:
		GameManager* gameManager;
	public:
		Wrapper();
		~Wrapper();
		void StartGame();
		void EndGame();
	};
}