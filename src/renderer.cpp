#include "renderer.h"
#include "editor.h"
#include <iostream>

void Renderer::render_assets(Position pos, std::vector<Texture2D> *assets, Properties &prop)
{
    Vector2 drawPos = pos.contents;
    Vector2 mouse = GetMousePosition();
    bool collision;
    const int text_x = 450;
    const int text_y = 525;
    const int text_size = 50;
    if (scene == Back)
    {
        if (count.back > 0)
        {
            for (int i = 0; i < count.back; i++)
            {
                DrawTextureEx((*assets)[i], drawPos, 0.0, 0.25, WHITE);
                DrawRectangleRec({drawPos.x, drawPos.y, (float)(*assets)[i].width, (float)(*assets)[i].height}, BLANK);
                collision = CheckCollisionCircleRec(mouse, 5.0, {drawPos.x, drawPos.y, 50, 50});
                if (collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    asset = i;
                    place = true;
                    layer1.push_back((*assets)[i]);
                }
                if (place)
                {
                    DrawTextureEx((*assets)[asset], {0, 0}, 0.0, 1.0, WHITE);
                }
                drawPos.x += 150;
            }
        }
        else
        {
            DrawText("Empty", text_x, text_y, text_size, BLACK);
        }
        if (IsKeyPressed(KEY_B))
            scene = main;
    }
    else if (scene == Mid)
    {
        int start = count.back;
        int end = count.back + count.mid;
        if (count.mid > 0)
        {
            for (int i = start; i < end; i++)
            {
                DrawTextureEx((*assets)[i], drawPos, 0.0, 0.25, WHITE);
                DrawRectangleRec({drawPos.x, drawPos.y, (float)(*assets)[i].width, (float)(*assets)[i].height}, BLANK);
                collision = CheckCollisionCircleRec(mouse, 5.0, {drawPos.x, drawPos.y, 50, 50});
                if (collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    asset = i;
                    pickup = true;
                    place = false;
                }
                if (mouse.x < SCREEN_WIDTH && mouse.y < SCREEN_HEIGHT && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    pickup = false;
                    place = true;
                }
                if (place)
                {
                    DrawTextureEx((*assets)[asset], {0, 0}, 0.0, 1.0, WHITE);
                }
                drawPos.x += 150;
            }
        }
        else
        {
            DrawText("Empty", text_x, text_y, text_size, BLACK);
        }
        if (IsKeyPressed(KEY_B))
            scene = main;
    }
    else if (scene == Fore)
    {
        int start = count.back + count.mid;
        int end = start + count.fore;
        if (count.fore > 0)
        {
            for (int i = start; i < end; i++)
            {
                DrawTextureEx((*assets)[i], drawPos, 0.0, 0.25, WHITE);
                DrawRectangleRec({drawPos.x, drawPos.y, (float)(*assets)[i].width, (float)(*assets)[i].height}, BLANK);
                collision = CheckCollisionCircleRec(mouse, 5.0, {drawPos.x, drawPos.y, 50, 50});
                if (collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    asset = i;
                    pickup = true;
                    place = false;
                }
                if (mouse.x < SCREEN_WIDTH && mouse.y < SCREEN_HEIGHT && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    pickup = false;
                    place = true;
                }
                if (place)
                {
                    DrawTextureEx((*assets)[asset], {0, 0}, 0.0, 1.0, WHITE);
                }
                drawPos.x += 150;
            }
        }
        else
        {
            DrawText("Empty", text_x, text_y, text_size, BLACK);
        }
        if (IsKeyPressed(KEY_B))
            scene = main;
    }
    else if (scene == Obj)
    {
        int start = count.back + count.mid + count.fore;
        int end = start + count.obj;
        // Draw asset icons for picking up
        if (count.obj > 0)
        {
            for (int i = start; i < end; i++)
            {
                DrawTextureEx((*assets)[i], drawPos, 0.0, 2.0, WHITE);
                DrawRectangleRec({drawPos.x, drawPos.y, (float)(*assets)[i].width, (float)(*assets)[i].height}, BLANK);
                DrawRectangleLinesEx({drawPos.x, drawPos.y, (float)(*assets)[i].width * 2.0f, (float)(*assets)[i].height * 2.0f}, 2.0, BLACK);

                // Pick up asset if clicked
                if (CheckCollisionCircleRec(mouse, 5.0, {drawPos.x, drawPos.y, 50, 50}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    asset = i;
                    pickup = true;
                }
                drawPos.x += 150;
            }

            // Place asset if one is picked up and mouse is in bounds
            if (pickup)
            {
                DrawTextureEx((*assets)[asset], mouse, 0.0, 1.0, WHITE);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && mouse.x < SCREEN_WIDTH && mouse.y < SCREEN_HEIGHT)
                {
                    layer4.push_back((*assets)[asset]);
                    location.push_back(mouse);
                    pickup = false;
                }
            }

            // Draw all placed objects
            for (int j = 0; j < layer4.size(); j++)
            {
                Rectangle rect = {location[j].x, location[j].y, (float)layer4[j].width * 4.0f, (float)layer4[j].height * 4.0f};
                DrawTextureEx(layer4[j], location[j], 0.0, 4.0, WHITE);
                DrawRectangleRec(rect, BLANK);
                bool is_colliding = CheckCollisionCircleRec(mouse, 5.0, rect);
                bool is_mouse_clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

                if (!clicked && is_colliding && is_mouse_clicked)
                {
                    clicked = true;
                    prop.selected = true;
                    asset_properties.push_back(prop);
                }
                else if (clicked)
                {
                    DrawRectangleLinesEx(rect, 5.0f, BLACK);
                    if (is_colliding && is_mouse_clicked)
                    {
                        clicked = false;
                    }
                }
                else
                {
                    ;
                }
            }
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                place = false;
            if (IsKeyPressed(KEY_B))
                scene = main;
            if (pickup == true)
            {
                DrawTextureEx((*assets)[asset], mouse, 0.0, 1.0, WHITE);
            }
        }
        else
        {
            DrawText("Empty", text_x, text_y, text_size, BLACK);
        }
    }
}

// renders the folder image and it contents
void Renderer::icons(Texture2D folder, Position pos, Count count)
{
    Rectangle back_rec = {ICONS_TEXT_X, pos.icons.y, 100, 100};
    Rectangle mid_rec = {ICONS_TEXT_X + 150, pos.icons.y, 100, 100};
    Rectangle fore_rec = {ICONS_TEXT_X + 300, pos.icons.y, 100, 100};
    Rectangle obj_rec = {ICONS_TEXT_X + 450, pos.icons.y, 100, 100};
    Vector2 mouse = GetMousePosition();
    if (scene == main)
    {
        for (int i = 0; i < 4; i++)
        {
            DrawTextureEx(folder, pos.icons, 0.0, 0.20, WHITE);
            DrawRectangleRec({pos.icons.x, pos.icons.y, 100, 100}, BLANK);
            pos.icons.x += 150;
        }
        DrawText("Background", ICONS_TEXT_X, ICONS_TEXT_Y, ICONS_TEXT_SIZE, BLACK);
        DrawText("Midground", ICONS_TEXT_X + 150, ICONS_TEXT_Y, ICONS_TEXT_SIZE, BLACK);
        DrawText("Foreground", ICONS_TEXT_X + 300, ICONS_TEXT_Y, ICONS_TEXT_SIZE, BLACK);
        DrawText("Objects", ICONS_TEXT_X + 450, ICONS_TEXT_Y, ICONS_TEXT_SIZE, BLACK);
        bool back_collision = CheckCollisionCircleRec(mouse, 1.0, back_rec);
        bool mid_collision = CheckCollisionCircleRec(mouse, 1.0, mid_rec);
        bool fore_collision = CheckCollisionCircleRec(mouse, 1.0, fore_rec);
        bool obj_collision = CheckCollisionCircleRec(mouse, 1.0, obj_rec);
        if (back_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            scene = Back;
        }
        if (mid_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            scene = Mid;
        }
        if (fore_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            scene = Fore;
        }
        if (obj_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            scene = Obj;
        }

        for (int j = 0; j < layer4.size(); j++)
        {
            DrawTextureEx(layer4[j], location[j], 0.0, 4.0, WHITE);
        }
    }
}
