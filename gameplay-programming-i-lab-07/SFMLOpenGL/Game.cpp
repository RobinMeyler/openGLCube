#include <Game.h>

bool updatable = false;



Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	index = glGenLists(1);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	
	m_corners[0] = { 1.0f, 1.0f, -1.0f };
	m_corners[1] = {-1.0f, 1.0f, -1.0f };
	m_corners[2] = {-1.0f, -1.0f, -1.0f };
	m_corners[3] = { 1.0f, -1.0f, -1.0f };

	m_corners[4] = { 1.0f, 1.0f, 1.0f };
	m_corners[5] = { -1.0f, 1.0f, 1.0f };
	m_corners[6] = { -1.0f, -1.0f, 1.0f };
	m_corners[7] = { 1.0f, -1.0f, 1.0f };

	m_translations[0] = { 1.0f, 1.0f, 1.0f };
	m_translations[1] = { 1.0f, 1.0f, 1.0f };
	m_translations[2] = { 1.0f, 1.0f, 1.0f };
	m_translations[3] = { 1.0f, 1.0f, 1.0f };

	m_translations[4] = { 0.0f, 0.0f, 0.0f };
	m_translations[5] = { 0.0f, 0.0f, 0.0f };
	m_translations[6] = { 0.0f, 0.0f, 0.0f };
	m_translations[7] = { 0.0f, 0.0f, 0.0f };


	m_result[0] = m_corners[0] + m_translations[0];
	m_result[1] = m_corners[1] + m_translations[1];
	m_result[2] = m_corners[2] + m_translations[2];
	m_result[3] = m_corners[3] + m_translations[3];

	m_result[4] = m_corners[4] + m_translations[4];
	m_result[5] = m_corners[5] + m_translations[5];
	m_result[6] = m_corners[6] + m_translations[6];
	m_result[7] = m_corners[7] + m_translations[7];
}

void Game::update()
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < 8; i++)
		{
			if (m_corners[i].z >= 0)
			{
				m_translations[i] = (MyMatrix3::translation(MyVector3{ 0, 0.01 ,0 }) *  m_translations[i]);			// Rotate them all
			}
			else
			{
				m_translations[i] = (MyMatrix3::translationMinus(MyVector3{ 0, 0.01 ,0 }) *  m_translations[i]);
			}
			
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < 8; i++)
		{
			if (m_translations[i].z >= 0)
			{
				m_translations[i] = (MyMatrix3::translation(MyVector3{ 0, -0.01 ,0 }) *  m_translations[i]);			// Rotate them all
			}
			else
			{
				m_translations[i] = (MyMatrix3::translationMinus(MyVector3{ 0, -0.01 ,0 }) *  m_translations[i]);
			}

		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < 8; i++)
		{
			if (m_translations[i].z >= 0)
			{
				m_translations[i] = (MyMatrix3::translation(MyVector3{ 0.01,0 ,0 }) *  m_corners[i]);			// Rotate them all
			}
			else
			{
				m_translations[i] = (MyMatrix3::translationMinus(MyVector3{0.01, 0 ,0 }) *  m_corners[i]);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < 8; i++)
		{
			if (m_translations[i].z >= 0)
			{
				m_translations[i] = (MyMatrix3::translation(MyVector3{ -0.01,0 ,0 }) *  m_translations[i]);			// Rotate them all
			}
			else
			{
				m_translations[i] = (MyMatrix3::translationMinus(MyVector3{ -0.01, 0 ,0 }) *  m_translations[i]);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 8; i++)
		{
			m_corners[i] = (MyMatrix3::rotationZ(0.01) * m_corners[i]);			// Rotate them all
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < 8; i++)
		{
			m_corners[i] = (MyMatrix3::rotationX(0.01) * m_corners[i]);			// Rotate them all
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		for (int i = 0; i < 8; i++)
		{
			m_corners[i] = (MyMatrix3::rotationY(0.01) * m_corners[i]);			// Rotate them all
		}
	}
	m_result[0] = m_corners[0] + m_translations[0];
	m_result[1] = m_corners[1] + m_translations[1];
	m_result[2] = m_corners[2] + m_translations[2];
	m_result[3] = m_corners[3] + m_translations[3];

	m_result[4] = m_corners[4] + m_translations[4];
	m_result[5] = m_corners[5] + m_translations[5];
	m_result[6] = m_corners[6] + m_translations[6];
	m_result[7] = m_corners[7] + m_translations[7];

	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		// Bottom
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(m_result[6].x, m_result[6].y, m_result[6].z);
		glVertex3f(m_result[2].x, m_result[2].y, m_result[2].z);
		glVertex3f(m_result[3].x, m_result[3].y, m_result[3].z);
		glVertex3f(m_result[7].x, m_result[7].y, m_result[7].z);

		//Back Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(m_result[0].x, m_result[0].y, m_result[0].z);
		glVertex3f(m_result[1].x, m_result[1].y, m_result[1].z);
		glVertex3f(m_result[2].x, m_result[2].y, m_result[2].z);
		glVertex3f(m_result[3].x, m_result[3].y, m_result[3].z);

		// Side
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(m_result[4].x, m_result[4].y, m_result[4].z);
		glVertex3f(m_result[0].x, m_result[0].y, m_result[0].z);
		glVertex3f(m_result[3].x, m_result[3].y, m_result[3].z);
		glVertex3f(m_result[7].x, m_result[7].y, m_result[7].z);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(m_result[5].x, m_result[5].y, m_result[5].z);
		glVertex3f(m_result[1].x, m_result[1].y, m_result[1].z);
		glVertex3f(m_result[2].x, m_result[2].y, m_result[2].z);
		glVertex3f(m_result[6].x, m_result[6].y, m_result[6].z);

		// Top
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(m_result[4].x, m_result[4].y, m_result[4].z);
		glVertex3f(m_result[0].x, m_result[0].y, m_result[0].z);
		glVertex3f(m_result[1].x, m_result[1].y, m_result[1].z);
		glVertex3f(m_result[5].x, m_result[5].y, m_result[5].z);

		//Front Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(m_result[4].x, m_result[4].y, m_result[4].z);
		glVertex3f(m_result[5].x, m_result[5].y, m_result[5].z);
		glVertex3f(m_result[6].x, m_result[6].y, m_result[6].z);
		glVertex3f(m_result[7].x, m_result[7].y, m_result[7].z);



		//Complete the faces of the Cube
	}
	glEnd();
	glEndList();

















	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!updatable)
		{
			updatable = true;
		}
		else
			updatable = false;
	}

	if (updatable)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}
	
	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << endl;
	glLoadIdentity();
	glTranslatef(0, -3, -20);
	glRotatef(20, 1, 0, 0); // Rotates the camera on Y Axis

	glCallList(1);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

