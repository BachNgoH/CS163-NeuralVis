//
// Created by LENOVO on 8/2/2023.
//

#include "InferencePage.h"

void InferencePage::drawData(sf::RenderWindow &window, Event &event) {
    Texture bounderTexture; bounderTexture.loadFromFile("../resources/blocks/InputBounder.png");
    Sprite inputBounder; inputBounder.setTexture(bounderTexture);
    inputBounder.setPosition(22, 331);
    window.draw(inputBounder);

    for(int i = 0; i < 28; i ++){
        for(int j = 0; j < 28; j++){
            int value = static_cast<int>(this->inputData(i * 28 + j, 0));
            sf::RectangleShape pixel; pixel.setSize(sf::Vector2f(15, 15));
            pixel.setPosition(48 + j * 16, 353+ i * 16);
            pixel.setFillColor(sf::Color(value, value, value));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
                pixel.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(window)))){
                inputData(i * 28 + j, 0) = std::min(255.0, inputData(i * 28 + j, 0) + 230.0);
                if(i + 1 < 28 && j + 1 < 28) inputData((i + 1) * 28 + j + 1, 0) = std::min(255.0, inputData((i + 1) * 28 + j + 1, 0) + 230.0);
                if(i + 1 < 28) inputData((i + 1) * 28 + j, 0) = std::min(255.0, inputData((i + 1) * 28 + j, 0) + 110.0);
                if(j + 1 < 28) inputData( i * 28 + j + 1, 0) = std::min(255.0, inputData(i * 28 + j + 1, 0) + 110.0);

            }
            window.draw(pixel);
        }
    }

    sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getPosition(window));
    Texture startButtonT; startButtonT.loadFromFile("../resources/button/StartButton_2.png");
    Sprite startButton; startButton.setTexture(startButtonT);
    startButton.setPosition(182, 863);
    if(startButton.getGlobalBounds().contains(mousePos)){
        startButtonT.loadFromFile("../resources/button/StartButton_2_sel.png");
        startButton.setTexture(startButtonT);
        if(event.type == Event::MouseButtonPressed)
            infer = true;

    }
    window.draw(startButton);

    Texture clearButtonT; clearButtonT.loadFromFile("../resources/button/ClearButton.png");
    Sprite clearButton; clearButton.setTexture(clearButtonT);
    clearButton.setPosition(22, 245);
    if(clearButton.getGlobalBounds().contains(mousePos)){
        clearButtonT.loadFromFile("../resources/button/ClearButton_sel.png");
        clearButton.setTexture(clearButtonT);
        if(Mouse::isButtonPressed(Mouse::Left)) {
            infer = false;
            for(int i = 0; i < inputData.rows(); i++){
                for(int j = 0; j < inputData.cols(); j++)
                    inputData(i, j) = 0.0;
            }
        }
    }
    window.draw(clearButton);
}


void InferencePage::drawNetwork(sf::RenderWindow &window, sf::Event &event, int label) {
    for(size_t k = 1; k < this->model.units_per_layer.size() - 1; k++){
        int i = k - 1;
        for(int j = 0; j < std::min(this->model.units_per_layer[i], 11); j++){
            double opacity = 0.2;
            if(this->model.activations[i].size() > 1){
                // std::cout << model.activations[i].rows() << ", " << model.activations[i].cols() << std::endl;
                opacity = std::max(std::min(0.2, model.activations[i](j, 0)), 1.0);
            }
            RectangleShape node; node.setSize(sf::Vector2f(30, 30));

            node.setFillColor(Color(217, 217, 217, 225 * opacity));
            node.setPosition( 626 + i * 220, 249 + j * 42);
            window.draw(node);
            // draw connection

            if(i > 0){
                sf::Vector2f point1(626 + i * 220, 264 + j * 42);
                for(int f = 0; f < std::min(this->model.units_per_layer[i - 1], 11); f++){
                    sf::Vector2f  point2(656 + (i - 1) * 220, 264 + f * 42);
                    sf::Vertex line[] = {point1, point2};

                    line[0].color = Color(179, 179, 179, 255 * opacity);
                    line[1].color = Color(179, 179, 179, 255 * opacity);

                    window.draw(line, 2, sf::Lines);
                }
                if(this->model.units_per_layer[i - 1] > 11){
                    sf::Vector2f  point2(656 + (i - 1) * 220, 789);
                    sf::Vertex line[] = {point1, point2};
                    line[0].color = Color(179, 179, 179, 255 * opacity);
                    line[1].color = Color(179, 179, 179, 255 * opacity);

                    sf::Vector2f  point3(656 + (i - 1) * 220, 831);
                    sf::Vertex line2[] = {point1, point3};
                    line2[0].color = Color(179, 179, 179, 255 * opacity);
                    line2[1].color = Color(179, 179, 179, 255 * opacity);


                    window.draw(line, 2, sf::Lines);
                    window.draw(line2, 2, sf::Lines);
                }
            }

        }
        if(this->model.units_per_layer[i] > 11) {
            Texture threeDotTexture; threeDotTexture.loadFromFile("../resources/blocks/HasMore.png");
            Sprite threeDot; threeDot.setTexture(threeDotTexture);
            threeDot.setPosition(635 + i * 220, 730);
            double opacity1 = 0.2;
            if(this->model.activations[i].size() != 0){
                // std::cout << model.activations[i].rows() << ", " << model.activations[i].cols() << std::endl;
                opacity1 = std::max(std::min(0.2, model.activations[i](model.activations[i].size() - 2, 0)), 1.0);
            }

            RectangleShape node1; node1.setSize(sf::Vector2f(30, 30));
            node1.setFillColor(Color(217, 217, 217, 255 * opacity1));
            node1.setPosition(626 + i * 220, 774);

            double opacity2 = 0.2;
            if(this->model.activations[i].size() != 0){
                // std::cout << model.activations[i].rows() << ", " << model.activations[i].cols() << std::endl;
                opacity2 = std::min(0.2, model.activations[i](model.activations[i].size() - 1, 0));
            }

            RectangleShape node2; node2.setSize(sf::Vector2f(30, 30));
            node2.setFillColor(Color(217, 217, 217, 255 * opacity2));
            node2.setPosition(626 + i * 220, 816);

            window.draw(threeDot);
            window.draw(node1);
            window.draw(node2);

            if(i > 0) {
                for(int pos: {789, 831}) {
                    double opacity = 0.2;
                    
                    sf::Vector2f point1(626 + i * 220, pos);
                    for (int f = 0; f < std::min(this->model.units_per_layer[i - 1], 11); f++) {
                        sf::Vector2f point2(656 + (i - 1) * 220, 264 + f * 42);
                        sf::Vertex line[] = {point1, point2};
                        line[0].color = Color(179, 179, 179, 255 * opacity);
                        line[1].color = Color(179, 179, 179, 255 * opacity);

                        window.draw(line, 2, sf::Lines);
                    }
                    if (this->model.units_per_layer[i - 1] > 11) {
                        sf::Vector2f point2(656 + (i - 1) * 220, 789);
                        sf::Vertex line[] = {point1, point2};
                        line[0].color = Color(179, 179, 179, 255 * opacity);
                        line[1].color = Color(179, 179, 179, 255 * opacity);

                        sf::Vector2f point3(656 + (i - 1) * 220, 831);
                        sf::Vertex line2[] = {point1, point3};
                        line2[0].color = Color(179, 179, 179, 255 * opacity);
                        line2[1].color = Color(179, 179, 179, 255 * opacity);


                        window.draw(line, 2, sf::Lines);
                        window.draw(line2, 2, sf::Lines);
                    }
                }
            }
        }
        Text layerName; layerName.setFont(font);
        layerName.setString("hidden " + std::to_string(i));
        layerName.setCharacterSize(20);
        layerName.setPosition(593 + i * 220, 194);

        window.draw(layerName);

        Texture layerBounderTexture; layerBounderTexture.loadFromFile("../resources/blocks/LayerBounder.png");
        Sprite layerBounder; layerBounder.setTexture(layerBounderTexture);
        layerBounder.setPosition(582 + i * 220, 224);
        window.draw(layerBounder);

        Text nodesNumText; nodesNumText.setString(std::to_string(this->model.units_per_layer[k]));
        nodesNumText.setFont(font); nodesNumText.setCharacterSize(20);

        nodesNumText.setPosition(628 + i * 220, 865);
        window.draw(nodesNumText);

    }
    // Draw output layers
    Texture outputLayerTexture; outputLayerTexture.loadFromFile("../resources/blocks/OutputLayer.png");
    Sprite outputLayer; outputLayer.setTexture(outputLayerTexture);
    outputLayer.setPosition(582 + 220 * (this->model.units_per_layer.size() - 2), 268);
    window.draw(outputLayer);

    for(int nodeIdx = 0; nodeIdx < 10; nodeIdx++){
        RectangleShape node; node.setSize(sf::Vector2f(30, 30));
        double opacity = 0.2;
        if (label == nodeIdx)
            opacity = 0.8;

        node.setFillColor(Color(217, 217, 217, 255 * opacity));
        node.setPosition(626 + (this->model.units_per_layer.size() - 2) * 220, 351 + nodeIdx * 42);
        window.draw(node);

        sf::Vector2f point1(626 + (this->model.units_per_layer.size() - 2) * 220, 366 + nodeIdx * 42);
        for (int f = 0; f < std::min(this->model.units_per_layer[this->model.units_per_layer.size() - 2], 11); f++) {
            sf::Vector2f point2(656 + (this->model.units_per_layer.size() - 3) * 220, 264 + f * 42);
            sf::Vertex line[] = {point1, point2};
            line[0].color = Color(179, 179, 179, 255 * opacity);
            line[1].color = Color(179, 179, 179, 255 * opacity);

            window.draw(line, 2, sf::Lines);
        }

        if (this->model.units_per_layer[this->model.units_per_layer.size() - 2] > 11) {
            sf::Vector2f point2(656 + (this->model.units_per_layer.size() - 3) * 220, 789);
            sf::Vertex line[] = {point1, point2};
            line[0].color = Color(179, 179, 179, 255 * opacity);
            line[1].color = Color(179, 179, 179, 255 * opacity);

            sf::Vector2f point3(656 + (this->model.units_per_layer.size() - 3) * 220, 831);
            sf::Vertex line2[] = {point1, point3};
            line2[0].color = Color(179, 179, 179, 255 * opacity);
            line2[1].color = Color(179, 179, 179, 255 * opacity);


            window.draw(line, 2, sf::Lines);
            window.draw(line2, 2, sf::Lines);
        }
    }
}

void InferencePage::drawNavBar(sf::RenderWindow &window, sf::Event &event, int &mode) {

    Texture navBarTexture; navBarTexture.loadFromFile("../resources/blocks/InferenceNavBar.png");
    Sprite navBar; navBar.setTexture(navBarTexture);
    navBar.setPosition(19, 20);

    Texture homeButtonT; homeButtonT.loadFromFile("../resources/button/HomeButton.png");
    Sprite homeButton; homeButton.setTexture(homeButtonT);
    homeButton.setPosition(55, 53);

    sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getPosition(window));
    if(homeButton.getGlobalBounds().contains(mousePos)) {
        homeButtonT.loadFromFile("../resources/button/HomeButton_sel.png");
        homeButton.setTexture(homeButtonT);
        if (Mouse::isButtonPressed(Mouse::Left))
            mode = 0;
    }

    window.draw(navBar);
    window.draw(homeButton);
}

void InferencePage::render(sf::RenderWindow &window, sf::Event &event, int &mode) {
    drawData(window, event);
    if(infer){
        MatrixXd data = this->inputData;

        MatrixXd mLabel = model.forward(data);

        int maxIdx = 0;
        double maxVal = mLabel(0, 0);
        for(int i = 1; i < mLabel.rows(); i++){
            if(mLabel(i, 0) > maxVal){
                maxVal = mLabel(i, 0);
                maxIdx = i;
            }
        }
        label = maxIdx;
    }
    drawNetwork(window, event, label);
    drawNavBar(window, event, mode);
}
