#include"easyx.h"
#include"menu_scene.h"
#include"game_scene.h"
#include"scene.h"
#include"scene_manager.h"
#include"select_scene.h"
#include"util.h"
#include"platform.h"
#include"atlas.h"
#include"player.h"
#pragma comment(lib,"Winmm.lib")
#include"bullet.h"

bool is_debug = false;

	IMAGE img_menu_background;//���˵�����ͼƬ

	IMAGE img_vs;//vs������ͼƬ
	IMAGE img_1p;//1p�ı�ͼƬ
	IMAGE img_2p;//2p�ı�ͼƬ
	IMAGE img_1p_desc;//1p��λ����ͼƬ
	IMAGE img_2p_desc;//2p��λ����ͼƬ
	IMAGE img_gravestone_left;//�����Ĺ��
	IMAGE img_gravestone_right;//���ҵ�Ĺ��
	IMAGE img_selector_tip;//ѡ��ɫ��������ʾ��Ϣ�ı�ͼƬ
	IMAGE img_selector_background;//ѡ��ɫ���汳��ͼ
	IMAGE img_1p_selector_btn_idle_left;//1p����ѡ��ťĬ��״̬ͼƬ
	IMAGE img_1p_selector_btn_idle_right;//1p����ѡ��ťĬ��״̬ͼƬ
	IMAGE img_1p_selector_btn_down_left;//1p����ѡ��ť����״̬ͼƬ
	IMAGE img_1p_selector_btn_down_right;//1p����ѡ��ť����״̬ͼƬ
	IMAGE img_2p_selector_btn_idle_left;//2p����ѡ��ťĬ��״̬ͼƬ
	IMAGE img_2p_selector_btn_idle_right;//2p����ѡ��ťĬ��״̬ͼƬ
	IMAGE img_2p_selector_btn_down_left;//2p����ѡ��ť����״̬ͼƬ
	IMAGE img_2p_selector_btn_down_right;//2p����ѡ��ť����״̬ͼƬ
	IMAGE img_peashooter_select_background_left;//ѡ�ǽ��泯������㶹���ֱ���ͼƬ
	IMAGE img_peashooter_select_background_right;//ѡ�ǽ��泯���ҵ��㶹���ֱ���ͼƬ
	IMAGE img_sunflower_select_background_left;//ѡ�ǽ��泯��������տ�����ͼƬ
	IMAGE img_sunflower_select_background_right;//ѡ�ǽ��泯���ұߵ����տ�����ͼƬ

	IMAGE img_sky;//���ͼƬ
	IMAGE img_hills;//ɽ��ͼƬ
	IMAGE img_platform_large;//����ƽ̨ͼƬ
	IMAGE img_platform_small;//С��ƽ̨ͼƬ

	IMAGE img_1p_cursor;//1pָʾ���ͼƬ
	IMAGE img_2p_cursor;//2pָʾ���ͼƬ

	Atlas atlas_peashooter_idle_left;//�㶹���ֳ������Ĭ�϶���ͼ��
	Atlas atlas_peashooter_idle_right;//�㶹���ֳ����ҵ�Ĭ�϶���ͼ��
	Atlas atlas_peashooter_run_left;//�㶹���������ܵĶ���ͼ��
	Atlas atlas_peashooter_run_right;//�㶹���������ܵĶ���ͼ��
	Atlas atlas_peashooter_attack_ex_left;//�㶹���ֳ���������⹥������ͼ��
	Atlas atlas_peashooter_attack_ex_right;//�㶹���ֳ����ҵ����⹥������ͼ��
	Atlas atlas_peashooter_die_left;//�㶹�������������Ķ���ͼ��
	Atlas atlas_peashooter_die_right;//�㶹�������������Ķ���ͼ��


	Atlas atlas_sunflower_idle_left;//���տ��������Ĭ�϶���ͼ��
	Atlas atlas_sunflower_idle_right;//���տ������ҵ�Ĭ�϶���ͼ��
	Atlas atlas_sunflower_run_left;//���տ������ܵĶ���ͼ��
	Atlas atlas_sunflower_run_right;//���տ������ܵĶ���ͼ��
	Atlas atlas_sunflower_attack_ex_left;//���տ�����������⹥������ͼ��
	Atlas atlas_sunflower_attack_ex_right;//���տ������ҵ����⹥������ͼ��
	Atlas atlas_sunflower_die_left;//���տ����������Ķ���ͼ��
	Atlas atlas_sunflower_die_right;//���տ����������Ķ���ͼ��

	IMAGE img_pea;//�㶹ͼƬ
	Atlas atlas_pea_break;//�㶹���鶯��ͼ��
	Atlas atlas_sun;//�չ⶯��ͼ��
	Atlas atlas_sun_explode;//�չⱬը����ͼ��
	Atlas atlas_sun_ex;//�����չ⶯��ͼ��
	Atlas atlas_sun_ex_explode;//�����չⱬը����ͼ��
	Atlas atlas_sun_text;//���ա��ı�����ͼ��

	Atlas atlas_run_effect;//������Ч�����ϼ�
	Atlas atlas_jump_effect;//��Ծ�����ϼ�
	Atlas atlas_land_effect;//��ض����ϼ�

	IMAGE img_1p_winner;//1p��ʤ�ı�ͼƬ
	IMAGE img_2p_winner;//2p��ʤ�ı�ͼƬ
	IMAGE img_winner_bar;//��ʤ����ı�����ͼƬ

	IMAGE img_avator_peashooter;//�㶹����ͷ��
	IMAGE img_avator_sunflower;//���տ�ͷ��

	Scene* menu_scene = nullptr;
	Scene* game_scene = nullptr;
	Scene* select_scene = nullptr;

	camera main_camera;
	SceneManager scene_manager;

	std::vector<Bullet*>bullet_list;
	std::vector<Platform> platform_list;

	Player* player_1 = nullptr;
	Player* player_2 = nullptr;

	IMAGE* img_player_1_avatar = nullptr;
	IMAGE* img_player_2_avatar = nullptr;



void flip_atlas(Atlas& src, Atlas& dst)
{
	dst.clear();
	for (int i = 0; i < src.get_size(); i++)
	{
		IMAGE img_flpiped;
		flip_image(src.get_image(i), &img_flpiped);
		dst.add_image(img_flpiped);
	}
}
//ʵ�ֶ�����ת

void load_game_recourse()
{
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);
	//��������

	loadimage(&img_menu_background, _T("resources/bk.png"));

	loadimage(&img_vs, _T("resources/vs1.png"));
	loadimage(&img_1p, _T("resources/1P.png"));
	loadimage(&img_2p, _T("resources/2P.png"));
	loadimage(&img_1p_desc, _T("D:\\1\\c++\\ֲ��\\resources\\1P_desc.png"));
	loadimage(&img_2p_desc, _T("D:\\1\\c++\\ֲ��\\resources\\2P_desc.png"));
	loadimage(&img_gravestone_right, _T("D:\\1\\c++\\ֲ��\\resources\\gravestone.png"));
	flip_image(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_selector_tip, _T("D:\\1\\c++\\ֲ��\\resources\\selector_tip.png"));
	loadimage(&img_selector_background, _T("D:\\1\\c++\\ֲ��\\resources\\sl.png"));

	loadimage(&img_1p_selector_btn_idle_right, _T("D:\\1\\c++\\ֲ��\\resources\\1P_selector_btn_idle.png"));
	flip_image(&img_1p_selector_btn_idle_right, &img_1p_selector_btn_idle_left);
	loadimage(&img_1p_selector_btn_down_right, _T("D:\\1\\c++\\ֲ��\\resources\\1P_selector_btn_down.png"));
	flip_image(&img_1p_selector_btn_down_right, &img_1p_selector_btn_down_left);

	loadimage(&img_2p_selector_btn_idle_right, _T("D:\\1\\c++\\ֲ��\\resources\\2P_selector_btn_idle.png"));
	flip_image(&img_2p_selector_btn_idle_right, &img_2p_selector_btn_idle_left);
	loadimage(&img_2p_selector_btn_down_right, _T("D:\\1\\c++\\ֲ��\\resources\\2P_selector_btn_down.png"));
	flip_image(&img_2p_selector_btn_down_right, &img_2p_selector_btn_down_left);
	
	loadimage(&img_peashooter_select_background_right, _T("D:\\1\\c++\\ֲ��\\resources\\peashooter_selector_background.png"));
	flip_image(&img_peashooter_select_background_right, &img_peashooter_select_background_left);
	loadimage(&img_sunflower_select_background_right, _T("D:\\1\\c++\\ֲ��\\resources\\sunflower_selector_background.png"));
	flip_image(&img_sunflower_select_background_right, &img_sunflower_select_background_left);


	loadimage(&img_sky, _T("D:\\1\\c++\\ֲ��\\resources\\sky.png"));
	loadimage(&img_hills, _T("D:\\1\\c++\\ֲ��\\resources\\nhs.png"));
	loadimage(&img_platform_large, _T("D:\\1\\c++\\ֲ��\\resources\\platform_large.png"));
	loadimage(&img_platform_small, _T("D:\\1\\c++\\ֲ��\\resources\\platform_small.png"));

	loadimage(&img_1p_cursor, _T("D:\\1\\c++\\ֲ��\\resources\\1P_cursor.png"));
	loadimage(&img_2p_cursor, _T("D:\\1\\c++\\ֲ��\\resources\\2P_cursor.png"));

	atlas_peashooter_idle_right.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\peashooter_idle_%d.png"), 9);
	flip_atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	atlas_peashooter_run_right.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\peashooter_run_%d.png"), 5);
	flip_atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);
	atlas_peashooter_attack_ex_right.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\peashooter_attack_ex_%d.png"), 3);
	flip_atlas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);
	atlas_peashooter_die_right.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\peashooter_die_%d.png"), 4);
	flip_atlas(atlas_peashooter_die_right, atlas_peashooter_die_left);

	atlas_sunflower_idle_right.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\sunflower_idle_%d.png"), 8);
	flip_atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
	atlas_sunflower_run_right.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\sunflower_run_%d.png"), 5);
	flip_atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);
	atlas_sunflower_attack_ex_right.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\sunflower_attack_ex_%d.png"), 9);
	flip_atlas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);
	atlas_sunflower_die_right.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\sunflower_die_%d.png"), 2);
	flip_atlas(atlas_sunflower_die_right, atlas_sunflower_die_left);

	loadimage(&img_pea, _T("D:\\1\\c++\\ֲ��\\resources\\pea.png"));
	atlas_pea_break.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\pea_break_%d.png"),3);
	atlas_sun.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\sun_%d.png"), 5);
	atlas_sun_explode.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\sun_explode_%d.png"), 5);
	atlas_sun_ex.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\sun_ex_%d.png"), 5);
	atlas_sun_ex_explode.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\sun_ex_explode_%d.png"), 5);
	atlas_sun_text.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\sun_text_%d.png"), 6);

	atlas_run_effect.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\run_effect_%d.png"), 4);
	atlas_jump_effect.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\jump_effect_%d.png"), 5);
	atlas_land_effect.load_from_file(_T("D:\\1\\c++\\ֲ��\\resources\\land_effect_%d.png"), 2);

	loadimage(&img_1p_winner, _T("D:\\1\\c++\\ֲ��\\resources\\1P_winner.png"));
	loadimage(&img_2p_winner, _T("D:\\1\\c++\\ֲ��\\resources\\2P_winner.png"));
	loadimage(&img_winner_bar, _T("D:\\1\\c++\\ֲ��\\resources\\winnner_bar.png"));

	loadimage(&img_avator_peashooter, _T("D:\\1\\c++\\ֲ��\\resources\\avatar_peashooter.png"));
	loadimage(&img_avator_sunflower, _T("D:\\1\\c++\\ֲ��\\resources\\avatar_sunflower.png"));

	mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
	mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);
}
int main()
{
	ExMessage msg;
	const int FPS = 144;

	load_game_recourse();

	initgraph(1280, 720);

	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);//�����ı�����ɫΪ͸��

	BeginBatchDraw();

	menu_scene = new MenuScene();
	game_scene = new GameScene();
	select_scene = new SelectorScene();

	scene_manager.set_current_scene(menu_scene);

	//����Ϊ��ʼ��
	//����Ϊ��Ϸ��ѭ��
	while (true)
	{
		DWORD frame_start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
		}
		
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;
		scene_manager.on_update(delta_tick);
		last_tick_time = current_tick_time;

		cleardevice();
		scene_manager.on_draw(main_camera);
		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < 1000 / FPS)
			Sleep(1000 / FPS - frame_delta_time);
		//��̬��ʱ��ȷ��ѭ���ٶȾ������ȶ���60֡
	}
	//�ͷ���Դ

	EndBatchDraw();
	return 0;
}