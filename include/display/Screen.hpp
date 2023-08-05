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
    DISPLAY_BLACK = 0x11111111,
    DISPLAY_DARK = 0x78787878,
    DISPLAY_LIGHT = 0xb4b4b4b4,
    DISPLAY_WHITE = 0xffffffff
};

class Screen
{
protected:
    int fbfd;
    unsigned char *fbp;
    size_t screensize = 0;

    unsigned int width;
    unsigned int height;
public:
    Screen();
    ~Screen();
};

#endif