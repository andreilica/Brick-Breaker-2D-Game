#include "BrickGame.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2DHome.h"
#include "Objects.h"


using namespace std;

BrickGame::BrickGame()
{
}

BrickGame::~BrickGame()
{
}

void BrickGame::Init()
{
	srand((unsigned int)time(NULL));
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner1 = glm::vec3(0, 80, 0);
	rectangleWidth1 = 25;
	rectangleHeight1 = 640;

	glm::vec3 corner2 = glm::vec3(25, 695, 0);
	rectangleWidth2 = 1230;
	rectangleHeight2 = 25;

	glm::vec3 corner3 = glm::vec3(1255, 80, 0);
	rectangleWidth3 = 25;
	rectangleHeight3 = 640;

	glm::vec3 corner4 = glm::vec3(0, 0, 0);
	rectangleWidth4 = 1280;
	rectangleHeight4 = 15;

	glm::vec3 dockCorner = glm::vec3(540, 20, 0);
	dockWidth = 200;
	dockHeight = 10;

	glm::vec3 brickCorner = glm::vec3(230, 600, 0);
	brickWidth = 50;
	brickHeight = 30;

	powerWidth = 10;
	powerHeight = 10;
	
	glm::vec3 ballCenter = glm::vec3(640, 60, 0);
	ballRadius = 10;
	bigBallRadius = 12;
	ballSpeed = 350;
	glm::vec3 life1Center = glm::vec3(30, 30, 0);
	glm::vec3 life2Center = glm::vec3(60, 30, 0);
	glm::vec3 life3Center = glm::vec3(90, 30, 0);

	translateDockX = 0;
	signX = 1;
	signY = 1;
	sinX = 1;
	cosX = 0;
	brokenBricks = 0;
	
	Wall* wall1 = new Wall("wall1", corner1, rectangleWidth1, rectangleHeight1, glm::vec3(0.66, 0.62, 0.41), true);
	AddMeshToList(wall1 -> getMesh());
	walls.push_back(wall1);
	Wall* wall2 = new Wall("wall2", corner2, rectangleWidth2, rectangleHeight2, glm::vec3(0.66, 0.62, 0.41), true);
	AddMeshToList(wall2->getMesh());
	walls.push_back(wall2);
	Wall* wall3 = new Wall("wall3", corner3, rectangleWidth3, rectangleHeight3, glm::vec3(0.66, 0.62, 0.41), true);
	AddMeshToList(wall3->getMesh());
	walls.push_back(wall3);
	wall4 = new Wall("wall4", corner4, rectangleWidth4, rectangleHeight4, glm::vec3(0.66, 0.62, 0.41), true);
	AddMeshToList(wall4->getMesh());

	Mesh* life1 = Object2DHome::CreateCircle("life1", life1Center, ballRadius, glm::vec3(0.6, 0.03, 0.16));
	AddMeshToList(life1);
	Mesh* life2 = Object2DHome::CreateCircle("life2", life2Center, ballRadius, glm::vec3(0.6, 0.03, 0.16));
	AddMeshToList(life2);
	Mesh* life3 = Object2DHome::CreateCircle("life3", life3Center, ballRadius, glm::vec3(0.6, 0.03, 0.16));
	AddMeshToList(life3);

	

	dock = new Dock("dock", dockCorner, dockWidth, dockHeight, glm::vec3(0.07, 0.11, 0.14), true, 3);
	AddMeshToList(dock ->getMesh());

	ball = new Ball("ball", ballCenter, ballRadius, glm::vec3(0.8, 0.51, 0.2));
	AddMeshToList(ball -> getMesh());


	nextLine = 0;
	for (int i = 0; i < 120; i++) {
		auto name = "brick" + std::to_string(i);
		Brick* brick;
		if (levelMatrix1[i / 12][i % 12] == 1) {
			brick = new Brick(name, brickCorner, brickWidth, brickHeight, glm::vec3(0.3, 0.22, 0.18), true, 3, nullptr);
			brick->setPowerful(true);
		}
		else {
			brick = new Brick(name, brickCorner, brickWidth, brickHeight, glm::vec3(0.54, 0.4, 0.32), true, 1, nullptr);
		}
		
		bricks.push_back(brick);
		nextLine++;
		if (nextLine % 12 == 0) {
			brickCorner.x = 230;
			brickCorner.y -= 40;
		}
		else {
			brickCorner.x += 70;
		}
	}

	for (it = bricks.begin(); it != bricks.end(); it++) {
		Brick* br = *it;
		Powerup* passThrough;
		Powerup* bottomWall;
		Powerup* bigBall;

		if ((it - bricks.begin()) % 7 == 0) {
			glm::vec3 coords = br->getCornerCoords();
			passThrough = new Powerup("power" + std::to_string(it - bricks.begin()), 
				glm::vec3(coords.x + (br->getDimensions().x / 2) - (powerWidth / 2), coords.y + (br->getDimensions().y / 2) - (powerHeight / 2), coords.z), 
				powerWidth, powerHeight, glm::vec3(1, 0, 0), true, powers::passThrough);

			pws.push_back(passThrough);
			br->setPower(passThrough);
			AddMeshToList(passThrough -> getMesh());
		}
		if ((it - bricks.begin()) % 8 == 0) {
			glm::vec3 coords = br->getCornerCoords();
			bottomWall = new Powerup("power" + std::to_string(it - bricks.begin()), 
				glm::vec3(coords.x + (br->getDimensions().x / 2) - (powerWidth / 2), coords.y + (br->getDimensions().y / 2) - (powerHeight / 2), coords.z),
				powerWidth, powerHeight, glm::vec3(1, 1, 0), true, powers::bottomWall);

			pws.push_back(bottomWall);
			br->setPower(bottomWall);
			AddMeshToList(bottomWall->getMesh());
		}
		if ((it - bricks.begin()) % 9 == 0) {
			glm::vec3 coords = br->getCornerCoords();
			bigBall = new Powerup("power" + std::to_string(it - bricks.begin()),
				glm::vec3(coords.x + (br->getDimensions().x / 2) - (powerWidth / 2), coords.y + (br->getDimensions().y / 2) - (powerHeight / 2), coords.z),
				powerWidth, powerHeight, glm::vec3(0, 0, 1), true, powers::bigBall);

			pws.push_back(bigBall);
			br->setPower(bigBall);
			AddMeshToList(bigBall->getMesh());
		}
	}

	for (it = bricks.begin(); it != bricks.end(); it++) {
		
		AddMeshToList( (*it) ->getMesh());
	}

}

void BrickGame::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor((GLclampf)0.91, (GLclampf)0.87, (GLclampf)0.78, (GLclampf)1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void BrickGame::Update(float deltaTimeSeconds)
{
	brickMatrix = glm::mat3(1);
	brickDestroyedMatrix = glm::mat3(1);
	modelMatrix = glm::mat3(1);
	ballMatrix = glm::mat3(1);
	dockMatrix = glm::mat3(1);
	powerMatrix = glm::mat3(1);

	for (int i = 1; i <= 3; i++) {
		auto name = "wall" + std::to_string(i);
		RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
	}

	dockMatrix *= Transform2D::Translate(dock->getTranslation().x, 0);
	RenderMesh2D(meshes["dock"], shaders["VertexColor"], dockMatrix);

	switch (dock->getLives()) {
		case 3:
			for (int i = 1; i <= 3; i++) {
				auto name = "life" + std::to_string(i);
				RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
			}
			break;
		case 2:
			for (int i = 1; i <= 2; i++) {
				auto name = "life" + std::to_string(i);
				RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
			}
			break;
		case 1:
			for (int i = 1; i <= 1; i++) {
				auto name = "life" + std::to_string(i);
				RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
			}
			break;
		case 0:
			int index;
			for (pwsIter = pws.begin(); pwsIter != pws.end(); pwsIter++) {
				(*pwsIter)->setActive(false);
			}
			dock->setLives(3);
			brokenBricks = 0;
			signX = 1;
			signY = 1;
			sinX = 1;
			cosX = 0;
			ball->setPass(false);
			ball->setBig(false);
			ball->setScale(1.0, 1.0);
			ball->setRadius(ballRadius);
			for (it = bricks.begin(); it != bricks.end(); it++) {
				Brick* br = *it;
				index = (int)(it - bricks.begin());
				if (dock->getLevel() == 1) {
					if (levelMatrix1[index / 12][index % 12] == 1) {
						br->setLife(3);
						br->setPowerful(true);
						br->setScale(1.0, 1.0);
						br->setDestroyed(false);
					}
					else {
						br->setLife(1);
						br->setPowerful(false);
						br->setScale(1.0, 1.0);
						br->setDestroyed(false);
					}
					if (br->getPower() != nullptr) {
						br->getPower()->setTranslation(0, 0);
						br->getPower()->setRot(0);
						br->getPower()->setLife(1);
						powerMatrix = glm::mat3(1);
					}
				} else if (dock->getLevel() == 2) {
					if (levelMatrix2[index / 12][index % 12] == 1) {
						br->setLife(3);
						br->setPowerful(true);
						br->setScale(1.0, 1.0);
						br->setDestroyed(false);
					}
					else {
						br->setLife(1);
						br->setPowerful(false);
						br->setScale(1.0, 1.0);
						br->setDestroyed(false);
					}
					if (br->getPower() != nullptr) {
						br->getPower()->setTranslation(0, 0);
						br->getPower()->setRot(0);
						br->getPower()->setLife(1);
						powerMatrix = glm::mat3(1);
					}
				}
				else {
					if ((it - bricks.begin()) % randomBricks == 0) {
						br->setLife(3);
						br->setPowerful(true);
						br->setScale(1.0, 1.0);
						br->setDestroyed(false);
					}
					else {
						br->setLife(1);
						br->setPowerful(false);
						br->setScale(1.0, 1.0);
						br->setDestroyed(false);
					}
					if (br->getPower() != nullptr) {
						br->getPower()->setTranslation(0, 0);
						br->getPower()->setRot(0);
						br->getPower()->setLife(1);
						powerMatrix = glm::mat3(1);
					}
				}
				
			}
	}
	
	if (brokenBricks == 120) {
		int index;
		dock->incLevel();
		randomBricks = rand() % 15 + 5;
		ballSpeed += 100;
		ball->setPass(false);
		ball->setBig(false);
		ball->setRadius(ballRadius);
		dock->setLives(3);
		launched = false;
		signX = 1;
		signY = 1;
		sinX = 1;
		cosX = 0;
		ball->setScale(1.0, 1.0);
		for (pwsIter = pws.begin(); pwsIter != pws.end(); pwsIter++) {
			(*pwsIter)->setActive(false);
		}
		for (it = bricks.begin(); it != bricks.end(); it++) {
			Brick* br = *it;
			index = (int)(it - bricks.begin());
			if (dock->getLevel() == 2) {
				if (levelMatrix2[index / 12][index % 12] == 1) {
					br->setPowerful(true);
					br->setLife(3);
					br->setScale(1.0, 1.0);
					br->setDestroyed(false);
				}
				else {
					br->setPowerful(false);
					br->setLife(1);
					br->setScale(1.0, 1.0);
					br->setDestroyed(false);
				}
				if (br->getPower() != nullptr) {
					br->getPower()->setTranslation(0, 0);
					br->getPower()->setRot(0);
					br->getPower()->setLife(1);
					powerMatrix = glm::mat3(1);
				}
			}
			else {
				if ((it - bricks.begin()) % randomBricks == 0) {
					br->setPowerful(true);
					br->setLife(3);
					br->setScale(1.0, 1.0);
					br->setDestroyed(false);
				}
				else {
					br->setPowerful(false);
					br->setLife(1);
					br->setScale(1.0, 1.0);
					br->setDestroyed(false);
				}
				if (br->getPower() != nullptr) {
					br->getPower()->setTranslation(0, 0);
					br->getPower()->setRot(0);
					br->getPower()->setLife(1);
					powerMatrix = glm::mat3(1);
				}
			}
			
		}
		
		brokenBricks = 0;
	}

	for (it = bricks.begin(); it != bricks.end(); it++) {
		Brick* br = *it;
		if (br->getLife() > 0) {
			if (!br->getPowerful())
				RenderMesh2D(meshes[br->getName()], brickMatrix, glm::vec3(0.54, 0.4, 0.32));
			else
				switch (br->getLife()) {
					case 3:
						RenderMesh2D(meshes[br->getName()], brickMatrix, glm::vec3(0.3, 0.22, 0.18));
						break;
					case 2:
						RenderMesh2D(meshes[br->getName()], brickMatrix, glm::vec3(0.36, 0.29, 0.25));
						break;
					case 1:
						RenderMesh2D(meshes[br->getName()], brickMatrix, glm::vec3(0.43, 0.36, 0.33));
						break;
				}
		}
		else if (br->getScale().x > 0 && br->getScale().y > 0 && br -> getLife() == 0) {
			br->setScale(br->getScale().x - 4 * deltaTimeSeconds, br->getScale().y - 4 * deltaTimeSeconds);
			brickDestroyedMatrix *= Transform2D::Translate((br->getCornerCoords().x + br->getDimensions().x / 2), (br->getCornerCoords().y + br->getDimensions().y / 2));
			brickDestroyedMatrix *= Transform2D::Scale(br->getScale().x, br->getScale().y);
			brickDestroyedMatrix *= Transform2D::Translate(- (br->getCornerCoords().x + br ->getDimensions().x / 2) , - (br->getCornerCoords().y + br->getDimensions().y / 2));
			
			if (!br->getPowerful())
				RenderMesh2D(meshes[br->getName()], brickDestroyedMatrix, glm::vec3(0.54, 0.4, 0.32));
			else
				RenderMesh2D(meshes[br->getName()], brickDestroyedMatrix, glm::vec3(0.43, 0.36, 0.33));
		}
		else {
			if (!br->getDestroyed()) {
				br->setDestroyed(true);
				brokenBricks++;
			}
			brickDestroyedMatrix = glm::mat3(1);
			if (br->getPower() != nullptr) {
				Powerup* pow = br->getPower();
				if (pow->getLife() > 0) {
					powerMatrix = glm::mat3(1);
					if (collisionDetPowerPlatform(pow, dock)) {
						pow->decreaseLife();
						if (pow->getActivity() == false) {
							pow->setActive(true);
							pow->startTime();
						}
					}

					pow->setTranslation(pow->getTranslation().x, pow->getTranslation().y - 200 * deltaTimeSeconds);
					pow->setRot(pow->getRot() + 2 * deltaTimeSeconds);
					if (pow->getRot() == 2 * M_PI)
						pow->setRot(0);
					powerMatrix *= Transform2D::Translate(pow->getCornerCoords().x + (pow->getDimensions().x / 2), pow->getCornerCoords().y + (pow->getDimensions().y / 2) + pow->getTranslation().y);
					powerMatrix *= Transform2D::Rotate(pow->getRot());
					powerMatrix *= Transform2D::Translate(-pow->getCornerCoords().x - (pow->getDimensions().x / 2), -pow->getCornerCoords().y - (pow->getDimensions().y / 2));
					RenderMesh2D(meshes[br->getPower()->getName()], shaders["VertexColor"], powerMatrix);
				}
				if (pow->getActivity() == true) {
					pow->setSecondsElapsed(difftime(time(0), pow->getStartTime()));
					switch (pow->getPowerType()) {
						case powers::bottomWall:
							if (walls.size() == 3) {
								walls.push_back(wall4);
							}
							RenderMesh2D(meshes["wall4"], shaders["VertexColor"], modelMatrix);
							break;
						case powers::passThrough:
							ball->setPass(true);
							break;
						case powers::bigBall:
							ball->setBig(true);
							ball->setRadius(15);
							break;
					}

					if (pow->getSecondsElapsed() == 5) {
						switch (pow->getPowerType()) {
						case powers::bottomWall:
							walls.pop_back();
							break;
						case powers::passThrough:
							ball->setPass(false);
							break;
						case powers::bigBall:
							ball->setBig(false);
							ball->setRadius(ballRadius);
							break;
						}
						pow->setActive(false);
						pow->setSecondsElapsed(0);
					}
				}
			}
		}
	}

	if (!launched) {
		ballMatrix *= Transform2D::Translate(dock->getTranslation().x, 0);
	}
	else {
		for (it = bricks.begin(); it != bricks.end(); it++) {
			Brick* br = *it;
			if (br->getLife() > 0) {
				std::pair <bool, collisionSide> check = collisionDetBricks(ball, br);
				if (check.first) {
					if (check.second == collisionSide::horizontal) {
						if (!ball->getBig())
							br->decreaseLife();
						else
							br->setLife(0);
						if(!ball->getPass())
							signY = -signY;
					}
					else if (check.second == collisionSide::vertical) {
						if (!ball->getBig())
							br->decreaseLife();
						else
							br->setLife(0);
						if (!ball->getPass())
							signX = -signX;
					}
					else if (check.second == collisionSide::corner) {
						if (!ball->getBig())
							br->decreaseLife();
						else
							br->setLife(0);
						if (!ball->getPass()) {
							signY = -signY;
							signX = -signX;
						}
					}
				}
			}
		}

		std::pair <bool, glm::vec2> check = collisionDetPlatform(ball, dock);
		if (check.first) {
			signX = 1;
			signY = 1;
			cosX = (check.second.x - dock->getTranslatedCoords().x - (dock->getDimensions().x / 2)) / (dock->getDimensions().x / 2);
			sinX = sqrt(1 - cosX * cosX);
		}

		for (wallIter = walls.begin(); wallIter != walls.end(); wallIter++) {
			Wall* wl = *wallIter;
			std::pair <bool, collisionSide> check = collisionDetWall(ball, wl);
			if (check.first) {
				if (check.second == collisionSide::horizontal) {
					signY = -signY;
				}
				else if (check.second == collisionSide::vertical) {
					signX = -signX;
				}
			}
		}

		if (ball->getBig()) {
			if(ball->getScale().x < 1.5 && ball->getScale().y < 1.5)
				ball->setScale(ball->getScale().x + deltaTimeSeconds, ball->getScale().y + deltaTimeSeconds);
			ballMatrix *= Transform2D::Translate(ball->getTranslatedCoords().x, ball->getTranslatedCoords().y);
			ballMatrix *= Transform2D::Scale(ball->getScale().x, ball->getScale().y);
			ballMatrix *= Transform2D::Translate(-(ball->getTranslatedCoords().x), -(ball->getTranslatedCoords().y));
		}
		else {
			if (ball->getScale().x > 1 && ball->getScale().y > 1)
				ball->setScale(ball->getScale().x - deltaTimeSeconds, ball->getScale().y - deltaTimeSeconds);
			ballMatrix *= Transform2D::Translate(ball->getTranslatedCoords().x, ball->getTranslatedCoords().y);
			ballMatrix *= Transform2D::Scale(ball->getScale().x, ball->getScale().y);
			ballMatrix *= Transform2D::Translate(-(ball->getTranslatedCoords().x), -(ball->getTranslatedCoords().y));
		}

		if (ball->getTranslatedCoords().y <= 0 || ball->getTranslatedCoords().y >= 720 ||ball->getTranslatedCoords().x <= 0 || ball->getTranslatedCoords().x >= 1280) { //Pierdere viata 
			dock->decreaseLife();
			launched = false;
			signX = 1;
			signY = 1;
			sinX = 1;
			cosX = 0;
			ball->setPass(false);
			ball->setBig(false);
			ball->setScale(1, 1);
			ball->setRadius(ballRadius);
			ballMatrix = glm::mat3(1);
			ball->setTranslation(dock->getTranslation().x, 0);
			ballMatrix *= Transform2D::Translate(dock->getTranslation().x, 0);

			for (pwsIter = pws.begin(); pwsIter != pws.end(); pwsIter++) {
				(*pwsIter)->setActive(false);
			}
		}
		else {
			ball->setTranslation(ball->getTranslation().x + cosX * signX * ballSpeed * deltaTimeSeconds, ball->getTranslation().y + sinX * signY * ballSpeed * deltaTimeSeconds);
			ballMatrix *= Transform2D::Translate(ball->getTranslation().x, ball->getTranslation().y);
		}

	}

	if (!ball->getBig())
		RenderMesh2D(meshes["ball"], shaders["VertexColor"], ballMatrix);
	else
		RenderMesh2D(meshes["ball"], ballMatrix, glm::vec3(1.0, 0.31, 0.0));

}

void BrickGame::FrameEnd()
{

}

void BrickGame::OnInputUpdate(float deltaTime, int mods)
{
	
}

void BrickGame::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_F) {
		dockResize = true;
	}
}

void BrickGame::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void BrickGame::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{	
	dock->setTranslation((float)mouseX - 640, 0);
	if(!launched)
		ball->setTranslation((float)mouseX - 640, 0);
	// add mouse move event
}

void BrickGame::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) {
		launched = true;
	}
}

void BrickGame::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void BrickGame::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void BrickGame::OnWindowResize(int width, int height)
{
}
