#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <time.h>   
#include <Core/Engine.h>
#include "Object2DHome.h"
#include "Objects.h"

class BrickGame : public SimpleScene
{
	public:
		BrickGame();
		~BrickGame();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix, dockMatrix, ballMatrix, brickMatrix, brickDestroyedMatrix, powerMatrix;
		int nextLine, randomBricks, brokenBricks;
		float translateDockX;
		float scaleX, scaleY;
		float signX, signY, sinX, cosX;
		float platformCenter;
		Ball* ball;
		float ballRadius, bigBallRadius, ballSpeed;
		Wall* wall4;
		std::vector<Brick*> bricks;
		std::vector<Brick*>::iterator it;
		std::vector<Wall*> walls;
		std::vector<Wall*>::iterator wallIter;
		std::vector<Powerup*> pws;
		std::vector<Powerup*>::iterator pwsIter;
		float rectangleWidth1, rectangleHeight1, rectangleWidth2, rectangleHeight2, rectangleWidth3, rectangleHeight3, rectangleWidth4, rectangleHeight4;
		float dockWidth, dockHeight, brickWidth, brickHeight, powerWidth, powerHeight;

		Dock* dock;
		bool dockResize, launched;	

		int levelMatrix1[10][12] = {
			{0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
			{0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
			{0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
			{0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0},
			{0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0},
			{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
			{0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0},
			{0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0},
			{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
			{0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0}
		};

		int levelMatrix2[10][12] = {
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0 },
			{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 },
			{ 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0 },
			{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
			{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
			{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
		};
};
