#pragma once
#include"player.h"
#include"pea_bullet.h"
#include"iostream"

extern Atlas atlas_peashooter_idle_left;//豌豆射手朝向左的默认动画图集
extern Atlas atlas_peashooter_idle_right;//豌豆射手朝向右的默认动画图集
extern Atlas atlas_peashooter_run_left;//豌豆射手向左跑的动画图集
extern Atlas atlas_peashooter_run_right;//豌豆射手向右跑的动画图集
extern Atlas atlas_peashooter_attack_ex_left;//豌豆射手朝向左的特殊攻击动画图集 
extern Atlas atlas_peashooter_attack_ex_right;//豌豆射手朝向右的特殊攻击动画图集
extern Atlas atlas_peashooter_die_left;
extern Atlas atlas_peashooter_die_right;


class PeashooterPlayer:public Player
{
public:
	PeashooterPlayer(bool facing_right = true):Player(facing_right)
	{
		animation_idle_left.set_atlas(&atlas_peashooter_idle_left);
		animation_idle_right.set_atlas(&atlas_peashooter_idle_right);
		animation_run_left.set_atlas(&atlas_peashooter_run_left);
		animation_run_right.set_atlas(&atlas_peashooter_run_right);
		animation_attack_ex_left.set_atlas(&atlas_peashooter_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_peashooter_attack_ex_right);
		animation_die_left.set_atlas(&atlas_peashooter_die_left);
		animation_die_right.set_atlas(&atlas_peashooter_die_right);

		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
		animation_attack_ex_left.set_interval(75);
		animation_attack_ex_right.set_interval(75);
		animation_die_left.set_interval(150);
		animation_die_right.set_interval(150);

		animation_die_left.set_loop(false);
		animation_die_right.set_loop(false);



		size.x = 96, size.y = 96;

		timer_attack_ex.set_wait_time(attack_ex_duration);
		timer_attack_ex.set_one_shot(true);
		timer_attack_ex.set_callback([&]()
			{
				is_attacking_ex = false;
			});

		timer_spwan_pea_ex.set_wait_time(100);
		timer_spwan_pea_ex.set_callback([&]()
			{
				spawn_pea_bullet(speed_pea_ex);
			});

		attack_cd = 100;
	}
	~PeashooterPlayer() = default;

	void on_update(int delta)
	{
		Player::on_update(delta);

		if (is_attacking_ex)
		{
			main_camera.shake(5, 100);
			timer_attack_ex.on_up_date(delta);
			timer_spwan_pea_ex.on_up_date(delta);
		}
	}

	void on_attack()
	{
		spawn_pea_bullet(speed_pea);//生成子弹

		switch (rand()%2)
		{
		case 0:
			mciSendString(_T("play pea_shoot_1 form 0"), NULL, 0, NULL);
			break;
		case 1:
			mciSendString(_T("play pea_shoot_2 form 0"), NULL, 0, NULL);
			break;
		}
	}

	void on_attack_ex()
	{
		is_attacking_ex = true;
		timer_attack_ex.restart();//重启定时器

		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();
		mciSendString(_T("play pea_shoot_ex from 0"), NULL, 0, NULL);
	}
private:
	void spawn_pea_bullet(float speed)
	{
		Bullet* bullet = new PeaBullet();

		Vector2 bullet_position, bullet_velocity;
		const Vector2& bullet_size = bullet->get_size();
		bullet_position.x = is_facing_right
			? position.x + size.x - bullet_size.x / 2
			: position.x - bullet_size.x / 2;
		bullet_position.y = position.y;
		bullet_velocity.x = is_facing_right ? speed : -speed;
		bullet_velocity.y = 0;

		bullet->set_position(bullet_position.x, bullet_position.y);
		bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);

		bullet->set_colliide_target(id == PlayerID::p1 ? PlayerID::p2 : PlayerID::p1);
		bullet->set_callback([&]() {mp += 25; });//按引用捕获

		bullet_list.push_back(bullet);
	}
private:
	const float speed_pea = 0.75f;
	const float speed_pea_ex = 1.5f;
	const int attack_ex_duration = 2500;//特殊攻击持续时长

private:
	Timer timer_attack_ex;//特攻状态定时器
	Timer timer_spwan_pea_ex;//豌豆子弹发射定时器
};