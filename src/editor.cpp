#include "editor.h"
#include "../include/raylib.h"
#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

// stops showing grid, coors, or dots
void clear(Show *show)
{
  if (IsKeyDown(KEY_RIGHT_CONTROL) && IsKeyDown(KEY_G) && show->grid == true ||
      IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_G) && show->grid == true)
    show->grid = false;
  else if (IsKeyDown(KEY_RIGHT_CONTROL) && IsKeyDown(KEY_C) && show->coors == true ||
           IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_C) && show->coors == true)
    show->coors = false;
  else if (IsKeyDown(KEY_RIGHT_CONTROL) && IsKeyDown(KEY_D) && show->dots == true ||
           IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_D) && show->dots == true)
    show->dots = false;
  else
  {
    ;
  }
}
// shows grid, coors, or dots
void revel(Show *show, Grid *grid)
{
  if (IsKeyDown(KEY_G))
  {
    show->grid = true;
  }
  else if (IsKeyDown(KEY_C))
  {
    show->coors = true;
  }
  else if (IsKeyDown(KEY_D))
  {
    show->dots = true;
  }
  else
  {
    ;
  }
  if (show->grid)
  {
    // draw vertical lines
    for (int i = 0; i < VERTICAL_LINES; i++)
    {
      DrawLineEx(grid->start_v, grid->end_v, 1.0, BLACK);
      grid->start_v.x += SCREEN_DRAWING_AMOUNT;
      grid->end_v.x += SCREEN_DRAWING_AMOUNT;
    }
    // draw horizontal lines
    for (int i = 0; i < HORIZONTAL_LINES; i++)
    {
      DrawLineEx(grid->start_h, grid->end_h, 1.0, BLACK);
      grid->start_h.y += SCREEN_DRAWING_AMOUNT;
      grid->end_h.y += SCREEN_DRAWING_AMOUNT;
    }
  }
  if (show->coors)
  {
    // draw coors
    for (int i = 0; i < 11; i++)
    {
      for (int j = 0; j < 7; j++)
      {
        Vector2 coors = {SCREEN_DRAWING_AMOUNT * float(i), SCREEN_DRAWING_AMOUNT * float(j)};
        DrawText(TextFormat("(%i,%i)", SCREEN_DRAWING_AMOUNT * i, SCREEN_DRAWING_AMOUNT * j), int(coors.x), int(coors.y), 5.0, BLACK);
      }
    }
  }
  if (show->dots)
  {
    // draw coors dots
    for (int i = 0; i < 11; i++)
    {
      for (int j = 0; j < 7; j++)
      {
        Vector2 circles = {SCREEN_DRAWING_AMOUNT * float(i), SCREEN_DRAWING_AMOUNT * float(j)};
        DrawCircleV(circles, 5.0, BLACK);
      }
    }
  }
}
// renders the folder image and it contents
void icons(Texture2D folder, Position pos, Count count, Render &render)
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
    bool back = CheckCollisionCircleRec(mouse, 1.0, back_rec);
    bool mid = CheckCollisionCircleRec(mouse, 1.0, mid_rec);
    bool fore = CheckCollisionCircleRec(mouse, 1.0, fore_rec);
    bool obj = CheckCollisionCircleRec(mouse, 1.0, obj_rec);
    if (back && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      render.back = true;
      if (render.back)
        scene = Back;
    }
    if (mid && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      render.mid = true;
      if (render.mid)
        scene = Mid;
    }
    if (fore && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      render.fore = true;
      if (render.fore)
        scene = Fore;
    }
    if (obj && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      render.obj = true;
      if (render.obj)
        scene = Obj;
    }
  }
}

void render_assets(Position pos, std::vector<Texture2D> *assets, RenderAssets &ra)
{
  Vector2 drawPos = pos.contents;
  Vector2 mouse = GetMousePosition();
  bool collision;
  const int text_x = 450;
  const int text_y = 525;
  const int text_size = 50;
  if (scene == Back)
  {
    if (ra.count.back > 0)
    {
      for (int i = 0; i < ra.count.back; i++)
      {
        DrawTextureEx((*assets)[i], drawPos, 0.0, 0.25, WHITE);
        DrawRectangleRec({drawPos.x, drawPos.y, (float)(*assets)[i].width, (float)(*assets)[i].height}, BLANK);
        collision = CheckCollisionCircleRec(mouse, 5.0, {drawPos.x, drawPos.y, 50, 50});
        if (collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
          ra.asset = i;
          ra.place = true;
          ra.layer1.push_back((*assets)[i]);
        }
        if (ra.place)
        {
          DrawTextureEx((*assets)[ra.asset], {0, 0}, 0.0, 1.0, WHITE);
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
    int start = ra.count.back;
    int end = ra.count.back + ra.count.mid;
    if (ra.count.mid > 0)
    {
      for (int i = start; i < end; i++)
      {
        DrawTextureEx((*assets)[i], drawPos, 0.0, 0.25, WHITE);
        DrawRectangleRec({drawPos.x, drawPos.y, (float)(*assets)[i].width, (float)(*assets)[i].height}, BLANK);
        collision = CheckCollisionCircleRec(mouse, 5.0, {drawPos.x, drawPos.y, 50, 50});
        if (collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
          ra.asset = i;
          ra.pickup = true;
          ra.place = false;
        }
        if (mouse.x < SCREEN_WIDTH && mouse.y < SCREEN_HIGHT && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
          ra.pickup = false;
          ra.place = true;
        }
        if (ra.place)
        {
          DrawTextureEx((*assets)[ra.asset], {0, 0}, 0.0, 1.0, WHITE);
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
    int start = ra.count.back + ra.count.mid;
    int end = start + ra.count.fore;
    if (ra.count.fore > 0)
    {
      for (int i = start; i < end; i++)
      {
        DrawTextureEx((*assets)[i], drawPos, 0.0, 0.25, WHITE);
        DrawRectangleRec({drawPos.x, drawPos.y, (float)(*assets)[i].width, (float)(*assets)[i].height}, BLANK);
        collision = CheckCollisionCircleRec(mouse, 5.0, {drawPos.x, drawPos.y, 50, 50});
        if (collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
          ra.asset = i;
          ra.pickup = true;
          ra.place = false;
        }
        if (mouse.x < SCREEN_WIDTH && mouse.y < SCREEN_HIGHT && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
          ra.pickup = false;
          ra.place = true;
        }
        if (ra.place)
        {
          DrawTextureEx((*assets)[ra.asset], {0, 0}, 0.0, 1.0, WHITE);
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
    int start = ra.count.back + ra.count.mid + ra.count.fore;
    int end = start + ra.count.obj;
    // Draw asset icons for picking up
    if (ra.count.obj > 0)
    {
      for (int i = start; i < end; i++)
      {
        DrawTextureEx((*assets)[i], drawPos, 0.0, 2.0, WHITE);
        DrawRectangleRec({drawPos.x, drawPos.y, (float)(*assets)[i].width, (float)(*assets)[i].height}, BLANK);
        DrawRectangleLinesEx({drawPos.x, drawPos.y, (float)(*assets)[i].width * 2.0f, (float)(*assets)[i].height * 2.0f}, 2.0, BLACK);

        // Pick up asset if clicked
        if (CheckCollisionCircleRec(mouse, 5.0, {drawPos.x, drawPos.y, 50, 50}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
          ra.asset = i;
          ra.pickup = true;
        }
        drawPos.x += 150;
      }

      // Place asset if one is picked up and mouse is in bounds
      if (ra.pickup)
      {
        DrawTextureEx((*assets)[ra.asset], mouse, 0.0, 1.0, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && mouse.x < SCREEN_WIDTH && mouse.y < SCREEN_HIGHT)
        {
          ra.layer4.push_back((*assets)[ra.asset]);
          ra.location.push_back(mouse);
          ra.pickup = false;
        }
      }

      // Draw all placed objects
      for (int j = 0; j < ra.layer4.size(); j++)
      {
        DrawTextureEx(ra.layer4[j], ra.location[j], 0.0, 4.0, WHITE);
      }
      if (IsKeyPressed(KEY_B))
        scene = main;
      if (ra.pickup == true)
      {
        DrawTextureEx((*assets)[ra.asset], mouse, 0.0, 1.0, WHITE);
      }
    }
    else
    {
      DrawText("Empty", text_x, text_y, text_size, BLACK);
    }
    if (IsKeyPressed(KEY_B))
      scene = main;
  }
}
std::vector<Texture2D> load_assets(Count &count)
{
  std::vector<std::string> back_asset;
  std::vector<std::string> mid_asset;
  std::vector<std::string> fore_asset;
  std::vector<std::string> obj_asset;
  std::vector<Texture2D> assets;
  std::string back = "assets/background/";
  std::string mid = "assets/midground/";
  std::string fore = "assets/foreground/";
  std::string obj = "assets/objects/";
  if (fs::directory_iterator(back) != fs::directory_iterator())
  {
    for (const auto &filename : fs::directory_iterator(back))
    {
      std::cout << filename.path().filename();
      back_asset.push_back(filename.path().filename().string());
    }
  }
  else
    std::cout << "Background empty" << std::endl;

  if (!back_asset.empty())
  {
    for (int i = 0; i < back_asset.size(); i++)
    {
      std::string full_path = back + back_asset[i];
      Texture2D a = LoadTexture(full_path.c_str());
      assets.push_back(a);
    }
    count.back = back_asset.size();
  }
  else
  {
    ;
  }
  if (fs::directory_iterator(mid) != fs::directory_iterator())
  {
    for (const auto &filename : fs::directory_iterator(mid))
    {
      std::cout << filename.path().filename();
      mid_asset.push_back(filename.path().filename().string());
    }
  }
  else
    std::cout << "Midground empty" << std::endl;
  if (!mid_asset.empty())
  {
    for (int i = 0; i < mid_asset.size(); i++)
    {
      std::string full_path = mid + mid_asset[i];
      Texture2D a = LoadTexture(full_path.c_str());
      assets.push_back(a);
      std::cout << "loaded";
    }
    count.mid = mid_asset.size();
  }
  else
  {
    ;
  }
  if (fs::directory_iterator(fore) != fs::directory_iterator())
  {
    for (const auto &filename : fs::directory_iterator(fore))
    {
      std::cout << filename.path().filename();
      fore_asset.push_back(filename.path().filename().string());
    }
  }
  else
    std::cout << "Foreground empty" << std::endl;
  if (!fore_asset.empty())
  {
    for (int i = 0; i < fore_asset.size(); i++)
    {
      std::string full_path = fore + fore_asset[i];
      Texture2D a = LoadTexture(full_path.c_str());
      assets.push_back(a);
    }
    count.fore = fore_asset.size();
  }
  else
  {
    ;
  }
  if (fs::directory_iterator(obj) != fs::directory_iterator())
  {
    for (const auto &filename : fs::directory_iterator(obj))
    {
      std::cout << filename.path().filename();
      obj_asset.push_back(filename.path().filename().string());
    }
  }
  else
    std::cout << "Objects empty" << std::endl;
  if (!obj_asset.empty())
  {
    for (int i = 0; i < obj_asset.size(); i++)
    {
      std::string full_path = obj + obj_asset[i];
      Texture2D a = LoadTexture(full_path.c_str());
      assets.push_back(a);
    }
    count.obj = obj_asset.size();
  }
  else
  {
    ;
  }
  return assets;
}

void State::save()
{
}

void State::load()
{
}

void editor()
{
  struct Window
  {
    Vector2 start_w;
    Vector2 end_w;
    Vector2 start_h;
    Vector2 end_h;
  };

  Count count = {0};

  Position pos = {
      {150, 525},
      {50, 525},
  };

  Show show = {
      false};

  Render render = {
      false};

  InitWindow(1000, 650, "Editor");
  Texture2D folder = LoadTexture("folder.png");
  std::vector<Texture2D> assets = load_assets(count);
  RenderAssets ra = {
      .count = count,
      .asset = -1,
      .pickup = false,
      .place = false,
  };

  while (!WindowShouldClose())
  {
    Window window = {
        .start_w = {0, 0},
        .end_w = {0, SCREEN_HIGHT},
        .start_h = {0, 0},
        .end_h = {SCREEN_WIDTH, 0},
    };
    Grid grid = {
        {SCREEN_DRAWING_AMOUNT, 0},
        {SCREEN_DRAWING_AMOUNT, SCREEN_HIGHT},
        {0, SCREEN_DRAWING_AMOUNT},
        {SCREEN_WIDTH, SCREEN_DRAWING_AMOUNT},
    };
    BeginDrawing();
    ClearBackground(WHITE);
    for (int i = 0; i < 2; i++)
    {
      DrawLineEx(window.start_w, window.end_w, 1.0, BLACK);
      DrawLineEx(window.start_h, window.end_h, 1.0, BLACK);
      window.start_h.y += SCREEN_HIGHT;
      window.end_h.y += SCREEN_HIGHT;
      window.start_w.x += SCREEN_WIDTH;
      window.end_w.x += SCREEN_WIDTH;
    }
    revel(&show, &grid);
    clear(&show);
    icons(folder, pos, count, render);
    render_assets(pos, &assets, ra);
    EndDrawing();
  }
  UnloadTexture(folder);
  for (const auto x : assets)
  {
    UnloadTexture(x);
  }
  CloseWindow();
}
