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
#include <algorithm>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
Camera2D* camera = { 0 };
Player* player = { 0 };
Vector2 mouse_position = { 0 };

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
        GetScreenWidth() / 2.0f - player->get_size() / 2, 
        GetScreenHeight() / 2.0f - player->get_size() / 2 };

    camera->target = player->get_position();
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
    
    framesCounter = 0;
    finishScreen = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
    float delta = GetFrameTime();
    camera->target = player->get_position(); // FIXED CAMERA
    mouse_position = GetScreenToWorld2D(GetMousePosition(), *camera);
    player->update(delta, *camera, mouse_position);

    for (unsigned i = 0; i < player->attacks.size(); i++)
    {
        if (player->attacks[i].state == 0)
        {
            player->attacks[i].update(delta);
        }

        // remove element from the player attacks Vector if their state is 1 (Inactive)
        // this is probably the best way off doing it
        player->attacks.erase(std::remove_if(player->attacks.begin(), player->attacks.end(),
            [](Projectile const x) -> bool { return x.state == 1; }),
            player->attacks.end());

    }
    
    // SMOOTH CAMERA
    /*camera->target.x = Lerp(camera->target.x, player->get_position().x, 10 * delta);
    camera->target.y = Lerp(camera->target.y, player->get_position().y, 10 * delta);*/


    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 1;
        //PlaySound(fxCoin);
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    float _width = GetScreenWidth();
    float _height = GetScreenHeight();

    draw_gameplay_ui();

    #ifdef DEBUG
        // DEBUG screen center
        DrawLineEx(
            { 0.0, _height / 2.0f },
            { _width, _height / 2.0f },
            2, DARKPURPLE);
        DrawLineEx(
            { _width / 2.0f, 0.0 },
            { _width / 2.0f, _height},
            2, DARKPURPLE);
    #endif

    // TODO: Draw GAMEPLAY screen here!
    BeginMode2D(*camera);
        #ifdef DEBUG
            // DEBUG Draw grid
            for (int x = 0; x <= 800; x += 50)
            {
                DrawLineEx({ (float)x, 0.0 }, { (float)x, (float)800 }, 1, GREEN);
            }
            for (int y = 0; y <= 800; y += 50)
            {
                DrawLineEx({ 0.0, (float)y }, { (float)800, (float)y }, 1, GREEN);
            }
        #endif

        for (unsigned i = 0; i < player->attacks.size(); i++)
        {
            if (player->attacks[i].state == 0)
            {
                player->attacks[i].draw();
            }
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
    delete camera;
    delete player;
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}