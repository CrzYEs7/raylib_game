#include "player.hpp"
#include "raymath.h"
#include <iostream>
#include <string>

Player::Player() :
	m_mov_dir({ 0.0, 0.0 }), m_mouse_pos({ 0.0, 0.0 }),
	m_size({ 20, 20 }), m_motion_vector({ 0.0, 0.0 }),
	m_pos({ 0.0, 0.0 }), m_speed(200.0), m_angle(0),
	m_velocity({ 0.0, 0.0 }), m_look_dir({ 0.0, 0.0 })
{
}

void Player::update(float delta, Camera2D camera, Vector2 mouse_position)
{
	this->m_look_dir = Vector2Subtract(Vector2Add(this->m_pos, { 10.0, 10.0 }), mouse_position);
	this->m_angle = atan2f(this->m_look_dir.y, this->m_look_dir.x) * RAD2DEG;
	this->move(delta);

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		this->attack();
	}
}

void Player::draw() const
{
	DrawPoly(Vector2Add(this->m_pos, {10, 10}), 3, 20.0, this->m_angle - 180, RED);
	//DrawRectangleV(this->m_pos, this->m_size, RED);

	// DEBUG speed
	DrawTextEx(font, ("speedX: " + std::to_string(this->m_velocity.x)).c_str(), 
		{ this->m_pos.x + 80.0f, this->m_pos.y + 10.0f }, font.baseSize, 4, RED);
	DrawTextEx(font, ("speedY: " + std::to_string(this->m_velocity.y)).c_str(), 
		{ this->m_pos.x + 80.0f, this->m_pos.y + 25.0f }, font.baseSize, 4, RED);
	
	// DEBUG mouse position
	DrawTextEx(font, ("mouseX: " + std::to_string(this->m_mouse_pos.x)).c_str(),
		{ this->m_pos.x + 80.0f, this->m_pos.y + 50.0f }, font.baseSize, 4, BLUE);
	DrawTextEx(font, ("mouseY: " + std::to_string(this->m_mouse_pos.y)).c_str(),
		{ this->m_pos.x + 80.0f, this->m_pos.y + 70.0f }, font.baseSize, 4, BLUE);
}

void Player::move(float delta)
{
	this->m_mov_dir = { 0.0 , 0.0 };

	if (IsKeyDown(KEY_W))
		this->m_mov_dir.y = -1.0;
	if (IsKeyDown(KEY_S))
		this->m_mov_dir.y = 1.0;
	if (IsKeyDown(KEY_A))
		this->m_mov_dir.x = -1.0;
	if (IsKeyDown(KEY_D))
		this->m_mov_dir.x = 1.0;

	this->m_mov_dir = Vector2Normalize(this->m_mov_dir);
	this->m_velocity.x = this->m_mov_dir.x * this->m_speed * delta;
	this->m_velocity.y = this->m_mov_dir.y * this->m_speed * delta;
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

void Player::attack()
{
	std::cout << "attack" << std::endl;
}