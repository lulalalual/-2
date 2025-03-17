#pragma once
#include"scene.h"
#include"scene_manager.h"
#include"animation.h"
#include"peashooter_player.h"
#include"sunflower_player.h"
#include"player_id.h"

extern Player* player_1;
extern Player* player_2;

extern IMAGE img_vs;//vs������ͼƬ
extern IMAGE img_1p;//1p�ı�ͼƬ
extern IMAGE img_2p;//2p�ı�ͼƬ
extern IMAGE img_1p_desc;//1p��λ����ͼƬ
extern IMAGE img_2p_desc;//2p��λ����ͼƬ
extern IMAGE img_gravestone_left;//�����Ĺ��
extern IMAGE img_gravestone_right;//���ҵ�Ĺ��
extern IMAGE img_selector_tip;//ѡ��ɫ��������ʾ��Ϣ�ı�ͼƬ
extern IMAGE img_selector_background;//ѡ��ɫ���汳��ͼ

extern IMAGE img_1p_selector_btn_idle_left;//1p����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1p_selector_btn_idle_right;//1p����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1p_selector_btn_down_left;//1p����ѡ��ť����״̬ͼƬ
extern IMAGE img_1p_selector_btn_down_right;//1p����ѡ��ť����״̬ͼƬ

extern IMAGE img_2p_selector_btn_idle_left;//2p����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_2p_selector_btn_idle_right;//2p����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_2p_selector_btn_down_left;//2p����ѡ��ť����״̬ͼƬ
extern IMAGE img_2p_selector_btn_down_right;//2p����ѡ��ť����״̬ͼƬ

extern IMAGE img_peashooter_select_background_left;//ѡ�ǽ��泯������㶹���ֱ���ͼƬ
extern IMAGE img_peashooter_select_background_right;//ѡ�ǽ��泯���ҵ��㶹���ֱ���ͼƬ

extern IMAGE img_sunflower_select_background_left;//ѡ�ǽ��泯��������տ�����ͼƬ
extern IMAGE img_sunflower_select_background_right;//ѡ�ǽ��泯���ұߵ����տ�����ͼƬ

extern Atlas atlas_peashooter_idle_right;//�㶹���ֳ����ҵ�Ĭ�϶���ͼ��
extern Atlas atlas_sunflower_idle_right;//���տ������ҵ�Ĭ�϶���ͼ��

extern IMAGE img_avator_peashooter;//�㶹����ͷ��
extern IMAGE img_avator_sunflower;//���տ�ͷ��

extern SceneManager scene_manager;

extern IMAGE* img_player_1_avatar;
extern IMAGE* img_player_2_avatar;

class SelectorScene :public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	void on_enter()
	{
		animation_peashooter.set_atlas(&atlas_peashooter_idle_right);
		animation_sunflower.set_atlas(&atlas_sunflower_idle_right);
		animation_peashooter.set_interval(100);
		animation_sunflower.set_interval(100);

		static const int OFFSET_X = 50;
		pos_img_vs.x = (getwidth() - img_vs.getwidth()) / 2;
		pos_img_vs.y = (getheight() - img_vs.getheight()) / 2;
		pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
		pos_img_tip.y = getheight() - 125;
		pos_img_1p.x = (getwidth() / 2 - img_1p.getwidth()) / 2 - OFFSET_X;
		pos_img_1p.y = 35;
		pos_img_2p.x = getwidth() / 2 + (getwidth() / 2 - img_2p.getwidth()) / 2 + OFFSET_X;
		pos_img_2p.y = pos_img_1p.y;
		pos_img_1p_desc.x = (getwidth() / 2 - img_1p_desc.getwidth()) / 2 - OFFSET_X;
		pos_img_1p_desc.y = getheight() - 150;
		pos_img_2p_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2p_desc.getwidth()) / 2 + OFFSET_X;
		pos_img_2p_desc.y = pos_img_1p_desc.y;

		pos_img_1p_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X;
		pos_img_1p_gravestone.y = pos_img_1p.y + img_1p.getheight() + 35;
		pos_img_2p_gravestone.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
		pos_img_2p_gravestone.y = pos_img_1p_gravestone.y;

		pos_animation_1p.x = (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 - OFFSET_X;
		pos_animation_1p.y = pos_img_1p_gravestone.y + 80;
		pos_animation_2p.x = getwidth() / 2 + (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 + OFFSET_X;
		pos_animation_2p.y = pos_animation_1p.y;

		pos_img_1p_name.y = pos_animation_1p.y + 155;
		pos_img_2p_name.y = pos_img_1p_name.y;

		pos_1p_selector_btn_left.x = pos_img_1p_gravestone.x - img_1p_selector_btn_idle_left.getwidth();
		pos_1p_selector_btn_left.y = pos_img_1p_gravestone.y + (img_gravestone_right.getheight() - img_1p_selector_btn_idle_left.getheight()) / 2;
		pos_1p_selector_btn_right.x = pos_img_1p_gravestone.x + img_gravestone_right.getwidth();
		pos_1p_selector_btn_right.y = pos_1p_selector_btn_left.y;

		pos_2p_selector_btn_left.x = pos_img_2p_gravestone.x - img_2p_selector_btn_idle_left.getwidth();
		pos_2p_selector_btn_left.y = pos_1p_selector_btn_left.y;
		pos_2p_selector_btn_right.x = pos_img_2p_gravestone.x + img_gravestone_left.getwidth();
		pos_2p_selector_btn_right.y = pos_1p_selector_btn_left.y;
	}

	void on_update(int delta)
	{
		animation_peashooter.on_update(delta);
		animation_sunflower.on_update(delta);

		selector_background_scorll_offset_x += 5;
		if (selector_background_scorll_offset_x >= img_peashooter_select_background_left.getwidth())
		{
			selector_background_scorll_offset_x = 0;
		}
	}

	void on_draw(const camera& camera) 
	{
		IMAGE* img_p1_selector_background = nullptr;
		IMAGE* img_p2_selector_background = nullptr;

		switch (player_type_2)
		{
		case SelectorScene::PlayerType::peashooter:
			img_p1_selector_background = &img_peashooter_select_background_right;
			break;
		case SelectorScene::PlayerType::sunflower:
			img_p1_selector_background = &img_sunflower_select_background_right;
			break;
		default:
			img_p1_selector_background = &img_peashooter_select_background_right;
			break;
		}

		switch (player_type_1)
		{
		case SelectorScene::PlayerType::peashooter:
			img_p2_selector_background = &img_peashooter_select_background_left;
			break;
		case SelectorScene::PlayerType::sunflower:
			img_p2_selector_background = &img_sunflower_select_background_left;
			break;
		default:
			img_p2_selector_background = &img_peashooter_select_background_left;
			break;
		}

		putimage(0, 0, &img_selector_background);

		putimage_alpha(selector_background_scorll_offset_x - img_p1_selector_background->getwidth(), 0, img_p1_selector_background);
		putimage_alpha(selector_background_scorll_offset_x, 0,
			img_p1_selector_background->getwidth() - selector_background_scorll_offset_x, 0, img_p1_selector_background, 0, 0);
		putimage_alpha(getwidth() - img_p2_selector_background->getwidth(), 0, img_p2_selector_background->getwidth() -
			selector_background_scorll_offset_x, 0, img_p2_selector_background, selector_background_scorll_offset_x, 0);
		putimage_alpha(getwidth() - selector_background_scorll_offset_x, 0, img_p2_selector_background);
		//�Լ�Ӱ����ͼ���в�����ʾ��ÿ����ҵı���ͼ�������������������Ҳ��������

		putimage_alpha(pos_img_vs.x, pos_img_vs.y, &img_vs);

		putimage_alpha(pos_img_1p.x, pos_img_1p.y, &img_1p);
		putimage_alpha(pos_img_2p.x, pos_img_2p.y, &img_2p);
		putimage_alpha(pos_img_1p_gravestone.x, pos_img_1p_gravestone.y, &img_gravestone_right);
		putimage_alpha(pos_img_2p_gravestone.x, pos_img_2p_gravestone.y, &img_gravestone_left);
		//��Ϊ��ҽ�ɫ��Ĺ���ϲ㣬������Ĺ����Ⱦ������Ⱦ
		switch (player_type_1)
		{
		case SelectorScene::PlayerType::peashooter:
			animation_peashooter.on_draw(camera, pos_animation_1p.x, pos_animation_1p.y);
			pos_img_1p_name.x = pos_img_1p_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtextxy_shaded(pos_img_1p_name.x, pos_img_1p_name.y, str_peashooter_name);
			break;
		case SelectorScene::PlayerType::sunflower:
			animation_sunflower.on_draw(camera, pos_animation_1p.x, pos_animation_1p.y);
			pos_img_1p_name.x = pos_img_1p_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_1p_name.x, pos_img_1p_name.y, str_sunflower_name);
			break;
		}

		switch (player_type_2)
		{
		case SelectorScene::PlayerType::peashooter:
			animation_peashooter.on_draw(camera, pos_animation_2p.x, pos_animation_2p.y);
			pos_img_2p_name.x = pos_img_2p_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtextxy_shaded(pos_img_2p_name.x, pos_img_2p_name.y, str_peashooter_name);
			break;
		case SelectorScene::PlayerType::sunflower:
			animation_sunflower.on_draw(camera, pos_animation_2p.x, pos_animation_2p.y);
			pos_img_2p_name.x = pos_img_2p_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_2p_name.x, pos_img_2p_name.y, str_sunflower_name);
			break;
		}
		//������ҽ�ɫ������Ⱦ��ͬ��ɫ�������߼�

		putimage_alpha(pos_1p_selector_btn_left.x, pos_1p_selector_btn_left.y,
			is_btn_1p_left_down ? &img_1p_selector_btn_down_left : &img_1p_selector_btn_idle_left);
		putimage_alpha(pos_1p_selector_btn_right.x, pos_1p_selector_btn_right.y,
			is_btn_1p_right_down ? &img_1p_selector_btn_down_right : &img_1p_selector_btn_idle_right);
		putimage_alpha(pos_2p_selector_btn_left.x, pos_2p_selector_btn_left.y,
			is_btn_2p_left_down ? &img_2p_selector_btn_down_left : &img_2p_selector_btn_idle_left);
		putimage_alpha(pos_2p_selector_btn_right.x, pos_2p_selector_btn_right.y,
			is_btn_2p_right_down ? &img_2p_selector_btn_down_right : &img_2p_selector_btn_idle_right);

		putimage_alpha(pos_img_1p_desc.x, pos_img_1p_desc.y, &img_1p_desc);
		putimage_alpha(pos_img_2p_desc.x, pos_img_2p_desc.y, &img_2p_desc);

		putimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);
	}

	void on_input(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
				//A
			case 0x41:
				is_btn_1p_left_down = true;
				break;
				//D
			case 0x44:
				is_btn_1p_right_down = true;
				break;
				//<-
			case VK_LEFT:
				is_btn_2p_left_down = true;
				break;
				//->
			case VK_RIGHT:
				is_btn_2p_right_down = true;
				break;
			}
			break;
		case WM_KEYUP:
			switch (msg.vkcode)
			{
				//A
			case 0x41:
				is_btn_1p_left_down = false;
				player_type_1 = (PlayerType)(((int)PlayerType::invalid + (int)player_type_1 - 1) % (int)PlayerType::invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				//��ȷ���������0
				//��ȷ�����������ڵ���invalidֵ
				//��󽫵õ���intֵת��Ϊö����
				//�����Ϳ���ȷ�����°�ť��������ͷ����˱仯��ͬʱ���ֵ����ö����ĵ�һ��ֵ�����һ��ֵ֮��
				break;
				//D
			case 0x44:
				is_btn_1p_right_down = false;
				player_type_1 = (PlayerType)(((int)player_type_1 + 1) % (int)PlayerType::invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
				//<-
			case VK_LEFT:
				is_btn_2p_left_down = false;
				player_type_2 = (PlayerType)(((int)PlayerType::invalid + (int)player_type_2 - 1) % (int)PlayerType::invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
				//->
			case VK_RIGHT:
				is_btn_2p_right_down = false;
				player_type_2 = (PlayerType)(((int)player_type_2 + 1) % (int)PlayerType::invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_RETURN:
				scene_manager.switch_to(SceneManager::SceneType::Game);
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				break;
			}
			break;
		default:
			break;
		}
	}

	void on_exit()
	{
		switch (player_type_1)
		{
		case SelectorScene::PlayerType::peashooter:
			player_1 = new PeashooterPlayer();
			img_player_1_avatar = &img_avator_peashooter;
			break;
		case SelectorScene::PlayerType::sunflower:
			player_1 = new SumflowerPlayer();
			img_player_1_avatar = &img_avator_sunflower;
			break;
		}
		player_1->set_id(PlayerID::p1);

		switch (player_type_2)
		{
		case SelectorScene::PlayerType::peashooter:
			player_2 = new PeashooterPlayer(false);
			img_player_2_avatar = &img_avator_peashooter;
			break;
			break;
		case SelectorScene::PlayerType::sunflower:
			player_2 = new SumflowerPlayer(false);
			img_player_2_avatar = &img_avator_sunflower;
			break;
		}
		player_2->set_id(PlayerID::p2);

		mciSendString(_T("stop bgm_menu"), NULL, 0, NULL);
	}
private:
	enum class PlayerType
	{
		peashooter=0,
		sunflower,
		invalid
	};

private:
	POINT pos_img_vs = { 0 };
	POINT pos_img_tip = { 0 };
	POINT pos_img_1p = { 0 };
	POINT pos_img_2p = { 0 };
	POINT pos_img_1p_desc = { 0 }; 
	POINT pos_img_2p_desc = { 0 };
	POINT pos_img_1p_name = { 0 }; 
	POINT pos_img_2p_name = { 0 };
	POINT pos_animation_1p = { 0 };
	POINT pos_animation_2p = { 0 };
	POINT pos_img_1p_gravestone = { 0 };
	POINT pos_img_2p_gravestone = { 0 };
	POINT pos_1p_selector_btn_left = { 0 };
	POINT pos_1p_selector_btn_right = { 0 };
	POINT pos_2p_selector_btn_left = { 0 };
	POINT pos_2p_selector_btn_right = { 0 };

	Animation animation_peashooter;//�㶹���ֽ�ɫ����
	Animation animation_sunflower;

	PlayerType player_type_1 = PlayerType::peashooter;//1p��ɫ����
	PlayerType player_type_2 = PlayerType::sunflower;//2p��ɫ����

	LPCTSTR str_peashooter_name = _T("�δ�");//�㶹��ɫ��
	LPCTSTR str_sunflower_name = _T("�ζ�");//���տ���ɫ��

	int selector_background_scorll_offset_x = 0;//�������������

	bool is_btn_1p_left_down = false;//1p2p���������л���ť�Ƿ��� 
	bool is_btn_1p_right_down = false;
	bool is_btn_2p_left_down = false;
	bool is_btn_2p_right_down = false;

private:
	void outtextxy_shaded(int x, int y, LPCTSTR str)
	{
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}
	//���ƴ���ӰЧ�����ı�
};