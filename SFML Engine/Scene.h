#pragma once
#include <filesystem>
#include <string>
#include <SFML/Graphics.hpp>
#include "SceneEnumeration.h"

enum class SceneUpdateCode
{
    EXIT,
    RUNNING,
    LOAD_SCENE,
    SWITCH_SCENE,
    LOAD_AND_SWITCH_SCENE,
};

class Scene
{
protected:
    // Поля
    std::map<sf::Keyboard::Key, bool> keysMap;
    sf::RenderWindow &targetWindow;

    SceneEnum previousSceneName;
    SceneEnum nextSceneName;

    /*
    // Получение строки с конфигурацией
    std::string getConfigurationString(std::string name)
    {

    }

    // Парсинг строки конфигурации
    
    virtual void parseConfiguration() = 0;
    */

public:
    // Конструктор
    Scene(sf::RenderWindow& window)
    : targetWindow(window)
    , previousSceneName(SceneEnum::none)
    , nextSceneName(SceneEnum::none)
    {}

    // Обработка нажатия клавиш
    virtual void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) = 0;

    // Обновление логики
    virtual SceneUpdateCode update(const sf::Time& deltaTime) = 0;

    // Отрисовка кадра
    virtual void render() = 0;

    // SceneUpdateCode
    virtual SceneUpdateCode exitCodeAction() = 0;

    // previousSceneName
    SceneEnum getPreviousSceneName()
    {
        return previousSceneName;
    }
    void setPreviousSceneName(const SceneEnum& sceneName)
    {
        previousSceneName = sceneName;
    }

    // nextSceneName
    SceneEnum getNextSceneName()
    {
        return nextSceneName;
    }
    void setNextSceneName(const SceneEnum& sceneName)
    {
        nextSceneName = sceneName;
    }
};