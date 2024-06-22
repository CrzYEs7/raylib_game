#include "raylib.h"

class Player
{
public:
	Player();
	~Player() = default;
private:
	Vector2 m_pos;
	Vector2 m_dir;
	Vector2 m_mov_vector;
	Vector2 m_velocity;
	float m_speed;

public:
	void move(float delta);
	void update(float delta);
	void draw() const;
};