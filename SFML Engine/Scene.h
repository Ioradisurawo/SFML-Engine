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
    // ����
    std::map<sf::Keyboard::Key, bool> keysMap;
    sf::RenderWindow &targetWindow;

    SceneEnum previousSceneName;
    SceneEnum nextSceneName;

    /*
    // ��������� ������ � �������������
    std::string getConfigurationString(std::string name)
    {

    }

    // ������� ������ ������������
    
    virtual void parseConfiguration() = 0;
    */

public:
    // �����������
    Scene(sf::RenderWindow& window)
    : targetWindow(window)
    , previousSceneName(SceneEnum::none)
    , nextSceneName(SceneEnum::none)
    {}

    // ��������� ������� ������
    virtual void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) = 0;

    // ���������� ������
    virtual SceneUpdateCode update(const sf::Time& deltaTime) = 0;

    // ��������� �����
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