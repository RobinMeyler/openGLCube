#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "MyVector3.h"
#include "Matrix3.h"

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void unload();

	GLuint index;
	Clock clock;
	Time elapsed;

	
	

	MyVector3 m_corners[8];
	MyVector3 m_translations[8];
	MyVector3 m_result[8];
	bool showFace[6] = { false, false, false, false, false, false };
	float rotationAngle = 30.0f;
};