#include "raylib.h"

class Player
{
public:
	Player();
	~Player() = default;
private:
	Font font = font = LoadFont("resources/mecha.png");
	Vector2 m_pos;
	Vector2 m_dir;
	Vector2 m_motion_vector;
	Vector2 m_velocity;
	Vector2 m_size;
	float m_speed;

public:
	void move(float delta);
	void update(float delta);
	void draw() const;

	Vector2 get_position() const;
	Vector2 get_size() const;
};