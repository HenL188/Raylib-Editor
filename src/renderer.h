#include "editor.h"

struct Renderer
{
    Count count;
    int asset;
    bool pickup;
    bool place;
    std::vector<Texture2D> layer1, layer2, layer3, layer4;
    std::vector<std::vector<Texture2D>> save;
    std::vector<Vector2> location;
    std::vector<std::pair<int, Vector2>> placedObjects;
    void render_assets(Position pos, std::vector<Texture2D> *assets);
    void icons(Texture2D folder, Position pos, Count count);
};