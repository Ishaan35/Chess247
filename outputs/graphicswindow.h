#ifndef GRAPHICSWINDOW_H
#define GRAPHICSWINDOW_H

#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>
#include <iostream>
#include <stdexcept>

class GraphicsWindow
{
private:
    Display *display;
    Window window;
    cairo_surface_t *surface;
    int width, height;

public:
    GraphicsWindow(int w, int h);

    ~GraphicsWindow();

    void renderPNG(const std::string &filename, int target_width, int target_height, int x, int y);
    void drawRectangle(int x, int y, int rect_width, int rect_height, int red, int green, int blue);

    void drawText(const std::string &text, int x, int y, double font_size, int red, int green, int blue);

    // send out the pending tasks for rendering
    void flush();

    // POTENTIAL SPECIAL FEATURE: User can click on a piece to highlight squares that piece can move to!!!
    void handleEvents();
};

#endif