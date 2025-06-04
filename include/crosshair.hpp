#pragma once

#include "includes.hpp"
#include "SettingsMan.hpp"

class Crosshair
{
public:

    Crosshair();
    void Start();

private:

    void RenderCross();
    void RenderMenu();
    void InitMenuWindow();
    void InitMainWindow();
    void KillContext();
    void LoadSettings();
    void SaveSettings();

    bool activeMenu = false;

    float crossSize = 42.0f;
    float thickness = crossSize / 7;
    float MenuSize =  250.0f;
    float fullWidth = 500.0f;

    int windowWidth = static_cast<int>(crossSize);
    int windowHeight = static_cast<int>(crossSize);
    int screenWidth;
    int screenHeight;

    float CurrentColor[4] = { 0.5f, 0.0f, 0.5f, 1.0f }; 

    GLFWwindow* MainWindow;
    GLFWwindow* MenuWindow;
    const GLFWvidmode* mode;
};