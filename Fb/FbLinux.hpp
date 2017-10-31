// SolidEng.co. Han T.K. since 2017.10.31
//
#ifndef __SE__FBLINUX_HPP__
#define __SE__FBLINUX_HPP__

#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>

#include "Singleton.hpp"

namespace se
{
    class FbLinux
    {
    private:
        static const std::string mFbPath;
        int mFbfd;
    protected:
        struct fb_var_screeninfo mVInfo;
        struct fb_fix_screeninfo mFInfo;
    public:
        FbLinux(void);
        ~FbLinux(void);
        void Init(void);
        bool OpenFb(void);
        bool IsOpen(void);
        bool ReadFScreenInfo(void);
        bool ReadVScreenInfo(void);
        bool PutVScreenInfo(void);
        void CloseFb(void);
        void PrintVirtualInfo(void) const;
        void PrintFixInfo(void) const;
        // Color
        uint32_t Get32Color(const uint32_t & r,
            const uint32_t & g,
            const uint32_t & b,
            const uint32_t & a = 255) const;
        uint16_t Get16Color(const uint16_t & r,
            const uint16_t & g,
            const uint16_t & b) const;

    };

}

#endif // __SE__FBLINUX_HPP__
