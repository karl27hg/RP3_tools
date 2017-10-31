#include "CheeseBoard.hpp"
#include <cassert>

using namespace std;
using namespace se;

void CheeseBoard::Draw32CheeseBoard(const int & boxSize)
{
    assert(IsOpen());
    assert(32 == mVInfo.bits_per_pixel);
    int rows = mVInfo.yres;
    int cols = mVInfo.xres;
    auto pfb = (uint32_t *)mmap(0,
        rows * cols * 4,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mFbfd,
        0);
    auto green = Get32Color(0, 255, 0);
    auto black = Get32Color(0, 0, 0);
    for(int r = 0; r < rows; ++r)
    {
        auto fb_ptr = pfb + r*cols;
        bool isFaceRow = (r / boxSize % 2) == 0;
        for(int c = 0; c < cols; ++c)
        {
            bool isFaceCol = (c / boxSize % 2) == 1;
            fb_ptr[c] = (isFaceRow ^ isFaceCol) ? green : black;
        }
    }
    munmap(pfd, rows * cols * 4);
}

void CheeseBoard::Draw16CheeseBoard(const int & boxSize)
{
    assert(IsOpen());
    assert(16 == mVInfo.bits_per_pixel);
    int rows = mVInfo.yres;
    int cols = mVInfo.xres;
    auto pfb = (uint16_t *)mmap(0,
        rows * cols * 2,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mFbfd,
        0);
    auto green = Get32Color(0, 255, 0);
    auto black = Get32Color(0, 0, 0);
    for(int r = 0; r < rows; ++r)
    {
        auto fb_ptr = pfb + r * cols;
        bool isFaceRow = (r / boxSize % 2) == 0;
        for(int c = 0; c < cols; ++c)
        {
            bool isFaceCol = (c / boxSize % 2) == 1;
            fb_ptr[c] = (isFaceRow ^ isFaceCol)? green : black;
        }
    }
}