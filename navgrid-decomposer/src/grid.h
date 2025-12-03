#pragma once
#include <cstdint>
#include <vector>

class Grid2D
{
public:
    Grid2D() = default;

    Grid2D(int in_width, int in_height)
    {
        Resize(in_width, in_height);
    }

    void Resize(int in_width, int in_height)
    {
        width = in_width;
        height = in_height;
        cells.assign((size_t)width * (size_t)height, 0);
    }

    void Clear(uint8_t value = 0);

    inline bool InBounds(int x, int y) const { return (x >= 0 && x < width && y >= 0 && y < height); }
    inline int  Index(int x, int y) const { return y * width + x; }

    inline uint8_t Get(int x, int y) const { return cells[(size_t)Index(x, y)]; }
    inline void Set(int x, int y, uint8_t v) { cells[(size_t)Index(x, y)] = v; }
    inline void Toggle(int x, int y) { cells[(size_t)Index(x, y)] ^= 1; }

    void FillRandom(int on_percent, uint32_t seed);

    int Width() const { return width; }
    int Height() const { return height; }
    const std::vector<uint8_t>& Data() const { return cells; }

private:
    void Reset();

    int width = 0;
    int height = 0;
    std::vector<uint8_t> cells;
};
