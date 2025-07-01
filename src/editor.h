#pragma once

#include <vector>
#include "../include/raylib.h"

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

void clear(Show *show);
void revel(Show *show, Grid *grid);
void icons(Texture2D folder, Vector2 pos);
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
