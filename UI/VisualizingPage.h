#pragma once
#include "../DeepLearningV2/MLP.h"
#include "SFML/Graphics.hpp"
#include <iostream>
using namespace sf;

class VisualizingPage {
public:
    nn::MLP model;
    Font font;
    int epoch = 0;
    double acc = 0.0;
    double loss = 0.0;
    double progress;
    bool pauseTraining = false;
    bool weightWindowOpen = false;
    bool activationWindowOpen = false;

    int weightLayer = 0;
    int activationLayer = 0;

    int delay = 0;
    bool isSaveClicked = false;
    bool stepMode = false;

    int stepIter = 100;
    bool isSteping = true;
    int stepCounter = 0;
    bool stopStepping = false;

    VisualizingPage() {
        font.loadFromFile("../resources/fonts/JetBrains_Mono/JetBrainsMono-VariableFont_wght.ttf");
    };

    void drawStepByStepButton(RenderWindow &window, Event &event);
    void drawSteppingNav(RenderWindow &window, Event &event);
    void drawNavBar(RenderWindow &window, Event &event);
    void drawData(RenderWindow &window, MatrixXd data);
    void drawNetwork(RenderWindow &window, Event &event, int label);
    void drawWeightLayer(RenderWindow &window, Event &event);
    void drawActivationLayer(RenderWindow &window, Event &event);

    void drawSaveButton(RenderWindow &window, Event &event, int &mode);
    void render(RenderWindow &window, Event &event, std::tuple<MatrixXd, MatrixXd> data, int &mode);
};