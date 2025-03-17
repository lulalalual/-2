#pragma once
#include"util.h"
#include"camera.h"

extern bool is_debug;

class Platform
{
public:
	struct CollisionShape
	{
		float y;//平台的竖直坐标位置
		float left, right;//平台的水平方向
	};
	//碰撞外形
public:
	CollisionShape shape;
	//数据监测（以上）
	//和绘图（以下）
	IMAGE* img = nullptr;
	POINT render_position = { 0 };//渲染位置

public:
	Platform() = default;
	~Platform() = default;

	void on_draw(const camera& camera) const
	{
		putimage_alpha(camera, render_position.x, render_position.y, img);

		if (is_debug)
		{
			setlinecolor(RGB(255, 0, 0));
			line(camera, (int)shape.left, (int)shape.y, (int)shape.right, (int)shape.y);
		}
	}
};