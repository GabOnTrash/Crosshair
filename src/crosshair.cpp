#include "crosshair.hpp"

Crosshair::Crosshair()
{
    if (!glfwInit())
    {
        glfwTerminate();
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    screenWidth = mode->width;
    screenHeight = mode->height;

    LoadSettings();
    InitMainWindow();
    InitMenuWindow();
}

void Crosshair::Start()
{
    while (!glfwWindowShouldClose(MainWindow))
    {
        glfwPollEvents();

        RenderCross();

        if (glfwGetKey(MainWindow, GLFW_KEY_F2) == GLFW_PRESS)
            activeMenu = true;

        (activeMenu == true && !glfwWindowShouldClose(MenuWindow)) ? RenderMenu() : glfwHideWindow(MenuWindow);
    }
    KillContext();
    glfwTerminate();
}
void Crosshair::RenderCross()
{
    glfwMakeContextCurrent(MainWindow);

    glClearColor(0, 0, 0, 0); // Trasparenza
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(windowWidth / 2.0f, windowHeight / 2.0f, 0.0f);
    glColor4fv(CurrentColor);

    // Orizzontale
    glBegin(GL_QUADS);
    glVertex2f(-crossSize / 2.0f, thickness / 2.0f);
    glVertex2f(crossSize / 2.0f, thickness / 2.0f);
    glVertex2f(crossSize / 2.0f, -thickness / 2.0f);
    glVertex2f(-crossSize / 2.0f, -thickness / 2.0f);
    glEnd();

    // Verticale
    glBegin(GL_QUADS);
    glVertex2f(-thickness / 2.0f, crossSize / 2.0f);
    glVertex2f(thickness / 2.0f, crossSize / 2.0f);
    glVertex2f(thickness / 2.0f, -crossSize / 2.0f);
    glVertex2f(-thickness / 2.0f, -crossSize / 2.0f);
    glEnd();

    glPopMatrix();

    windowWidth = static_cast<int>(crossSize);
    windowHeight = static_cast<int>(crossSize);
    glfwSetWindowSize(MainWindow, windowWidth, windowHeight);
    glfwSetWindowPos(MainWindow, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);

    glfwSwapBuffers(MainWindow);
}
void Crosshair::RenderMenu()
{
    glfwMakeContextCurrent(MenuWindow);
    glfwShowWindow(MenuWindow);

    glClearColor(0, 0, 0, 0); 
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGui::SetNextWindowSizeConstraints(ImVec2(MenuSize, MenuSize), ImVec2(MenuSize, MenuSize));
    ImGui::Begin("Crosshair Settings", nullptr, ImGuiWindowFlags_NoCollapse);

    ImGuiStyle& style = ImGui::GetStyle();
    fullWidth = ImGui::GetWindowWidth() - style.WindowPadding.x * 2;

    ImGui::Text("-- Crosshair Color --");
    ImGui::Separator();
    ImGui::SetNextItemWidth(fullWidth);
    ImGui::ColorEdit4("##color", CurrentColor, ImGuiColorEditFlags_Float);
    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    ImGui::Text("-- Crosshair Thickness --");
    ImGui::Separator();
    ImGui::SetNextItemWidth(fullWidth);
    ImGui::SliderFloat("##thickness", &thickness, 1.0f, 200.0f, "%.1f", ImGuiSliderFlags_None);
    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    ImGui::Text("-- Crosshair Size --");
    ImGui::Separator();
    ImGui::SetNextItemWidth(fullWidth);
    ImGui::SliderFloat("##size", &crossSize, 10.0f, 200.0f, "%.1f", ImGuiSliderFlags_None);
    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    if (ImGui::Button("Save and Close", ImVec2(fullWidth, 40)))
    {
        SaveSettings();
        activeMenu = false;
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(MenuWindow);
}

void Crosshair::InitMainWindow()
{
    MainWindow = glfwCreateWindow(windowWidth, windowHeight, "Crosshair", nullptr, nullptr);

    windowWidth = static_cast<int>(crossSize);
    windowHeight = static_cast<int>(crossSize);
    glfwSetWindowSize(MainWindow, windowWidth, windowHeight);
    glfwSetWindowPos(MainWindow, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);
    
    glfwMakeContextCurrent(MainWindow);
    glfwSwapInterval(1);
}
void Crosshair::InitMenuWindow()
{
    MenuWindow = glfwCreateWindow(500, 400, "Menu", nullptr, nullptr);

    glfwSetWindowSize(MenuWindow, screenWidth, screenHeight - 50);
    glfwSetWindowPos(MenuWindow, 0, 0);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(MenuWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");	// "3.3.0"

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    glfwHideWindow(MenuWindow); // Parte nascosto
    glfwMakeContextCurrent(MainWindow);
}
void Crosshair::KillContext()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(MainWindow);                                                                                          // elimina la finestra
    glfwDestroyWindow(MenuWindow);
}

void Crosshair::LoadSettings()
{
    Manager sManager("CrosshairSettings.json");

    crossSize = sManager.GetSingleKey<float>("CrossSize");
    thickness = sManager.GetSingleKey<float>("CrossThickness");
    
    CurrentColor[0] = sManager.GetKey<float>("Color", "Red");
    CurrentColor[1] = sManager.GetKey<float>("Color", "Green");
    CurrentColor[2] = sManager.GetKey<float>("Color", "Blue");
    CurrentColor[3] = sManager.GetKey<float>("Color", "Alpha");

    crossSize == 0 ? crossSize = 42.0f : crossSize = crossSize;
    thickness == 0 ? thickness = crossSize / 7 : thickness = thickness;

    CurrentColor[0] == 0.0f ? CurrentColor[0] = 0.5f : CurrentColor[0] = CurrentColor[0];
    CurrentColor[1] == 0.0f ? CurrentColor[1] = 0.0f : CurrentColor[1] = CurrentColor[1];
    CurrentColor[2] == 0.0f ? CurrentColor[2] = 0.5f : CurrentColor[2] = CurrentColor[2];
    CurrentColor[3] == 0.0f ? CurrentColor[3] = 1.0f : CurrentColor[3] = CurrentColor[3];

}
void Crosshair::SaveSettings()
{
    Manager sManager("CrosshairSettings.json");

    sManager.SetSingleKey<float>("CrossSize", crossSize);
    sManager.SetSingleKey<float>("CrossThickness", thickness);

    sManager.SetKey("Color", "Red", CurrentColor[0]);
    sManager.SetKey("Color", "Green", CurrentColor[1]);
    sManager.SetKey("Color", "Blue", CurrentColor[2]);
    sManager.SetKey("Color", "Alpha", CurrentColor[3]);

    sManager.SaveData();
}
