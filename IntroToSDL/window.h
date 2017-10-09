#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#include <Windows.h>

//int init_window(SDL_Window* window);

void create_menu(HWND hWnd);

void menu_command(HWND hwnd, WORD lwParam);

#endif