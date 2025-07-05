#pragma once

#include <Engine/Scene/Scene.h>

class Level : public Scene {

public:
    Level();
    Level(std::unordered_map<std::string, std::shared_ptr<GameObject>> objects);
    ~Level();


};