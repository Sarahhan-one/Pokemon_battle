#include "pch.h"

#include "Wrapper.h"
#include "../Game1/GameManager.h"
#include "../Game1/BattleManager.h"
#include <mutex>
#include <condition_variable>

using namespace CppCliWrapper;
using namespace System::Runtime::InteropServices;

// Add these globals to handle card selection synchronization
std::mutex cardSelectionMutex;
std::condition_variable cardSelectionCV;
bool cardsSelected = false;
std::vector<int> selectedCardIndices;

void CallDrawWpfMapFromNative(
    const std::vector<std::vector<std::string>>& paths,
    int playerCurrentHp,
    int playerMaxHp,
    int computerCurrentHp,
    int computerMaxHp,
    std::string sound_path)
{
    System::String^ managedSoundPath = gcnew System::String(sound_path.c_str());
        CppCliWrapper::Wrapper::CallManagedShowImages(
        paths,
        playerCurrentHp,
        playerMaxHp,
        computerCurrentHp,
        computerMaxHp, 
        managedSoundPath);
}
void CallShowAvailableCardsFromNative(const std::vector<std::string>& availableCardNames)
{
    CppCliWrapper::Wrapper::CallManagedShowAvailableCards(availableCardNames);
}

// Added function to receive card selections from native code
std::vector<int> WaitForCardSelections(int numCards)
{
    std::unique_lock<std::mutex> lock(cardSelectionMutex);
    cardsSelected = false;
    
    // Wait until the UI thread signals that cards have been selected
    cardSelectionCV.wait(lock, [] { return cardsSelected; });
    
    // Return a copy of the selected indices
    std::vector<int> result = selectedCardIndices;
    selectedCardIndices.clear();
    return result;
}

// ShowImagesCallback^ Wrapper::imageCallback = nullptr;

CppCliWrapper::Wrapper::Wrapper() {
	gameManager = new GameManager();
}

CppCliWrapper::Wrapper::~Wrapper() {
	delete gameManager;
}

void CppCliWrapper::Wrapper::StartGame() {
    gameManager->init();
}

void CppCliWrapper::Wrapper::EndGame() {
	gameManager->exitGame();
}

void CppCliWrapper::Wrapper::RegisterImageCallback(ShowImagesCallback^ cb)
{
    imageCallback = cb;
}
void CppCliWrapper::Wrapper::RegisterAvailableCardsCallback(ShowAvailableCardsCallback^ cb) {
    availableCardsCallback = cb;
}

// Add a new method to register the card selection callback
void CppCliWrapper::Wrapper::RegisterCardSelectionCallback(CardSelectionCallback^ cb)
{
    cardSelectionCallback = cb;
}

// Add a method to submit card selections from C# to C++
void CppCliWrapper::Wrapper::SubmitCardSelections(List<int>^ selectedCards)
{
    std::unique_lock<std::mutex> lock(cardSelectionMutex);
    
    // Convert managed List to native vector
    selectedCardIndices.clear();
    for (int i = 0; i < selectedCards->Count; i++)
    {
        selectedCardIndices.push_back(selectedCards[i]);
    }
    
    // Signal that cards have been selected
    cardsSelected = true;
    cardSelectionCV.notify_one();
}

void CppCliWrapper::Wrapper::CallManagedShowImages(
    const std::vector<std::vector<std::string>>& paths,
    int playerCurrentHp,
    int playerMaxHp,
    int computerCurrentHp,
    int computerMaxHp,
    System::String^ sound_path
)
{
    if (imageCallback == nullptr) return;

    auto managedList = gcnew List<List<String^>^>();
    for (const auto& row : paths)
    {
        auto managedRow = gcnew List<String^>();
        for (const auto& s : row)
            managedRow->Add(gcnew String(s.c_str()));
        managedList->Add(managedRow);
    }

    imageCallback(
        managedList,
        playerCurrentHp,
        playerMaxHp,
        computerCurrentHp,
        computerMaxHp,
        sound_path);
}
void Wrapper::CallManagedShowAvailableCards(const vector<string>& availableCardNames) {
    if (availableCardsCallback == nullptr) return;

    auto managedAvailableCardList = gcnew List<String^>();
    for (const auto& s : availableCardNames) {
        managedAvailableCardList->Add(gcnew String(s.c_str()));
    }

    availableCardsCallback(managedAvailableCardList);
}

void Wrapper::SelectCharacter(int characterId) {
    gameManager->SelectCharacterProgrammatically(characterId);
    gameManager->update();
}

void Wrapper::ExitGame() {
    gameManager->exitGame();
}