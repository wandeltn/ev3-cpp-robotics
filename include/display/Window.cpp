#include "Window.hpp"
#include <unistd.h>
#include <iostream>


Window::Window(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, bool border)
{
    startX = x0;
    startY = y0;
    width = x1 - x0;
    height = y1 - y0;
    bits_per_pixel = 32;
    _screensize = width * height;
    for (size_t i = 1; i <= _screensize; i++) {
        frameBuffer.push_back(DISPLAY_WHITE);
    }
    if (border) {
        drawRect(x0 +1, y0 +1, x1 -1, y1 -1, DISPLAY_BLACK);
    }
}

Window::~Window()
{
    frameBuffer.clear();
}

std::vector<uint32_t>& Window::getFBP()
{
    return frameBuffer;
}

uint_fast8_t Window::getScreensize()
{
    return _screensize;
}

DisplayColors Window::getPixel(uint_fast8_t x0, uint_fast8_t y0)
{
    return static_cast<DisplayColors>(frameBuffer[y0 * width + x0]);
}

void Window::clearScreen()
{
    Window::fillScreen(DISPLAY_WHITE);
}

void Window::fillScreen(DisplayColors color)
{
    for (size_t index = 0; index <= frameBuffer.size(); index++) {
        frameBuffer[index] = color;
    }
}

void Window::drawPixel(uint_fast8_t xpos, uint_fast8_t ypos, DisplayColors color)
{
    for (int pixelIndex = 0; pixelIndex <= 4; pixelIndex++) {
        // frameBuffer[ypos * width + (xpos + pixelIndex)] = color;
    }
    // frameBuffer[ypos * width + (xpos)] = color;
    frameBuffer[0] = DISPLAY_BLACK;
    frameBuffer.back() = DISPLAY_BLACK;
    std::cout << frameBuffer.size();
}

void Window::drawPixel(Vector pos, DisplayColors color)
{
    drawPixel(pos.x, pos.y, color);
}


void Window::drawHLine(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, DisplayColors color)
{
    if (x0 != x1) {
        perror("Error while checking for horizontality");
        return;
    }
    for (int posy = y0; posy <= y1; posy++){
        drawPixel(x0, posy, color);
    }
}

void Window::drawHLine(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t length, DisplayColors color)
{
    drawHLine(x0, y0, x0, y0 + length, color);
}

void Window::drawVLine(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, DisplayColors color)
{
    if (y0 != y1) {
        perror("Error while checking for verticality");
        return;
    }
    for (int posx = x0; posx <= x1; posx++){
        drawPixel(posx, y0, color);
    }
}

void Window::drawVLine(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t length, DisplayColors color)
{
    drawVLine(x0, y0, x0 + length, y0, color);
}

void Window::drawLine(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, DisplayColors color)
{
    if (x0 == x1) {
        if (y0 > y1)
            _swap_int16_t(y0, y1);
        drawVLine(x0, y0, y1 - y0 + 1, color);
    } else if (y0 == y1) {
        if (x0 > x1)
            _swap_int16_t(x0, x1);
        drawHLine(x0, y0, x1 - x0 + 1, color);
    } else {
        int16_t steep = abs(y1 - y0) > abs(x1 - x0);
        if (steep) {
            _swap_int16_t(x0, y0);
            _swap_int16_t(x1, y1);
        }

        if (x0 > x1) {
            _swap_int16_t(x0, x1);
            _swap_int16_t(y0, y1);
        }

        int16_t dx, dy;
        dx = x1 - x0;
        dy = abs(y1 - y0);

        int16_t err = dx / 2;
        int16_t ystep;

        if (y0 < y1) {
            ystep = 1;
        } else {
            ystep = -1;
        }

        for (; x0 <= x1; x0++) {
            if (steep) {
                drawPixel(y0, x0, color);
            } else {
                drawPixel(x0, y0, color);
            }
            err -= dy;
            if (err < 0) {
                y0 += ystep;
                err += dx;
            }
        }
    }
}

void Window::drawLine(Vector start, Vector end, DisplayColors color)
{
    drawLine(start.x, start.y, end.x, end.y, color);
}

void Window::drawCircle(uint_fast8_t x0, uint_fast8_t y0, uint_fast16_t r, DisplayColors color) {
int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0, y0 + r, color);
  drawPixel(x0, y0 - r, color);
  drawPixel(x0 + r, y0, color);
  drawPixel(x0 - r, y0, color);

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

void Window::drawRect(uint_fast8_t x0, uint_fast8_t y0, uint_fast8_t x1, uint_fast8_t y1, DisplayColors color)
{
    drawLine(x0, y0, x0, y1, color); //left vertical
    drawLine(x1, y1, x1, y0, color); //right vertical
    drawLine(x0, y0, x1, y0, color); //upper horitontal
    drawLine(x1, y1, x0, y1, color); //lower horizontal
}

