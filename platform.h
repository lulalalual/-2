#pragma once
#include"util.h"
#include"camera.h"

extern bool is_debug;

class Platform
{
public:
	struct CollisionShape
	{
		float y;//ƽ̨����ֱ����λ��
		float left, right;//ƽ̨��ˮƽ����
	};
	//��ײ����
public:
	CollisionShape shape;
	//���ݼ�⣨���ϣ�
	//�ͻ�ͼ�����£�
	IMAGE* img = nullptr;
	POINT render_position = { 0 };//��Ⱦλ��

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