#pragma once
#include <string>

enum class SceneEnum
{
	none,
	startup,
	hello
};

std::string sceneEnumToString(SceneEnum sceneEnum)
{
	switch (sceneEnum)
	{
		case SceneEnum::startup:
			return "startup";

		case SceneEnum::hello:
			return "hello";

		default:
			return "none";
	}
}