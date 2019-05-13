#pragma once
#ifndef SDL_DEPENDENCIES_H_INCLUDED
#define SDL_DEPENDENCIES_H_INCLUDED
/* 
These will have all the libraries and dependencies that we need placed here. 
Please do not add files somewhere else to prevent duplication of headers.
Although, I put pragma once and ifndef, I would prefer to not add duplication of headers.
*/
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <Windows.h>
#include <stdio.h>

SDL_Renderer * render; // Global variable so any function/file can call upon the renderer
SDL_Window * window; // Global variable so any function/file can call upon the window
TTF_Font *font;
TTF_Font *font2;

#endif
