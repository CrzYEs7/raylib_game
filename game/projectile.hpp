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
	Vector2 m_look_dir;
	Vector2 m_pos;
	Vector2 m_dir;

public:
	float damage;
	int state;

public:
	void update(float delta);
	void draw() const;

private:
	void move(float delta);
};

