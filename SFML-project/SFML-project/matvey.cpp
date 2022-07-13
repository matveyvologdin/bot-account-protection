#include "matvey.h"
#include "ivan_s.h"
#include <Windows.h>

char login[100] = "";
char name[20][255];
extern int session_load[20];
extern int session_rating[20];
extern int session_comment[20];
extern int bot_coms;
void catalog(RenderWindow& window, int flag, std::string user)
{
	double menu_time_start = clock();
	if (user == "")
	{
		window.clear(Color(129, 181, 221));
		Font font;//шрифт 
		font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
		Text info("", font, 60);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		info.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
		info.setPosition(100, 200);//задаем позицию текста, центр камеры
		info.setString("Пройдите авторизацию");//задает строку тексту
		window.draw(info);
		window.display();
		Sleep(2000);
		return;
	}
	int ii = 0;
	for (ii = 0; ii < user.length(); ii++)
		login[ii] = user[ii];
	login[ii] = 0;
	int action = 0;
	std::ifstream catalog_file("catalog.txt");
	int i = 0, count_loaded = 0;
	while (!catalog_file.eof())
		catalog_file.getline(name[i++], 255);//считываем названия приложений из файла в массив
	catalog_file.close();

	if (flag)
		for (i = 0; i < 20; i++)
			count_loaded += isloaded(i);

	int start_app = 0;//первое отрисовывающееся приложение
	while (!(Keyboard::isKeyPressed(Keyboard::Escape)))//пока не нажат escape
	{
		sf::Event event;
		if (window.pollEvent(event))
		{
			window.clear(Color(129, 181, 221));
			//удаление/скачивание
			for (int i = 1; i <= 8; i++)
				if (IntRect(888, 90 * i - 40, 50, 50).contains(Mouse::getPosition(window))
					&& Mouse::isButtonPressed(Mouse::Left))
				{
					if (i + start_app > count_loaded && flag == 1)//если просматриваются скачанные и нажимается на пустую ячейку
						continue;
					int load;
					if (flag == 1)
					{
						load = start_app + i;//номер выбранного скачанного приложения
						int cnt_load = 0;
						for (int j = 0; j < 20; j++)
						{
							if (isloaded(j)) cnt_load++;
							if (cnt_load == load)
							{
								load = j;
								break;
							}
						}
						change_status_load(load + 1);
						save_load_session(load + 1);
						install(load + 1, window);
						double menu_time_end = clock() - menu_time_start;
						change_make_act_time(user, menu_time_end);
						menu_time_start = clock();//меняем начальное время
						//cout << "time: " << menu_time_end / CLOCKS_PER_SEC << endl;
						count_loaded--;//пользователь удалил приложение
						Sleep(2000);
						window.clear(Color(129, 181, 221));
						break;
					}
					//если смотрится каталог и приложение не скачано
					change_status_load(start_app + i);
					save_load_session(start_app + i);
					install(start_app + i, window);
					double menu_time_end = clock() - menu_time_start;
					change_make_act_time(user, menu_time_end);
					menu_time_start = clock();//меняем начальное время
					//cout << "time: " << menu_time_end / CLOCKS_PER_SEC << endl;
					Sleep(2000);
					window.clear(Color(129, 181, 221));
				}
			//просмотр комментариев/рейтинга
			for (int i = 1; i <= 8; i++)
				//420, 35, 40, 54
				if (IntRect(540, 90 * i - 40, 335, 50).contains(Mouse::getPosition(window))
					&& Mouse::isButtonPressed(Mouse::Left))
				{
					if (i + start_app > count_loaded && flag == 1)//если просматриваются скачанные и нажимается на пустую ячейку
						continue;
					int load;
					if (flag == 1)//если просматриваются скачанные
					{
						load = start_app + i;//номер выбранного скачанного приложения
						int cnt_load = 0;
						for (int j = 0; j < 20; j++)
						{
							if (isloaded(j)) cnt_load++;
							if (cnt_load == load)
							{
								load = j;
								break;
							}
						}
						double menu_time_end = clock() - menu_time_start;
						change_make_act_time(user, menu_time_end);
						menu_time_start = clock();//меняем начальное время
						//cout << "time: " << menu_time_end / CLOCKS_PER_SEC << endl;
						show_info(window, load + 1, user);
						break;
					}
					//если смотрится каталог и приложение не скачано
					double menu_time_end = clock() - menu_time_start;
					change_make_act_time(user, menu_time_end);
					menu_time_start = clock();//меняем начальное время
					//cout << "time: " << menu_time_end / CLOCKS_PER_SEC << endl;
					show_info(window, start_app + i, user);
				}
			action = draw_buttons(window, CATALOG);
			if (action == 1 && start_app > 0 && Mouse::isButtonPressed(Mouse::Left))
			{//нажатие на стрелку вверх
				double menu_time_end = clock() - menu_time_start;
				change_make_act_time(user, menu_time_end);
				menu_time_start = clock();//меняем начальное время
				//cout << "time: " << menu_time_end / CLOCKS_PER_SEC << endl;
				start_app--;
			}
			if ((flag == 1 && start_app < count_loaded - 8 || flag == 0 && start_app < 12) && action == 2 &&
				Mouse::isButtonPressed(Mouse::Left))
			{//нажатие на стрелку вниз
				double menu_time_end = clock() - menu_time_start;
				change_make_act_time(user, menu_time_end);
				menu_time_start = clock();//меняем начальное время
				//cout << "time: " << menu_time_end / CLOCKS_PER_SEC << endl;
				start_app++;
			}
			draw_catalog(window, start_app, flag);

			window.display();
		}
	}
	double menu_time_end = clock() - menu_time_start;
	change_make_act_time(user, menu_time_end);
	//cout << "time: " << menu_time_end / CLOCKS_PER_SEC << endl;
}

int draw_buttons(RenderWindow& window, int flag)
{
	int ret = 0;
	int x;
	if (flag == CATALOG)
		x = 420;
	else
		x = 500;
	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта

	Texture up_icon, down_icon;//текстуры кнопок
	up_icon.loadFromFile("images/up.png");
	down_icon.loadFromFile("images/down.png");

	Sprite up(up_icon), down(down_icon);
	up.setColor(sf::Color::White);//цвет кнопок без наведения
	down.setColor(sf::Color::White);

	if (IntRect(x, 35, 40, 54).contains(Mouse::getPosition(window)))
	{
		up.setColor(sf::Color::Blue);//цвет при наведении
		ret = 1;
	}
	if (IntRect(x, 645, 40, 54).contains(Mouse::getPosition(window)))
	{
		down.setColor(sf::Color::Blue);//цвет при наведении
		ret = 2;
	}
	up.setScale(0.2, 0.2);//изменяем масштаб
	down.setScale(0.2, 0.2);
	up.setPosition(x, 35);//задаем позицию
	down.setPosition(x, 645);
	window.draw(up);//отрисовываем все объекты
	window.draw(down);
	return ret;
}

void draw_catalog(RenderWindow& window, int start_app, int flag)
{
	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта

	int cur_app = start_app;
	int printed = 0;
	while (printed < 8)
	{
		if (!isloaded(cur_app) && flag == 1)
		{
			cur_app++;
			continue;
		}
		Texture background;//текстура фона объекта в каталоге
		background.loadFromFile("images/back.png");

		Sprite box;//объект для приложения в каталоге
		box.setTexture(background);
		box.setColor(sf::Color::White);
		box.setPosition(538, (printed + 1) * 90 - 40);

		Text name_app("", font, 30);//объект текста с названием приложения
		if (cur_app < 20)
		{
			name_app.setString(name[cur_app]);
			name_app.setPosition(box.getPosition().x + (400 - 11 * strlen(name[cur_app])) / 2, box.getPosition().y);
		}
		else
		{
			name_app.setString("Empty");
			name_app.setPosition(box.getPosition().x + 345 / 2, box.getPosition().y);
		}
		name_app.setFillColor(sf::Color::Black);
		name_app.setStyle(sf::Text::Bold | sf::Text::Underlined);

		window.draw(box);//отрисовываем все объекты
		window.draw(name_app);
		if (flag == 0)
		{
			Texture load_icon;//текстура кнопки загрузки
			if (isloaded(cur_app))//проверка скачано ли приложение
				load_icon.loadFromFile("images/delete.png");//если скачано - иконка удаления
			else
				load_icon.loadFromFile("images/load.png");//если не скачано - иконка скачки

			Sprite load(load_icon);//объект кнопки загрузки
			load.setPosition(888, (cur_app - start_app + 1) * 90 - 40);//задаем позицию
			load.setScale(0.22, 0.22);//изменяем масштаб
			window.draw(load);
		}
		printed++;
		cur_app++;
	}
}

int change_status_load(int index)
{
	if (index <= 0)
		return 0;
	char line[255];
	int sdvig = 0;
	char c;
	std::fstream load_file("load.txt");
	while (!load_file.eof())
	{
		load_file.getline(line, 255);
		if (strncmp(line, login, strlen(login)) == 0)
		{
			sdvig = 2 * (index - 20) - 3;
			load_file.seekg(sdvig, std::ios::cur);
			c = load_file.get();
			load_file.seekg(-1, std::ios::cur);
			if (c == '1')
				load_file.write("0", 1);
			if (c == '0')
				load_file.write("1", 1);
			break;
		}
	}
	load_file.close();
	return 1;
}

int isloaded(int i)
{
	char name_app[255];
	int sdvig = 0;
	char c = -1;
	std::fstream load_file("load.txt");
	while (!load_file.eof())
	{
		load_file.getline(name_app, 255);
		if (strncmp(name_app, login, strlen(login)) == 0)
		{
			sdvig = 2 * (i - 20) - 1;
			load_file.seekg(sdvig, std::ios::cur);
			c = load_file.get() - '0';
			break;
		}
	}
	load_file.close();
	return c;
}

void install(int index, RenderWindow& window)
{
	int printed = 0;
	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта

	int cur_app = index;
	Texture background;//текстура фона объекта в каталоге
	background.loadFromFile("images/back.png");

	Sprite box;//объект для приложения в каталоге
	box.setTexture(background);
	box.setColor(sf::Color::White);
	box.setPosition(538, (printed + 1) * 90 - 40);

	Text name_app("", font, 30);//объект текста с названием приложения
	if (cur_app < 20)
	{
		name_app.setString(name[cur_app - 1]);
		name_app.setPosition(box.getPosition().x + (400 - 11 * strlen(name[cur_app])) / 2, box.getPosition().y);
	}
	else
	{
		name_app.setString("Empty");
		name_app.setPosition(box.getPosition().x + 345 / 2, box.getPosition().y);
	}
	name_app.setFillColor(sf::Color::Black);
	name_app.setStyle(sf::Text::Bold | sf::Text::Underlined);

	window.draw(box);//отрисовываем все объекты
	window.draw(name_app);
	Texture load_icon;//текстура кнопки загрузки
	load_icon.loadFromFile("images/installing.png");//если скачано - иконка удаления

	Sprite load(load_icon);//объект кнопки загрузки
	load.setPosition(888, (cur_app - index + 1) * 90 - 40);//задаем позицию
	load.setScale(0.22, 0.22);//изменяем масштаб
	window.draw(load);
	window.display();
}

void show_info(RenderWindow& window, int index, std::string user)
{
	double menu_time_start = clock();
	
	window.clear(Color(129, 181, 221));

	std::string name, cnt, rating;
	std::ifstream load_file("rating.txt");
	for (int i = 1; i < index; i++)
	{
		load_file >> name;
		load_file >> cnt;
		load_file >> rating;
	}
	load_file >> name;
	load_file >> cnt;
	load_file >> rating;
	//в cnt лежит количество оценок, в rating - рейтинг, в name - имя приложения
	load_file.close();

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта

	Text app("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	app.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	app.setPosition(100, 100);//задаем позицию текста, центр камеры
	std::string app_name = "Имя приложения: ";
	app_name += name;
	app.setString(app_name);

	Text info("", font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	info.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	info.setPosition(100, 200);//задаем позицию текста, центр камеры
	std::string rat = "Рейтинг: ";
	rat += rating;
	info.setString(rat);

	Text rat_cnt("", font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	rat_cnt.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	rat_cnt.setPosition(100, 300);//задаем позицию текста, центр камеры
	std::string cnt_downloads = "Скачано: ";
	cnt_downloads += cnt;
	cnt_downloads += " раз";
	rat_cnt.setString(cnt_downloads);

	Text back("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	back.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	back.setPosition(100, 510);//задаем позицию текста, центр камеры
	back.setString("Нажмите esc, чтобы вернуться в каталог");

	Texture menuTexture1, menuTexture2;
	menuTexture1.loadFromFile("images/rating.png");
	menuTexture2.loadFromFile("images/comment.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2);
	int menuNum = 0;
	menu1.setPosition(100, 400);
	menu2.setPosition(100, 460);

	//////////////////////////////МЕНЮ///////////////////
	while (!(Keyboard::isKeyPressed(Keyboard::Escape)))
	{
		window.clear(Color(129, 181, 221));

		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;

		if (IntRect(100, 400, 180, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 460, 240, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
			if (menuNum > 0 && menuNum < 3)
			{
				double menu_time_end = clock() - menu_time_start;
				change_make_act_time(user, menu_time_end);
				menu_time_start = clock();//меняем начальное время
				if (menuNum == 1)
				{
					give_rating(window, index, user);
					window.clear(Color(129, 181, 221));
					return;
				}
				else
				{
					comments(window, index, user);
				}
			}

		window.draw(info);
		window.draw(rat_cnt);
		window.draw(app);
		window.draw(back);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
	double menu_time_end = clock() - menu_time_start;
	change_make_act_time(user, menu_time_end);
	menu_time_start = clock();//меняем начальное время

	while (Keyboard::isKeyPressed(Keyboard::Escape));//пропуск escape, которые остались
	window.clear(Color(129, 181, 221));
}

void give_rating(RenderWindow& window, int index, std::string user)
{
	double menu_time_start = clock();
	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	window.clear(Color(129, 181, 221));
	if (is_give_rating(index) == 1)
	{
		Text info("", font, 60);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		info.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
		info.setPosition(100, 200);//задаем позицию текста, центр камеры
		info.setString("Вы уже оценили работу этого приложения");//задает строку тексту
		window.draw(info);
		window.display();
		Sleep(2000);
		window.clear(Color(129, 181, 221));
		return;
	}
	//пользователь еще не оценивал работу этого приложения
	Text info2("", font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	info2.setString("Введите оценку (от 1 до 5): ");//задает строку тексту
	info2.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	info2.setPosition(100, 100);//задаем позицию текста, центр камеры
	std::string str = "";
	Text rate("", font, 30);
	rate.setStyle(sf::Text::Bold | sf::Text::Underlined);
	rate.setPosition(600, 100);
	int ccccccc = 0;
	while (!(Keyboard::isKeyPressed(Keyboard::Return)))//до тех пор, пока не нажат энтер
	{
		window.draw(info2);//рисую этот текст
		window.draw(rate);//рисую этот текст
		window.display();
		sf::Event event;
		if (window.pollEvent(event))
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode <= '5' && event.text.unicode >= '1')
				{
					if (ccccccc) continue;
					str += static_cast<char>(event.text.unicode);
					rate.setString(str);
					ccccccc++;
				}
			}
		window.clear(Color(129, 181, 221));
	}
	double menu_time_end = clock() - menu_time_start;
	change_make_act_time(user, menu_time_end);
	menu_time_start = clock();//меняем начальное время
	//пользователь ввел рейтинг
	change_status_rating(index, str);//ставим флаг, что рейтинг дан
	save_rating_session(index, (int)(str[0] - '0'));
	std::string name, cnt, rating;
	std::ifstream load_file("rating.txt");
	for (int i = 1; i < index; i++)
	{
		load_file >> name;
		load_file >> cnt;
		load_file >> rating;
	}
	load_file >> name;
	load_file >> cnt;
	load_file >> rating;
	//в cnt лежит количество оценок, в rating - рейтинг, в name - имя приложения
	load_file.close();
	int cnt_rating = stoi(cnt);//перевод строки в число
	cnt_rating++;
	cnt = std::to_string(cnt_rating);

	int new_rating = stoi(rating);//перевод строки в число
	if (cnt_rating > 1)
		new_rating = (new_rating + str[0] - '0') * (cnt_rating - 1) / cnt_rating;
	else new_rating = str[0] - '0';
	rating = std::to_string(new_rating);
	set_new_rating(rating, cnt, index);//установка нового рейтинга и количества оценок

	Text info3("", font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	info3.setString("Спасибо за оценку!");//задает строку тексту
	info3.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	info3.setPosition(100, 100);//задаем позицию текста, центр камеры
	window.draw(info3);//рисую этот текст
	window.display();
	Sleep(1000);
}

void comments(RenderWindow& window, int index, std::string user)
{
	double menu_time_start = clock();
	index--;
	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта

	char name[50], comment[20][50];
	memset(comment, 0, sizeof(comment));

	std::fstream comment_file("comment.txt");
	comment_file.getline(name, 50);//имя
	for (int i = 0; i < index; i++)
	{
		comment_file.getline(name, 50);//имя или комментарий
		if (name[0] == '\t')
		{
			while (name[0] == '\t')
				comment_file.getline(name, 50);
		}
	}
	int i = 0;
	while (!comment_file.eof())
	{
		comment_file.getline(comment[i], 50);
		if (comment[i][0] != '\t')
		{
			memset(comment[i], 0, sizeof(comment[i]));
			break;
		}
		i++;
	}
	int max_com = i;
	comment_file.close();
	int menuNum = 0, start_com = 0, action;
	int len = 0;
	std::string str = "";
	Text com("", font, 30);
	com.setStyle(sf::Text::Bold | sf::Text::Underlined);
	com.setPosition(100, 200);

	Text app("", font, 30);
	app.setStyle(sf::Text::Bold | sf::Text::Underlined);
	app.setString(name);
	app.setPosition(100, 100);
	app.setFillColor(sf::Color::Black);

	while (!(Keyboard::isKeyPressed(Keyboard::Escape)))
	{
		menuNum = 0;
		if (IntRect(100, 300, 281, 38).contains(Mouse::getPosition(window)))
			menuNum = 1;

		window.clear(Color(129, 181, 221));
		action = draw_buttons(window, COMMENTS);

		sf::Event event;
		if (window.pollEvent(event))
		{
			if (!is_user_posted(index))
				if (event.type == sf::Event::TextEntered)
				{
					if ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z') || (event.text.unicode >= '!' && event.text.unicode <= '?')
						|| event.text.unicode <= ' ' || event.text.unicode <= ',' || event.text.unicode <= '.')
					{
						if (len >= 35) continue;
						str += static_cast<char>(event.text.unicode);
						com.setString(str);
						len++;
					}
				}
			if (action == 1 && start_com > 0 && Mouse::isButtonPressed(Mouse::Left))
			{//нажатие на стрелку вверх
				start_com--;
			}
			if (start_com < max_com - 8 && action == 2 && Mouse::isButtonPressed(Mouse::Left))
			{//нажатие на стрелку вниз
				start_com++;
			}
		}
		if (is_user_posted(index))
		{
			Text info("", font, 30);
			info.setStyle(sf::Text::Bold | sf::Text::Underlined);
			info.setPosition(100, 200);
			info.setString("Вы уже ввели свой комментарий");
			window.draw(info);
		}
		draw_comments(window, start_com, index);
		Texture post;
		post.loadFromFile("images/post_comment.png");
		Sprite post_button(post);
		post_button.setPosition(100, 300);

		if (menuNum == 1)
			post_button.setColor(sf::Color::Blue);

		if (Mouse::isButtonPressed(Mouse::Left))
			if (menuNum == 1 && !(is_user_posted(index)))
			{
				if (str == "");
				else
				{
					save_comment(index, str);
					session_comment[index] = 1;
					com.setString("");
					user_posted(index);
				}
			}

		window.draw(app);
		if (!is_user_posted(index))
		{
			window.draw(com);
			window.draw(post_button);
		}
		window.display();
	}
	double menu_time_end = clock() - menu_time_start;
	change_make_act_time(user, menu_time_end);
	menu_time_start = clock();//меняем начальное время
	while (Keyboard::isKeyPressed(Keyboard::Escape));
}

int is_give_rating(int i)
{
	char name_app[255];
	int sdvig = 0;
	char c = -1;
	std::string str = "";
	std::fstream load_file("give_rating.txt");
	while (!load_file.eof())
	{
		load_file.getline(name_app, 255);
		if (strncmp(name_app, login, strlen(login)) == 0)
		{
			sdvig = 2 * (i - 20) - 3;
			load_file.seekg(sdvig, std::ios::cur);
			load_file >> str;
			c = str[0] - '0';
			break;
		}
	}
	load_file.close();
	return c;
}

int change_status_rating(int index, string rating)
{
	if (index <= 0)
		return 0;
	char line[255];
	int sdvig = 0;
	char c;
	std::fstream load_file("give_rating.txt");
	while (!load_file.eof())
	{
		load_file.getline(line, 255);
		if (strncmp(line, login, strlen(login)) == 0)
		{
			sdvig = 2 * (index - 20) - 3;
			load_file.seekg(sdvig, std::ios::cur);
			c = load_file.get();
			load_file.seekg(-1, std::ios::cur);
			load_file.write(rating.c_str(), 1);
			break;
		}
	}
	load_file.close();

	std::fstream load_file1("qwerty.txt");
	load_file1.seekg(index * 2, std::ios::beg);
	char c1 = load_file1.get();
	if (c1 == '0')
	{
		load_file1.seekg(-1, std::ios::cur);
		load_file1.write("1", 1);
	}
	load_file1.close();
	return 1;
}

void set_new_rating(std::string rating, std::string cnt, int index)
{
	std::string name[15], cnt1[15], rating1[15];

	std::ifstream file("rating.txt");
	for (int i = 0; i < 15; i++)
	{
		file >> name[i];
		file >> cnt1[i];
		file >> rating1[i];
	}
	file.close();
	std::ofstream out("rating.txt");
	for (int i = 0; i < 15; i++)
	{
		out << name[i] << ' ';
		if (i == index - 1)
		{
			out << cnt << ' ';
			out << rating << std::endl;
		}
		else
		{
			out << cnt1[i] << ' ';
			out << rating1[i] << std::endl;
		}
	}
	out.close();
}

void save_comment(int index, std::string input)
{
	if (input == "")
		return;
	std::fstream comment_file("comment.txt");
	char name[50], comment[150][50];
	int cnt[20], cur_com = 0, max_com;
	memset(comment, 0, sizeof(comment));
	memset(cnt, 0, sizeof(cnt));
	comment_file.getline(name, 50);//имя
	for (int i = 0; i < 15; i++)
	{
		comment_file.getline(name, 50);//имя или комментарий
		if (name[0] == '\t')
		{
			strcpy(comment[cur_com], name);
			cur_com++;
			while (name[0] == '\t')
			{
				comment_file.getline(name, 50);
				strcpy(comment[cur_com], name);
				cur_com++;
				cnt[i]++;
			}
			cur_com--;
			memset(comment[cur_com], 0, sizeof(comment[cur_com]));
		}
	}
	comment_file.close();
	max_com = cur_com;
	cur_com = 0;
	std::ifstream catalog_file("catalog.txt");
	std::ofstream commen_file("comment.txt");
	std::string str = "";
	for (int i = 0; i < 15; i++)
	{
		catalog_file >> str;
		commen_file << str << std::endl;
		for (int j = 0; j < cnt[i]; j++)
		{
			commen_file << comment[cur_com] << std::endl;
			cur_com++;
		}
		if (i == index)
			commen_file << '\t' << login << '\t' << input << std::endl;
	}
	catalog_file.close();
	commen_file.close();
}

void draw_comments(RenderWindow& window, int start_com, int index)
{
	char line[50], str[50], comments[150][50];
	char* log = NULL;
	int cur_com = 0, max_com;
	memset(str, 0, sizeof(str));
	memset(line, 0, sizeof(line));
	memset(comments, 0, sizeof(comments));
	std::fstream catalog_file("catalog.txt");
	std::fstream comment_file("comment.txt");
	for (int i = 0; i < index + 1; i++)
		catalog_file.getline(line, 50);
	while (strcmp(line, str) != 0)
		comment_file.getline(str, 50);
	catalog_file.getline(line, 50);
	while (strcmp(line, str) != 0)
	{
		comment_file.getline(str, 50);
		strcpy(comments[cur_com], str);
		cur_com++;
	}
	max_com = cur_com - 1;

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта

	cur_com = start_com;
	while (cur_com < start_com + 8)
	{
		Texture background;//текстура фона объекта в каталоге
		background.loadFromFile("images/back_comment.png");

		Sprite box;//объект для приложения в каталоге
		box.setTexture(background);
		box.setColor(sf::Color::White);
		box.setPosition(650, (cur_com - start_com + 1) * 90 - 40);
		box.setTextureRect(IntRect(0, 0, 650, 50));
		Text name_com("", font, 30);//объект текста с названием приложения
		Text name_user("", font, 20);//объект текста с именем пользователя
		if (cur_com < max_com)
		{
			strcpy(str, comments[cur_com]);
			log = strtok(str, "\t");
			name_user.setString(log);
			name_user.setPosition(box.getPosition().x + (620 - 7 * strlen(log)) / 2, box.getPosition().y + 50);
			log = strtok(NULL, "\t");
			name_com.setString(log);
			name_com.setPosition(box.getPosition().x + (620 - 11 * strlen(log)) / 2, box.getPosition().y);
		}
		else
		{
			name_com.setString("Empty");
			name_com.setPosition(box.getPosition().x + (620 - 11 * 5) / 2, box.getPosition().y);
		}
		name_com.setFillColor(sf::Color::Black);
		name_com.setStyle(sf::Text::Bold | sf::Text::Underlined);
		name_user.setFillColor(sf::Color::Black);
		name_user.setStyle(sf::Text::Bold | sf::Text::Underlined);
		window.draw(box);//отрисовываем все объекты
		window.draw(name_com);
		window.draw(name_user);
		cur_com++;
	}
	catalog_file.close();
	comment_file.close();
}

void user_posted(int index)
{
	if (index < 0)
		return;
	char line[255];
	int sdvig = 0;
	char c;
	std::fstream load_file("post_comment.txt");
	while (!load_file.eof())
	{
		load_file.getline(line, 255);
		if (strncmp(line, login, strlen(login)) == 0)
		{
			sdvig = 2 * (index - 20) - 1;
			load_file.seekg(sdvig, std::ios::cur);
			load_file.write("1", 1);
			break;
		}
	}
	load_file.close();
}

int is_user_posted(int index)
{
	char name_app[255];
	int sdvig = 0;
	char c = -1;
	std::string str = "";
	std::fstream load_file("post_comment.txt");
	while (!load_file.eof())
	{
		load_file.getline(name_app, 255);
		if (strncmp(name_app, login, strlen(login)) == 0)
		{
			sdvig = 2 * (index - 20) - 1;
			load_file.seekg(sdvig, std::ios::cur);
			load_file >> str;
			c = str[0] - '0';
			break;
		}
	}
	load_file.close();
	return c;
}

void save_load_session(int index)
{
	if (index <= 0)
		return;
	if (session_load[index - 1] == 0)
		session_load[index - 1] = 1;
	return;
}

void save_rating_session(int index, int rating)
{
	if (index <= 0)
		return;
	if (session_rating[index - 1] == 0)
		session_rating[index - 1] = rating;
	return;
}

void output_info()
{
	check_bot_comments();
	std::ofstream f("bots.txt", std::fstream::app);
	int session_l = 0, session_c = 0, session_r = 0, all_r = 0, all_r_count = 0, all_c = 0, all_c_count = 0;
	char sss[255];
	for (int i = 1; i <= 20; i++)
	{
		int res = is_give_rating(i);
		if (res > 0)
		{
			all_r_count++;//количество рейтингов за всё время
			all_r += res;// общая сумма рейтингов
		}
	}
	float av_rate = (float)all_r / all_r_count;//средний рейтинг

	for (int i = 0; i < 20; i++)
		session_l += session_load[i];// загрузок за сеанс
	int perc_l = (session_l - 2) / 8 * 100;// процент бота по загрузкам 
	if (perc_l < 0) perc_l = 0;

	for (int i = 0; i < 20; i++)
		session_c += session_comment[i];// комментариев за сеанс
	int perc_c = (session_c - 2) / 8 * 100; // процент бота по комментариям
	if (perc_c < 0) perc_c = 0;

	for (int i = 0; i < 20; i++)
		session_r += session_rating[i];// рейтингов за сеанс

	int perc_r;
	if (av_rate == 1 || av_rate == 5) perc_r = 100;//если средний 1 или 5, значит бот
	else perc_r = 0;

	int perc_bot_c = ((float)bot_coms / all_c_count) * 100;

	f << login << " Downloads counter of this session: " << session_l << " " << perc_l << "% bot;";
	f << " Comments counter of this session: " << session_c << " " << perc_c << "% bot;";
	f << " Ratings counter of this session: " << session_r << " " << perc_r << "% bot;";
	f << " Usual Rating of all time: " << av_rate << ";";
	f << " Bot comments of all time: " << bot_coms << ";";
	//здесь твои критерии
	f << std::endl;
	f.close();
}

void check_bot_comments()
{
	std::ifstream f("comment.txt");
	char line[50];
	char* ptr = NULL;
	while (!f.eof())
	{
		f.getline(line, 50);
		if (line[0] == '\t')
		{
			ptr = strtok(line, "\t");
			if (strcmp(ptr, login) == 0)
			{
				ptr = strtok(NULL, "\t");
				if (strchr(ptr, ' ') == NULL)
					bot_coms++;
			}
		}
		
	}
	f.close();
}