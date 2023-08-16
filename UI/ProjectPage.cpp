//
// Created by LENOVO on 7/21/2023.
//
#include "ProjectPage.h"

void ProjectPage::drawHeader(sf::RenderWindow &window, sf::Event &event, int &mode, string projectName) {
    Texture headerTexture;
    headerTexture.loadFromFile("../resources/blocks/RoundedRect_long.png");
    Sprite header; header.setTexture(headerTexture);
    header.setPosition(31, 34);

    Text projectText; projectText.setString(projectName);
    projectText.setFont(font); projectText.setCharacterSize(30);
    projectText.setPosition(58, 56);

    Texture backButtonTexture; backButtonTexture.loadFromFile("../resources/button/BackButton.png");
    Sprite backButton; backButton.setTexture(backButtonTexture);
    backButton.setPosition(1268, 49);

    if(backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(window)))){
        backButtonTexture.loadFromFile("../resources/button/BackButton_selected.png");
        backButton.setTexture(backButtonTexture);
        if(event.type == Event::MouseButtonPressed)
            mode = 0;
    }

    window.draw(header);
    window.draw(backButton);
    window.draw(projectText);
}

void ProjectPage::drawTrainingConfig(RenderWindow &window, Event &event) {
    Texture containerTexture; containerTexture.loadFromFile("../resources/blocks/ProjectSetting.png");
    Sprite container; container.setTexture(containerTexture);
    container.setPosition(900, 165);

    Texture newLayerTexture; newLayerTexture.loadFromFile("../resources/button/NewLayer.png");
    Sprite newLayerButton; newLayerButton.setTexture(newLayerTexture);
    newLayerButton.setPosition(918, 183);

    Text layerTitle; layerTitle.setString("Linear"); layerTitle.setCharacterSize(26);
    layerTitle.setFont(font); layerTitle.setStyle(layerTitle.Bold); layerTitle.setPosition(952, 204);
    layerTitle.setFillColor(Color::Black);

    Text nodeNum; nodeNum.setString("Nodes: \nActivations:Sigmoid"); nodeNum.setCharacterSize(26);
    nodeNum.setFont(font); nodeNum.setPosition(952, 238);
    nodeNum.setFillColor(Color::Black);

    Text configTitle; configTitle.setString("Training Configs"); configTitle.setCharacterSize(26);
    configTitle.setFont(font); configTitle.setStyle(configTitle.Bold); configTitle.setPosition(952, 388);
    configTitle.setFillColor(Color::Black);

    Text config; config.setString("Epochs: \nLearning Rate: "); config.setCharacterSize(26);
    config.setFont(font); config.setPosition(952, 432);
    config.setFillColor(Color::Black);

    Texture trainConfTexture; trainConfTexture.loadFromFile("../resources/blocks/TrainingConf.png");
    Sprite trainingConfigButton; trainingConfigButton.setTexture(trainConfTexture);
    trainingConfigButton.setPosition(918, 363);

    numNodesText.setPosition(sf::Vector2f(1056, 236));
    numNodesText.setLimit(true, 2);
    numNodesText.setColor(Color::Black); numNodesText.setFont(font);
    numNodesText.setCharacterSize(26);

    epochsText.setPosition(sf::Vector2f(1068, 432));
    epochsText.setLimit(true, 1);
    epochsText.setColor(Color::Black); epochsText.setFont(font);
    epochsText.setCharacterSize(26);

    learningRateText.setPosition(sf::Vector2f(1178, 466));
    learningRateText.setLimit(true, 5);
    learningRateText.setColor(Color::Black); learningRateText.setFont(font);
    learningRateText.setCharacterSize(26);

    sf::Vector2i mousePosition = Mouse::getPosition(window);
    if (event.type == Event::MouseButtonPressed) {
        if (mousePosition.x > 1043 && mousePosition.x < 1137 && mousePosition.y > 235 && mousePosition.y < 273) {
            numNodesText.setSelected(true);
            epochsText.setSelected(false);
            learningRateText.setSelected(false);
        } else if(mousePosition.x > 1062 && mousePosition.x < 1156 && mousePosition.y > 420 && mousePosition.y < 460){
            learningRateText.setSelected(false);
            numNodesText.setSelected(false);
            epochsText.setSelected(true);
        } else if (mousePosition.x > 1174 && mousePosition.x < 1268 && mousePosition.y > 462 && mousePosition.y < 512){
            learningRateText.setSelected(true);
            numNodesText.setSelected(false);
            epochsText.setSelected(false);
        }
        else {
            learningRateText.setSelected(false);
            numNodesText.setSelected(false);
            epochsText.setSelected(false);
        }
    }
    if (event.type == Event::TextEntered && timeDelay > 5) {
        numNodesText.typedOn(event);
        epochsText.typedOn(event);
        learningRateText.typedOn(event);
        timeDelay = 0;
    }

    CircleShape addButton;
    addButton.setPosition(1280, 214);
    addButton.setRadius(40);
    addButton.setFillColor(Color(171, 71, 188));
    if(numNodesText.isEmpty())
        addButton.setFillColor(Color(171, 71, 188, 112));

    Text addSign; addSign.setFont(font);
    addSign.setString("+"); addSign.setPosition(1311, 233);

    if (addButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && !numNodesText.isEmpty())
        addButton.setFillColor(Color(232, 125, 62));

    if (event.type == Event::MouseButtonPressed &&
        addButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && timeDelay > 10){
        if(!numNodesText.isEmpty() && nodesPerLayer.size() < 3) {
            int nodes = stoi(numNodesText.getText());
            nodesPerLayer.push_back(nodes);
            numNodesText.clearText();
        }else if(nodesPerLayer.size() >= 3){
            errorMessage.setString("Max number of layers is 3!");
        }
        timeDelay = 0;
    }



    window.draw(container);
    window.draw(newLayerButton);
    window.draw(trainingConfigButton);
    window.draw(layerTitle);
    window.draw(nodeNum);
    window.draw(configTitle);
    window.draw(config);
    numNodesText.drawTo(window);
    epochsText.drawTo(window);
    learningRateText.drawTo(window);
    window.draw(addButton);
    window.draw(addSign);
}

void ProjectPage::drawNetwork(sf::RenderWindow &window, sf::Event &event) {
    for(size_t i = 0; i < nodesPerLayer.size(); i++){
        for(int j = 0; j < min(nodesPerLayer[i], 11); j++){
            RectangleShape node; node.setSize(sf::Vector2f(30, 30));
            node.setFillColor(Color(217, 217, 217));
            node.setPosition(126 + i * 220, 249 + j * 42);
            window.draw(node);
        }
        if(nodesPerLayer[i] > 11) {
            Texture threeDotTexture; threeDotTexture.loadFromFile("../resources/blocks/HasMore.png");
            Sprite threeDot; threeDot.setTexture(threeDotTexture);
            threeDot.setPosition(135 + i * 220, 730);

            RectangleShape node1; node1.setSize(sf::Vector2f(30, 30));
            node1.setFillColor(Color(217, 217, 217));
            node1.setPosition(126 + i * 220, 774);

            RectangleShape node2; node2.setSize(sf::Vector2f(30, 30));
            node2.setFillColor(Color(217, 217, 217));
            node2.setPosition(126 + i * 220, 816);

            window.draw(threeDot);
            window.draw(node1);
            window.draw(node2);
        }
        Text layerName; layerName.setFont(font);
        layerName.setString("hidden " + to_string(i));
        layerName.setCharacterSize(20);
        layerName.setPosition(93 + i * 220, 194);

        window.draw(layerName);
        
        Texture layerBounderTexture; layerBounderTexture.loadFromFile("../resources/blocks/LayerBounder.png");
        Sprite layerBounder; layerBounder.setTexture(layerBounderTexture);
        layerBounder.setPosition(82 + i * 220, 224);
        window.draw(layerBounder);

        Text nodesNumText; nodesNumText.setString(to_string(nodesPerLayer[i]));
        nodesNumText.setFont(font); nodesNumText.setCharacterSize(20);

        nodesNumText.setPosition(128 + i * 220, 865);
        window.draw(nodesNumText);

        Texture minusButtonT; minusButtonT.loadFromFile("../resources/button/MinusButton.png");
        Sprite minusButton; minusButton.setTexture(minusButtonT);
        minusButton.setPosition(104 + i * 220, 917);
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if(minusButton.getGlobalBounds().contains(mousePos)){
            minusButtonT.loadFromFile("../resources/button/MinusButton_sel.png");
            minusButton.setTexture(minusButtonT);

            if(event.type == Event::MouseButtonPressed && timeDelay > 5){
                nodesPerLayer.erase(nodesPerLayer.begin() + i);
                timeDelay = 0;
            }
        }
        window.draw(minusButton);
    }
}

void ProjectPage::render(sf::RenderWindow &window, sf::Event &event, int &mode, string projectName) {
    timeDelay += 1;
    drawHeader(window, event, mode, projectName);
    drawTrainingConfig(window, event);
    drawNetwork(window, event);

    Texture startButtonTexture; startButtonTexture.loadFromFile("../resources/button/StartButton.png");
    Sprite startButton; startButton.setTexture(startButtonTexture);
    startButton.setPosition(1045, 837);

    Vector2i mousePosition = Mouse::getPosition(window);
    if(startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))){
        startButtonTexture.loadFromFile("../resources/button/StartButton_sel.png");
        startButton.setTexture(startButtonTexture);
    }

    if(event.type == Event::MouseButtonPressed && startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))){
        if(nodesPerLayer.size() != 0 && !epochsText.getText().empty() && !learningRateText.getText().empty()) {
            try {
                std::stof(learningRateText.getText());
                if(std::stof(learningRateText.getText()) <= 0)
                    errorMessage.setString("lr must be > 0");
                else
                    mode = 2;

            } catch(...){
                errorMessage.setString("lr must be a valid number");
            }
        }
        else if(nodesPerLayer.size() == 0)
            errorMessage.setString("Hidden layers must be > 0");
        else if(epochsText.getText().empty())
            errorMessage.setString("Need to specify number of epochs");
        else if(learningRateText.getText().empty())
            errorMessage.setString("Need to specify the learning rate");
    }

    errorMessage.setPosition(977, 660);
    window.draw(errorMessage);
    window.draw(startButton);

}