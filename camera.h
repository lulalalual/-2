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
		//�������λ���ڶ���ǿ��Ϊ�뾶��Բ��������ã�����ǿ��ǰ�˵��Ǹ����������˵�λԲ�ķ�Χ��
		// ȡֵΪ-1.0��1.0֮��ĸ�����
	}

private:
	Vector2 position;//�����λ��
	Timer timer_shake;//�����������ʱ��
	bool is_shaking = false;//������Ƿ����ڶ���
	float shaking_strength = 0;//�������������
};