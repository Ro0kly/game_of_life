#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void output(int n, int m, int field[n][m]) {
    printw("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printw("%d", field[i][j]);
        }
        printw("\n");
    }
}