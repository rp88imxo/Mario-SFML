#include <SFML\Graphics.hpp>

const int HEIGHT_MAP = 20;
const int WIDTH_MAP = 40;

sf::String TileMap[HEIGHT_MAP] =
{
	"                                        ",
	"                                        ",
	"                                        ",
	"                                        ",
	"                                        ",
	"                                        ",
	"                                        ",
	"                                        ",
	"                                        ",
	"                                        ",
	"                                        ",
	"                                        ",
	"                                        ",
	"                                PPPP    ",
	"                 PPPP                   ",
	"                                        ",
	"         PPPP                           ",
	"                                        ",
	"W                                      W",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
};
void randomMapGenerator()
{
	int randomElementX = 0;
	int randomElementY = 0;
	srand(time(0));
	int knightCount = 10;
	while (knightCount > 0)
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 'K';
			std::cout << "x = " << randomElementX << " y= " << randomElementY << std::endl;
			knightCount--;
		}
	}
}
