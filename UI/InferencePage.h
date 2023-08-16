//
// Created by LENOVO on 8/2/2023.
//

#ifndef NEURALVISUALIZER_INFERENCEPAGE_H
#define NEURALVISUALIZER_INFERENCEPAGE_H

#include "SFML/Graphics.hpp"
#include "../Eigen/Core"
#include "../DeepLearningV2/MLP.h"
using namespace Eigen;
using namespace sf;

class InferencePage {
public:
    sf::Font font;
    Eigen::MatrixXd inputData;
    nn::MLP model;
    bool infer = false;
    int label = -1;

    InferencePage() {
        font.loadFromFile("../resources/fonts/JetBrains_Mono/JetBrainsMono-VariableFont_wght.ttf");
        inputData = MatrixXd::Zero(784, 1);
        model.load_weights("../checkpoint/model_weights.bin");
    }

    void drawNavBar(sf::RenderWindow &window, sf::Event &event, int &mode);
    void drawNetwork(sf::RenderWindow &window, sf::Event &event, int label);
    void drawData(sf::RenderWindow &window, sf::Event &event);
    void render(sf::RenderWindow &window, sf::Event &event, int &mode);
};


#endif //NEURALVISUALIZER_INFERENCEPAGE_H
