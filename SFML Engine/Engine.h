#pragma once
#pragma comment(lib, "opengl32")
#pragma comment(lib, "freetype")
#pragma comment(lib, "winmm.lib")
#include <string>
#include <memory>
#include <map>

#include "SceneManager.h"

class Engine
{
    // Поля
    sf::RenderWindow window;
    SceneManager sceneManager;


    // Обработка кода обновления сцены
    void processSceneUpdateCode(const SceneUpdateCode &updateCode)
    {
        if (updateCode == SceneUpdateCode::EXIT)
            processSceneUpdateCodeRest(sceneManager.getCurrentScene()->exitCodeAction());
        else
            processSceneUpdateCodeRest(updateCode);
    }
    void processSceneUpdateCodeRest(const SceneUpdateCode &updateCode)
    {
        switch (updateCode)
        {
            case SceneUpdateCode::EXIT:
            {
                window.close();
                break;
            }
            case SceneUpdateCode::RUNNING:
            {
                break;
            }
            case SceneUpdateCode::LOAD_SCENE:
            {
                sceneManager.loadScene(sceneManager.getCurrentScene()->getNextSceneName());
                break;
            }
            case SceneUpdateCode::SWITCH_SCENE:
            {
                sceneManager.setCurrentScene(sceneManager.getCurrentScene()->getNextSceneName());
                break;
            }
            case SceneUpdateCode::LOAD_AND_SWITCH_SCENE:
            {
                SceneEnum tmpName = sceneManager.getCurrentScene()->getNextSceneName();
                sceneManager.loadScene(tmpName);
                sceneManager.setCurrentScene(tmpName);
                break;
            }
        }
    }


    // Обработка событий
    void processEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
                case sf::Event::KeyPressed:
                {
                    sceneManager.getCurrentScene()->handlePlayerInput(event.key.code, true);
                    break;
                }
                case sf::Event::KeyReleased:
                {
                    sceneManager.getCurrentScene()->handlePlayerInput(event.key.code, false);
                    break;
                }
            }
        }
    }


public:
    // Конструктор с параметрами
    Engine(unsigned int width, unsigned int height, std::string title)
    : window(sf::VideoMode(width, height), title)
    , sceneManager(window)
    {
        window.setVerticalSyncEnabled(true);
    }


    // Запуск цикла игры
    void run()
    {
        const sf::Time TimePerFrame = sf::seconds(1.f / 60);
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        while (window.isOpen())
        {
            processEvents();
            timeSinceLastUpdate += clock.restart();
            while (timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;
                processEvents();
                processSceneUpdateCode(sceneManager.getCurrentScene()->update(TimePerFrame));
            }
            sceneManager.getCurrentScene()->render();
        }
    }
};