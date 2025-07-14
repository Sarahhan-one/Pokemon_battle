#pragma once

#include <vector>
#include <string>

#define __RPC_unique_pointer
#include <servprov.h>
#undef __RPC_unique_pointer

using namespace System;
using namespace System::Collections::Generic;
using namespace std;

class GameManager;

namespace CppCliWrapper {
    public delegate void ShowImagesCallback(
        List<List<String^>^>^ paths, 
        int playerCurrentHp, 
        int playerMaxHp, 
        int computerCurrentHp, 
        int computerMaxHp,
        String^ sound_path);
    public delegate void ShowAvailableCardsCallback(List<String^>^ availableCardNames);
    public delegate void CardSelectionCallback(); // New delegate for card selection

    public ref class Wrapper
    {
    private:
        GameManager* gameManager;
        static ShowImagesCallback^ imageCallback;
        static ShowAvailableCardsCallback^ availableCardsCallback;
        static CardSelectionCallback^ cardSelectionCallback; // New callback

    public:
        Wrapper();
        ~Wrapper();

        void StartGame();
        void EndGame();
        void SelectCharacter(int characterId);
        void ExitGame();
        
        static void RegisterImageCallback(ShowImagesCallback^ cb);
        static void RegisterAvailableCardsCallback(ShowAvailableCardsCallback^ cb);
        static void RegisterCardSelectionCallback(CardSelectionCallback^ cb); // New registration method
        
        static void CallManagedShowImages(
            const vector<vector<string>>& paths,
            int playerCurrentHp,
            int playerMaxHp,
            int computerCurrentHp,
            int computerMaxHp,
            String^ sound_path);
        static void CallManagedShowAvailableCards(const vector<string>& availableCardNames);
        
        static void SubmitCardSelections(List<int>^ selectedCards); 
    };
}

// Add function declaration for native code
std::vector<int> WaitForCardSelections(int numCards);