#pragma once
#include"atlas.h"
#include"easyx.h"
#include"util.h"
#include"functional"
#include"camera.h"

class Animation
{
public:
	Animation() = default;
	~Animation() = default;

	void reset()
	{
		timer = 0;
		idx_frame = 0;
	}

	void set_atlas(Atlas* new_atlas)
	{
		reset();
		atlas = new_atlas; 
	}

	void set_loop(bool flag)
	{
		is_loop = flag;
	}

	void set_interval(int ms)
	{
		interval = ms;
	}

	int get_idx_frame()
	{
		return idx_frame;
	}
	//��ȡ֡����
	IMAGE* get_frame()
	{
		return atlas->get_image(idx_frame);
	}
	//��ȡ֡ͼƬ
	bool check_finished()
	{
		if (is_loop) return false;
		return(idx_frame == atlas->get_size() - 1);//֡��������ͼ����β��
	}

	void on_update(int delta)
	{
		timer += delta;
		if (timer >= interval)
		{
			timer = 0;
			idx_frame++;
			if (idx_frame >= atlas->get_size())
			{
				idx_frame = is_loop ? 0 : atlas->get_size() - 1;
				if (!is_loop && callback)
					callback();
				//���֡��������ͼ����β�������Ҷ���û������ѭ�������һص��������ڣ��Ǿ�ִ�лص�������ģ��
			}
		}
	}

	void on_draw(const camera& camera,int x, int y)const
	{
		putimage_alpha(camera,x, y, atlas->get_image(idx_frame));
	}

	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}

private:
	int timer = 0;//��ʱ��
	int interval = 0;//֡���
	int idx_frame = 0;//֡����
	bool is_loop = true;//�Ƿ�ѭ��
	Atlas* atlas = nullptr;
	std::function<void()> callback;//һ���������󣬷���ֵΪvoid��û���κβ���
};