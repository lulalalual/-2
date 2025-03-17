#pragma once
#include"scene.h"

extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* select_scene;

class SceneManager
{
public:
	enum class SceneType
	{
		Menu,
		Game,
		Selector
	};

public:
	SceneManager() = default;
	~SceneManager() = default;

	void on_update(int delta)
	{
		current_scene->on_update(delta);
	}

	void on_draw(const camera& camera)
	{
		current_scene->on_draw(camera);
	}

	void on_input(const ExMessage& msg)
	{
		current_scene->on_input(msg);
	}

	void set_current_scene(Scene* scene)
	{
		current_scene = scene;
		current_scene->on_enter();
	}

	void switch_to(SceneType type)
	{
		current_scene->on_exit();
		switch (type)
		{
		case SceneManager::SceneType::Menu:
			current_scene = menu_scene;
			break;
		case SceneManager::SceneType::Game:
			current_scene = game_scene;
			break;
		case SceneManager::SceneType::Selector:
			current_scene = select_scene;
			break;
		default:
			break;
		}
		current_scene->on_enter();
	}
private:
	Scene* current_scene = nullptr;
};