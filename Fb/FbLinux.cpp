#include "FbLinux.hpp"

using namespace std;
using namespace se;

const string FbLinux::mFbPath = "/dev/fb0";
FbLinux::FbLinux(void)
{
    Init();
}
FbLinux::~FbLinux(void)
{
    CloseFb();
}

void FbLinux::Init(void)
{
    mFbfd = -2;
    memset(&mVInfo, 0, sizeof mVInfo);
    memset(&mFInfo, 0, sizeof mFInfo);
}

bool FbLinux::OpenFb(void)
{
    mFbfd = open(mFbPath, O_RDWR);
    return IsOpen();
}

bool FbLinux::IsOpen(void)
{
    return mFbfd > 0;
}

bool FbLinux::ReadFScreenInfo(void)
{
    assert(IsOpen());
    return ioctl(mFbfd, FBIOGET_FSCREENINFO, &mFInfo) >= 0;
}

bool FbLinux::ReadVScreenInfo(void)
{
    assert(IsOpen());
    return ioctl(mFbfd, FBIOGET_VSCREENINFO, &mVInfo) >= 0;
}

bool FbLinux::PutVScreenInfo(void)
{
    assert(IsOpen());
    return ioctl(mFbfd, FBOPUT_VSCREENINFO, &mVInfo) >= 0;
}

void FbLinux::CloseFb(void)
{
    if(mFbfd > 0)
    {
        close(mFbfd);
        mFbfd = -2;
    }
}

void FbLinux::PrintVirtualInfo(void) const
{
    cout << "=== Virtual Info ===" << endl;
    cout << "Resolution : " << mVInfo.xres << " x " << mVInfo.yres <<
        ", " << mVInfo.bits_per_pixel << "dpp" << endl;
    cout << "Virtual Resolution : " << mVInfo.xres_virtual << " x " <<
        mVInfo.yres_virtual << endl;
}

void FbLinux::PrintFixInfo(void) const
{
    cout << "=== Fixed Info ===" << endl;
    cout << "Length of frame buffer memory : " << mFInfo.smem_len << endl;
}

//

uint32_t Get32Color(const uint32_t & r,
    const uint32_t & g,
    const uint32_t & b,
    const uint32_t & a = 255) const
{
    return (uint32_t)((a << 24) | (r << 16) | (g << 8) | b);
}

uint16_t Get16Color(const uint16_t & 
    const uint16_t & g,
    const uint16_t & b) const
{
    return (uint16_t) ((r >> 3) << 11 | (g >> 2) << 5 | (b >>3) );
}