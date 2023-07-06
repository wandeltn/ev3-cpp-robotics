#include <linux/fb.h>
#include <sys/mman.h>
#include <stdint.h>


#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }
#endif

enum DisplayColors {
    DISPLAY_BLACK = 0x00,
    DISPLAY_DARK = 0x78,
    DISPLAY_LIGHT = 0xb4,
    DISPLAY_WHITE = 0xff
};

class Screen
{
protected:
    int fbfd;
    unsigned char *fbp;
    size_t screensize = 0;

    uint_fast8_t width;
    uint_fast8_t height;
public:
    Screen();
    ~Screen();
};

#endif