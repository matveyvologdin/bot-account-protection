#ifndef MATVEY_H
#define MATVEY_H

#define _CRT_SECURE_NO_WARNINGS
#define ALL_APPS 0
#define ONLY_LOADED 1
#define CATALOG 1
#define COMMENTS 0
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace sf;

void catalog(RenderWindow& window, int flag, std::string user);
void draw_catalog(RenderWindow& window, int start_app, int flag);
int draw_buttons(RenderWindow& window, int flag);
int change_status_load(int index);
void install(int index, RenderWindow& window);
void show_info(RenderWindow& window, int index, std::string user);
int isloaded(int i);
int is_give_rating(int i);
void give_rating(RenderWindow& window, int index, std::string user);
void comments(RenderWindow& window, int index, std::string user);
int change_status_rating(int index, std::string rating);
void set_new_rating(std::string rating, std::string cnt, int index);
void save_comment(int index, std::string input);
void save_load_session(int index);
void save_rating_session(int index,int rating);
void draw_comments(RenderWindow& window, int start_com, int index);
void user_posted(int index);
int is_user_posted(int index);
void output_info();
void check_bot_comments();
#endif