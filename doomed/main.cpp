#include <SFML\Graphics.hpp>
#include <iostream>
#include "view.h"
#include <sstream>
#include "level.h"
#include <vector>
#include <list>
#include <SFML\Audio.hpp>


using namespace sf;


int heroDimensionX = 16;
int heroDimensionY = 16;
int dirTemp;




class CHARACTER
{
public:
	std::vector<Object> obj;
	float x, y, w, h, dx, dy, speed,timer;
	int health;
	bool life, onGround, isMove;
	Texture texture;
	Sprite sprite;
	String name;
	CHARACTER(Texture &image, float X, float Y, float Weight, float Height,String charName)
	{
		name = charName;
		isMove = false;
		timer = 0;
		onGround = false;
		life = true;
		speed = 0;
		dx = 0;
		dy = 0;
		sprite.setTexture(image);
		x = X; w = Weight;
		y = Y; h = Height;
		health = 100;
	}
	FloatRect getRect()
	{
		return FloatRect(x,y,w,h);
	}
	virtual void update(float time) = 0;
};
class PLAYER : public CHARACTER
{
public:
	SoundBuffer jump_buffer;
	Sound jump_sound;
	float CurrentFrame;
	int playerScore;
	enum stateObject
	{
		left,right,up,down,jump,stay
	};
	stateObject state;
	PLAYER(Texture &image, float X, float Y,float Weight,float Height,String charName,Level &lvl1) : CHARACTER(image,X,Y,Weight,Height,charName)
	{
		CurrentFrame = 1;
		obj = lvl1.GetAllObjects();
		state = stay;
		playerScore = 0;
		sprite.setTextureRect(IntRect(80, 32, w, h));
		jump_buffer.loadFromFile("bin/music/jump.wav");
		Sound jump_sound(jump_buffer);
	}
	void update(float time)
	{
		if (life)
		{

		
		control(time);
		switch (state)
		{
		case PLAYER::left: dx = -speed;
			break;
		case PLAYER::right: dx = speed;
			break;
		case PLAYER::up:
			break;
		case PLAYER::down:
			break;
		case PLAYER::jump:jump_sound.play();
			break;
		case PLAYER::stay: sprite.setTextureRect(IntRect(80, 32, heroDimensionX, heroDimensionY));
			break;
		default:
			break;
		}
		if (!onGround)
		{
			if (dx > 0)
			{
				sprite.setTextureRect(IntRect(80 + heroDimensionX * 5, 32, heroDimensionX, heroDimensionY));
			}
			else
			{
				sprite.setTextureRect(IntRect(80 + heroDimensionX * 5 + heroDimensionX, 32 , -heroDimensionX, heroDimensionY));
			}
			
		}
			x += dx * time;
			collision(dx, 0);
			y += dy * time;
			collision(0,dy);
			speed = 0;
			if (health <= 0) { life = false; }
			
			dx = 0;
			dy += 0.0015*time; collision(0, dy);
			sprite.setPosition(x, y);
		}
	}
	void control(float time)
	{
		state = stay;
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			state = right;
			speed = 0.2; 
			CurrentFrame += 0.02 * time;
			if (CurrentFrame > 5) CurrentFrame = 1;
			if (onGround)
			{
				sprite.setTextureRect(IntRect(80 + heroDimensionX * int(CurrentFrame), 32, heroDimensionX, heroDimensionY));
			}
			
			getPlayerPosView(getPlayerPosX(),getPlayerPosY());

		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			state = left;
			speed = 0.2; 
			CurrentFrame += 0.02 * time;
			if (CurrentFrame > 5) CurrentFrame = 1;
			if (onGround)
			{
				sprite.setTextureRect(IntRect(80 + heroDimensionX * int(CurrentFrame) + heroDimensionX, 32, -heroDimensionX, heroDimensionY));
			}
			getPlayerPosView(getPlayerPosX(), getPlayerPosY());

		}
		if ((Keyboard::isKeyPressed(Keyboard::Space)) && (onGround))
		{
			state = jump;
			dy = -0.4;
			onGround = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			x = 100;
			y = 400;
		}
	}
	float getPlayerPosX()
	{
		return x;
	}
	float getPlayerPosY()
	{
		return y;
	}
	void collision(float dX, float dY)
		/*{
			for (int i = y/16; i < (y+heroDimensionY)/16; i++)
				for (int j = x/16; j < (x + heroDimensionX)/16; j++)
				{
					if ((TileMap[i][j] == 'W'))
					{
						if (dX > 0)
						{
							x = 16*j - heroDimensionX;
							dx = 0;
						}
						if (dX < 0)
						{
							x = 16 * j + 16;
							dx = 0;
						}
						if (dY < 0)
						{
							y = 16 * i + 16;
							dy = 0.1;
						}
						if (dY > 0)
						{
							y = 16 * i - heroDimensionY;
							dy = 0;
							onGround = true;
						}
					}
					if ((TileMap[i][j] == 'P'))
					{
						if (dX > 0)
						{
							x = 16 * j - heroDimensionX;
							dx = 0;
						}
						if (dX < 0)
						{
							x = 16 * j + 16;
							dx = 0;
						}
						if (dY < 0)
						{
							y = 16 * i + 16;
							dy = 0.1;
						}
						if (dY > 0)
						{
							y = 16 * i - heroDimensionY;
							dy = 0;
							onGround = true;
						}
						TileMap[i][j] = 'A';
					}
				}



		}*/
	{
		for (int i = 0; i < obj.size();i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					if (dY > 0) { y = obj[i].rect.top - h; dy = 0; onGround = true; }
					if (dY < 0) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
					if (dX > 0) { x = obj[i].rect.left - w; }
					if (dX < 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
				if (obj[i].name == "Coin")
				{
					obj[i].name = "";
					playerScore++;
				}
			}
	}
};
class ENEMY : public CHARACTER
{
public:
	float currentFrame;
	ENEMY(Texture &image, float X, float Y, float Weight, float Height, String charName,Level &lvl1) : CHARACTER(image,X,Y,Weight,Height,charName)
	{
		obj = lvl1.GetObjects("solid");
		if (name == "mushroom")
		{
			currentFrame = 0;
			sprite.setTextureRect(IntRect(0,16,w,h));
			dx = 0.1;
		}
	}
	void collisionWithMap(float dX, float dY)
	/*{
		for (int i = y / 16; i < (y + heroDimensionY) / 16; i++)
			for (int j = x / 16; j < (x + heroDimensionX) / 16; j++)
			{
				if ((TileMap[i][j] == 'W'))
				{
					if (dX > 0)
					{
						x = 16 * j - heroDimensionX;
						dx = -0.2;
					}
					if (dX < 0)
					{
						x = 16 * j + 16;
						dx = 0.2;
					}
					if (dY < 0)
					{
						y = 16 * i + 16;
						dy = 0.1;
					}
					if (dY > 0)
					{
						y = 16 * i - heroDimensionY;
						dy = 0;
						onGround = true;
					}
				}
			}
	}*/
		{
			for (int i = 0; i < obj.size(); i++)
				if (getRect().intersects(obj[i].rect))
				{
					if (dY > 0) { y = obj[i].rect.top - h; dy = 0; onGround = true; }
					if (dY < 0) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
					if (dX > 0) { x = obj[i].rect.left - w; dx *= -1; }
					if (dX < 0) { x = obj[i].rect.left + obj[i].rect.width; dx *= -1; }
				}
		}
	void update(float time)
	{
		if (name == "mushroom")
		{
			currentFrame += 0.01 * time;
			if (currentFrame > 2) currentFrame = 0;
			x += dx * time;
			collisionWithMap(dx, 0);
			y += dy * time;
			collisionWithMap(0,dy);
			sprite.setTextureRect(IntRect(16 * int(currentFrame),16,w,h));
			sprite.setPosition(x,y);
			if (health <= 0)
			{
				life = false;
			}
			dy += 0.0015*time; collisionWithMap(0, dy);
		}
	}
};
class GameLogic
{
public:
	//peremenie
	float CurrentFrame = 0;
	int frameWithWeapon = 1;
	int timeOfplay;
	int timeForGenerator = 0;
	float tempX = 0;
	float tempY = 0;
	float distance = 0;
	float dx;
	float dy;
	std::ostringstream playerScoreOs;


	RenderWindow window { VideoMode(800,600),"Test" };
	Texture background_texture;
	Sprite background;
	Level lvl;
	Music mainTheme;
	Font font;
	Image herrr;
	Texture heroimage;
	Texture enemyTexture;
	Clock clock;
	Clock playTime;
	Object playerObj ;
	Object mushroomEnemyObj ;
	Texture dead_back_texture;
	Sprite dead_back;


	//список,кидаем врагов
	std::list<CHARACTER*> entities;
	std::list<CHARACTER*>::iterator it; //итератор дл€ прохождени€ по списку
	std::list<CHARACTER*>::iterator it2; //прохождение внутри по списку дл€ вы€вленни€ столкновей ммежду обьектами одного класса
	std::vector<Object> enemy_all;
	std::vector<Object> coins_all;
	
	//ENEMY mushroom(enemyTexture, mushroomEnemyObj.rect.left, mushroomEnemyObj.rect.top, heroDimensionX, heroDimensionY, "mushroom", lvl);

	GameLogic()
	{
		view.reset(FloatRect(0, 0, 640, 480));
		window.setFramerateLimit(60);
		lvl.LoadFromFile("map.tmx");
		mainTheme.openFromFile("bin/music/back_music_ol.ogg");
		font.loadFromFile("bin/fonts/CyrilicOld.TTF");
		herrr.loadFromFile("bin/images/hero.png");
		herrr.createMaskFromColor(Color(0, 0, 255));
		background_texture.loadFromFile("bin/images/back.png");
		heroimage.loadFromImage(herrr);
		enemyTexture.loadFromFile("bin/images/Enemies.png");
		playerObj = lvl.GetObject("player");
		mushroomEnemyObj = lvl.GetObject("mushroomEnemy");
		enemy_all = lvl.GetObjects("mushroomEnemy");
		coins_all = lvl.GetObjects("Coins");
		background_texture.loadFromFile("bin/images/back.png");
		background.setTexture(background_texture);
		background.setTextureRect(IntRect(0, 0, 3600, 2310));
		dead_back_texture.loadFromFile("bin/images/dead.png");
		dead_back.setTexture(dead_back_texture);
		dead_back.setTextureRect(IntRect(0, 0, 640, 480));
		dead_back.setPosition(140, 250);
		font.loadFromFile("bin/fonts/CyrilicOld.TTF");
		

		for (int i = 0; i < enemy_all.size(); i++)
			entities.push_back(new ENEMY(enemyTexture, enemy_all[i].rect.left, enemy_all[i].rect.top, heroDimensionX, heroDimensionY, "mushroom", lvl));
	}
	
	
	void isGame()
	{

		PLAYER player ( heroimage, playerObj.rect.left, playerObj.rect.top, heroDimensionX, heroDimensionY, "Player", lvl );
		
		
			mainTheme.play();
			while (window.isOpen())
			{
				

				
					float time = clock.getElapsedTime().asMicroseconds();
					clock.restart();
					time = time / 1000;

					if (player.life)
					{
						timeOfplay = playTime.getElapsedTime().asSeconds();
					}

					Event event;
					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed)
							window.close();
					}
					if (player.life)
					{
					player.update(time);
					//апдейт врагов из листа их контроль
					for (it = entities.begin(); it != entities.end();)
					{
						CHARACTER *b = *it;
						b->update(time);
						if ((b->life == false)) { it = entities.erase(it); delete b; }
						else it++;
					}

					for (it = entities.begin(); it != entities.end(); it++)
					{
						if ((*it)->getRect().intersects(player.getRect()))
						{
							if ((*it)->name == "mushroom")
							{
								if ((player.dy > 0) && (!player.onGround))
								{
									(*it)->dx = 0;
									(*it)->health = 0;
									player.dy = -0.3;
									player.playerScore *= 2;
								}
								else
								{
									player.life = false;
								}
							}
						}
						for (it2 = entities.begin(); it2 != entities.end(); it2++)
						{
							if ((*it)->getRect() != ((*it2)->getRect()))
								if ((*it)->getRect().intersects((*it2)->getRect()) && ((*it)->name == "mushroom") && ((*it)->name == "mushroom"))
								{
									(*it)->dx *= -1;

								}
						}
					}

					std::cout << "x = " << player.getPlayerPosX() << "y = " << player.getPlayerPosY() << std::endl;
					Text text("", font, 15);
					Text t_score("", font, 15);
					text.setColor(Color::White);
					t_score.setColor(Color::White);

					std::ostringstream playerScoreOs;
					playerScoreOs << player.playerScore;
					text.setString("MARIO:");
					text.setPosition(view.getCenter().x - 300, view.getCenter().y - 200);
					t_score.setString(playerScoreOs.str());
					t_score.setPosition(view.getCenter().x - 300, view.getCenter().y - 185);
					
					window.setView(view);
					window.clear(Color::White);
					window.draw(background);
					getPlayerPosView(player.getPlayerPosX(), player.getPlayerPosY());
					lvl.Draw(window);
					if (player.life == true)
					{
						window.draw(player.sprite);
					}

					for (it = entities.begin(); it != entities.end(); it++)
					{
						window.draw((*it)->sprite);
					}
					window.draw(t_score);
					window.draw(text);
					window.display();

				}
					else
					{
						mainTheme.stop();
						window.clear(Color::Black);
						window.draw(dead_back);
						window.display();
					}


			}
		
		
	}
	void menu()
	{
		Texture menu_t;
		menu_t.loadFromFile("bin/images/menu1.jpg");
		Sprite menu(menu_t);
		menu.setTextureRect(IntRect(0, 0, 800, 600));
		Texture currentMenu;
		currentMenu.loadFromFile("bin/images/elementmenu.png");
		Sprite currMenu;
		currMenu.setTexture(currentMenu);
		currMenu.setTextureRect(IntRect(0, 0, 24, 24));
		currMenu.setPosition(262, 362);

		bool isMenu = 1;
		int menuNum = 0;

		IntRect start(294, 362, 552, 36);
		IntRect exit(294, 400, 552, 36);

		while (isMenu)
		{
			window.clear();

			if (start.contains(Mouse::getPosition(window)))
			{
				menuNum = 1;
				currMenu.setPosition(262, 362);
			}
			if (exit.contains(Mouse::getPosition(window)))
			{
				menuNum = 2;
				currMenu.setPosition(262, 400);
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 1) isMenu = false;
			}
			window.draw(menu);
			window.draw(currMenu);
			window.display();

		}
	}
};






int main()
{
	GameLogic logic;
	//logic.menu();
	logic.isGame();
	/*RenderWindow window(VideoMode(800,600),"Test");
	logic.menu(window);
	view.reset(FloatRect(0, 0, 640, 480));
	
	bool isPressed = false;
	window.setFramerateLimit(60);

	Level lvl;
	lvl.LoadFromFile("map.tmx");
	
	Music mainTheme;
	mainTheme.openFromFile("bin/music/back_music_ol.ogg");
	//mainTheme.play();

	
	Font font;
	font.loadFromFile("bin/fonts/CyrilicOld.TTF");

	Image herrr;
	herrr.loadFromFile("bin/images/hero.png");
	herrr.createMaskFromColor(Color(0, 0, 255));

	Texture background_texture;
	background_texture.loadFromFile("bin/images/back.png");
	
	Sprite background;
	background.setTexture(background_texture);
	background.setTextureRect(IntRect(0,0,3600,2310));

	Texture heroimage;
	heroimage.loadFromImage(herrr);

	Texture enemyTexture;
	enemyTexture.loadFromFile("bin/images/Enemies.png");

	Clock clock;
	Clock playTime;
	

	//создаем обьект игрока и врагов
	Object playerObj = lvl.GetObject("player");
	Object mushroomEnemyObj = lvl.GetObject("mushroomEnemy");

	//список,кидаем врагов
	std::list<CHARACTER*> entities;
	std::list<CHARACTER*>::iterator it; //итератор дл€ прохождени€ по списку
	std::list<CHARACTER*>::iterator it2; //прохождение внутри по списку дл€ вы€вленни€ столкновей ммежду обьектами одного класса

	std::vector<Object> enemy_all = lvl.GetObjects("mushroomEnemy");//пихаем обьекты врага карты в оьект enemy_all

	for (int i = 0; i < enemy_all.size(); i++)
		entities.push_back(new ENEMY(enemyTexture, enemy_all[i].rect.left, enemy_all[i].rect.top, heroDimensionX, heroDimensionY, "mushroom", lvl));

	

	// лассы обьектов и логики игры
	PLAYER player(heroimage,playerObj.rect.left, playerObj.rect.top, heroDimensionX, heroDimensionY,"Player",lvl);
	ENEMY mushroom(enemyTexture, mushroomEnemyObj.rect.left, mushroomEnemyObj.rect.top, heroDimensionX, heroDimensionY, "mushroom", lvl);
	
	float CurrentFrame = 0;
	int frameWithWeapon = 1;
	int timeOfplay;
	int timeForGenerator = 0;
	float tempX = 0;
	float tempY = 0;
	float distance = 0;

	float dx;
	float dy;
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1000;

		if (player.life)
		{
			timeOfplay = playTime.getElapsedTime().asSeconds();
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		player.update(time);
		//апдейт врагов из листа их контроль
		for (it = entities.begin(); it != entities.end();)
		{
			CHARACTER *b = *it;
			b->update(time);
			if ((b->life == false)) { it = entities.erase(it); delete b; }
			else it++;
		}
	
		for (it = entities.begin(); it != entities.end();it++)
		{
			if ((*it)->getRect().intersects(player.getRect()))
			{
				if ((*it)->name == "mushroom")
				{
					if ((player.dy > 0) && (!player.onGround))
					{
						(*it)->dx = 0;
						(*it)->health = 0;
						player.dy = -0.3;
					}
					else
					{
						player.health -= 1;
					}
				}
			}
			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				if ((*it)->getRect() != ((*it2)->getRect()))
					if ((*it)->getRect().intersects((*it2)->getRect()) && ((*it)->name == "mushroom") && ((*it)->name == "mushroom"))
				{
					(*it)->dx *= -1;
					
				}
			}
		}
		
		std::cout << "x = " << player.getPlayerPosX() << "y = " << player.getPlayerPosY() << std::endl;
		window.setView(view);
		window.clear(Color::White);
		window.draw(background);
		getPlayerPosView(player.getPlayerPosX(), player.getPlayerPosY());
		lvl.Draw(window);
		window.draw(player.sprite);
		for (it = entities.begin();it != entities.end(); it++)
		{
			window.draw((*it)->sprite);
		}
		
		window.display();
		
	}
	*/
	return 0;
}