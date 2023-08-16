//
// Created by LENOVO on 7/12/2023.
//

#ifndef NEURALVISUALIZER_UTILS_H
#define NEURALVISUALIZER_UTILS_H

#include "Eigen/Dense"
#include <windows.h>
#include <fstream>
#include <tuple>
using namespace Eigen;
using namespace std;

class MNISTDataset {
public:
    int batch_size;
    string data_dir;
    int num_lines;
    explicit MNISTDataset(int batch_size) : batch_size(batch_size) {
        data_dir = "../data/train.csv";
        num_lines = countLines(data_dir) / 2;
    };

    tuple<MatrixXd, MatrixXd> loadData (int batch_num) {

        MatrixXd batch_data(batch_size, 784);
        MatrixXd label(batch_size, 1);
        ifstream file(data_dir);

        if(file.is_open()) {
            for (int i = 0; i < batch_num * batch_size + 1; i++){
                string line;
                getline(file, line);
            }
            int row = 0;
            while(row < batch_size) {
                string line;
                if(!getline(file, line))
                    // Handle Error if file ends before all rows are read
                    break;

                stringstream lineStream(line);
                string cell;
                for (int col = 0; col < 785; ++col){
                    if(!getline(lineStream, cell, ','))
                        // Handle error if row ends before all columns are read
                        break;
                    if (col == 0) {
                        label(row, col) = static_cast<int>(stod(cell));
                    } else
                        batch_data(row, col - 1) = stod(cell) / 255;
                }
                row++;
            }
        }else {
            cout << "Cannot open data file" << endl;
        }
        MatrixXd one_hot_label = MatrixXd::Zero(batch_size, 10);
        for(int i = 0; i < label.rows(); i++){
            one_hot_label(i, static_cast<int>(label(i, 0))) = 1.0;
        }
        return make_tuple(batch_data, one_hot_label);
    }

    int countLines(const string &filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Failed to open the file: " << filename << std::endl;
            return 0;
        }

        int lineCount = 0;
        std::string line;
        while (std::getline(file, line)) {
            lineCount++;
        }

        file.close();

        return lineCount;
    }
};

class utils {
public:
    static void drawLine(RenderWindow &window, sf::Vector2f point1, sf::Vector2f point2,
                         sf::Color fillColor, sf::Color fillColor2, double hightLightPercent) {
        float lineWidth = 1.0f;  // Width of the line

        sf::Vector2f direction = point2 - point1;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265f;

        sf::RectangleShape rectangle1;
        rectangle1.setSize(sf::Vector2f(length * hightLightPercent, lineWidth));
        rectangle1.setPosition(point1);
        rectangle1.setOrigin(0, lineWidth * hightLightPercent);
        rectangle1.setFillColor(fillColor2);
        rectangle1.setRotation(angle);

        sf::RectangleShape rectangle2;
        rectangle2.setSize(sf::Vector2f(length * hightLightPercent, lineWidth));
        rectangle2.setPosition(point2);
        rectangle2.setOrigin(0, lineWidth * (1- hightLightPercent));
        rectangle2.setFillColor(fillColor);
        rectangle2.setRotation(angle+180);

        window.draw(rectangle1);
        window.draw(rectangle2);

    }
};

#endif //NEURALVISUALIZER_UTILS_H
