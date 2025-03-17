#pragma once
#include"camera.h"
#include"easyx.h"
#include"animation.h"
#include"vector2.h"
#include"bullet.h"
#include"player_id.h"
#include"platform.h"
#include"util.h"
#include"particle.h"

extern std::vector<Platform> platform_list;
extern std::vector<Bullet*>bullet_list;
extern Atlas atlas_run_effect;
extern Atlas atlas_jump_effect;
extern Atlas atlas_land_effect;
extern IMAGE img_1p_cursor;
extern IMAGE img_2p_cursor;



class Player
{
public:
	Player(bool facing_right = true):is_facing_right(facing_right)
	{
		current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;

		timer_attack_cd.set_wait_time(attack_cd);
		timer_attack_cd.set_one_shot(true);//单次触发
		timer_attack_cd.set_callback([&]()
			{
				can_attack = true;
			});
		//补充回调函数逻辑

		timer_invulnerable.set_wait_time(750);
		timer_invulnerable.set_one_shot(true);
		timer_invulnerable.set_callback([&]()
			{
				is_invulnerable = false;
			});

		timer_invulnerable_blink.set_wait_time(75);
		timer_invulnerable_blink.set_callback([&]()
			{
				is_showing_sketch_frame = !is_showing_sketch_frame;
			});

		timer_run_effect_generation.set_wait_time(75);
		timer_run_effect_generation.set_callback([&]()
			{
				Vector2 paticle_position;
				IMAGE* frame = atlas_run_effect.get_image(0);
				paticle_position.x = position.x + (size.x - frame->getwidth()) / 2;
				paticle_position.y = position.y + size.y - frame->getheight();
				particle_list.emplace_back(paticle_position, &atlas_run_effect, 45);
				//每次定时器时间到达时，都向粒子数组中增加新的对象。
			});

		timer_die_effect_generation.set_wait_time(35);//死亡尾迹生成更快
		timer_die_effect_generation.set_callback([&]()
			{
				Vector2 paticle_position;
				IMAGE* frame = atlas_run_effect.get_image(0);
				paticle_position.x = position.x + (size.x - frame->getwidth()) / 2;
				paticle_position.y = position.y + size.y - frame->getheight();
				particle_list.emplace_back(paticle_position, &atlas_run_effect, 150);//持续时间更长
				//每次定时器时间到达时，都向粒子数组中增加新的对象。
			});

		animation_jump_effect.set_atlas(&atlas_jump_effect);
		animation_jump_effect.set_interval(25);
		animation_jump_effect.set_loop(false);
		animation_jump_effect.set_callback([&]()
			{
				is_jump_effect_visible = false;
			});

		animation_land_effect.set_atlas(&atlas_land_effect);
		animation_land_effect.set_interval(50);
		animation_land_effect.set_loop(false);
		animation_land_effect.set_callback([&]()
			{
				is_land_effect_visible = false;
			});

		timer_cursor_visibility.set_wait_time(2500);
		timer_cursor_visibility.set_one_shot(true);
		timer_cursor_visibility.set_callback([&]()
			{
				is_cursor_visible = false;
			});

	}
	~Player() = default;

	void make_invulnerable()
	{
		is_invulnerable = true;
		timer_invulnerable.restart();
	}

	virtual void on_update(int delta)
	{
		int direction = is_right_key_down - is_left_key_down;

		if (direction != 0)
		{
			if(!is_attacking_ex)
				is_facing_right = direction > 0;
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float distance = direction * run_velocity * delta;
			on_run(distance);
		}
		else//没有移动时
		{
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
			timer_run_effect_generation.pause();
		}
		if (is_attacking_ex)
		{
			current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
		}

		if (hp <= 0)
		{
			current_animation = last_hurt_direction.x < 0 ? &animation_die_left : &animation_die_right;
		}

		current_animation->on_update(delta);
		animation_jump_effect.on_update(delta);
		animation_land_effect.on_update(delta);


		timer_attack_cd.on_up_date(delta);
		timer_invulnerable.on_up_date(delta);
		timer_invulnerable_blink.on_up_date(delta);
		timer_run_effect_generation.on_up_date(delta);
		timer_cursor_visibility.on_up_date(delta);

		if (hp <= 0)
			timer_die_effect_generation.on_up_date(delta);
		particle_list.erase(std::remove_if(
			particle_list.begin(), particle_list.end(),
			[](const Particle& particle)
			{
				return!particle.check_valid();
			}),
			particle_list.end());
		for (Particle& particle : particle_list)
			particle.on_update(delta);

		if (is_showing_sketch_frame)
			sketch_image(current_animation->get_frame(), &img_sketch);
		//抓取当前动画的帧，然后处理为剪影。

		move_and_collide(delta);
	}

	virtual void on_draw(const camera& camera)
	{
		if (is_jump_effect_visible)
			animation_jump_effect.on_draw(camera, (int)position_jump_effect.x, (int)position_jump_effect.y);
		if (is_land_effect_visible)
			animation_land_effect.on_draw(camera, (int)position_land_effect.x, (int)position_land_effect.y);

		for (const Particle& particle : particle_list)
			particle.on_draw(camera);

		if (hp > 0 && is_invulnerable && is_showing_sketch_frame)
			putimage_alpha(camera, (int)position.x, (int)position.y, &img_sketch);
		else
			current_animation->on_draw(camera, (int)position.x, (int)position.y);

		if (is_cursor_visible)
		{
			switch (id)
			{
			case PlayerID::p1:
				putimage_alpha(camera, (int)(position.x + (size.x - img_1p_cursor.getwidth()) / 2),
					(int)(position.y - img_1p_cursor.getheight()), &img_1p_cursor);
				break;
			case PlayerID::p2:
				putimage_alpha(camera, (int)(position.x + (size.x - img_2p_cursor.getwidth()) / 2),
					(int)(position.y - img_2p_cursor.getheight()), &img_2p_cursor);
				break;
			default:
				break;
			}
		}
	}

	virtual void on_input(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (id)
			{
			case PlayerID::p1:
				switch (msg.vkcode)
				{
					//A
				case 0x41:
					is_left_key_down = true;
					break;
					//D
				case 0x44:
					is_right_key_down = true;
					break;
					//W
				case 0x57:
					on_jump();
					break;
					//F
				case 0x46:
					if (can_attack)
					{
						on_attack();
						can_attack = false;
						timer_attack_cd.restart();
					}
					break;
					//G
				case 0x47:
					if (mp >= 100)
					{
						on_attack_ex();
						mp = 0;
					}
					break;
				}
				break;
			case PlayerID::p2:
				switch (msg.vkcode)
				{
				case VK_LEFT:
					is_left_key_down = true;
					break;
				case VK_RIGHT:
					is_right_key_down = true;
					break;
				case VK_UP:
					on_jump();
					break;
					//.
				case VK_OEM_PERIOD:
					if (can_attack)
					{
						on_attack();
						can_attack = false;
						timer_attack_cd.restart();
					}
					break;
					// : '/'
				case VK_OEM_2:
					if (mp >= 100)
					{
						on_attack_ex();
						mp = 0;
					}
					break;
				}
				break;
			}
			break;
		case WM_KEYUP:
			switch (id)
			{
			case PlayerID::p1:
				switch (msg.vkcode)
				{
					//A
				case 0x41:
					is_left_key_down = false;
					break;
					//D
				case 0x44:
					is_right_key_down = false;
					break;
				}
				break;
			case PlayerID::p2:
				switch (msg.vkcode)
				{
				case VK_LEFT:
					is_left_key_down = false;
					break;
				case VK_RIGHT:
					is_right_key_down = false;
					break;

				}
				break;
			}
			break;
		}
	}

	void set_position(float x, float y)
	{
		position.x = x, position.y = y;
	}

	const Vector2& get_position()const
	{
		return position;
	}

	const Vector2& get_size()const
	{
		return size;
	}

	void set_hp(int val)
	{
		hp = val;
	}

	int get_hp()const
	{
		return hp;
	}

	int get_mp()const
	{
		return mp;
	}

	virtual void on_attack() {};

	virtual void on_attack_ex() {};

	void set_id(PlayerID id)
	{
		this->id = id;
	}

	virtual void on_run(float distance)
	{
		if (is_attacking_ex) return;
		position.x += distance;
		timer_run_effect_generation.resume();
	}

	virtual void on_jump()
	{
		if (velocity.y != 0||is_attacking_ex)
		{
			return;
		}
		velocity.y += jump_velocity;
		is_jump_effect_visible = true;
		animation_jump_effect.reset();

		IMAGE* effect_frame = animation_jump_effect.get_frame();
		position_jump_effect.x = position.x + (size.x - effect_frame->getwidth()) / 2;
		position_jump_effect.y = position.y + size.y - effect_frame->getheight();
	}

	virtual void on_land()
	{
		is_land_effect_visible = true;
		animation_land_effect.reset();

		IMAGE* effect_frame = animation_land_effect.get_frame();
		position_land_effect.x = position.x + (size.x - effect_frame->getwidth()) / 2;
		position_land_effect.y = position.y + size.y - effect_frame->getheight();
	}

protected:
	const float gravity = 1.6e-3f;//玩家重力
	const float run_velocity = 0.55f;//跑动速度
	const float jump_velocity = -0.85f;//跳跃速度

	void move_and_collide(int delta)
	{
		float last_velocity_y = velocity.y;

		velocity.y += gravity * delta;
		position += velocity * (float)delta;

		if (hp <= 0) return;//角色死亡则不进行后续碰撞判定

		if (velocity.y > 0)
		{
			for (const Platform& platform : platform_list)
			{
				const	Platform::CollisionShape& shape = platform.shape;
				bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left)
					<= size.x + (shape.right - shape.left));
				//判断玩家矩形和平台是否在水平位置上发生了碰撞
				bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);

				if (is_collide_x && is_collide_y)
				{
					float delta_pos_y = velocity.y * delta;
					float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;//上一帧玩家脚的位置，回退
					if (last_tick_foot_pos_y <= shape.y)
					{
						position.y = shape.y - size.y;
						velocity.y = 0;//把玩家放在平台上，设置竖直速度为0

						if (last_velocity_y != 0)
							on_land();


						break;
					}
				}
			}
		}
		//判断玩家和环境的碰撞
		
		//判断玩家和子弹的碰撞
		if (!is_invulnerable)
		{
			for (Bullet* bullet : bullet_list)
			{
				if (!bullet->get_valid() || bullet->get_collide_target() != id) 
					continue;
				//判断是否可以发生碰撞以及ID是否匹配，不是就跳过

				if (bullet->check_collison(position, size))
				{
					make_invulnerable();
					bullet->on_collide();
					bullet->set_valid(false);//设置这个子弹不可以继续碰撞
					hp -= bullet->get_damage();
					last_hurt_direction = bullet->get_position() - position;
					if (hp <= 0)
					{
						velocity.x = last_hurt_direction.x < 0 ? 0.35f : -0.35f;
						velocity.y = -1.0f;
					}
					//生命值减少
				}//如果可以发生碰撞
			}
		}	
	}


protected:

	int mp = 0;//能量
	int hp = 100;//生命值

	Vector2 size;//角色尺寸
	Vector2 position;//二维向量记录玩家位置
	Vector2 velocity;//角色速度

	Animation animation_idle_left;//朝向左的默认动画
	Animation animation_idle_right;//朝向右的默认动画
	Animation animation_run_left;//朝向左的奔跑动画
	Animation animation_run_right;//朝向右的奔跑动画
	Animation animation_attack_ex_left;//朝向左的特攻动画
	Animation animation_attack_ex_right;//朝向右的特攻动画
	Animation animation_jump_effect;//跳跃粒子
	Animation animation_land_effect;//落地粒子
	Animation animation_die_left;
	Animation animation_die_right;


	bool is_jump_effect_visible = false;//跳跃动画是否可见
	bool is_land_effect_visible = false;//跳跃动画是否可见

	Vector2 position_jump_effect;
	Vector2 position_land_effect;

	Animation* current_animation = nullptr;//当前正在播放的动画

	PlayerID id = PlayerID::p1;//玩家序号ID

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;//角色是否朝向右

	bool can_attack = true;//是否可以释放普攻
	int attack_cd = 500;//普攻冷却时间
	Timer timer_attack_cd;//普攻冷却定时器

	bool is_attacking_ex = false;//是否在释放特殊攻击

	IMAGE img_sketch;//剪影图片
	bool is_invulnerable = false;//是否无敌
	bool is_showing_sketch_frame = false;//当前帧是否显示剪影
	Timer timer_invulnerable;//无敌状态定时器
	Timer timer_invulnerable_blink;//无敌状态闪烁定时器

	std::vector<Particle>particle_list;//粒子对象数组

	Timer timer_run_effect_generation;//跑动粒子发射定时器
	Timer timer_die_effect_generation;//死亡粒子发射定时器

	bool is_cursor_visible = true;//玩家光标指示器是否显示
	Timer timer_cursor_visibility;//玩家光标指示器可见定时器

	Vector2 last_hurt_direction;//最后一次受到攻击的方向
};