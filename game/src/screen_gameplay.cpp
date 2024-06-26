/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "screens.h"
#include "player.hpp"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
Camera2D* camera = { 0 };
Player* player = { 0 };

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    camera = new Camera2D;
    player = new Player();
    camera->offset = { 
        GetScreenWidth() / 2.0f - player->get_size().x / 2, 
        GetScreenHeight() / 2.0f - player->get_size().y / 2 };

    camera->target = player->get_position();
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
    
    framesCounter = 0;
    finishScreen = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    float delta = GetFrameTime();
    // TODO: Update GAMEPLAY screen variables here!
    player->update(delta);

    // FIXED
    camera->target = player->get_position();
    // SMOOTH
    /*camera->target.x = Lerp(camera->target.x, player->get_position().x, 10 * delta);
    camera->target.y = Lerp(camera->target.y, player->get_position().y, 10 * delta);*/


    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        //PlaySound(fxCoin);
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    draw_gameplay_ui();

    // DEBUG screen center
    DrawLineEx({ 0.0, GetScreenHeight() / 2.0f }, { GetScreenWidth() * 1.0f, GetScreenHeight() / 2.0f }, 2, DARKPURPLE);
    DrawLineEx({ GetScreenWidth() / 2.0f, 0.0 }, { GetScreenWidth() / 2.0f, GetScreenHeight() * 1.0f }, 2, DARKPURPLE);

    // TODO: Draw GAMEPLAY screen here!

    BeginMode2D(*camera);
        // DEBUG Draw grid
        for (int x = 0; x <= 800; x += 50)
        {
            DrawLineEx({ (float)x, 0.0 }, { (float)x, (float)800 }, 1, GREEN);
        }
        for (int y = 0; y <= 800; y += 50)
        {
            DrawLineEx({ 0.0, (float)y }, { (float)800, (float)y }, 1, GREEN);
        }

        player->draw();
    EndMode2D();
}

void draw_gameplay_ui(void)
{
    DrawFPS(10, 10);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}