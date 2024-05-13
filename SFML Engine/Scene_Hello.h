#pragma once
#include "Scene.h"

class Scene_Hello : public Scene
{
    sf::CircleShape playerCircle;

public:
    // Конструктор
    Scene_Hello(sf::RenderWindow& window) : Scene(window)
    , playerCircle(16.f)
    {
        keysMap.emplace(sf::Keyboard::Key::W, false);
        keysMap.emplace(sf::Keyboard::Key::A, false);
        keysMap.emplace(sf::Keyboard::Key::S, false);
        keysMap.emplace(sf::Keyboard::Key::D, false);
        keysMap.emplace(sf::Keyboard::Key::Escape, false);

        playerCircle.setFillColor(sf::Color::Yellow);
    }

    // Обработка нажатия клавиш
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) override
    {
        // Как сделать это более грамотно?
        try
        {
            keysMap.at(key) = isPressed;
        }
        catch(std::exception)
        {

        }
    }

    // Обновление логики
    SceneUpdateCode update(const sf::Time& deltaTime) override
    {
        if (keysMap.at(sf::Keyboard::Key::Escape))
            return SceneUpdateCode::EXIT;

        sf::Vector2f movement(0.f, 0.f);

        if (keysMap.at(sf::Keyboard::Key::W))
            movement.y -= 15.f;
        if (keysMap.at(sf::Keyboard::Key::A))
            movement.x -= 15.f;
        if (keysMap.at(sf::Keyboard::Key::S))
            movement.y += 15.f;
        if (keysMap.at(sf::Keyboard::Key::D))
            movement.x += 15.f;

        playerCircle.move(movement * deltaTime.asSeconds());

        return SceneUpdateCode::RUNNING;
    }

    // Отрисовка кадра
    void render() override
    {
        targetWindow.clear();
        targetWindow.draw(playerCircle);
        targetWindow.display();
    }

    // SceneUpdateCode
    virtual SceneUpdateCode exitCodeAction() override
    {
        return SceneUpdateCode::EXIT;
    }
};