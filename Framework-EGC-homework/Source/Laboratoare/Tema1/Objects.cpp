#include "Object2DHome.h"
#include "Objects.h"

Brick::Brick(std::string name, glm::vec3 brickCorner, float width, float height, glm::vec3 color, bool fill, int life, Powerup* pow)
{
	this->name = name;
	this->corner = brickCorner;
	this->width = width;
	this->height = height;
	this->color = color;
	this->fill = fill;
	this->life = life;
	this->brickMesh = Object2DHome::CreateRectangle(name, brickCorner, width, height, color, fill);
	this->scaleX = 1;
	this->scaleY = 1;
	this->power = pow;
	this->destroyed = false;
	this->powerful = false;
}

Brick::~Brick() {}

Mesh * Brick::getMesh()
{
	return this->brickMesh;
}

glm::vec2 Brick::getDimensions()
{
	return glm::vec2(this->width, this->height);
}

std::string Brick::getName()
{
	return this -> name;
}

glm::vec3 Brick::getCornerCoords()
{
	return this -> corner;
}

int Brick::getLife()
{
	return this->life;
}

void Brick::decreaseLife()
{
	if (this -> life > 0)
		this -> life--;
}

void Brick::setLife(int life)
{
	this->life = life;
}

void Brick::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;
}

void Brick::setPower(Powerup * power)
{
	this->power = power;
}

void Brick::setDestroyed(bool a)
{
	this->destroyed = a;
}

bool Brick::getDestroyed()
{
	return this->destroyed;
}

void Brick::setPowerful(bool a)
{
	this->powerful = a;
}

bool Brick::getPowerful()
{
	return this->powerful;
}

Powerup * Brick::getPower()
{
	return this->power;
}

glm::vec2 Brick::getScale()
{
	return glm::vec2(this->scaleX, this->scaleY);
}

Dock::Dock(std::string name, glm::vec3 dockCorner, float dockWidth, float dockHeight, glm::vec3 color, bool fill, int lives)
{
	this->name = name;
	this->corner = dockCorner;
	this->width = dockWidth;
	this->height = dockHeight;
	this->color = color;
	this->fill = fill;
	this->lives = lives;
	this->dockMesh = Object2DHome::CreateRectangle(name, dockCorner, dockWidth, dockHeight, color, fill);
	this->translationX = 0;
	this->translationY = 0;
	this->level = 1;
}

Dock::~Dock(){}

Mesh * Dock::getMesh()
{
	return this->dockMesh;
}

glm::vec2 Dock::getDimensions()
{
	return glm::vec2(this->width, this->height);
}

std::string Dock::getName()
{
	return this->name;
}

glm::vec3 Dock::getCornerCoords()
{
	return this->corner;
}

int Dock::getLives()
{
	return this->lives;
}

void Dock::setLives(int lives)
{
	this->lives = lives;
}

void Dock::decreaseLife()
{
	if(lives > 0)
		this->lives--;
}

void Dock::setTranslation(float x, float y)
{
	this->translationX = x;
	this->translationY = y;
}

void Dock::setDimensions(float x, float y)
{
	this->width = x;
	this->height = y;
}

void Dock::setWide(bool w)
{
	this->wide = w;
}

bool Dock::getWide()
{
	return this->wide;
}

void Dock::setLevel(int lev)
{
	this->level = lev;
}

void Dock::incLevel()
{
	level++;
}

int Dock::getLevel()
{
	return level;
}

glm::vec2 Dock::getTranslation()
{
	return glm::vec2(this->translationX, this->translationY);
}

glm::vec2 Dock::getTranslatedCoords()
{
	return glm::vec2(this->corner.x + this->translationX, this->corner.y + this->translationY);
}

Ball::Ball(std::string name, glm::vec3 center, float radius, glm::vec3 color)
{
	this->name = name;
	this->center = center;
	this->radius = radius;
	this->color = color;
	this->ballMesh = Object2DHome::CreateCircle(name, center, radius, color);
	this->translateX = 0;
	this->translateY = 0;
	this->passThrough = false;
	this->big = false;
	this->scaleX = 1;
	this->scaleY = 1;
}

Ball::~Ball(){}

Mesh * Ball::getMesh()
{
	return this->ballMesh;
}

float Ball::getRadius()
{
	return this -> radius;
}

std::string Ball::getName()
{
	return this -> name;
}

glm::vec3 Ball::getCenterCoords()
{
	return glm::vec3(this->center.x, this->center.y, this->center.z);
}

void Ball::setTranslation(float x, float y)
{
	this->translateX = x;
	this->translateY = y;
}

glm::vec2 Ball::getTranslation()
{
	return glm::vec2(this->translateX, this->translateY);
}

glm::vec2 Ball::getTranslatedCoords()
{
	return glm::vec2(this->center.x + this -> translateX, this->center.y + this->translateY);
}

void Ball::updateMesh(float newRadius)
{
	this->ballMesh = Object2DHome::CreateCircle(this->name, this->center, newRadius, this->color);
}

bool Ball::getPass()
{
	return this->passThrough;
}

void Ball::setPass(bool p)
{
	this->passThrough = p;
}

bool Ball::getBig()
{
	return big;
}

void Ball::setBig(bool p)
{
	big = p;
}

void Ball::setRadius(float r)
{
	this->radius = r;
}

void Ball::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;
}

glm::vec2 Ball::getScale()
{
	return glm::vec2(this->scaleX, this->scaleY);
}

Wall::Wall(std::string name, glm::vec3 wallCorner, float width, float height, glm::vec3 color, bool fill)
{
	this->name = name;
	this->corner = wallCorner;
	this->width = width;
	this->height = height;
	this->color = color;
	this->fill = fill;
	this->wallMesh = Object2DHome::CreateRectangle(name, wallCorner, width, height, color, true);
}

Mesh * Wall::getMesh()
{
	return this->wallMesh;
}

glm::vec2 Wall::getDimensions()
{
	return glm::vec2(this->width, this->height);
}

std::string Wall::getName()
{
	return this->name;
}

glm::vec3 Wall::getCornerCoords()
{
	return this->corner;
}

float interval(float value, float min, float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

std::pair <bool, collisionSide> collisionDetBricks(Ball * ball, Brick * brick)
{
	float nearX, nearY, centerX, centerY, brickX, brickY, distance;
	collisionSide side;
	bool collision;
	centerX = ball->getTranslatedCoords().x;
	centerY = ball->getTranslatedCoords().y;
	brickX = brick->getCornerCoords().x;
	brickY = brick->getCornerCoords().y;

	nearX = interval(centerX, brickX, brickX + brick->getDimensions().x);
	nearY = interval(centerY, brickY, brickY + brick->getDimensions().y);

	if (nearX == brickX || nearX == brickX + brick->getDimensions().x)
		if (nearY == brickY || nearY == brickY + brick->getDimensions().y)
			side = collisionSide::corner;
		else
			side = collisionSide::vertical;
	else
		side = collisionSide::horizontal;

	distance = (centerX - nearX) * (centerX - nearX) + (centerY - nearY) * (centerY - nearY);
	collision = distance <= (ball->getRadius() * ball->getRadius());
	return std::pair <bool, collisionSide> (collision, side);
}

std::pair <bool, collisionSide> collisionDetWall(Ball * ball, Wall * wall)
{
	float nearX, nearY, centerX, centerY, wallX, wallY, distance;
	collisionSide side;
	bool collision;
	centerX = ball->getTranslatedCoords().x;
	centerY = ball->getTranslatedCoords().y;
	wallX = wall->getCornerCoords().x;
	wallY = wall->getCornerCoords().y;

	nearX = interval(centerX, wallX, wallX + wall->getDimensions().x);
	nearY = interval(centerY, wallY, wallY + wall->getDimensions().y);

	if (nearX == wallX || nearX == wallX + wall->getDimensions().x)
		if (nearY == wallY || nearY == wallY + wall->getDimensions().y)
			side = collisionSide::corner;
		else
			side = collisionSide::vertical;
	else
		side = collisionSide::horizontal;

	distance = (centerX - nearX) * (centerX - nearX) + (centerY - nearY) * (centerY - nearY);
	collision = distance <= (ball->getRadius() * ball->getRadius());
	return std::pair <bool, collisionSide>(collision, side);
}

std::pair <bool, glm::vec2> collisionDetPlatform(Ball * ball, Dock * dock)
{
	float nearX, nearY, centerX, centerY, dockX, dockY, distance;
	float radius = ball->getRadius();
	bool collision;
	centerX = ball->getTranslatedCoords().x;
	centerY = ball->getTranslatedCoords().y;
	dockX = dock->getTranslatedCoords().x;
	dockY = dock->getTranslatedCoords().y;

	nearX = interval(centerX, dockX, dockX + dock->getDimensions().x);
	nearY = interval(centerY, dockY, dockY + dock->getDimensions().y);

	distance = (centerX - nearX) * (centerX - nearX) + (centerY - nearY) * (centerY - nearY);
	collision = distance <= (radius * radius);
	return std::pair <bool, glm::vec2> (collision, glm::vec2(nearX, nearY));
}

bool collisionDetPowerPlatform(Powerup* pow, Dock* dock)
{
	float nearX, nearY, centerX, centerY, dockX, dockY, distance;
	float radius = (float)(pow->getDimensions().x * sqrt(2)) / 2;
	bool collision;
	centerX = pow->getTranslatedCoords().x + pow->getDimensions().x / 2;
	centerY = pow->getTranslatedCoords().y + pow->getDimensions().y / 2;
	dockX = dock->getTranslatedCoords().x;
	dockY = dock->getTranslatedCoords().y;

	nearX = interval(centerX, dockX, dockX + dock->getDimensions().x);
	nearY = interval(centerY, dockY, dockY + dock->getDimensions().y);

	distance = (centerX - nearX) * (centerX - nearX) + (centerY - nearY) * (centerY - nearY);
	collision = distance <= (radius * radius);
	return collision;
}

Powerup::Powerup(std::string name, glm::vec3 powerCorner, float width, float height, glm::vec3 color, bool fill, powers type)
{
	this->name = name;
	this->corner = powerCorner;
	this->width = width;
	this->height = height;
	this->color = color;
	this->fill = fill;
	this->type = type;
	this->powerMesh = Object2DHome::CreateRectangle(name, powerCorner, width, height, color, true);
	this->translateX = 0;
	this->translateY = 0;
	this->rot = 0;
	this->life = 1;
	this->active = false;
}

Powerup::Powerup(){}

Powerup::~Powerup(){}

Mesh * Powerup::getMesh()
{
	return this->powerMesh;
}

glm::vec2 Powerup::getDimensions()
{
	return glm::vec2(this->width, this->height);
}

std::string Powerup::getName()
{
	return this->name;
}

glm::vec3 Powerup::getCornerCoords()
{
	return this->corner;
}

glm::vec3 Powerup::getColor()
{
	return this->color;
}

bool Powerup::getFill()
{
	return this->fill;
}

powers Powerup::getPowerType()
{
	return this->type;
}

void Powerup::setLife(int l)
{
	this->life = l;
}

int Powerup::getLife()
{
	return this->life;
}

void Powerup::decreaseLife()
{
	if (this->life > 0)
		this->life--;
}

void Powerup::setTranslation(float x, float y)
{
	this->translateX = x;
	this->translateY = y;
}

void Powerup::setRot(float u)
{
	this->rot = u;
}

float Powerup::getRot()
{
	return this->rot;
}

void Powerup::setActive(bool a)
{
	this->active = a;
}

void Powerup::startTime()
{
	this->start = time(0);
}

time_t Powerup::getStartTime()
{
	return this->start;
}

void Powerup::setSecondsElapsed(double sec)
{
	this->secondsElapsed = sec;
}

double Powerup::getSecondsElapsed()
{
	return this->secondsElapsed;
}

bool Powerup::getActivity()
{
	return this->active;
}

glm::vec2 Powerup::getTranslation()
{
	return glm::vec2(this->translateX, this->translateY);
}

glm::vec2 Powerup::getTranslatedCoords()
{
	return glm::vec2(this->corner.x + this -> translateX, this->corner.y + this -> translateY);
}
