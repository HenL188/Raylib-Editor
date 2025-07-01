#include "editor.h"
#include "../include/raylib.h"
#include <iostream>
#include <filesystem>

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
    // draw veritcal lines
    for (int i = 0; i < 10; i++)
    {
      DrawLineEx(grid->start_v, grid->end_v, 1.0, BLACK);
      grid->start_v.x += 80;
      grid->end_v.x += 80;
    }
    // draw horzontal lines
    for (int i = 0; i < 6; i++)
    {
      DrawLineEx(grid->start_h, grid->end_h, 1.0, BLACK);
      grid->start_h.y += 80;
      grid->end_h.y += 80;
    }
  }
  if (show->coors)
  {
    // draw coors
    for (int i = 0; i < 11; i++)
    {
      for (int j = 0; j < 7; j++)
      {
        Vector2 coors = {80 * float(i), 80 * float(j)};
        DrawText(TextFormat("(%i,%i)", 80 * i, 80 * j), int(coors.x), int(coors.y), 5.0, BLACK);
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
        Vector2 circles = {80 * float(i), 80 * float(j)};
        DrawCircleV(circles, 5.0, BLACK);
      }
    }
  }
}

void icons(Texture2D folder, Vector2 pos, std::vector<Texture2D> *assets)
{
  Vector2 mouse = GetMousePosition();
  for (int i; i < 4; i++)
  {
    DrawTextureEx(folder, pos, 0.0, 0.20, WHITE);
    DrawRectangleRec({pos.x, pos.y, 100, 100}, RED);
    pos.x += 150;
  }
  DrawText("Background", 180, 590, 10, BLACK);
  DrawText("Midground", 330, 590, 10, BLACK);
  DrawText("Foreground", 470, 590, 10, BLACK);
  DrawText("Objects", 630, 590, 10, BLACK);
  DrawCircleV(mouse, 1.0, RED);
  bool back = CheckCollisionCircleRec(mouse, 1.0, {150, pos.y, 100, 100});
  bool mid = CheckCollisionCircleRec(mouse, 1.0, {300, pos.y, 100, 100});
  bool fore = CheckCollisionCircleRec(mouse, 1.0, {450, pos.y, 100, 100});
  bool obj = CheckCollisionCircleRec(mouse, 1.0, {600, pos.y, 100, 100});
  if (back && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
  }
  else if (mid && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
  }
  else if (fore && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
  }
  else if (obj && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
  }
  else
  {
    ;
  }
}

std::vector<Texture2D> load_assets(Count& count)
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
    (exit(EXIT_FAILURE));
  if (!back_asset.empty())
  {
    for (int i = 0; i < back_asset.size(); i++)
    {
      std::string full_path = back + back_asset[i];
      Texture2D a = LoadTexture(full_path.c_str());
      assets.push_back(a);
    }
    count.back = back_asset.size();
  } else{;}
  if (fs::directory_iterator(mid) != fs::directory_iterator())
  {
    for (const auto &filename : fs::directory_iterator(mid))
    {
      std::cout << filename.path().filename();
      back_asset.push_back(filename.path().filename().string());
    }
  }
  else
    (exit(EXIT_FAILURE));
  if (!mid_asset.empty())
  {
    for (int i = 0; i < mid_asset.size(); i++)
    {
      std::string full_path = back + mid_asset[i];
      Texture2D a = LoadTexture(full_path.c_str());
      assets.push_back(a);
    }
    count.mid = mid_asset.size();
  }
  else{;}
  if (fs::directory_iterator(fore) != fs::directory_iterator())
  {
    for (const auto &filename : fs::directory_iterator(fore))
    {
      std::cout << filename.path().filename();
      back_asset.push_back(filename.path().filename().string());
    }
  }
  else
    (exit(EXIT_FAILURE));
  if (!fore_asset.empty())
  {
    for (int i = 0; i < fore_asset.size(); i++)
    {
      std::string full_path = back + fore_asset[i];
      Texture2D a = LoadTexture(full_path.c_str());
      assets.push_back(a);
    }
    count.fore = fore_asset.size();
  }else{;}
  if (fs::directory_iterator(obj) != fs::directory_iterator())
  {
    for (const auto &filename : fs::directory_iterator(obj))
    {
      std::cout << filename.path().filename();
      back_asset.push_back(filename.path().filename().string());
    }
  }
  else
    (exit(EXIT_FAILURE));
  if (!back_asset.empty())
  {
    for (int i = 0; i < obj_asset.size(); i++)
    {
      std::string full_path = back + obj_asset[i];
      Texture2D a = LoadTexture(full_path.c_str());
      assets.push_back(a);
    }
    count.obj = obj_asset.size();
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

  Vector2 pos = {150, 525};

  Show show = {
      false,
      false,
      false,
  };

  InitWindow(1000, 650, "Editor");
  Texture2D folder = LoadTexture("folder.png");
  std::vector<Texture2D> assets = load_assets(count);

  while (!WindowShouldClose())
  {
    Window window = {
        .start_w = {0, 0},
        .end_w = {0, 480},
        .start_h = {0, 0},
        .end_h = {854, 0},
    };
    Grid grid = {
        {80, 0},
        {80, 480},
        {0, 80},
        {854, 80},
    };
    BeginDrawing();
    ClearBackground(WHITE);
    for (int i = 0; i < 2; i++)
    {
      DrawLineEx(window.start_w, window.end_w, 1.0, BLACK);
      DrawLineEx(window.start_h, window.end_h, 1.0, BLACK);
      window.start_h.y += 480;
      window.end_h.y += 480;
      window.start_w.x += 854;
      window.end_w.x += 854;
    }
    icons(folder, pos, &assets);
    revel(&show, &grid);
    clear(&show);
    EndDrawing();
  }
  UnloadTexture(folder);
  for (const auto x : assets){
    UnloadTexture(x);
  }
  CloseWindow();
}
