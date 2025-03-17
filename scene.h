#pragma once
#include"easyx.h"
#include"camera.h"

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	virtual void on_enter() {};//进入场景的初始化逻辑
	virtual void on_update(int delta) {};//处理数据
	virtual void on_draw(const camera& camera) {};//渲染绘图
	virtual void on_input(const ExMessage& msg) {};//场景处理玩家输入
	virtual void on_exit() {};//退出场景的卸载逻辑

private:

};