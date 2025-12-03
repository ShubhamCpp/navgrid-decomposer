#include "greedy_rect.h"
#include <algorithm>

std::vector<Rect2D> GreedyRectCover(const Grid2D& grid, uint8_t max_size)
{
    const int W = grid.Width();
    const int H = grid.Height();

    std::vector<Rect2D> rects;
    Grid2D visited(W, H); // visited set
    visited.Clear(0);

    auto IsOn = [&](int x, int y) -> bool { return grid.Get(x, y) != 0; };
    auto IsUsed = [&](int x, int y) -> bool { return visited.Get(x, y) != 0; };

    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            if (!IsOn(x, y) || IsUsed(x, y)) continue;

            // Grow width
            int w = 0;
            while (x + w < W && w < (int)max_size && IsOn(x + w, y) && !IsUsed(x + w, y))
                w++;

            // Grow height until valid
            int h = 1;
            while (y + h < H && h < (int)max_size)
            {
                bool ok = true;
                for (int k = 0; k < w; ++k)
                {
                    if (!IsOn(x + k, y + h) || IsUsed(x + k, y + h))
                    {
                        ok = false;
                        break;
                    }
                }
                if (!ok) break;
                h++;
            }

            // Mark cells visited
            for (int yy = y; yy < y + h; ++yy)
                for (int xx = x; xx < x + w; ++xx)
                    visited.Set(xx, yy, 1);

            // Add rectangle to set
            rects.emplace_back(x, x + w, y, y + h);
        }
    }

    return rects;
}
