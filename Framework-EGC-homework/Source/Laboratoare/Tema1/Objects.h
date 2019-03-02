#pragma once
#include <iostream>
#include <cmath>
#include <ctime>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

enum class collisionSide { horizontal, vertical, corner};
enum class powers {passThrough, bottomWall, bigBall};

class Powerup {
public:
	Powerup(std::string name, glm::vec3 powerCorner, float width, float height, glm::vec3 color, bool fill, powers type);
	Powerup();
	~Powerup();
	Mesh* getMesh();
	glm::vec2 getDimensions();
	std::string getName();
	glm::vec3 getCornerCoords();
	glm::vec3 getColor();
	bool getFill();
	powers getPowerType();
	void setLife(int l);
	int getLife();
	void decreaseLife();
	void setTranslation(float x, float y);
	void setRot(float u);
	float getRot();
	void setActive(bool a);
	void startTime();
	time_t getStartTime();
	void setSecondsElapsed(double sec);
	double getSecondsElapsed();
	bool getActivity();
	glm::vec2 getTranslation();
	glm::vec2 getTranslatedCoords();
private:
	std::string name;
	glm::vec3 corner, color;
	powers type;
	int life;
	float width, height, translateX, translateY, rot;
	bool fill;
	bool active;
	time_t start;
	double secondsElapsed;
	Mesh* powerMesh;
};

class Wall {
public:
	Wall(std::string name, glm::vec3 wallCorner, float width, float height, glm::vec3 color, bool fill);
	~Wall();
	Mesh* getMesh();
	glm::vec2 getDimensions();
	std::string getName();
	glm::vec3 getCornerCoords();
private:
	std::string name;
	glm::vec3 corner, color;
	float width, height;
	bool fill;
	Mesh* wallMesh;
};


class Brick{
public: 
	Brick(std::string name, glm::vec3 brickCorner, float width, float height, glm::vec3 color, bool fill, int life, Powerup* pow);
	~Brick();
	Mesh* getMesh();
	glm::vec2 getDimensions();
	std::string getName();
	glm::vec3 getCornerCoords();
	int getLife();
	void decreaseLife();
	void setLife(int life);
	void setScale(float x, float y);
	void setPower(Powerup* power);
	void setDestroyed(bool a);
	bool getDestroyed();
	void setPowerful(bool a);
	bool getPowerful();
	Powerup* getPower();
	glm::vec2 getScale();
private:
	std::string name;
	glm::vec3 corner, color;
	int life;
	float width, height, scaleX, scaleY;
	bool fill, destroyed, powerful;
	Mesh* brickMesh;
	Powerup* power;
};

class Dock {
public:
	Dock(std::string name, glm::vec3 dockCorner, float dockWidth, float dockHeight, glm::vec3 color, bool fill, int lives);
	~Dock();
	Mesh* getMesh();
	glm::vec2 getDimensions();
	std::string getName();
	glm::vec3 getCornerCoords();
	int getLives();
	void setLives(int lives);
	void decreaseLife();
	void setTranslation(float x, float y);
	void setDimensions(float x, float y);
	void setWide(bool w);
	bool getWide();
	void setLevel(int lev);
	void incLevel();
	int getLevel();
	glm::vec2 getTranslation();
	glm::vec2 getTranslatedCoords();
private:
	int lives, level;
	std::string name;
	glm::vec3 corner, color;
	float width, height, translationX, translationY;
	bool fill, wide;
	Mesh* dockMesh;
};

class Ball {
public:
	Ball(std::string name, glm::vec3 center, float radius, glm::vec3 color);
	~Ball();
	Mesh* getMesh();
	float getRadius();
	std::string getName();
	glm::vec3 getCenterCoords();
	void setTranslation(float x, float y);
	glm::vec2 getTranslation();
	glm::vec2 getTranslatedCoords();
	void updateMesh(float newRadius);
	bool getPass();
	void setPass(bool p);
	bool getBig();
	void setBig(bool p);
	void setRadius(float r);
	void setScale(float x, float y);
	glm::vec2 getScale();
private:
	std::string name;
	glm::vec3 center, color;
	float radius, translateX, translateY, scaleX, scaleY;
	bool passThrough, big;
	Mesh* ballMesh;
};



float interval(float value, float min, float max);
std::pair <bool, collisionSide> collisionDetBricks(Ball* ball, Brick* brick);
std::pair <bool, collisionSide> collisionDetWall(Ball* ball, Wall* wall);
std::pair <bool, glm::vec2> collisionDetPlatform(Ball* ball, Dock* dock);
bool collisionDetPowerPlatform(Powerup* pow, Dock* dock);

