#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

//#include<vld.h>

#include"SceneManager.h"

#include<string.h>

float Camera::cameraCos = 1;
float Camera::cameraSin = 0;

unsigned int Camera::screenWidth = 1280;
unsigned int Camera::screenHeight = 720;

template<class T>
void inBytes(T val, const char *c = "\n")
{
	const int size = sizeof(T);
	unsigned char *bytes = (unsigned char*)(&val);
	unsigned char checker = 1 << 7;

	//printf("checker = %d", checker);

	for (int n = size - 1; n >= 0; n--)
	{
		unsigned char byte = bytes[n];
		//printf("%d", byte);
		for (int i = 0; i < 8; i++)
		{
			printf("%c", ((byte & checker) == checker) ? '1' : '0');
			byte <<= 1;
		}
		if (n > 0)
			printf(" ");
	}

	printf("%s", c);
}

void test()
{
	float min = 7, max = 8;

	for (float val = min; val <= max; val += (1.f / 256.f))
	{
		printf("%f:\t", val);
		inBytes(val);
	}

	system("pause");
}

void test2()
{
	float min = 1, max = 2048;

	for (float val = min; val <= max; val += 1)
	{
		printf("%f:\t", val);
		inBytes(val);
	}

	system("pause");
}

#define PrintSizeOf(X) printf("size of " #X " = %zd B\n", sizeof(X));

ItemValues **itemValues;

//#pragma startup itemValuesInit
//#pragma exit itemValuesDelete

int main()
{
	//printf("%f\n", TAN(60));

	//PrintSizeOf(DynamicObject);
	//PrintSizeOf(Unit);
	//PrintSizeOf(Ship);

	srand(time(NULL));
	//test2();

	//return 0;

	itemValuesInit();

	Game *game = new Game();

	SceneManager *sceneManager = new SceneManager(game, SceneType::Menu);

	bool vertical_sync = false;

	string window_name = "Everspace i FTL w jednym";

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(Camera::screenWidth, Camera::screenHeight, 32U), window_name, sf::Style::Close, settings);
	window.setVerticalSyncEnabled(vertical_sync);
	//window.setMouseCursorVisible(false);

	//window.setFramerateLimit(10);

	sf::Clock fps;
	sf::Clock fps2;
	size_t fpsc = 0;

	//sf::Clock clock;

	//window.setVisible(false);

	while (window.isOpen())
	{
		bool changeScene = false;
		Scene *scene = sceneManager->getActiveScene();

		sf::Event event;
		sf::Keyboard keys;
		float time = fps.restart().asSeconds();
		
		/*
		fpsc++;
		if (fps2.getElapsedTime().asSeconds() >= 1.)
		{
			fps2.restart();
			printf("%d\n", fpsc);
			fpsc = 0;
		}
		//*/

		//printf("%f\n", 1.0f / time.asSeconds());

		bool cont = true;

		while (window.pollEvent(event))
		{
			sf::Mouse mouse;
			Mouse::update(window, event, mouse);
			//Mouse::getOnWindowPos().print("\n");

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				Camera::screenWidth = event.size.width;
				Camera::screenHeight = event.size.height;
				sf::View view;
				view.setSize(Camera::screenWidth, Camera::screenHeight);
				window.setView(view);
				//window.setSize({ screenWidth, screenHeight });
				break;
			}

			if (changeScene == false)
			{
				if (scene->event(event, keys, time))
					changeScene = true;
			}
		}

		if (scene->update(event, keys, time))
			changeScene = true;

		if (changeScene)
		{
			sceneManager->changeScene();
			scene = sceneManager->getActiveScene();
		}

		//cout << window.getSize().x << ", " << window.getSize().y << "\n";

		if (sceneManager->getActiveSceneType() == SceneType::NONE)
		{
			window.close();
			//printf("\nEND\n\n");
			//system("pause");
			break;
		}

		window.clear(sf::Color::Black);
		
		scene->draw(window);

		window.display();
	}

	delete game;

	delete sceneManager;

	itemValuesDelete();

	//system("pause");

	return 0;
}