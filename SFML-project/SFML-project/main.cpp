#include "ivan_s.h"
#include "matvey.h"
using namespace sf;
string user = "";

extern int session_load[20];
extern int session_rating[20];
extern int session_comment[20];
int main()
{
	RenderWindow window(sf::VideoMode(1376, 768), "Test market");
	int is_user = 0;

	while (1)
	{
		int menuNum = menu(window,is_user, user);//вызов меню
		if (menuNum == 5)//закрытие
		{
			output_info();
			window.close();
			return 0;
		}
		if (menuNum == 4)
		{
			string res = authorization(window);
			if (res != "")
			{
				is_user = 1;
				user = res;
			}
		}
		if (menuNum == 3)//регистрация
		{
			registration(window);
		}
		if (menuNum == 2)//каталог
		{
			catalog(window, ALL_APPS, user);
		}
		if (menuNum == 1)//скачанные
		{
			catalog(window, ONLY_LOADED, user);
		}
	}
	window.close();



	/*while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}*/

	return 0;
}