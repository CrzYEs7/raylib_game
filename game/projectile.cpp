#include "projectile.hpp"

Projectile::Projectile(Vector2 position, Vector2 direction) :
	m_pos(position), m_dir(direction), m_speed(500),
	m_look_dir({ 0.0,0.0 }), damage(5.0), m_size(5.0),
	m_angle(0.0), state(1)
{
}

void Projectile::update(float delta)
{
	this->m_look_dir = Vector2Subtract(Vector2Add(this->m_pos, { 10.0, 10.0 }), this->m_dir);
	this->m_angle = atan2f(this->m_look_dir.y, this->m_look_dir.x) * RAD2DEG;

	this->move(delta);
}

void Projectile::move(float delta)
{
	this->m_pos = Vector2Add(Vector2Scale(this->m_dir, this->m_speed * delta), this->m_pos);
}

void Projectile::draw() const
{
	DrawPoly(Vector2Add(this->m_pos, { this->m_size / 2, this->m_size / 2 }), 4,
		this->m_size, this->m_angle, GREEN);
}
