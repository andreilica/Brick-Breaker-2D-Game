#include "Object2DHome.h"
#include <iostream>
#include <Core/Engine.h>

Mesh* Object2DHome::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
		
	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* Object2DHome::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color)
{
	int triangles = 30;
	float circleX = center.x;
	float circleY = center.y;
	float circumference = (float) (2 * M_PI); 
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(circleX, circleY, 0), color));

	for (double i = 0; i <= triangles; i++) {
		vertices.push_back(VertexFormat(glm::vec3(circleX + (radius * cos(i * circumference / triangles)), circleY + (radius * sin(i * circumference / triangles)), 0), color));
	}

	Mesh* circle = new Mesh(name);
	std::vector<unsigned short> indices;

	for (int i = 0; i < triangles + 2; i++) {
		indices.push_back(i);
	}

	circle->SetDrawMode(GL_TRIANGLE_FAN);
	circle->InitFromData(vertices, indices);

	return circle;
}