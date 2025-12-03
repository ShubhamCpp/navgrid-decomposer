#pragma once
#include <vector>
#include <cstdint>
#include "grid.h"
#include "greedy_rect.h"
#include "raylib.h"

// Splits the full grid into tile_size x tile_size blocks and runs greedy rect cover per tile.
// Returns rectangles in grid coordinates.
// tile_size must be >= 1.
std::vector<Rect2D> TiledGreedyRectCover(const Grid2D& grid, int tile_size, uint8_t max_rect_size);

// Draw tile boundaries
void DrawTileGrid(Vector2 origin, int grid_w, int grid_h, int tile_size, int cell_size, Color color);
