#pragma once
//
// Created by LENOVO on 7/21/2023.
//

#ifndef NEURALVISUALIZER_PROJECTPAGE_H
#define NEURALVISUALIZER_PROJECTPAGE_H
#include "SFML/Graphics.hpp"
#include "TextBox.h"
#include <vector>
#include <string>
using namespace sf;
using namespace std;


class ProjectPage {
public:
    Font font;
    TextBox numNodesText;
    TextBox learningRateText;
    TextBox epochsText;
    int timeDelay = 0;
    Text errorMessage;

    vector<int> nodesPerLayer;

    ProjectPage() {
        font.loadFromFile("../resources/fonts/JetBrains_Mono/JetBrainsMono-VariableFont_wght.ttf");
        errorMessage.setFont(font);
        errorMessage.setString("");
        errorMessage.setCharacterSize(18);
        nodesPerLayer.push_back(32);
        nodesPerLayer.push_back(32);
    }

    void drawTrainingConfig(RenderWindow &window, Event &event);
    void drawHeader(RenderWindow &window, Event &event, int &mode, string projectName);
    void drawNetwork(RenderWindow &window, Event &event);
    void render(RenderWindow &window, Event &event, int &mode, string projectName);
};


#endif //NEURALVISUALIZER_PROJECTPAGE_H
