#pragma once
#include <vector>
#include <cstdint>
#include "grid.h"

// Rectangle: [x0,x1) x [y0,y1)
class Rect2D
{
public:
    Rect2D(int in_x0, int in_x1, int in_y0, int in_y1)
        : x0(in_x0), x1(in_x1), y0(in_y0), y1(in_y1)
    {
    };

    inline int W() const { return x1 - x0; }
    inline int H() const { return y1 - y0; }
    inline int Area() const { return W() * H(); }

    inline int GetX0() const { return x0; }
    inline int GetY0() const { return y0; }
    inline int GetX1() const { return x1; }
    inline int GetY1() const { return y1; }

private:
    int x0 = 0, y0 = 0;
    int x1 = 0, y1 = 0;
};

// Returns a set of non-overlapping rectangles that cover all 1 (filled) cells in grid.
// In: grid - input grid in 2D
// In: max_size - max size of rectangle in 2D
// Out: set of non-overlapping greedy rectangles in 2D
std::vector<Rect2D> GreedyRectCover(const Grid2D& grid, uint8_t max_size);
