#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void fill_field(int n, int m, int (*field)[m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            scanf("%d", &x);
            field[i][j] = x;
        }
    }
}

void output(int n, int m, int field[n][m]) {
    printw("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printw("%d", field[i][j]);
        }
        printw("\n");
    }
}

void speed_change(int* p_speed) {
    int key = getch();
    if (key == 'w' && (*p_speed - 2500 > 0)) {
        *p_speed -= 2500;
        printw("SPEED+");
    }
    if (key == 's') {
        *p_speed += 2500;
        printw("SPEED-");
    }
    if (key == 'q') *p_speed = 0;
    refresh();
}