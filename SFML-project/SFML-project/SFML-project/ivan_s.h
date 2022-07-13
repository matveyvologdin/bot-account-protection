#ifndef IVAN_S_H
#define IVAN_S_H

#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <sstream>

using namespace std;
using namespace sf;

int menu(RenderWindow& window, int is_user, string user);
int registration(RenderWindow& window);
string authorization(RenderWindow& window);
void add_to_load(string login);
void add_to_give_rating(string login);
void add_to_post_comment(string login);
void add_to_input_time(string login, double, double);
void change_input_time(string login, double log, double pas);
void refresh_cur_session();
void change_make_act_time(string login, double time);
#endif