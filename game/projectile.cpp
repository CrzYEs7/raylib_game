#include "projectile.hpp"

Projectile::Projectile(Vector2 position, Vector2 direction) :
	m_pos(position), m_dir(direction), m_speed(500),
	m_look_dir({ 0.0,0.0 }), damage(5.0), m_size(5.0),
	m_angle(0.0), state(1), m_dist_traveled(0.0),
	m_max_dist_traveled(200)
{
	this->m_pos = Vector2Subtract(this->m_pos, {this->m_size / 2, this->m_size / 2 });
}

void Projectile::update(float delta)
{
	if (m_max_dist_traveled < m_dist_traveled)
	{
		this->state = 0;
		return;
	}
	this->m_look_dir = Vector2Subtract(Vector2Add(this->m_pos, { m_size / 2, m_size / 2 }), this->m_dir);
	this->m_angle = atan2f(this->m_look_dir.y, this->m_look_dir.x) * RAD2DEG;

	this->m_dist_traveled += m_speed * delta;
	this->move(delta);
}

void Projectile::move(float delta)
{
	this->m_pos = Vector2Add(Vector2Scale(this->m_dir, this->m_speed * delta), this->m_pos);
}

void Projectile::draw() const
{
	DrawPoly(Vector2Add(this->m_pos, { this->m_size / 2, this->m_size / 2 }), 4,
		this->m_size/2, this->m_angle, GREEN);
}
