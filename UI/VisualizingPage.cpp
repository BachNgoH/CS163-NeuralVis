//
// Created by LENOVO on 7/27/2023.
//
#include "VisualizingPage.h"
#include "../utils.h"

void VisualizingPage::drawNetwork(sf::RenderWindow &window, sf::Event &event, int label) {
    for(size_t k = 1; k < this->model.units_per_layer.size() - 1; k++){
        int i = k - 1;
        for(int j = 0; j < std::min(this->model.units_per_layer[k], 11); j++){
            RectangleShape node; node.setSize(sf::Vector2f(30, 30));
            double opacity = 0.2;
            if(this->model.activations[k].size() > 0)
                opacity = std::max(0.2, this->model.activations[k](j, 0));
            if(stepMode) {
                if(stepCounter > static_cast<double>(stepIter) * k / static_cast<double>(model.units_per_layer.size())) {
                    opacity = std::max(0.2, this->model.activations[k](j, 0));
                }else
                    opacity = 0.2;
            }

            node.setFillColor(Color(217, 217, 217, 225 * opacity));
            node.setPosition( 626 + i * 220, 249 + j * 42);
            window.draw(node);
            // draw connection

            if(k > 1){
                sf::Vector2f point1(626 + i * 220, 264 + j * 42);
                for(int f = 0; f < std::min(this->model.units_per_layer[k - 1], 11); f++){
                    sf::Vector2f  point2(656 + (i - 1) * 220, 264 + f * 42);

                    if (stepMode) {
                        sf::Vector2f point1_shifted = sf::Vector2f(point1.x, point1.y - 10);
                        sf::Vector2f point2_shifted = sf::Vector2f(point2.x, point2.y - 10);

                        sf::Vertex line[] = {point1_shifted, point2_shifted};
                        line[0].color = Color(179, 179, 179, 255 * opacity);
                        line[1].color = Color(179, 179, 179, 255 * opacity);
                        window.draw(line, 2, sf::Lines);

                        double opacity2 = 0.2;
                        if(stepCounter > stepIter + static_cast<double>(stepIter) * (model.units_per_layer.size() - k) / static_cast<double>(model.units_per_layer.size()))
                            opacity2 = std::max(0.2, this->model.activations[k](j, 0));

                        sf::Vector2f point1_back = sf::Vector2f(point1.x, point1.y + 10);
                        sf::Vector2f point2_back = sf::Vector2f(point2.x, point2.y + 10);

                        sf::Vertex line2[] = {point1_back, point2_back};
                        line2[0].color = Color(179, 179, 179, 255 * opacity2);
                        line2[1].color = Color(179, 179, 179, 255 * opacity2);
                        window.draw(line2, 2, sf::Lines);

                    }else
                        utils::drawLine(window, point1, point2,
                                    Color(179, 179, 179, 255 * opacity),
                                    Color(179, 179, 179, 255 * 0.2),
                                    1.0);

                }
                if(this->model.units_per_layer[k - 1] > 11){
                    if (stepMode) {
                        sf::Vector2f point2(656 + (i - 1) * 220, 789);
                        sf::Vector2f point1_shifted = sf::Vector2f(point1.x, point1.y - 10);
                        sf::Vector2f point2_shifted = sf::Vector2f(point2.x, point2.y - 10);

                        sf::Vertex line[] = {point1_shifted, point2_shifted};
                        line[0].color = Color(179, 179, 179, 255 * opacity);
                        line[1].color = Color(179, 179, 179, 255 * opacity);
                        window.draw(line, 2, sf::Lines);

                        double opacity2 = 0.2;
                        if(stepCounter > stepIter + static_cast<double>(stepIter) * (model.units_per_layer.size() - k) / static_cast<double>(model.units_per_layer.size()))
                            opacity2 = std::max(0.2, this->model.activations[k](j, 0));

                        sf::Vector2f point1_back = sf::Vector2f(point1.x, point1.y + 10);
                        sf::Vector2f point2_back = sf::Vector2f(point2.x, point2.y + 10);

                        sf::Vertex line2[] = {point1_back, point2_back};
                        line2[0].color = Color(179, 179, 179, 255 * opacity2);
                        line2[1].color = Color(179, 179, 179, 255 * opacity2);
                        window.draw(line2, 2, sf::Lines);

                        sf::Vector2f point3(656 + (i - 1) * 220, 831);
                        sf::Vector2f point3_shifted = sf::Vector2f(point3.x, point3.y - 10);
                        sf::Vertex line3[] = {point1_shifted, point3_shifted};
                        line3[0].color = Color(179, 179, 179, 255 * opacity);
                        line3[1].color = Color(179, 179, 179, 255 * opacity);
                        window.draw(line3, 2, sf::Lines);


                        sf::Vector2f point3_back = sf::Vector2f(point3.x, point3.y + 10);

                        sf::Vertex line4[] = {point1_back, point3_back};
                        line4[0].color = Color(179, 179, 179, 255 * opacity2);
                        line4[1].color = Color(179, 179, 179, 255 * opacity2);
                        window.draw(line4, 2, sf::Lines);

                    }else{
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
        if(this->model.units_per_layer[k] > 11) {
            Texture threeDotTexture; threeDotTexture.loadFromFile("../resources/blocks/HasMore.png");
            Sprite threeDot; threeDot.setTexture(threeDotTexture);
            threeDot.setPosition(635 + i * 220, 730);
            double opacity1 = 0.2;
            int numRows = this->model.activations[k].rows();
            if(this->model.activations[k].size() > 0)
                opacity1 = std::max(0.2, this->model.activations[k](numRows - 2, 0));
            if(stepMode) {
                if(stepCounter > static_cast<double>(stepIter) * k / static_cast<double>(model.units_per_layer.size())) {
                    opacity1 = std::max(0.2, this->model.activations[k](numRows - 2, 0));
                }else
                    opacity1 = 0.2;
            }


            RectangleShape node1; node1.setSize(sf::Vector2f(30, 30));
            node1.setFillColor(Color(217, 217, 217, 255 * opacity1));
            node1.setPosition(626 + i * 220, 774);

            double opacity2 = 0.2;
            if(this->model.activations[k].size() > 0)
                opacity2 = std::max(0.2, this->model.activations[k](numRows - 1, 0));
            if(stepMode) {
                if(stepCounter > static_cast<double>(stepIter) * k / static_cast<double>(model.units_per_layer.size())) {
                    opacity2 = std::max(0.2, this->model.activations[k](numRows - 1, 0));
                }else
                    opacity2 = 0.2;
            }

            RectangleShape node2; node2.setSize(sf::Vector2f(30, 30));
            node2.setFillColor(Color(217, 217, 217, 255 * opacity2));
            node2.setPosition(626 + i * 220, 816);

            window.draw(threeDot);
            window.draw(node1);
            window.draw(node2);

            if(k > 1) {
                for(int pos: {789, 831}) {
                    sf::Vector2f point1(626 + i * 220, pos);
                    for (int f = 0; f < std::min(this->model.units_per_layer[k - 1], 11); f++) {
                        double opacityLine=((double)rand()/(double)RAND_MAX);
                        if(stepCounter > static_cast<double>(stepIter) * k / static_cast<double>(model.units_per_layer.size())) {
                            opacityLine = std::max(0.2, this->model.activations[k](model.activations[k].rows() - 1, 0));
                        }else
                            opacityLine = 0.2;

                        if(stepMode) {
                            if(stepCounter > static_cast<double>(stepIter) * k / static_cast<double>(model.units_per_layer.size())) {
                                opacityLine = std::max(0.2, this->model.activations[k](model.activations[k].rows() - 1, 0));
                            }else
                                opacityLine = 0.2;

                            sf::Vector2f point2(656 + (i - 1) * 220, 264 + f * 42);
                            sf::Vector2f point1_shifted = sf::Vector2f(point1.x, point1.y - 10);
                            sf::Vector2f point2_shifted = sf::Vector2f(point2.x, point2.y - 10);

                            sf::Vertex line[] = {point1_shifted, point2_shifted};
                            line[0].color = Color(179, 179, 179, 255 * opacityLine);
                            line[1].color = Color(179, 179, 179, 255 * opacityLine);
                            window.draw(line, 2, sf::Lines);

                            double opacity2 = 0.2;
                            if(stepCounter > stepIter + static_cast<double>(stepIter) * (model.units_per_layer.size() - k) / static_cast<double>(model.units_per_layer.size()))
                                opacity2 = std::max(0.2, this->model.activations[k](model.activations[k].rows() - 1, 0));

                            sf::Vector2f point1_back = sf::Vector2f(point1.x, point1.y + 10);
                            sf::Vector2f point2_back = sf::Vector2f(point2.x, point2.y + 10);

                            sf::Vertex line2[] = {point1_back, point2_back};
                            line2[0].color = Color(179, 179, 179, 255 * opacity2);
                            line2[1].color = Color(179, 179, 179, 255 * opacity2);
                            window.draw(line2, 2, sf::Lines);
                        }else {

                            sf::Vector2f point2(656 + (i - 1) * 220, 264 + f * 42);
                            sf::Vertex line[] = {point1, point2};
                            line[0].color = Color(179, 179, 179, 255 * opacity1 * opacityLine);
                            line[1].color = Color(179, 179, 179, 255 * opacity1 * opacityLine);

                            window.draw(line, 2, sf::Lines);
                        }
                    }
                    if (this->model.units_per_layer[k - 1] > 11) {
                        sf::Vector2f point2(656 + (i - 1) * 220, 789);
                        sf::Vertex line[] = {point1, point2};
                        line[0].color = Color(179, 179, 179, 255 * opacity1);
                        line[1].color = Color(179, 179, 179, 255 * opacity1);

                        sf::Vector2f point3(656 + (i - 1) * 220, 831);
                        sf::Vertex line2[] = {point1, point3};
                        line2[0].color = Color(179, 179, 179, 255 * opacity2);
                        line2[1].color = Color(179, 179, 179, 255 * opacity2);


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

        Texture expandButtonTexture; expandButtonTexture.loadFromFile("../resources/button/ExpandButton.png");
        Sprite expandButton; expandButton.setTexture(expandButtonTexture);
        expandButton.setPosition(590 + i * 220, 920);
        if(expandButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(window)))){
            expandButtonTexture.loadFromFile("../resources/button/ExpandButton_selected.png");
            expandButton.setTexture(expandButtonTexture);
        }
        if(event.type == Event::MouseButtonPressed &&
            expandButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(window)))){
            activationWindowOpen = true;
            activationLayer = static_cast<int>(k);
        }

        window.draw(expandButton);

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
            opacity = 1.0;
        if(stepMode) {
            int k = model.activations.size() - 1;
            if(stepCounter > static_cast<double>(stepIter) * k / static_cast<double>(model.units_per_layer.size())) {
                if (label == nodeIdx)
                    opacity = 1.0;
            }else
                opacity = 0.2;
        }

        node.setFillColor(Color(217, 217, 217, 255 * opacity));
        node.setPosition(626 + (this->model.units_per_layer.size() - 2) * 220, 351 + nodeIdx * 42);
        window.draw(node);

        sf::Vector2f point1(626 + (this->model.units_per_layer.size() - 2) * 220, 366 + nodeIdx * 42);
        for (int f = 0; f < std::min(this->model.units_per_layer[this->model.units_per_layer.size() - 2], 11); f++) {
            sf::Vector2f point2(656 + (this->model.units_per_layer.size() - 3) * 220, 264 + f * 42);

            sf::Vector2f point1_shifted = sf::Vector2f(point1.x, point1.y - 10);
            sf::Vector2f point2_shifted = sf::Vector2f(point2.x, point2.y - 10);

            sf::Vertex line[] = {point1_shifted, point2_shifted};
            line[0].color = Color(179, 179, 179, 255 * opacity);
            line[1].color = Color(179, 179, 179, 255 * opacity);
            window.draw(line, 2, sf::Lines);

            double opacity2 = 0.2;
            if(stepCounter > stepIter + static_cast<double>(stepIter) / static_cast<double>(model.units_per_layer.size()))
                opacity2 = opacity;

            sf::Vector2f point1_back = sf::Vector2f(point1.x, point1.y + 10);
            sf::Vector2f point2_back = sf::Vector2f(point2.x, point2.y + 10);

            sf::Vertex line2[] = {point1_back, point2_back};
            line2[0].color = Color(179, 179, 179, 255 * opacity2);
            line2[1].color = Color(179, 179, 179, 255 * opacity2);
            window.draw(line2, 2, sf::Lines);

        }

        if (this->model.units_per_layer[this->model.units_per_layer.size() - 2] > 11) {
            sf::Vector2f point2(656 + (this->model.units_per_layer.size() - 3) * 220, 789);

            sf::Vector2f point1_shifted = sf::Vector2f(point1.x, point1.y - 10);
            sf::Vector2f point2_shifted = sf::Vector2f(point2.x, point2.y - 10);

            sf::Vertex line[] = {point1_shifted, point2_shifted};
            line[0].color = Color(179, 179, 179, 255 * opacity);
            line[1].color = Color(179, 179, 179, 255 * opacity);
            window.draw(line, 2, sf::Lines);

            double opacity2 = 0.2;
            if(stepCounter > stepIter + static_cast<double>(stepIter) / static_cast<double>(model.units_per_layer.size()))
                opacity2 = opacity;

            sf::Vector2f point1_back = sf::Vector2f(point1.x, point1.y + 10);
            sf::Vector2f point2_back = sf::Vector2f(point2.x, point2.y + 10);

            sf::Vertex line2[] = {point1_back, point2_back};
            line2[0].color = Color(179, 179, 179, 255 * opacity2);
            line2[1].color = Color(179, 179, 179, 255 * opacity2);
            window.draw(line2, 2, sf::Lines);


            sf::Vector2f point3(656 + (this->model.units_per_layer.size() - 3) * 220, 831);
            sf::Vector2f point3_shifted = sf::Vector2f(point3.x, point3.y - 10);

            sf::Vertex line3[] = {point1_shifted, point3_shifted};
            line3[0].color = Color(179, 179, 179, 255 * opacity);
            line3[1].color = Color(179, 179, 179, 255 * opacity);
            window.draw(line3, 2, sf::Lines);

            sf::Vector2f point3_back = sf::Vector2f(point2.x, point2.y + 10);

            sf::Vertex line4[] = {point1_back, point3_back};
            line4[0].color = Color(179, 179, 179, 255 * opacity2);
            line4[1].color = Color(179, 179, 179, 255 * opacity2);
            window.draw(line2, 2, sf::Lines);
        }
    }

    for(int weightIdx = 0; weightIdx < model.units_per_layer.size() - 2; weightIdx++){
        Texture showWeightButtonT;
        showWeightButtonT.loadFromFile("../resources/button/ShowWeightButton.png");

        Sprite showWeightButton; showWeightButton.setTexture(showWeightButtonT);
        showWeightButton.setPosition(736 + weightIdx * 220, 534);

        if(showWeightButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(window)))){
            showWeightButtonT.loadFromFile("../resources/button/ShowWeightButton_sel.png");
            showWeightButton.setTexture(showWeightButtonT);
            if(Mouse::isButtonPressed(Mouse::Left)){
                weightWindowOpen = true;
                weightLayer = weightIdx + 1;
            }
        }
        window.draw(showWeightButton);
    }
}

void VisualizingPage::drawWeightLayer(sf::RenderWindow &window, sf::Event &event) {
    if(weightWindowOpen){
        Texture weightBoxTexture; weightBoxTexture.loadFromFile("../resources/blocks/WeightBox.png");
        Sprite weightBox; weightBox.setTexture(weightBoxTexture);
        weightBox.setPosition(247, 229);

        Texture closeButtonTexture; closeButtonTexture.loadFromFile("../resources/button/CloseButton.png");
        Sprite closeButton; closeButton.setTexture(closeButtonTexture);
        closeButton.setPosition(1138, 249);
        sf::Vector2f mousePosition = static_cast<sf::Vector2f>(Mouse::getPosition(window));

        if(closeButton.getGlobalBounds().contains(mousePosition)){
            closeButtonTexture.loadFromFile("../resources/button/CloseButton_sel.png");
            closeButton.setTexture(closeButtonTexture);
            if(event.type == Event::MouseButtonPressed)
                weightWindowOpen = false;
        }

        window.draw(weightBox);
        window.draw(closeButton);

        if(stepMode){
            MatrixXd layerWeight = this->model.weights[weightLayer];
            MatrixXd gradientWeight = this->model.gradient[weightLayer];

            for (int i = 0; i < std::min(layerWeight.rows(), 8); i++) {
                for (int j = 0; j < std::min(layerWeight.cols(), 5); j++) {
                    double value = layerWeight(i, j);
                    if (stepCounter < stepIter){
                        value -= gradientWeight(i, j);
                    }
                    Text param;
                    param.setFont(font);
                    param.setCharacterSize(20);
                    param.setPosition(sf::Vector2f(330 + j * 63, 306 + 56 * i));
                    param.setString(std::to_string(value).substr(0, 4));
                    window.draw(param);
                }
            }


            if (layerWeight.rows() > 8) {
                Texture moreWeightT;
                moreWeightT.loadFromFile("../resources/blocks/HasMoreStep.png");
                Sprite moreWeight;
                moreWeight.setTexture(moreWeightT);
                moreWeight.setPosition(330, 744);
                window.draw(moreWeight);
                moreWeight.setPosition(752, 744);
                window.draw(moreWeight);

            }

            if (layerWeight.cols() > 11) {
                Texture moreWeightT;
                moreWeightT.loadFromFile("../resources/blocks/MoreWeightVertical.png");
                Sprite moreWeight;
                moreWeight.setTexture(moreWeightT);
                moreWeight.setPosition(665, 306);
                window.draw(moreWeight);
                moreWeight.setPosition(1092, 306);
                window.draw(moreWeight);
            }

            for (int i = 0; i < std::min(gradientWeight.rows(), 8); i++) {
                for (int j = 0; j < std::min(gradientWeight.cols(), 5); j++) {
                    double value = gradientWeight(i, j);
                    if(stepCounter < stepIter)
                        value = 0.0;
                    Text param;
                    param.setFont(font);
                    param.setCharacterSize(20);
                    param.setPosition(sf::Vector2f(330 + (j + 7) * 63, 306 + 56 * i));
                    param.setString(std::to_string(value).substr(0, 4));
                    window.draw(param);
                }
            }

            RectangleShape sepLine;
            sepLine.setSize(sf::Vector2f(4, 531));
            sepLine.setFillColor(Color(217,217,217));
            sepLine.setPosition(727, 266);
            window.draw(sepLine);

            Text weightText;
            weightText.setString("weight");
            weightText.setCharacterSize(20);
            weightText.setFont(font);
            weightText.setPosition(460, 266);
            window.draw(weightText);

            Text gradientText;
            gradientText.setString("gradient");
            gradientText.setCharacterSize(20);
            gradientText.setFont(font);
            gradientText.setPosition(877, 269);
            window.draw(gradientText);

        }else {
            MatrixXd layerWeight = this->model.weights[weightLayer];
            for (int i = 0; i < std::min(layerWeight.rows(), 8); i++) {
                for (int j = 0; j < std::min(layerWeight.cols(), 11); j++) {
                    Text param;
                    param.setFont(font);
                    param.setCharacterSize(20);
                    param.setPosition(sf::Vector2f(330 + j * 63, 306 + 56 * i));
                    param.setString(std::to_string(layerWeight(i, j)).substr(0, 4));
                    window.draw(param);
                }
            }
            if (layerWeight.rows() > 8) {
                Texture moreWeightT;
                moreWeightT.loadFromFile("../resources/blocks/MoreWeight.png");
                Sprite moreWeight;
                moreWeight.setTexture(moreWeightT);
                moreWeight.setPosition(330, 744);
                window.draw(moreWeight);
            }
            if (layerWeight.cols() > 11) {
                Texture moreWeightT;
                moreWeightT.loadFromFile("../resources/blocks/MoreWeightVertical.png");
                Sprite moreWeight;
                moreWeight.setTexture(moreWeightT);
                moreWeight.setPosition(1037, 306);
                window.draw(moreWeight);
            }
        }
    }
}

void VisualizingPage::drawActivationLayer(sf::RenderWindow &window, sf::Event &event) {
    if(activationWindowOpen) {
        Texture weightBoxTexture;
        weightBoxTexture.loadFromFile("../resources/blocks/WeightBox.png");
        Sprite weightBox;
        weightBox.setTexture(weightBoxTexture);
        weightBox.setPosition(247, 229);

        Texture closeButtonTexture;
        closeButtonTexture.loadFromFile("../resources/button/CloseButton.png");
        Sprite closeButton;
        closeButton.setTexture(closeButtonTexture);
        closeButton.setPosition(1138, 249);
        sf::Vector2f mousePosition = static_cast<sf::Vector2f>(Mouse::getPosition(window));

        if (closeButton.getGlobalBounds().contains(mousePosition)) {
            closeButtonTexture.loadFromFile("../resources/button/CloseButton_sel.png");
            closeButton.setTexture(closeButtonTexture);
            if (event.type == Event::MouseButtonPressed)
                activationWindowOpen = false;
        }

        window.draw(weightBox);
        window.draw(closeButton);

        MatrixXd layerActivation = this->model.activations[activationLayer];
        for(int i = 0; i < min(layerActivation.rows(), 88); i++) {
            int col = i % 11;
            int row = i / 11;
            double value = layerActivation(i, 0);
            Text param; param.setFont(font); param.setCharacterSize(20);
            param.setPosition(sf::Vector2f(330 + col * 63, 306 + 56 * row));
            param.setString(std::to_string(value).substr(0, 4));
            window.draw(param);

        }

    }
}

void VisualizingPage::drawData(RenderWindow &window, Eigen::MatrixXd data) {
    for(int i = 0; i < 28; i ++){
        for(int j = 0; j < 28; j++){
            int value = static_cast<int>(data(i * 28 + j,0) * 255);
            RectangleShape pixel; pixel.setSize(sf::Vector2f(15, 15));
            pixel.setPosition(31 + j * 16, 353+ i * 16);
            pixel.setFillColor(Color(value, value, value));
            window.draw(pixel);
        }
    }
}

void VisualizingPage::drawNavBar(sf::RenderWindow &window, sf::Event &event) {
    Texture navBarTexture; navBarTexture.loadFromFile("../resources/blocks/NavBar.png");
    Sprite navBar; navBar.setTexture(navBarTexture);
    navBar.setPosition(19, 20);

    Text epochText; epochText.setString(std::to_string(epoch));
    epochText.setCharacterSize(30); epochText.setFont(font);
    epochText.setPosition(367, 57);

    Text lossText; lossText.setString(std::to_string(loss).substr(0, 4));
    lossText.setCharacterSize(30); lossText.setFont(font);
    lossText.setPosition(573, 57);

    Text accText; accText.setString(std::to_string(acc).substr(0, 4) + "%");
    accText.setCharacterSize(30); accText.setFont(font);
    accText.setPosition(769, 57);

    window.draw(navBar);
    window.draw(epochText);
    window.draw(lossText);
    window.draw(accText);

    if (!stepMode) {
        Texture progressBarTexture;
        progressBarTexture.loadFromFile("../resources/blocks/ProgressBar.png");
        Sprite progressBar;
        progressBar.setTexture(progressBarTexture);
        progressBar.setPosition(1023, 84);

        Texture progressBBTexture;
        progressBBTexture.loadFromFile("../resources/blocks/ProgressBarBounder.png");
        Sprite progressBB;
        progressBB.setTexture(progressBBTexture);
        progressBB.setPosition(1015, 77);

        RectangleShape progressPercent;
        progressPercent.setPosition(1023, 84);
        progressPercent.setSize(sf::Vector2f(332 * this->progress, 29));

        Text progressText;
        progressText.setString(std::to_string(static_cast<int>(this->progress * 100)) + "%");
        progressText.setFont(font);
        progressText.setCharacterSize(20);
        progressText.setPosition(1137, 44);

        // Pause Button
        Texture pauseTexture;
        pauseTexture.loadFromFile("../resources/button/PauseButton.png");
        if (pauseTraining)
            pauseTexture.loadFromFile("../resources/button/ContinueButton.png");

        Sprite pauseButton;
        pauseButton.setTexture(pauseTexture);
        pauseButton.setPosition(968, 83);
        if (event.type == Event::MouseButtonPressed) {
            if (pauseButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(window))) && delay > 5) {
                pauseTraining = !pauseTraining;
                delay = 0;
            }
        }
        window.draw(progressBar);
        window.draw(progressPercent);
        window.draw(progressBB);
        window.draw(progressText);
        window.draw(pauseButton);
    }

}

void VisualizingPage::drawSteppingNav(sf::RenderWindow &window, sf::Event &event) {
    if(stepMode){

        Texture pauseButtonTexture;
        if(stopStepping)
            pauseButtonTexture.loadFromFile("../resources/button/ContinueButton.png");
        else
            pauseButtonTexture.loadFromFile("../resources/button/PauseButton.png");
        Sprite pauseButton; pauseButton.setTexture(pauseButtonTexture);
        pauseButton.setPosition(1220, 58);

        sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getPosition(window));
        if(pauseButton.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left) && delay > 5){
            if (!stopStepping) {
                pauseButtonTexture.loadFromFile("../resources/button/ContinueButton.png");
                pauseButton.setTexture(pauseButtonTexture);
                stopStepping = true;
            }else{
                pauseButtonTexture.loadFromFile("../resources/button/PauseButton.png");
                pauseButton.setTexture(pauseButtonTexture);
                stopStepping = false;

            }
            delay = 0;
        }
        // Step button
        Texture nextButtonT; nextButtonT.loadFromFile("../resources/button/NextButton.png");
        Sprite nextButton; nextButton.setTexture(nextButtonT);
        nextButton.setPosition(1282, 63);

        Texture backButtonT; backButtonT.loadFromFile("../resources/button/StepBackButton.png");
        Sprite backButton; backButton.setTexture(backButtonT);
        backButton.setPosition(1169, 63);

        int stepSize = stepIter / model.units_per_layer.size();
        int totalStep = stepIter * 2 / stepSize;

        if (nextButton.getGlobalBounds().contains(mousePos)){
            nextButtonT.loadFromFile("../resources/button/NextButton_sel.png");
            nextButton.setTexture(nextButtonT);

            if(Mouse::isButtonPressed(Mouse::Left) && delay > 5) {
                stepCounter = (stepCounter + stepSize) % (stepIter * 2);
                delay = 0;
            }

        }
        if(backButton.getGlobalBounds().contains(mousePos)) {
            backButtonT.loadFromFile("../resources/button/StepBackButton_sel.png");
            backButton.setTexture(backButtonT);

            if(Mouse::isButtonPressed(Mouse::Left) && delay > 5) {
                stepCounter = max(0, stepCounter - stepSize);
                delay = 0;
            }
        }

        Texture progressBounderT; progressBounderT.loadFromFile("../resources/blocks/StepProgressBounder.png");
        Sprite progressBounder; progressBounder.setTexture(progressBounderT);
        progressBounder.setPosition(1105, 105);

        sf::RectangleShape progressBar;
        progressBar.setPosition(1108, 108);
        progressBar.setFillColor( Color(179,179,179));


        progressBar.setSize(sf::Vector2f(257 * (stepCounter / stepSize) / totalStep, 12));

        Text stageText; stageText.setPosition(1225, 237);
        stageText.setFont(font);
        stageText.setCharacterSize(20);
        if(stepCounter < stepIter)
            stageText.setString("Forward Stage");
        else
            stageText.setString("Backward Stage");

        window.draw(nextButton);
        window.draw(backButton);
        window.draw(pauseButton);
        window.draw(progressBar);
        window.draw(progressBounder);
        window.draw(stageText);
    }
}

void VisualizingPage::drawSaveButton(sf::RenderWindow &window, sf::Event &event, int &mode) {

    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(Mouse::getPosition(window));
    Texture tsaveWeightButton;
    tsaveWeightButton.loadFromFile("../resources/button/SaveWeightButton.png");
    Sprite saveWeightButton;
    saveWeightButton.setTexture(tsaveWeightButton);
    saveWeightButton.setPosition(1217, 848);
    if(saveWeightButton.getGlobalBounds().contains(mousePosition)) {
        tsaveWeightButton.loadFromFile("../resources/button/SaveWeightButton_sel.png");
        saveWeightButton.setTexture(tsaveWeightButton);

        if(event.type == Event::MouseButtonPressed){
            model.save_weights("../checkpoint/model_weights.bin");
            this->isSaveClicked = true;
            delay = 0;
        }
    }


    Texture tInferenceButton;
    tInferenceButton.loadFromFile("../resources/button/InferenceButton.png");
    Sprite inferenceButton;
    inferenceButton.setTexture(tInferenceButton);
    inferenceButton.setPosition(1217, 910);

    if(inferenceButton.getGlobalBounds().contains(mousePosition)) {
        tInferenceButton.loadFromFile("../resources/button/InferenceButton_sel.png");
        inferenceButton.setTexture(tInferenceButton);
        if (event.type == Event::MouseButtonPressed)
            mode = 3;
    }

    if(isSaveClicked && delay < 12) {
        Text message; message.setString("success");
        message.setFont(font); message.setFillColor(Color(10, 223, 57));
        message.setCharacterSize(20);
        message.setPosition(1264, 806);
        window.draw(message);
    }

    window.draw(saveWeightButton);
    window.draw(inferenceButton);
}

void VisualizingPage::drawStepByStepButton(sf::RenderWindow &window, sf::Event &event) {
    Texture stepButtonT;
    stepButtonT.loadFromFile("../resources/button/StepButton.png");
    Sprite stepButton;
    stepButton.setTexture(stepButtonT);
    stepButton.setPosition(1128, 162);
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getPosition(window));
    if(stepButton.getGlobalBounds().contains(mousePos)) {
        stepButtonT.loadFromFile("../resources/button/StepButton_sel.png");
        stepButton.setTexture(stepButtonT);
        if(Mouse::isButtonPressed(Mouse::Left) && delay > 5){
            stepMode = !stepMode;
            pauseTraining = !pauseTraining;
            delay = 0;
        }
    }
    if(stepMode){
        stepButtonT.loadFromFile("../resources/button/StepButton_sel.png");
        stepButton.setTexture(stepButtonT);
    }

    window.draw(stepButton);
}

void VisualizingPage::render(sf::RenderWindow &window, sf::Event &event, std::tuple<MatrixXd, MatrixXd> data, int &mode) {
    delay += 1;
    // print network
    MatrixXd x = std::get<0>(data).transpose();;
    MatrixXd one_hot_label = std::get<1>(data);
    int label = 0;
    for(int col = 0; col < 10; col++){
        if(one_hot_label(0, col) == 1.0)
            label = col;
    }

    drawNetwork(window, event, label);
    drawData(window, x);
    drawNavBar(window, event);
    drawWeightLayer(window, event);
    drawActivationLayer(window, event);
    drawSaveButton(window, event, mode);
    drawStepByStepButton(window, event);
    if(stepMode) {
        pauseTraining = true;
        if(isSteping && !stopStepping)
            stepCounter = (stepCounter + 1) % (stepIter * 2);
        drawSteppingNav(window, event);
    }
}

