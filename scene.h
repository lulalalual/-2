#pragma once
#include"easyx.h"
#include"camera.h"

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	virtual void on_enter() {};//���볡���ĳ�ʼ���߼�
	virtual void on_update(int delta) {};//��������
	virtual void on_draw(const camera& camera) {};//��Ⱦ��ͼ
	virtual void on_input(const ExMessage& msg) {};//���������������
	virtual void on_exit() {};//�˳�������ж���߼�

private:

};