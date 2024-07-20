#include "graphicswindow.h"

GraphicsWindow::GraphicsWindow(int w, int h) : width(w), height(h){
    display = XOpenDisplay(nullptr);
    if (!display)
    {
        throw std::runtime_error("Failed to open X display");
    }

    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, width, height, 0, 0, 0);
    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);
    XMapWindow(display, window);

    surface = cairo_xlib_surface_create(display, window, DefaultVisual(display, screen), width, height);
    if (cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS)
    {
        XDestroyWindow(display, window);
        XCloseDisplay(display);
        throw std::runtime_error("Failed to create Cairo Xlib surface");
    }
}

GraphicsWindow::~GraphicsWindow()
{
    cairo_surface_destroy(surface);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

void GraphicsWindow::renderPNG(const std::string &filename, int target_width, int target_height)
{
    cairo_t *cr = cairo_create(surface);

    // Clear the surface with a background color (e.g., white)
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); // White color
    cairo_paint(cr);

    // Render PNG file
    cairo_surface_t *image = cairo_image_surface_create_from_png(filename.c_str());
    if (cairo_surface_status(image) != CAIRO_STATUS_SUCCESS)
    {
        cairo_destroy(cr);
        throw std::runtime_error("Failed to load PNG file");
    }

    // Get original image dimensions
    int img_width = cairo_image_surface_get_width(image);
    int img_height = cairo_image_surface_get_height(image);

    // Calculate scaling factors
    double scale_x = static_cast<double>(target_width) / img_width;
    double scale_y = static_cast<double>(target_height) / img_height;

    // Scale image if necessary
    cairo_scale(cr, scale_x, scale_y);

    // Paint the scaled image onto the surface
    cairo_set_source_surface(cr, image, 0, 0);
    cairo_paint(cr);

    // Clean up
    cairo_surface_destroy(image);
    cairo_destroy(cr);

    // Flush to ensure everything is rendered
    flush();
}

void GraphicsWindow::drawRectangle(int x, int y, int rect_width, int rect_height, int red, int green, int blue)
{
    cairo_t *cr = cairo_create(surface);

    // Convert color values from 0-255 to 0.0-1.0
    double cairo_red = static_cast<double>(red) / 255.0;
    double cairo_green = static_cast<double>(green) / 255.0;
    double cairo_blue = static_cast<double>(blue) / 255.0;

    // Set rectangle color
    cairo_set_source_rgb(cr, cairo_red, cairo_green, cairo_blue);

    // Draw rectangle
    cairo_rectangle(cr, x, y, rect_width, rect_height);
    cairo_fill(cr);

    cairo_destroy(cr);

    // Flush to ensure rectangle is rendered
    flush();
}

void GraphicsWindow::drawText(const std::string &text, int x, int y, double font_size, int red, int green, int blue)
{
    cairo_t *cr = cairo_create(surface);

    // Convert color values from 0-255 to 0.0-1.0
    double cairo_red = static_cast<double>(red) / 255.0;
    double cairo_green = static_cast<double>(green) / 255.0;
    double cairo_blue = static_cast<double>(blue) / 255.0;

    // Set font options
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, font_size);

    // Set text color
    cairo_set_source_rgb(cr, cairo_red, cairo_green, cairo_blue);

    // Draw text
    cairo_move_to(cr, x, y);
    cairo_show_text(cr, text.c_str());

    cairo_destroy(cr);

    // Flush to ensure text is rendered
    flush();
}

void GraphicsWindow::flush()
{
    cairo_surface_flush(surface);
    XFlush(display);
}

void GraphicsWindow::handleEvents()
{
    XEvent event;
    while (true)
    {
        XNextEvent(display, &event);
        switch (event.type)
        {
        case Expose:
            // Handle expose events if needed
            break;
        case KeyPress:
            // Handle key press events if needed
            break;
        case ButtonPress:
            // Handle mouse button press events
            if (event.xbutton.button == Button1)
            { // Button1 is left mouse button
                int mouseX = event.xbutton.x;
                int mouseY = event.xbutton.y;
                std::cout << "Left mouse button clicked at: (" << mouseX << ", " << mouseY << ")" << std::endl;
                // Example: Check if click is within a rectangle
                if (mouseX >= 100 && mouseX <= 150 && mouseY >= 100 && mouseY <= 150)
                {
                    std::cout << "Clicked inside the brown rectangle!" << std::endl;
                }
            }
            break;
            // Add cases for other event types as needed
        }
    }
}