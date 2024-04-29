/*******************************************************************************************
*
*	raylib [core] example - Smooth Pixel-perfect camera
*
*	Example originally created with raylib 3.7, last time updated with raylib 4.0
*	
*	Example contributed by Giancamillo Alessandroni (@NotManyIdeasDev) and
*	reviewed by Ramon Santamaria (@raysan5)
*
*	Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*	BSD-like license that allows static linking with closed source software
*
*	Copyright (c) 2021-2024 Giancamillo Alessandroni (@NotManyIdeasDev) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

/********************************************************************************************
*	This was built off the aforementioned raylib example, it's license is to be respected for
*	this file
********************************************************************************************/
#include "include/vlibdmk.h"

// Change to raylib.h if you have raylib installed on your system's include path
#include "include/raylib.h"

#include <stdlib.h>
#include <cstdio>
#include <math.h>
#include <cstdint>

#define MAX_FILEPATH_RECORDED 4096
#define MAX_FILEPATH_SIZE 2048

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "VLibDMK test");
	
	// Instance the library
	VLibDMK vd;
	uint64_t bullet_idx = 0;
	uint16_t bullet_posx = 0;
	uint16_t bullet_posy = 0;
	printf("VLibDMK: Starting at idx %d\n", bullet_idx);
	#define TEST_BULLETS 70000
	// Set up active bullets
	while (bullet_idx < TEST_BULLETS){
		vd.write_bullet(bullet_idx, bullet_posx, bullet_posy, 0, 0, 1, 1, bullet_idx, 0 | BULLET_ACTIVE | BULLET_MOVING, 1);
		bullet_posx += 2;
		if (bullet_posx > 255){
			bullet_posx = 0;
			bullet_posy += 5;
		}
		bullet_idx++;
	}
	printf("VLibDMK: Active until idx %i\n", bullet_idx);
	//Set up inactive bullets, so that if we need more, they are initialized
	while (bullet_idx < RUNTIME_BULLETS){
		vd.write_bullet(bullet_idx, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		bullet_idx++;
	}
	printf("VLibDMK: Finishing at idx %d\n", bullet_idx);
	bullet_idx = 0;
	
	// For collision testing, using distance we can make a rhomboid hitbox
	const Vector2 tpos = {0,0};
	int test_dist = 0;
	
	// Load bullet texture
	Texture2D bullet_texture = LoadTexture("img/tp.png");
	
	// Bullet render space, will distribute bullets across the entire screen, use to limit
	// Bullet boundaries
	float windowXScale = GetScreenWidth()/255.0f;
	float windowYScale = GetScreenHeight()/255.0f;
	
	printf("VLibDMK: Ready to begin rendering...\n");
	Color ewe = WHITE;
	
	printf("int %i", 1 & 2); 
	uint8_t termo = 0;
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_F)) ToggleFullscreen();
		// Update bullet render space
		windowXScale = GetScreenWidth()/255.0f;
		windowYScale = GetScreenHeight()/255.0f;
		ClearBackground(RAYWHITE);
		BeginDrawing();
		
		// Begin bullet logic
		while (bullet_idx < TEST_BULLETS){
			//Skip half the bullets, for better performance; comment this block to process all of them
			if (bullet_idx % 2 == termo){
				bullet_idx++;
				continue;
			}
			// This is here for testing purposes, can be commented out
			// If you need a lot of prints here to debug bullet processing
			//a single iteration can take a couple ms due to printf overhead
			if (WindowShouldClose()){
				UnloadTexture(bullet_texture);
				CloseWindow();
				return 21;
			}
			// Move bullets
			if ((vd.get_bullet_data(bullet_idx, FLAG) & BULLET_MOVING) != 0){
				uint8_t i_tempxpos = vd.get_bullet_data(bullet_idx, XPOS);
				uint8_t i_tempypos = vd.get_bullet_data(bullet_idx, YPOS);
				uint8_t i_tempxdir = vd.get_bullet_data(bullet_idx, XDIR);
				uint8_t i_tempydir = vd.get_bullet_data(bullet_idx, YDIR);
				
				vd.set_bullet_data(bullet_idx, i_tempxpos + i_tempxdir, XPOS);
				vd.set_bullet_data(bullet_idx, i_tempypos + i_tempydir, YPOS);
			}
			// Draw bullets
			if ((vd.get_bullet_data(bullet_idx, FLAG) & BULLET_ACTIVE) != 0){
				// Spin every bullet, for showing purposes, in game this wouldn't be used
				vd.set_bullet_data(bullet_idx, vd.get_bullet_data(bullet_idx, ANGL)+1, ANGL);
				
				// Collision testing
				test_dist = vd.get_bullet_data(bullet_idx, XPOS) - tpos.x;
				test_dist += vd.get_bullet_data(bullet_idx, YPOS) - tpos.y;
				// Tint for colliding bullets
				if (test_dist < 25){
					ewe = GREEN;
					if (test_dist < 10){
						ewe = RED;
					}
				}
				
				// Actual drawing
				// Bullet position is scaled to fit renderspace
				Rectangle source = {0, 0, bullet_texture.width, bullet_texture.height};
				Rectangle dest = {vd.get_bullet_data(bullet_idx, XPOS) * windowXScale, vd.get_bullet_data(bullet_idx, YPOS) * windowYScale, bullet_texture.width, bullet_texture.height};
				Vector2 origin = {bullet_texture.width / 2, bullet_texture.height / 2};
				DrawTexturePro(bullet_texture, source, dest, origin, vd.get_bullet_data(bullet_idx, ANGL), ewe);
				ewe = WHITE;
			}
			bullet_idx++;
		} // End bullet logic
		
		// Flip this for half bullet processing, otherwise can be left out
		termo ^= 1;
		bullet_idx = 0;
		
			DrawText(TextFormat("Bullet n%i : %i, %i", bullet_idx, vd.get_bullet_data(bullet_idx, YPOS), vd.get_bullet_data(bullet_idx, YPOS)), 10, 70, 20, DARKPURPLE);
			DrawFPS(GetScreenWidth() - 95, 10);
		EndDrawing();
	}
	UnloadTexture(bullet_texture);
	CloseWindow();
	return 31;
}