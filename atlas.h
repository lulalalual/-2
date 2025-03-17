#pragma once
#include"vector"
#include"easyx.h"
#include"iostream"
#include"string"
using namespace std;


class Atlas
{
public:
	Atlas() = default;
	~Atlas() = default;

	//LPCTSTR ：长指针常量TCHAR字符串，简称：指向常量字符数组的指针，表面该参数是一个不可修改的字符串
	void load_from_file(LPCTSTR path_template, int num)
	{
		img_list.clear();
		img_list.resize(num);

		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path_template, i + 1);
			loadimage(&img_list[i], path_file);
		}
	}

	void clear()
	{
		img_list.clear();
	}
	//清空已加载的图片对象

	int get_size()
	{
		return (int)img_list.size();
	}
	//用来获取图集中图片的数量

	IMAGE* get_image(int idx)
	{
		if (idx < 0 || idx >= img_list.size())
		{
			return nullptr;
		}
		return &img_list[idx];
	}
	//获取实际渲染的动画帧

	void add_image(const IMAGE& img)
	{
		img_list.push_back(img);
	}

private:
	vector<IMAGE> img_list;
};