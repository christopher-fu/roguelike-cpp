#include <iostream>
#include "world.h"
#include "view.h"

using std::cout;
using std::endl;

int main() {
    WorldBuilder wb;
    World w = wb.build();

    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            cout << w.glyphat(i, j) << " ";
        }
        cout << endl;
    }

    cout << screenHeight << endl << screenWidth << endl;
    cout << centerX << endl;
    // cout << getScrollX(w) << endl << getScrollY(w) << endl;

    return 0;
}
