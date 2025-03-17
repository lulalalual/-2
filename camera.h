#pragma once
#include"vector2.h"
#include"timer.h"

class camera
{
public:
	camera()
	{
		timer_shake.set_one_shot(true);
		timer_shake.set_callback([&]()
			{
				is_shaking = false;
				reset();
			});
	}

	~camera() = default;

	void shake(float strength, int duration)
	{
		is_shaking = true;
		shaking_strength = strength;

		timer_shake.set_wait_time(duration);
		timer_shake.restart();
	}

	const Vector2& get_position()const
	{
		return position;
	}

	void reset()
	{
		position.x = 0;
		position.y = 0;
	}

	void on_update(int delta)
	{
		timer_shake.on_up_date(delta);

		if (is_shaking)
		{
			position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
			position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
		}
		//将摄像机位置在抖动强度为半径的圆内随机设置，抖动强度前乘的那个东西描述了单位圆的范围，
		// 取值为-1.0到1.0之间的浮点数
	}

private:
	Vector2 position;//摄像机位置
	Timer timer_shake;//摄像机抖动定时器
	bool is_shaking = false;//摄像机是否正在抖动
	float shaking_strength = 0;//摄像机抖动幅度
};