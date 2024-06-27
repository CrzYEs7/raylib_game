#include "player.hpp"
#include "raymath.h"
#include <iostream>
#include <string>

Player::Player()
{
	this->m_size = { 20, 20 };
	this->m_pos = { 0.0, 0.0 };
	this->m_dir = { 0.0, 0.0 };
	this->m_motion_vector = { 0.0, 0.0 };
	this->m_speed = 200.0;
	this->m_velocity = { 0.0, 0.0 };
	this->m_angle = 0;
}

void Player::move(float delta)
{
	float _delta = GetFrameTime();
	this->m_dir = { 0.0 , 0.0 };

	if (IsKeyDown(KEY_W))
		this->m_dir.y = -1.0;
	if (IsKeyDown(KEY_S))
		this->m_dir.y = 1.0;
	if (IsKeyDown(KEY_A))
		this->m_dir.x = -1.0;
	if (IsKeyDown(KEY_D))
		this->m_dir.x = 1.0;

	this->m_dir = Vector2Normalize(this->m_dir);
	this->m_velocity.x = this->m_dir.x * this->m_speed * delta;
	this->m_velocity.y = this->m_dir.y * this->m_speed * delta;

	this->m_pos = Vector2Add(this->m_pos, this->m_velocity);

}

Vector2 Player::get_position() const
{
	return m_pos;
}

Vector2 Player::get_size() const
{
	return m_size;
}

void Player::update(float delta)
{
	Vector2 _mouse_pos = GetMousePosition();
	this->move(delta);
}

void Player::draw() const
{
	//DrawRectangleV(this->m_pos, this->m_size, RED);

	DrawTriangle(Vector2Add(this->m_pos, {20, 10}), this->m_pos, Vector2Add(this->m_pos, {0, 20}), RED);

	// DEBUG speed
	DrawTextEx(font, ("speedX: " + std::to_string(this->m_velocity.x)).c_str(), 
		{ this->m_pos.x + 80.0f, this->m_pos.y + 10.0f }, font.baseSize, 4, RED);
	DrawTextEx(font, ("speedY: " + std::to_string(this->m_velocity.y)).c_str(), 
		{ this->m_pos.x + 80.0f, this->m_pos.y + 25.0f }, font.baseSize, 4, RED);
}