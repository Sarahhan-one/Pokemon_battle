#include "pch.h"

#include "Wrapper.h"
#include "../Game1/GameManager.h"
#include "../Game1/BattleManager.h"

using namespace CppCliWrapper;
using namespace System::Runtime::InteropServices;


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

// ShowImagesCallback^ Wrapper::imageCallback = nullptr;

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

void CppCliWrapper::Wrapper::RegisterImageCallback(ShowImagesCallback^ cb)
{
    imageCallback = cb;
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