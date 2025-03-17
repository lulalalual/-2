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
	//获取帧索引
	IMAGE* get_frame()
	{
		return atlas->get_image(idx_frame);
	}
	//获取帧图片
	bool check_finished()
	{
		if (is_loop) return false;
		return(idx_frame == atlas->get_size() - 1);//帧索引到达图集的尾部
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
				//如果帧索引到达图集的尾部，并且动画没有设置循环播放且回调函数存在，那就执行回调函数的模型
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
	int timer = 0;//计时器
	int interval = 0;//帧间隔
	int idx_frame = 0;//帧索引
	bool is_loop = true;//是否循环
	Atlas* atlas = nullptr;
	std::function<void()> callback;//一个函数对象，返回值为void且没有任何参数
};