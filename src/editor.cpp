#include "editor.h"
#include "renderer.h"
#include "../include/raylib.h"
#include <iostream>
#include <filesystem>
#include <vector>

#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

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

void properties(Properties &prop)
{
  DrawText("Properties", 870, 50, 10, BLACK);
  GuiCheckBox({870, 75, 20, 20}, "HitBox", &prop.hitbox);
  GuiCheckBox({870, 100, 20, 20}, "Gravtiy", &prop.gravity);
  for (auto &asset : asset_properties)
  {
    if (asset.selected)
    {
      prop.hitbox_checked = prop.hitbox;
      prop.gravity_checked = prop.gravity;
    }
  }
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

  InitWindow(1000, 650, "Editor");
  Texture2D folder = LoadTexture("folder.png");
  std::vector<Texture2D> assets = load_assets(count);
  Renderer ren = {
      .count = count,
      .asset = -1,
      .pickup = false,
      .place = false,
      .clicked = false,
  };

  Properties prop = {
      .size = 1.0f,
      .hitbox = false,
      .gravity = false,
      .selected = false,
      .hitbox_checked = false,
      .gravity_checked = false,
  };

  while (!WindowShouldClose())
  {
    Window window = {
        .start_w = {0, 0},
        .end_w = {0, SCREEN_HEIGHT},
        .start_h = {0, 0},
        .end_h = {SCREEN_WIDTH, 0},
    };
    Grid grid = {
        {SCREEN_DRAWING_AMOUNT, 0},
        {SCREEN_DRAWING_AMOUNT, SCREEN_HEIGHT},
        {0, SCREEN_DRAWING_AMOUNT},
        {SCREEN_WIDTH, SCREEN_DRAWING_AMOUNT},
    };
    BeginDrawing();
    ClearBackground(WHITE);
    for (int i = 0; i < 2; i++)
    {
      DrawLineEx(window.start_w, window.end_w, 1.0, BLACK);
      DrawLineEx(window.start_h, window.end_h, 1.0, BLACK);
      window.start_h.y += SCREEN_HEIGHT;
      window.end_h.y += SCREEN_HEIGHT;
      window.start_w.x += SCREEN_WIDTH;
      window.end_w.x += SCREEN_WIDTH;
    }
    revel(&show, &grid);
    clear(&show);
    ren.icons(folder, pos, count);
    ren.render_assets(pos, &assets, prop);
    // properties(prop);
    EndDrawing();
    // for (auto &i : asset_properties)
    // {
    //   std::cout << i.gravity_checked << std::endl;
    // }
  }
  UnloadTexture(folder);
  for (const auto x : assets)
  {
    UnloadTexture(x);
  }
  CloseWindow();
}
