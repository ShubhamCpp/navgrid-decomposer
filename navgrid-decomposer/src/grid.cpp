#include "grid.h"
#include "raylib.h"
#include <algorithm>

void Grid2D::Clear(uint8_t value)
{
    std::fill(cells.begin(), cells.end(), value);
}

void Grid2D::Reset()
{
    cells.clear();
}

void Grid2D::FillRandom(int on_percent, uint32_t seed)
{
    if (cells.empty()) return;

    on_percent = std::clamp(on_percent, 0, 100);

    SetRandomSeed((int)seed);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            const int r = GetRandomValue(0, 99);
            cells[(size_t)Index(x, y)] = (r < on_percent) ? 1 : 0;
        }
    }
}
