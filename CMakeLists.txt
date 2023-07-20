cmake_minimum_required(VERSION 3.23)
project(NeuralVisualizer)

set(CMAKE_CXX_STANDARD 14)

add_executable(NeuralVisualizer main.cpp DeepLearning/Tensor.cpp DeepLearning/Tensor.h DeepLearning/Dependency.h DeepLearning/Parameter.h DeepLearning/MLP.cpp DeepLearning/MLP.h DeepLearning/Layers.cpp DeepLearning/Layers.h DeepLearning/Activations.cpp DeepLearning/Activations.h utils.h DeepLearning/Loss.h DeepLearningV2/MLP.h)
