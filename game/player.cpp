#include "player.hpp"
#include "raymath.h"
#include <iostream>
#include <string>

Player::Player()
{
	this->m_pos = { 0.0, 0.0 };
	this->m_dir = { 0.0, 0.0 };
	this->m_mov_vector = { 0.0, 0.0 };
	this->m_speed = 150.0;
	this->m_velocity = { 0.0, 0.0 };
}

void Player::move(float delta)
{
	this->m_dir = { 0.0, 0.0 };

	if (IsKeyDown(KEY_W))
		this->m_dir.y = -1;
	if (IsKeyDown(KEY_S))
		this->m_dir.y = 1;
	if (IsKeyDown(KEY_A))
		this->m_dir.x = -1;
	if (IsKeyDown(KEY_D))
		this->m_dir.x = 1;

	this->m_dir = Vector2Normalize(this->m_dir);
	this->m_velocity.x = m_dir.x * this->m_speed;
	this->m_velocity.y = m_dir.y * this->m_speed;


	this->m_mov_vector = { this->m_velocity.x * delta, this->m_velocity.y * delta };
	this->m_pos = Vector2Add(this->m_pos, m_mov_vector);
}

void Player::update(float delta)
{
	this->move(delta);
}

void Player::draw() const
{
	DrawRectangle(this->m_pos.x, this->m_pos.y, 20, 20, RED);

	// Debug speed
	DrawText(("speedX: " + std::to_string(m_mov_vector.x)).c_str(), 130, 10, 8, RED);
	DrawText(("speedY: " + std::to_string(m_mov_vector.y)).c_str(), 130, 20, 8, RED);
}