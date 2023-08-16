//
// Created by LENOVO on 7/21/2023.
//

#include "MainMenu.h"

MainMenu::MainMenu(vector<string> &projects) : projects(projects) {
    font.loadFromFile("../resources/fonts/JetBrains_Mono/JetBrainsMono-VariableFont_wght.ttf");

}

void MainMenu::drawSidebar(RenderWindow &window, Event &event) {
    Texture sideBarTexture; sideBarTexture.loadFromFile("../resources/blocks/SideBar.png");
    Sprite sideBar; sideBar.setTexture(sideBarTexture);
    sideBar.setPosition(23, 26);

    Text projectPage; projectPage.setString("Projects");
    projectPage.setFont(font); projectPage.setCharacterSize(22);
    projectPage.setPosition(60, 220);

    Text settingPage; settingPage.setString("Settings");
    settingPage.setFont(font); settingPage.setCharacterSize(22);
    settingPage.setPosition(60, 280);

    window.draw(sideBar);
    window.draw(projectPage);
    window.draw(settingPage);
}

void MainMenu::drawProjectList(sf::RenderWindow &window, sf::Event &event, int &mode, int &projectNum) {
    for(int i = 0; i < projects.size(); i++){
        Texture rrectTexture; rrectTexture.loadFromFile("../resources/blocks/ProjectBox.png");
        Sprite projectBox; projectBox.setTexture(rrectTexture);
        projectBox.setPosition(330, 221 + i * 150);
        Text projectName; projectName.setString(projects[i]);
        projectName.setFont(font); projectName.setCharacterSize(22);
        projectName.setPosition(385, 264 + i * 150);

        if(projectBox.getGlobalBounds().contains(static_cast<Vector2f>(Mouse::getPosition(window)))){
            if(event.type == Event::MouseButtonPressed) {
                mode = 1;
                projectNum = i;
            }
            rrectTexture.loadFromFile("../resources/blocks/ProjectBox_selected.png");
            projectBox.setTexture(rrectTexture);
        }

        window.draw(projectBox);
        window.draw(projectName);
    }
}

void MainMenu::render(RenderWindow &window, Event &event, int &mode, int &projectNum) {

    drawSidebar(window, event);
    drawProjectList(window, event, mode, projectNum);
}