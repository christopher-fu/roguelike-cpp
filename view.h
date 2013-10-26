#ifndef VIEW_H
#define VIEW_H

#include "world.h"
#include <ncurses.h>

class View {
    public:
        virtual void displayOutput(WINDOW* window);
        virtual View* respondToUserInput(int input);
        View();
};

class PlayView : public View {
    public:
        PlayView(World w);

        int screenWidth;
        int screenHeight;
        int centerX;
        int centerY;
        World w;

        int getScrollX();
        int getScrollY();
        void scrollBy(int mx, int my);
        void displayTiles(WINDOW* window, int left, int top);
        void displayOutput(WINDOW* window);
        View* respondToUserInput(int input);
};

#endif
