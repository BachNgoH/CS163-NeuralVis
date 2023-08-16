cmake_minimum_required(VERSION 3.23)
project(NeuralVisualizer)

set(CMAKE_CXX_STANDARD 14)

add_executable(NeuralVisualizer main.cpp DeepLearning/Tensor.cpp DeepLearning/Tensor.h DeepLearning/Dependency.h DeepLearning/Parameter.h DeepLearning/MLP.cpp DeepLearning/MLP.h DeepLearning/Layers.cpp DeepLearning/Layers.h DeepLearning/Activations.cpp DeepLearning/Activations.h utils.h DeepLearning/Loss.h DeepLearningV2/MLP.h UI/MainMenu.cpp UI/MainMenu.h UI/Engine.h UI/ProjectPage.cpp UI/ProjectPage.h UI/TextBox.h UI/VisualizingPage.h UI/VisualizingPage.cpp UI/InferencePage.cpp UI/InferencePage.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(NeuralVisualizer sfml-system sfml-window sfml-graphics sfml-audio)