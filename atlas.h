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

	//LPCTSTR ����ָ�볣��TCHAR�ַ�������ƣ�ָ�����ַ������ָ�룬����ò�����һ�������޸ĵ��ַ���
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
	//����Ѽ��ص�ͼƬ����

	int get_size()
	{
		return (int)img_list.size();
	}
	//������ȡͼ����ͼƬ������

	IMAGE* get_image(int idx)
	{
		if (idx < 0 || idx >= img_list.size())
		{
			return nullptr;
		}
		return &img_list[idx];
	}
	//��ȡʵ����Ⱦ�Ķ���֡

	void add_image(const IMAGE& img)
	{
		img_list.push_back(img);
	}

private:
	vector<IMAGE> img_list;
};