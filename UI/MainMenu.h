//
// Created by LENOVO on 7/21/2023.
//

#ifndef NEURALVISUALIZER_MAINMENU_H
#define NEURALVISUALIZER_MAINMENU_H
#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

using namespace sf;
using namespace std;

class MainMenu {
public:
    Font font;
    vector<string> projects;

    explicit MainMenu(vector<string> &projects);

    void drawSidebar(RenderWindow &window, Event &event);
    void drawProjectList(RenderWindow &window, Event &event, int &mode, int &projectNum);
    void render(RenderWindow &window, Event &event, int &mode, int &projectNum);
};


#endif //NEURALVISUALIZER_MAINMENU_H
