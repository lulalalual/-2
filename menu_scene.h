#pragma once
#include"scene.h"
#include"scene_manager.h"
#include"iostream"
#include"atlas.h"
#include"animation.h"
#include"camera.h"
using namespace std;

extern Atlas atlas_peashooter_run_right;

extern SceneManager scene_manager;//声明外部的对象

extern IMAGE img_menu_background;

class MenuScene :public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	 void on_enter()
	 {
		 mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
	 };//进入场景的初始化逻辑
	
	 void on_draw(const camera& camera)
	 {
		 putimage(0, 0, &img_menu_background);
	 };//渲染绘图
	 
	 void on_input(const ExMessage& msg)
	 {
		 if (msg.message == WM_KEYUP)
		 {
			 mciSendString(_T("play ui_confirm repeat from 0"), NULL, 0, NULL);
			 scene_manager.switch_to(SceneManager::SceneType::Selector);
		 }
	 };//场景处理玩家输入
};