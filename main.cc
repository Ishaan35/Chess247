#include <iostream>
#include <stdexcept>
#include "./outputs/graphicswindow.h"
#include "application.h"

void doStuff()
{
    GraphicsWindow win1(600, 600);

    // Assuming chesspiece.png is in the current directory
    win1.renderPNG("assets/chesspiece.png", 50, 50, 0, 0);

    // Draw rectangles and text
    win1.drawRectangle(100, 100, 50, 50, 186, 104, 37);
    win1.drawRectangle(200, 100, 50, 50, 186, 104, 37);
    win1.drawRectangle(300, 100, 50, 50, 186, 104, 37);
    win1.drawRectangle(50, 150, 50, 50, 186, 104, 37);
    win1.drawRectangle(150, 150, 50, 50, 186, 104, 37);
    win1.drawRectangle(250, 150, 50, 50, 186, 104, 37);
    win1.drawRectangle(350, 150, 50, 50, 186, 104, 37);
    win1.drawText("Guess the elo", 50, 50, 20.0, 0, 0, 0);

    // Handle events (including mouse clicks)
    win1.handleEvents();

    // Control reaches here after handling events
    std::cout << "Exiting..." << std::endl;
}

int main()
{
    Application mainApp;
    mainApp.run();
    return 0;
}
