#pragma once
#include "../Game1/GameManager.h" // GameLogic 경로에 맞게 조정
#include "../Game1/BattleManager.h"
//#include <vcclr.h>

using namespace System;
using namespace System::Collections::Generic;

public delegate void ShowImagesCallback(List<List<String^>^>^ paths, int playerCurrentHp, int playerMaxHp, int computerCurrentHp, int computerMaxHp, String^ sound_path);
public delegate void ShowAvailableCardsCallback(List<String^>^ availableCardNames);

namespace CppCliWrapper {
	public ref class Wrapper {
	private:
		GameManager* gameManager;
		static ShowImagesCallback^ imageCallback;
		static ShowAvailableCardsCallback^ availableCardsCallback;
	public:
		Wrapper();
		~Wrapper();
		void StartGame();
		void EndGame();
		void SelectCharacter(int characterId);
		void ExitGame();

		static void RegisterImageCallback(ShowImagesCallback^ cb);
		static void RegisterAvailableCardsCallback(ShowAvailableCardsCallback^ cb);
		static void CallManagedShowImages(
			const std::vector<std::vector<std::string>>& paths,
			int playerCurrentHp,
			int playerMaxHp,
			int computerCurrentHp,
			int computerMaxHp,
			System::String^ sound_path
		);
		static void CallManagedShowAvailableCards(const std::vector<std::string>& availableCardNames);
	};
}