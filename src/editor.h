#pragma once

#include <vector>
#include <string>
#include "../include/raylib.h"

enum Scene {
  main,
  Back,
  Mid,
  Fore,
  Obj,
};

static Scene scene = main;

struct Show {
  bool grid;
  bool coors;
  bool dots;
};

struct Grid {
  Vector2 start_v;
  Vector2 end_v;
  Vector2 start_h;
  Vector2 end_h;
};

struct Count {
  int back;
  int mid;
  int fore;
  int obj;
};

struct Position{
  Vector2 icons;
  Vector2 contents;
};

struct Render {
 bool back;
 bool mid;
 bool fore;
 bool obj;
};

void clear(Show *show);
void revel(Show *show, Grid *grid);
void icons(Texture2D folder, Position pos, Count count, Render& render);
void render_assets(Position pos, std::vector<Texture2D> *assets, Count& count, int& asset, bool& pickup, bool& place);
std::vector<Texture2D> load_assets(Count& count);
void editor();
class State {
private:
 Texture2D backgroud;
 std::vector<Texture2D> midground, foregroud;
 std::vector<Vector2> location, objects;
public:
  void save();
  void load();    
};
