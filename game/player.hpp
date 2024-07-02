#pragma once

#include "raylib.h"
#include "projectile.hpp"
#include <vector>

class Player
{
public:
	Player();
	~Player();

private:
	Font font = LoadFont("resources/mecha.png");
	Vector2 m_pos;
	Vector2 m_mov_dir;
	Vector2 m_motion_vector;
	Vector2 m_velocity;
	Vector2 m_size;
	Vector2 m_mouse_pos;
	Vector2 m_look_dir;
	float m_speed;
	float m_angle;

private:
	void move(float delta);
	void attack();

public:
	void update(float delta, Camera2D camera, Vector2 mouse_position);
	void draw() const;

	Vector2 get_position() const;
	Vector2 get_size() const;
	std::vector<Projectile*> attacks;
};