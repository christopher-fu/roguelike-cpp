#include "view.h"
#include "world.h"
#include <ncurses.h>
#include <algorithm>

View::View() {

}

View* View::respondToUserInput(int input) {
    return this;
}

void View::displayOutput(WINDOW* window) {

}

PlayView::PlayView(World w) {
    this->w = w;
    screenWidth = COLS - 10;
    screenHeight = LINES - 10;
    centerX = 0;
    centerY = 0;
}

int PlayView::getScrollX() {
    return std::max(0, std::min(centerX - screenWidth / 2,
                w.width - screenWidth));
}

int PlayView::getScrollY() {
    return std::max(0, std::min(centerY - screenHeight / 2,
                w.height - screenHeight));
}

void PlayView::scrollBy(int mx, int my) {
    centerX = std::max(0, std::min(centerX + mx, w.width - 1));
    centerY = std::max(0, std::min(centerY + my, w.height - 1));
}

void PlayView::displayTiles(WINDOW* window, int left, int top) {
    for(int x = 0; x < screenWidth; x++) {
        for(int y = 0; y < screenHeight; y++) {
            int wx = x + left;
            int wy = y + top;

            mvwprintw(window, y, x, "%c", w.glyphat(wx, wy));
        }
    }
}

void PlayView::displayOutput(WINDOW* window) {
    int left = getScrollX();
    int top = getScrollY();
    displayTiles(window, left, top);
    mvwprintw(window, centerY - getScrollY(), centerX - getScrollX(),
            "%c", 'X');
}

View* PlayView::respondToUserInput(int input) {
    switch(input) {
        case KEY_UP:
            scrollBy(0, -1);
            break;
        case KEY_DOWN:
            scrollBy(0, 1);
            break;
        case KEY_LEFT:
            scrollBy(-1, 0);
            break;
        case KEY_RIGHT:
            scrollBy(1, 0);
            break;
    }
    return this;
}
