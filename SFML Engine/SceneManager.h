#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <memory>
#include <map>

#include "Scene.h"
#include "SceneIncludes.h"
#include "SceneEnumeration.h"

class SceneManager
{
	// Поля
	sf::RenderWindow &window;
	std::map<SceneEnum, std::shared_ptr<Scene>> sceneMap;
	std::shared_ptr<Scene> currentScene;

	

public:
	// Конструктор
	SceneManager(sf::RenderWindow &window)
	: window(window)
	{
		// Маппинг всех сцен
		sceneMap.emplace(SceneEnum::startup, std::shared_ptr<Scene_Startup>());
		sceneMap.emplace(SceneEnum::hello, std::shared_ptr<Scene_Hello>());

		// Загрузка изначальной сцены 
		loadScene(SceneEnum::hello); // Для теста
		loadScene(SceneEnum::startup);
		setCurrentScene(SceneEnum::startup);
	}

	// Загрузка сцены
	void loadScene(const SceneEnum &sceneName)
	{
		switch (sceneName)
		{
			case SceneEnum::startup:
			{
				sceneMap.at(SceneEnum::startup) = std::make_shared<Scene_Startup>(window);
				break;
			}
			case SceneEnum::hello:
			{
				sceneMap.at(SceneEnum::hello) = std::make_shared<Scene_Hello>(window);
				break;
			}
		}
	}

	// Освобождение сцены
	void unloadScene(const SceneEnum &sceneName)
	{
		sceneMap.at(sceneName) = nullptr;
	}

	// currentScene
	std::shared_ptr<Scene>& getCurrentScene()
	{
		return currentScene;
	}
	void setCurrentScene(const SceneEnum &sceneName)
	{
		currentScene = sceneMap.at(sceneName);
	}
};