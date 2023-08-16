#include <iostream>
#include "Eigen/Dense"
#include "UI/Engine.h"

using namespace std;

int main() {
    srand((unsigned)time(NULL));

    VisualizerEngine visualizer;
    visualizer.visualize();

    return 0;
}
