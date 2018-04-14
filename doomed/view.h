#include <SFML\Graphics.hpp>

using namespace sf;

View view;
View getPlayerPosView(float x, float y)
{
	float borderX = x; float borderY = y;
	if (x < 320)
		borderX = 320;
	if (x > 3520)
		borderX = 3520;
	if (y > 490)
		borderY = 496;
	
	view.setCenter(borderX, borderY);
	return view;
}
void viewScroll(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		view.move(0,-0.1 * time);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		view.move(0, 0.1 * time);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		view.move(-0.1 * time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		view.move(0.1 * time, 0);
	}
}
View changeView()
{
	if (Keyboard::isKeyPressed(Keyboard::R))
	{
		view.rotate(1);
	}
	return view;
}