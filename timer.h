#pragma once
#include"functional"
class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart()
	{
		pass_time = 0;
		shotted = false;
	}
	//重置定时器状态
	void set_wait_time(int val)
	{
		wait_time = val;
	}

	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}

	void set_callback(std::function<void()>callback)
	{
		this->callback = callback;
	}

	void pause()
	{
		paused = true;
	}

	void resume()
	{
		paused = false;
	}

	void on_up_date(int delta)
	{
		if (paused) return;
		pass_time += delta;
		if (pass_time >= wait_time)
		{
			if ((!one_shot || (one_shot && !shotted)) && callback)
				//如果定时器不是单次触发，或者单次触发且没有被触发过，同时callback也得有效
			{
				callback();
			}
			shotted = true;
			pass_time = 0;
		}
	}

private:
	int pass_time = 0;//已过时间
	int wait_time = 0;//等待时间
	bool paused = false;//是否暂停
	bool shotted = false;//是否触发
	bool one_shot = false;//单次触发
	std::function<void()> callback;//触发回调
};