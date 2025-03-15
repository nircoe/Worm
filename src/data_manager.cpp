#include "data_management/data_manager.hpp"

void DataManager::init(GameManager& gameManager, const std::string filename)
{
    m_filename = filename;
    if(!load())
    {
        // can't load, needs to ask the user for a nickname and create new GameData
        gameManager.newGame();
    }
}

void DataManager::newGame(std::string nickname)
{
    m_gamedata = GameData(nickname);
}

bool DataManager::load()
{
    std::optional<GameData> loadedGameData = DataReaderWriter::readData(m_filename);
    bool readDataSucceed = loadedGameData.has_value();
    if(readDataSucceed)
        m_gamedata = loadedGameData.value();
    return readDataSucceed;
}

bool DataManager::save()
{
    if(m_gamedata.getNickName().empty())
        return true; // no need to save (guest mode)

    return DataReaderWriter::writeData(m_gamedata, m_filename);
}

void DataManager::setNickName(std::string nickname)
{
    m_gamedata.setNickName(nickname);
}

void DataManager::setHighScore(Enums::Difficulty difficulty, int highscore)
{
    int index = difficulty == Enums::Difficulty::Easy ? 0 :
                difficulty == Enums::Difficulty::Medium ? 1 :
                difficulty == Enums::Difficulty::Hard ? 2 : 3;
    m_gamedata.setHighScore(index, highscore);
}

GameData DataManager::getGameData() const
{
    return m_gamedata;
}
