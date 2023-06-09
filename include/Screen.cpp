#include "Screen.hpp"
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

Screen::Screen()
{
    fbfd = open("/dev/fb0", O_RDWR);
    
    if(fbfd == -1) {
        perror("Error: cannot open framebuffer device");
    }
    printf("The framebuffer device was opened successfully.\n");
    /* Get fixed screen information */
    struct fb_var_screeninfo finfo;
    struct fb_var_screeninfo vinfo;

    if(ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
    }

    /* Get variable screen information */
    if(ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
    }

    /* Figure out the size of the screen in bytes */
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    printf("Screen size is %ld\n", screensize);
    printf("Vinfo.bpp = %d\n", vinfo.bits_per_pixel);
    printf("Yres = %d\n", vinfo.yres);
    printf("Xres = %d\n", vinfo.xres);

    /* Map the device to memory */
    fbp = static_cast<unsigned char*>(
        mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0)
    );
    if(fbp == MAP_FAILED) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    width = screensize / vinfo.yres;
    height = screensize / vinfo.xres;
}

Screen::~Screen()
{
    munmap(fbp, screensize);
    close(fbfd);
}
