#pragma once
#include "../Game1/GameManager.h" // GameLogic 경로에 맞게 조정
#include "../Game1/BattleManager.h"
//#include <vcclr.h>

using namespace System;
using namespace System::Collections::Generic;

public delegate void ShowImagesCallback(List<List<String^>^>^ paths);

namespace CppCliWrapper {
	public ref class Wrapper {
	private:
		GameManager* gameManager;
		static ShowImagesCallback^ imageCallback;
	public:
		Wrapper();
		~Wrapper();
		void StartGame();
		void EndGame();

		static void RegisterImageCallback(ShowImagesCallback^ cb);
		static void CallManagedShowImages(const std::vector<std::vector<std::string>>& paths);
	};
}