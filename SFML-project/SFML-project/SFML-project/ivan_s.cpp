#include "ivan_s.h"
#include "Common.h"

//���������� ���������� ������� �����, ������ ������� � ���, ��� ��� ����������
extern string user;
int session_load[20];
int session_rating[20];
int session_comment[20];
int bot_coms;
#pragma region �����

int menu(RenderWindow& window, int is_user, string user) {
	double menu_time_start = clock();
	Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, menuTexture5, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	menuTexture4.loadFromFile("images/444.png");
	menuTexture5.loadFromFile("images/555.png");
	menuBackground.loadFromFile("images/Penguins.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menu4(menuTexture4),
		menu5(menuTexture5), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menu4.setPosition(100, 210);
	menu5.setPosition(100, 270);
	menuBg.setPosition(345, 0);

	Font font;//����� 
	font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Text info("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	info.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	info.setPosition(100, 330);//������ ������� ������, ����� ������
	if (is_user)
		info.setString(user);//������ ������ ������
	else
		info.setString("Sign in/Log in");
	//////////////////////////////����///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menu4.setColor(Color::White);
		menu5.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 180, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 180, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 180, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }
		if (IntRect(100, 210, 180, 50).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Blue); menuNum = 4; }
		if (IntRect(100, 270, 180, 50).contains(Mouse::getPosition(window))) { menu5.setColor(Color::Blue); menuNum = 5; }

		if (Mouse::isButtonPressed(Mouse::Left))
			if (menuNum > 0 && menuNum < 6)
			{
				double menu_time_end = clock()-menu_time_start;//������� ������� ������������ ������ � ����
				if (user != "")
				{
					//cout << "change time" << endl;
					change_make_act_time(user, menu_time_end);
					//cout << "time: " << menu_time_end / CLOCKS_PER_SEC << endl;
				}
				return menuNum;
			}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);
		window.draw(menu5);
		window.draw(info);

		window.display();
	}
	////////////////////////////////////////////////////
}

int registration(RenderWindow& window)
{
	window.clear(Color(129, 181, 221));

	Font font;//����� 
	font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������

	Text login("", font, 30), password("", font, 30);
	password.setStyle(sf::Text::Bold | sf::Text::Underlined);
	login.setStyle(sf::Text::Bold | sf::Text::Underlined);
	password.setPosition(400, 200);
	login.setPosition(400, 100);
	std::string str_login = "";
	std::string str_password = "";

	Text login_text("", font, 30);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	login_text.setString("���������� �����: ");//������ ������ ������
	Text password_text("", font, 30);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	password_text.setString("���������� ������: ");//������ ������ ������
	login_text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	login_text.setPosition(100, 100);//������ ������� ������, ����� ������
	password_text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	password_text.setPosition(100, 200);//������ ������� ������, ����� ������

	Text info("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	info.setString("������� �����->������� Tab->������� ������->������� Enter");//������ ������ ������
	info.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	info.setPosition(100, 300);//������ ������� ������, ����� ������

	window.display();

	double input_login_time = clock();
	//�������� �����
	while (!(Keyboard::isKeyPressed(Keyboard::Tab)))//�� ��� ���, ���� �� ����� �����
	{
		window.draw(password_text);//����� ���� �����
		window.draw(login_text);//����� ���� �����
		window.draw(password);//����� ���� �����
		window.draw(login);//����� ���� �����
		window.draw(info);//����� ���� �����
		window.display();
		sf::Event event;
		if (window.pollEvent(event))
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128 && ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z')))
				{
					str_login += static_cast<char>(event.text.unicode);
					login.setString(str_login);
				}
			}
		window.clear(Color(129, 181, 221));
	}
	input_login_time = clock() - input_login_time;//�������� ����� �����
	//!(Keyboard::isKeyPressed(Keyboard::Return))
	sf::Event eventt;
	window.pollEvent(eventt);
	double input_password_time = clock();
	while (!(Keyboard::isKeyPressed(Keyboard::Return)))//�� ��� ���, ���� �� ����� �����
	{
		window.draw(password_text);//����� ���� �����
		window.draw(login_text);//����� ���� �����
		window.draw(password);//����� ���� �����
		window.draw(login);//����� ���� �����
		window.draw(info);//����� ���� �����
		window.display();
		sf::Event event;
		if (window.pollEvent(event))
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128 && ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z')))
				{
					str_password += static_cast<char>(event.text.unicode);
					password.setString(str_password);
				}
			}
		window.clear(Color(129, 181, 221));
	}
	input_password_time = clock()- input_password_time;
	std::ifstream fin("Users.txt");
	std::string s;
	while (!fin.eof())
	{
		fin >> s;
		if (str_login == s)
		{
			Text info("", font, 30);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
			info.setString("����� ��� ������������ ������ �������������, ���������� ������");//������ ������ ������
			info.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
			info.setPosition(100, 100);//������ ������� ������, ����� ������
			window.draw(info);//����� ���� �����
			window.display();
			fin.close();
			Sleep(3000);
			return 1;
		}
		fin >> s;
	}
	fin.close();
	std::ofstream fout("Users.txt", std::ios::app);//������ � ����� �����
	fout << str_login << ' ' << str_password << std::endl;
	fout.close();

	Text info2("", font, 30);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	info2.setString("������������ ������� ���������������");//������ ������ ������
	info2.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	info2.setPosition(100, 100);//������ ������� ������, ����� ������
	window.draw(info2);//����� ���� �����
	add_to_load(str_login);
	add_to_give_rating(str_login);
	add_to_post_comment(str_login);
	add_to_input_time(str_login, input_login_time, input_password_time);
	window.display();
	Sleep(3000);

	return 1;
}

void add_to_give_rating(string login)
{
	std::fstream load_file("give_rating.txt");
	load_file.seekg(0, std::ios::end);
	load_file << login << " 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" << std::endl;
	load_file.close();
}

void add_to_load(string login)
{
	std::fstream load_file("load.txt");
	load_file.seekg(0, std::ios::end);
	load_file << login << " 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" << std::endl;
	load_file.close();
}

//������ ����� - ��������� ������ ����� � ���������� ������ � ������ (���� ����� ������, ��\
��� ��� ����� � ������� ������������ ��� ��� � ���� ������� ����), ������ ����� - ������� ����� ������������ ����� ���������
void add_to_input_time(string login, double log, double pas)
{
	std::fstream load_file("input_time.txt");
	load_file.seekg(0, std::ios::end);
	double d = 0;
	int dd = 0;
	load_file << login << " " <<(log+pas)/CLOCKS_PER_SEC<<" "<<d<<' ' << dd << std::endl;
	load_file.close();
}

void add_to_post_comment(string login)
{
	std::fstream load_file("post_comment.txt");
	load_file.seekg(0, std::ios::end);
	load_file << login << " 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" << std::endl;
	load_file.close();
}

void refresh_cur_session()
{
	memset(session_load, 0, sizeof(session_load));
	memset(session_rating, 0, sizeof(session_rating));
	memset(session_comment, 0, sizeof(session_comment));
	bot_coms = 0;
}

void change_input_time(string login, double log, double pas)
{
	std::ifstream load_file("input_time.txt");
	std::string u_login[100];
	double u_entering[100], u_make_action[100];
	int u_actions[100];
	int i = 0;
	while (1)
	{
		load_file >> u_login[i];
		if (u_login[i] == "") break;
		load_file>>u_entering[i] >> u_make_action[i]>>u_actions[i];
		//std::cout << u_login[i] << " " << u_pas[i] << " " << u_log[i] << std::endl;
		i++;
	}
	load_file.close();
	std::ofstream out("input_time.txt");
	//�������� ������ ����� �����
	for (int j = 0; j < i; j++)
	{
		if (u_login[j] != login)
		{
			out << u_login[j] << ' ';
			out << u_entering[j] << ' ' << u_make_action[j] << ' '<<u_actions[j] << std::endl;
		}
		else
		{
			out << u_login[j] << ' ';
			out << (log + pas) / CLOCKS_PER_SEC << " "<<u_make_action[j] << " " << u_actions[j] << std::endl;
		}
	}
	out.close();
}

void change_make_act_time(string login, double time)
{
	std::ifstream load_file("input_time.txt");
	std::string u_login[100];
	double u_entering[100], u_make_action[100];
	int u_actions[100];
	int i = 0;
	while (1)
	{
		load_file >> u_login[i];
		if (u_login[i] == "") break;
		load_file >> u_entering[i] >> u_make_action[i] >> u_actions[i];
		//std::cout << u_login[i] << " " << u_pas[i] << " " << u_log[i] << std::endl;
		i++;
	}
	load_file.close();
	std::ofstream out("input_time.txt");
	//�������� ������ ����� �����
	for (int j = 0; j < i; j++)
	{
		if (u_login[j] != login)
		{
			out << u_login[j] << ' ';
			out << u_entering[j] << ' ' << u_make_action[j] << ' ' << u_actions[j] << std::endl;
		}
		else
		{
			out << u_login[j] << ' ';
			out << u_entering[j] << ' ' << (u_make_action[j]*u_actions[j] + time / CLOCKS_PER_SEC) / ++u_actions[j] << ' ' << u_actions[j] << std::endl;
		}
	}
	out.close();
}

#pragma region �����������

vector<string> ReadLines(string fileName)
{
	fstream stream(&fileName[0]);
	string line;
	vector<string> result;
	while (getline(stream, line))
		result.push_back(line);
	stream.close();
	return result;
}

vector<string> Split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string tok;
	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}
	return internal;
}

bool IsUserExists(string fileName, string userName, string password) {
	vector<string> lines = ReadLines(fileName);
	for (string line : lines) {
		vector<string> subLines = Split(line, ' ');
		if (subLines.size() == 2) {
			if (subLines[0] == userName && subLines[1] == password)
				return true;
		}
	}
	return false;
}

bool IsCharInRange(string alphabet, char c) {
	for (char t : alphabet)
		if (c == t)
			return true;
	return false;
}

string authorization(RenderWindow& window)
{
	window.clear(Color(129, 181, 221));
	Font font;//����� 
	font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������

	Text login("", font, 30), password("", font, 30);
	password.setStyle(sf::Text::Bold | sf::Text::Underlined);
	login.setStyle(sf::Text::Bold | sf::Text::Underlined);
	password.setPosition(400, 200);
	login.setPosition(400, 100);
	std::string str_login = "";
	std::string str_password = "";

	Text login_text("", font, 30);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	login_text.setString("�����: ");//������ ������ ������
	Text password_text("", font, 30);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	password_text.setString("������: ");//������ ������ ������
	login_text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	login_text.setPosition(100, 100);//������ ������� ������, ����� ������
	password_text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	password_text.setPosition(100, 200);//������ ������� ������, ����� ������

	Text info("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	info.setString("������� �����->������� Tab->������� ������->������� Enter");//������ ������ ������
	info.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	info.setPosition(100, 300);//������ ������� ������, ����� ������

	window.display();

	double input_login_time = clock();
	//�������� �����
	while (!(Keyboard::isKeyPressed(Keyboard::Tab)))//�� ��� ���, ���� �� ����� �����
	{
		window.draw(password_text);//����� ���� �����
		window.draw(login_text);//����� ���� �����
		window.draw(password);//����� ���� �����
		window.draw(login);//����� ���� �����
		window.draw(info);//����� ���� �����
		window.display();
		sf::Event event;
		if (window.pollEvent(event))
			if (event.type == sf::Event::TextEntered)
			{
				if (IsCharInRange(loginAlphabet, event.text.unicode))
				{
					str_login += static_cast<char>(event.text.unicode);
					login.setString(str_login);
				}
			}
		window.clear(Color(129, 181, 221));
	}
	input_login_time = clock()- input_login_time;
	//!(Keyboard::isKeyPressed(Keyboard::Return))
	sf::Event eventt;
	window.pollEvent(eventt);
	double input_password_time = clock();
	while (!(Keyboard::isKeyPressed(Keyboard::Return)))//�� ��� ���, ���� �� ����� �����
	{
		window.draw(password_text);//����� ���� �����
		window.draw(login_text);//����� ���� �����
		window.draw(password);//����� ���� �����
		window.draw(login);//����� ���� �����
		window.draw(info);//����� ���� �����
		window.display();
		sf::Event event;
		if (window.pollEvent(event))
			if (event.type == sf::Event::TextEntered)
			{
				if (IsCharInRange(passowrdAlphabet, event.text.unicode))
				{
					str_password += static_cast<char>(event.text.unicode);
					password.setString(str_password);
				}
			}
		window.clear(Color(129, 181, 221));
	}
	input_password_time = clock()-input_password_time;
#pragma region �������� ��������� ������
	bool isExists = IsUserExists(dbPath, str_login, str_password);
#pragma endregion

	int res = 0;
	Text info2("", font, 30);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	if (isExists)
	{
		info2.setString("������������ �����������");//������ ������ ������
		res = 1;
		change_input_time(str_login, input_login_time, input_password_time);
		refresh_cur_session();
	}
	else
		info2.setString("������������ � ����� ������ ��� ������� �� ����������!");
	info2.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	info2.setPosition(100, 100);//������ ������� ������, ����� ������
	window.draw(info2);//����� ���� �����
	window.display();
	Sleep(3000);
	if (res)
		return str_login;
	return "";
}
#pragma endregion

#pragma endregion

