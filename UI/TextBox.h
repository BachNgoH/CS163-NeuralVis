//
// Created by LENOVO on 7/22/2023.
//

#ifndef NEURALVISUALIZER_TEXTBOX_H
#define NEURALVISUALIZER_TEXTBOX_H
#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include <sstream>
using namespace std;
using namespace sf;

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox
{
private:
    Text textbox;
    ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit;

    void inputLogic(int charType) {
        if (charType != DELETE_KEY && charType != ENTER_KEY && charType != ESCAPE_KEY) {
            text << static_cast<char>(charType);
        }
        else if (charType == DELETE_KEY) {
            if (text.str().length() > 0) {
                deleteLastChar();
            }
        }

        textbox.setString(text.str() + "|");
    }

    void deleteLastChar() {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length() - 1; i++) {
            newT += t[i];
        }
        text.str("");
        text << newT;

        textbox.setString(text.str());
    }

public:
    TextBox() {};
    TextBox(int size, sf::Color color, bool isSelected) {
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        this->isSelected = isSelected;
        if (isSelected) {
            textbox.setString("|");
        }
        else {
            textbox.setString("");
        }
    }
    ~TextBox() {};

    void setColor(sf::Color color){
        textbox.setFillColor(color);
    }

    void setFont(sf::Font& font) {
        textbox.setFont(font);
    }

    void setPosition(sf::Vector2f pos) {
        textbox.setPosition(pos);
    }

    void setLimit(bool ToF, int limit) {
        hasLimit = ToF;
        this->limit = limit;

    }

    void setSelected(bool sel) {
        isSelected = sel;
        if (!sel) {
            std::string t = text.str();
            std::string newT = "";
            for (int i = 0; i < t.length(); i++) {
                newT += t[i];
            }
            textbox.setString(newT);
        }
        else {
            std::string t = text.str();
            t += "|";
            textbox.setString(t);
        }
    }

    void setCharacterSize(int size){
        textbox.setCharacterSize(size);
    }
    std::string getText() {
        return text.str();
    }

    void drawTo(RenderWindow& window) {
        window.draw(textbox);
    }

    void clearText(){
        text.str("");
    }

    void typedOn(Event& input) {
        if (isSelected) {
            int charType = input.text.unicode;
            if ((charType >= 48 && charType <= 57) || charType == 8 ||
                charType == 13 || charType == 27 || charType == 46) {
                if (hasLimit) {
                    if (text.str().length() <= limit) {
                        inputLogic(charType);
                    }
                    else if (text.str().length() > limit && charType == DELETE_KEY) {
                        deleteLastChar();
                    }
                }
                else {
                    inputLogic(charType);
                }
            }
        }
    }

    bool isEmpty() {
        return text.str() == "" || text.str() == "|";
    }
};

#endif //NEURALVISUALIZER_TEXTBOX_H
