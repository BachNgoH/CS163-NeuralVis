//
// Created by LENOVO on 7/21/2023.
//
#pragma once

#ifndef NEURALVISUALIZER_ENGINE_H
#define NEURALVISUALIZER_ENGINE_H

#include <vector>
#include <string>
#include "MainMenu.h"
#include "ProjectPage.h"
#include "VisualizingPage.h"
#include "../DeepLearningV2/MLP.h"
#include "../utils.h"
#include "InferencePage.h"

using namespace std;

class VisualizerEngine {
public:
    vector<string> projects;

    VisualizerEngine() {
        projects.emplace_back("MNIST Visualization");
    }

    int argmax(MatrixXd x, int col){
        int maxIdx = 0;
        double maxVal = x(0, col);
        for(int i = 1; i < x.rows(); i++){
            if(x(i, col) > maxVal){
                maxVal = x(i, col);
                maxIdx = i;
            }
        }
        return maxIdx;
    }

    double get_accuracy(MatrixXd pred, MatrixXd label){
        double acc = 0.0;
        for(int i = 0; i < pred.cols(); i++){
            acc += argmax(pred, i) == argmax(label, i);
        }
        return acc;
    }

    void visualize() {
        RenderWindow window(VideoMode(1440, 1024), "NeurlVis", Style::Titlebar | Style::Close);
        MainMenu mainPage(projects);
        ProjectPage projectPage;
        VisualizingPage visualizingPage;
        InferencePage inferencePage;

        int visualizingMode = 0;
        int choosenProject = -1;

        int batch_size = 32;
        int batch_idx = 0;
        MNISTDataset dataset(batch_size);

        double epoch_loss = 0.0;
        double epoch_acc = 0.0;

        double min_loss = 200.;
        double max_acc = 0.0;

        int epoch = 0;
        int inferStep = 0;

        while(window.isOpen()){
            Event event;
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
            }

            window.clear(Color(36,35,35));
            if(visualizingMode == 0)
                mainPage.render(window, event, visualizingMode, choosenProject);
            else if(visualizingMode == 1)
                projectPage.render(window, event, visualizingMode, projects[choosenProject]);
            else if(visualizingMode == 2) {
                auto batch_data = dataset.loadData(batch_idx);
                MatrixXd x = get<0>(batch_data).transpose();
                MatrixXd label = get<1>(batch_data).transpose();

                vector<int> layerNodes = projectPage.nodesPerLayer;
                int maxEpoch = stoi(projectPage.epochsText.getText());
                layerNodes.insert(layerNodes.begin(), 784);
                layerNodes.push_back(10);
                if (epoch == 0 && batch_idx == 0)
                    visualizingPage.model.init_model(layerNodes, std::stof(projectPage.learningRateText.getText()));
                visualizingPage.epoch = epoch;
                visualizingPage.loss = epoch_loss / ((batch_idx + 1) * batch_size);
                visualizingPage.acc = (epoch_acc / ((batch_idx + 1) * batch_size)) * 100;
                visualizingPage.progress = batch_idx / (static_cast<double>(dataset.num_lines) / static_cast<double>(dataset.batch_size));

                visualizingPage.render(window, event, batch_data, visualizingMode);


                // CODE TO TRAIN MODEL
                if (epoch < maxEpoch && !visualizingPage.pauseTraining) {

                    MatrixXd y_hat = visualizingPage.model.forward(x);
                    double loss = visualizingPage.model.backward(label);
                    double accuracy = get_accuracy(y_hat, label);
                    epoch_loss += loss;
                    epoch_acc += accuracy;
                    batch_idx += 1;

                    if (batch_idx > dataset.num_lines / dataset.batch_size) {
                    // if (batch_idx > 30) {
                        batch_idx = 0;
                        cout << "EPOCH [" << epoch << "] " << "LOSS [" << epoch_loss / dataset.num_lines << "], ACC ["
                             << epoch_acc / dataset.num_lines << "]" << endl;
                        epoch += 1;

                        if(epoch_loss < min_loss)
                            min_loss = epoch_loss;
                        if (epoch_acc > max_acc)
                            max_acc = epoch_acc;
                        epoch_loss = 0.0;
                        epoch_acc = 0.0;
                    }
                }else {
                    epoch_acc = max_acc / dataset.num_lines;
                    epoch_loss = min_loss / dataset.num_lines;
                    visualizingPage.pauseTraining = true;
                }
            }else if (visualizingMode == 3) {
                vector<int> layerNodes = projectPage.nodesPerLayer;
                layerNodes.insert(layerNodes.begin(), 784);
                layerNodes.push_back(10);

                if(inferStep == 0) {
                    inferencePage.model.init_model(layerNodes, 0.01);
                    inferencePage.model.load_weights("../checkpoint/model_weights.bin");
                    inferStep += 1;
                }

                inferencePage.render(window, event, visualizingMode);

            }
            window.display();
        }
    }
};

#endif //NEURALVISUALIZER_ENGINE_H
