#pragma once
#include"player.h"
#include"sun_bullet.h"
#include"sun_bullet_ex.h"

extern Atlas atlas_sunflower_idle_left;//���տ��������Ĭ�϶���ͼ��
extern Atlas atlas_sunflower_idle_right;//���տ������ҵ�Ĭ�϶���ͼ��
extern Atlas atlas_sunflower_run_left;//���տ������ܵĶ���ͼ��
extern Atlas atlas_sunflower_run_right;//���տ������ܵĶ���ͼ��
extern Atlas atlas_sunflower_attack_ex_left;//���տ�����������⹥������ͼ��
extern Atlas atlas_sunflower_attack_ex_right;//���տ������ҵ����⹥������ͼ��
extern Atlas atlas_sun_text;//���ա��ı�����ͼ��
extern Atlas atlas_sunflower_die_left;
extern Atlas atlas_sunflower_die_right;

extern Player* player_1;
extern Player* player_2;



class SumflowerPlayer :public Player
{
public:
	SumflowerPlayer(bool facing_right = true) :Player(facing_right)
	{
		animation_idle_left.set_atlas(&atlas_sunflower_idle_left);
		animation_idle_right.set_atlas(&atlas_sunflower_idle_right);
		animation_run_left.set_atlas(&atlas_sunflower_run_left);
		animation_run_right.set_atlas(&atlas_sunflower_run_right);
		animation_attack_ex_left.set_atlas(&atlas_sunflower_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_sunflower_attack_ex_right);
		animation_sun_text.set_atlas(&atlas_sun_text);
		animation_die_left.set_atlas(&atlas_sunflower_die_left);
		animation_die_right.set_atlas(&atlas_sunflower_die_right);


		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
		animation_attack_ex_left.set_interval(100);
		animation_attack_ex_right.set_interval(100);
		animation_sun_text.set_interval(100);
		animation_die_left.set_interval(150);
		animation_die_right.set_interval(150);

		animation_attack_ex_left.set_loop(false);
		animation_attack_ex_right.set_loop(false);
		animation_sun_text.set_loop(false);
		animation_die_left.set_loop(false);
		animation_die_right.set_loop(false);

		animation_attack_ex_left.set_callback([&]()
			{
				is_attacking_ex = false;
				is_sun_text_visibe = false;
			});
		animation_attack_ex_right.set_callback([&]()
			{
				is_attacking_ex = false;
				is_sun_text_visibe = false;
			});

		size.x = 96, size.y = 96;

		attack_cd = 250;
	}

	~SumflowerPlayer() = default;

	void on_update(int delta)
	{
		Player::on_update(delta);

		if (is_sun_text_visibe) animation_sun_text.on_update(delta);
	}

	void on_draw(const camera& camera)
	{
		Player::on_draw(camera);
		if (is_sun_text_visibe)
		{
			Vector2 text_position;
			IMAGE* frame = animation_sun_text.get_frame();
			text_position.x = position.x - (size.x - frame->getwidth()) / 2;
			text_position.y = position.y - frame->getheight();
			animation_sun_text.on_draw(camera, (int)text_position.x, (int)text_position.y);
		}
	}

	void on_attack()
	{
		Bullet* bullet = new SunBullet();

		Vector2 bullet_position;
		const Vector2& bullet_size = bullet->get_size();
		bullet_position.x = position.x + (size.x - bullet_size.x) / 2;
		bullet_position.y = position.y;

		bullet->set_position(bullet_position.x, bullet_position.y);
		bullet->set_velocity(is_facing_right ? velocity_sun.x : -velocity_sun.x, velocity_sun.y);

		bullet->set_colliide_target(id == PlayerID::p1 ? PlayerID::p2 : PlayerID::p1);

		bullet->set_callback([&]() {mp +=35; });
		bullet_list.push_back(bullet);
	}

	void on_attack_ex()
	{
		is_attacking_ex = true;
		is_sun_text_visibe = true;

		animation_sun_text.reset();
		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();

		Bullet* bullet = new SunBulletEx();
		Player* target_player = (id == PlayerID::p1 ? player_2 : player_1);

		Vector2 bullet_position, bullet_velocity;
		const Vector2& bullet_size = bullet->get_size();
		const Vector2& target_size = target_player->get_size();
		const Vector2& target_position = target_player->get_position();
		bullet_position.x = target_position.x + (target_size.x - bullet_size.x) / 2;
		bullet_position.y = -size.y;
		bullet_velocity.x = 0;
		bullet_velocity.y = speed_sun_ex;

		bullet->set_position(bullet_position.x, bullet_position.y);
		bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);

		bullet->set_colliide_target(id == PlayerID::p1 ? PlayerID::p2 : PlayerID::p1);

		bullet->set_callback([&]() { mp += 50; });
		bullet_list.push_back(bullet);
		mciSendString(_T("play sun_text from 0"), NULL, 0, NULL);
	}

private:
	const float speed_sun_ex = 0.15f;//�����չ������ٶ�
	const Vector2 velocity_sun = { 0.25f,-0.5f };//С���չ������ٶ�

private:
	Animation animation_sun_text;//ͷ���ı�����
	bool is_sun_text_visibe = false;//�Ƿ���ʾͷ������
};