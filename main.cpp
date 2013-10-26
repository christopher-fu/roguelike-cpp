#include <ncurses.h>
#include <iostream>
#include "view.h"
#include "world.h"

void print_menu(WINDOW *menu_win, int highlight, int n_choices,
        const char** choices) {
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices; ++i) {
        if(highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
        ++y;
    }
    wrefresh(menu_win);
}

WINDOW* create_newwin(int height, int width, int starty, int startx) {
    WINDOW* local_win;

    local_win = newwin(height, width, starty, startx);
    wrefresh(local_win);
    return local_win;
}

void init() {
    clear();
    refresh();
    WorldBuilder wb;
    World w = wb.build();
    PlayView playView(w);
    View* v = &playView;
    WINDOW* window = create_newwin(playView.screenHeight + 3,
            playView.screenWidth + 3, 0, 0);
    keypad(window, TRUE);
    playView.displayOutput(window);
    wrefresh(window);
    int input = 0;
    while(input != 113) {
        input = wgetch(window);
        v->respondToUserInput(input);
        v->displayOutput(window);
    }
}

void printTest() {
    int c;
    int flag = 1;
    printw("You are having fun.\n");
    printw("-- press [ESC] to lose or [ENTER] to win--\n");
    while(flag != 0) {
        c = getch();
        refresh();
        switch(c) {
            case 27:
                printw("You lose!");
                flag = 0;
                refresh();
                break;
            case 10:
                printw("You win!");
                flag = 0;
                refresh();
                break;
        }
    }
}

int main() {
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;
    int startx = 0;
    int starty = 0;

    const char* choices[] = {
        "New Game", "Quit"
    };

    int n_choices = sizeof(choices) / sizeof(char*);

    const int WIDTH = 20;
    const int HEIGHT = n_choices + 4;

    initscr();
    clear();
    noecho();
    cbreak();
    // keypad(stdscr, TRUE);
    curs_set(0);
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;

    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(0, 0,
            "Use arrow keys to go up and down. Press enter to select a choice");
    refresh();
    print_menu(menu_win, highlight, n_choices, choices);
    while(1) {
        c = wgetch(menu_win);
        switch(c) {
            case KEY_UP:
                if(highlight == 1) {
                    highlight = n_choices;
                }
                else {
                    --highlight;
                }
                break;
            case KEY_DOWN:
                if(highlight == n_choices) {
                    highlight = 1;
                }
                else {
                    ++highlight;
                }
                break;
            case 10:
                choice = highlight;
                break;
        }
        print_menu(menu_win, highlight, n_choices, choices);
        /* entry */
        if(choice == 1) {
            init();
            break;
        }
        else if(choice == 2) {
            break;
        }
    }
    clrtoeol();
    endwin();
    return 0;
}
