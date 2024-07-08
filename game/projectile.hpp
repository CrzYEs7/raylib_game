#pragma once

#include "raylib.h"
#include "raymath.h"
#include <string>

class Projectile
{
public:
	Projectile(Vector2 position, Vector2 direction);
	~Projectile() = default;
private:
	float m_speed;
	float m_size;
	float m_angle;
	float m_dist_traveled;
	float m_max_dist_traveled;
	Vector2 m_center;
	Vector2 m_look_dir;
	Vector2 m_pos;
	Vector2 m_dir;

public:
	float damage;
	int state;

public:
	void update(float delta);
	void draw() const;
	Vector2 get_center() const;

private:
	void set_origin(Vector2 position);
	void move(float delta);
};

