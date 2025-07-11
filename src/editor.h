#pragma once

#include <vector>
#include <string>
#include "../include/raylib.h"

#define VERTICAL_LINES 10
#define HORIZONTAL_LINES 6
#define SCREEN_DRAWING_AMOUNT 80
#define ICONS_TEXT_X 180
#define ICONS_TEXT_Y 590
#define ICONS_TEXT_SIZE 10
#define SCREEN_WIDTH 854
#define SCREEN_HEIGHT 480

enum Scene
{
  main,
  Back,
  Mid,
  Fore,
  Obj,
};

static Scene scene = main;

struct Show
{
  bool grid;
  bool coors;
  bool dots;
};

struct Grid
{
  Vector2 start_v;
  Vector2 end_v;
  Vector2 start_h;
  Vector2 end_h;
};

struct Count
{
  int back;
  int mid;
  int fore;
  int obj;
};

struct Position
{
  Vector2 icons;
  Vector2 contents;
};

struct Properties
{
  float size;
  bool hitbox;
  bool gravity;
  bool slected;
};

static std::vector<Properties> asset_properties;

void clear(Show *show);
void revel(Show *show, Grid *grid);
std::vector<Texture2D> load_assets(Count &count);
// void properties(Properties &prop);
void editor();
class State
{
private:
  Texture2D backgroud;
  std::vector<Texture2D> midground, foregroud;
  std::vector<Vector2> location, objects;

public:
  void save();
  void load();
};
