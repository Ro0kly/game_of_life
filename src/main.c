#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int check_friends(int n, int m, int field[n][m], int i, int j) {
    int friends = 0;
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            int friend_i = i + y == n ? 0 : i + y < 0 ? n - 1 : i + y;
            int friend_j = j + x == m ? 0 : j + x < 0 ? m - 1 : j + x;
            if ((friend_i != i || friend_j != j) && (field[friend_i][friend_j] == 1)) {
                friends += 1;
            }
        }
    }
    return friends;
}

void init_ncurses() {
    if (freopen("/dev/tty", "r", stdin) != NULL) {
        initscr();
        timeout(1);
        keypad(stdscr, TRUE);
        noecho();
        nodelay(stdscr, TRUE);
    }
}

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