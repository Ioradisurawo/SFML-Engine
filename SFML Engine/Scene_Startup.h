#pragma once
#include "Scene.h"
class Scene_Startup : public Scene
{
	sf::RectangleShape startupShape;
	sf::Time timer;

public:
	// Конструктор
	Scene_Startup(sf::RenderWindow& window)
	: Scene(window)
	{
		startupShape.setSize(sf::Vector2f(720.f, 480.f));
		startupShape.setFillColor(sf::Color::White);
	}

	// Обработка нажатия клавиш
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) override
	{

	}

	// Обновление логики
	SceneUpdateCode update(const sf::Time& deltaTime) override
	{
		if (startupShape.getFillColor().a == 0)
		{
			return SceneUpdateCode::EXIT;
		}
		else
		{
			timer += deltaTime;
			startupShape.setFillColor(sf::Color(255, 255, 255, startupShape.getFillColor().a - 0.1));
			return SceneUpdateCode::RUNNING;
		}
	}

	// Отрисовка кадра
	void render() override
	{
		targetWindow.clear();
		targetWindow.draw(startupShape);
		targetWindow.display();
	}

	// SceneUpdateCode
	virtual SceneUpdateCode exitCodeAction() override
	{
		this->setNextSceneName(SceneEnum::hello);
		return SceneUpdateCode::LOAD_AND_SWITCH_SCENE;
	}
};