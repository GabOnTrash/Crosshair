#include "SettingsMan.hpp"

Manager::Manager() {}
Manager::Manager(const std::string& filePath)
{
    this->path = GetFullPath(filePath);

    LoadData();
}

std::string Manager::GetFullPath(const std::string& fileName)
{
    char* buffer = nullptr;
    size_t size = 0;

    if (_dupenv_s(&buffer, &size, "USERPROFILE") != 0 || buffer == nullptr)
    {
        std::cerr << "Error trying to get USERPROFILE";
        return {};
    }

    std::filesystem::path userPath(buffer);
    free(buffer);

    std::filesystem::path fullPath = userPath / fileName;

    return fullPath.string();
}
void Manager::LoadData()
{
    std::ifstream file(path);

    if (file.is_open())
    {
        try
        {
            file >> settings;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Errore nel parsing del file JSON: " << e.what() << std::endl;
            settings = nlohmann::json::object();  
        }
    }
    else
    {
        std::cerr << "File di impostazioni non trovato. Verrà creato uno nuovo." << std::endl;
        settings = nlohmann::json::object();
    }
}
void Manager::SaveData() const
{
    std::ofstream file(path);

    if (file.is_open())
    {
        file << settings.dump(4); 
    }
    else
    {
        std::cerr << "Errore nel salvataggio delle impostazioni." << std::endl;
    }
}
void Manager::DeleteKey(const std::string& section)
{
    if (settings.contains(section)) settings.erase(section);
}