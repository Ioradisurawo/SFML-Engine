#pragma once

#include <Filesystem>
#include <fstream>
#include <map>
#include <iostream>
#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager
{
	// Папка с ресурсами
	std::filesystem::path resourceDirectory;
	
	// Наименования загруженных ресурсов
	std::list<std::filesystem::path> loadedResources;

	// Загруженные ресурсы
	std::map<std::filesystem::path, std::unique_ptr<sf::Image>>			mapImage;
	std::map<std::filesystem::path, std::unique_ptr<sf::Texture>>		mapTexture;
	std::map<std::filesystem::path, std::unique_ptr<sf::Font>>			mapFont;
	std::map<std::filesystem::path, std::unique_ptr<sf::SoundBuffer>>	mapSoundBuffer;
	std::map<std::filesystem::path, std::unique_ptr<std::string>>		mapMusic;

	// Для логирования
	template<typename T1, typename T2>
	void coutMessage(const std::string &action, const T1 &param1, const T2 &param2)
	{
		std::cout << "> " << action << " " << param1 << ": " << param2 << std::endl;
	}

	// Совпадение расширения файла
	bool matchesExtension(const std::string& extension, const std::string& category)
	{
		if (category == "audio")
		{
			return extension == ".ogg" 
				|| extension == ".mp3" 
				|| extension == ".wav" 
				|| extension == ".flac";
		}
		else if (category == "image")
		{
			return extension == ".png"
				|| extension == ".jpg"
				|| extension == ".gif";
		}
		else
		{
			return false;
		}
	}

	// Загрузка ресурса по имени файла
	void loadResource(const std::string& queryResourceName, std::filesystem::path path)
	{
		for (auto& i : std::filesystem::directory_iterator(path))
		{
			if (i.is_directory())
			{
				loadResource(queryResourceName, i.path());
			}
			else if (i.path().filename() == queryResourceName)
			{
				std::string currentParentName = i.path().parent_path().filename().string();
				std::string extension = i.path().extension().string();

				if (currentParentName == "Music" && matchesExtension(extension, "audio"))
				{
					mapMusic.emplace(i.path().filename(), std::make_unique<std::string>(i.path().string()));

					loadedResources.push_back(i.path().filename());
					coutMessage("LOADED", currentParentName, i.path().filename());
				}
				else if (currentParentName == "Sound" && matchesExtension(extension, "audio"))
				{
					sf::SoundBuffer soundBuffer;
					soundBuffer.loadFromFile(i.path().string());
					mapSoundBuffer.emplace(i.path().filename(), std::make_unique<sf::SoundBuffer>(soundBuffer));

					loadedResources.push_back(i.path().filename());
					coutMessage("LOADED", currentParentName, i.path().filename());
				}
				else if (currentParentName == "Image" && matchesExtension(extension, "image"))
				{
					sf::Image image;
					image.loadFromFile(i.path().string());
					mapImage.emplace(i.path().filename(), std::make_unique<sf::Image>(image));

					loadedResources.push_back(i.path().filename());
					coutMessage("LOADED", currentParentName, i.path().filename());
				}
				else if (currentParentName == "Texture" && matchesExtension(extension, "image"))
				{
					sf::Texture image;
					image.loadFromFile(i.path().string());
					mapTexture.emplace(i.path().filename(), std::make_unique<sf::Texture>(image));

					loadedResources.push_back(i.path().filename());
					coutMessage("LOADED", currentParentName, i.path().filename());
				}
				else if (currentParentName == "Font" && (extension == ".TTF"))
				{
					sf::Font font;
					font.loadFromFile(i.path().string());
					mapFont.emplace(i.path().filename(), std::make_unique<sf::Font>(font));

					loadedResources.push_back(i.path().filename());
					coutMessage("LOADED", currentParentName, i.path().filename());
				}
			}
		}
	}
public:

	// Конструктор с параметром
	ResourceManager(const std::filesystem::path &resourceDirectory)
	: resourceDirectory(resourceDirectory)
	{
		loadResource("Anon.png");
		releaseResource("Anon.png");
	}

	// Загрузка ресурса
	void loadResource(const std::string& queryResourceName)
	{
		loadResource(queryResourceName, resourceDirectory);
	}

	// Освобождение ресурса
	void releaseResource(const std::string& queryResourceName)
	{
		// string to path
		// https://stackoverflow.com/questions/43114174/convert-a-string-to-std-filesystem-path
		std::filesystem::path queryResourceFile = std::filesystem::u8path(queryResourceName);
		try
		{
			auto extension = queryResourceFile.extension().string();

			if (matchesExtension(extension, "audio"))
			{
				// Sound
				if (mapSoundBuffer.count(queryResourceFile) > 0)
				{
					mapSoundBuffer.at(queryResourceFile).release();
					coutMessage("UNLOADED", "Sound", queryResourceName);

				}
				// Music
				else if(mapMusic.count(queryResourceFile) > 0)
				{
					mapMusic.at(queryResourceFile).release();
					coutMessage("UNLOADED", "Music", queryResourceName);

				}
			}
			else if (matchesExtension(extension, "image"))
			{
				// Image
				if (mapImage.count(queryResourceFile) > 0)
				{
					mapImage.at(queryResourceFile).release();
					coutMessage("UNLOADED", "Image", queryResourceName);
				}
				// Texture
				else if (mapTexture.count(queryResourceFile) > 0)
				{
					mapTexture.at(queryResourceFile).release();
					coutMessage("UNLOADED", "Texture", queryResourceName);

				}
			}
			else if (extension == ".TTF")
			{
				// Font
				if (mapSoundBuffer.count(queryResourceFile) > 0)
				{
					mapSoundBuffer.at(queryResourceFile).release();
					coutMessage("UNLOADED", "Font", queryResourceName);
				}
			}
			else
			{
				coutMessage("ERROR ", "UNKNOWN EXTENSION", queryResourceName);
			}
		}
		catch (std::exception)
		{

		}
	}

	// Геттеры
	std::string& getMusic(const std::string filename) // Сомнительный момент
	{
		return *mapMusic.at(filename);
	}
	sf::SoundBuffer& getSound(const std::string filename)
	{
		return *mapSoundBuffer.at(filename);
	}
	sf::Image& getImage(const std::string filename)
	{
		return *mapImage.at(filename);
	}
	sf::Texture& getTexture(const std::string filename)
	{
		return *mapTexture.at(filename);
	}
	sf::Font& getFont(const std::string filename)
	{
		return *mapFont.at(filename);
	}
};