#pragma once

#include "includes.hpp"

class Manager
{
public:

    Manager();
    Manager(const std::string& filePath);

    void LoadData();
    void SaveData() const;

    template<typename T>
    T GetKey(const std::string& container, const std::string& type) const
    {
        if (settings.contains(container) && settings[container].contains(type))
        {
            return settings[container].at(type).get<T>();
        }
        return T{};  
    }
    
    template<typename T>
    T GetSingleKey(const std::string& type) const
    {
        if (settings.contains(type))
        {
            return settings.at(type).get<T>();
        }
        return T{};
    }

    template<typename T>
    void SetKey(const std::string& container, const std::string& type, T value)
    {
        settings[container][type] = value;
    }
    
    template<typename T>
    void SetSingleKey(const std::string& type, T value)
    {
        settings[type] = value;
    }

    void DeleteKey(const std::string& type);

private:

    std::string GetFullPath(const std::string& fileName);

    std::string path;
    nlohmann::json settings;
};