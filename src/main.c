#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void output(int n, int m, int field[n][m]);
int top(int n, int m, int field_buffer[n][m], int i, int j);
int check_friends(int n, int m, int field[n][m], int i, int j);
void speed_change(int* p_speed);
void init_ncurses();
void fill_field(int n, int m, int (*field)[m]);

void fill_field(int n, int m, int (*field)[m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            scanf("%d", &x);
            field[i][j] = x;
        }
    }
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

int main() {
    int n = 25, m = 80, speed = 30000;
    int* p_speed = &speed;
    int field[n][m], field_buffer[n][m];
    fill_field(n, m, field);
    init_ncurses();
    while (*p_speed > 0) {
        usleep(*p_speed);
        clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                field_buffer[i][j] = field[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int friends = check_friends(n, m, field, i, j);
                if (friends != 2 && friends != 3) {
                    field_buffer[i][j] = 0;
                } else if (friends == 3) {
                    field_buffer[i][j] = 1;
                } else {
                    field_buffer[i][j] = field[i][j];
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                field[i][j] = field_buffer[i][j];
            }
        }
        output(n, m, field);
        speed_change(p_speed);
    }
    endwin();
}