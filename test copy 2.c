#include <stdio.h>

int field_width;
int field_height;
int paddle_size;
int win_score;
int ball_x;
int ball_y;
int ball_dir_x;
int ball_dir_y;
int left_paddle_y;
int right_paddle_y;
int player1_score;
int player2_score;
int is_running;

static void game_start(void) {
    field_width = 80;
    field_height = 25;
    paddle_size = 3;
    win_score = 21;

    ball_x = field_width / 2;
    ball_y = field_height / 2;
    ball_dir_x = 1;
    ball_dir_y = 1;
    left_paddle_y = field_height / 2 - 1;
    right_paddle_y = field_height / 2 - 1;
    player1_score = 0;
    player2_score = 0;
    is_running = 1;
}

static void left_paddle_move(int dir) {
    left_paddle_y = left_paddle_y + dir;
    if (left_paddle_y < 1) left_paddle_y = 1;
    if (left_paddle_y + paddle_size - 1 > field_height - 2)
        left_paddle_y = field_height - 2 - paddle_size + 1;
}

static void right_paddle_move(int dir) {
    right_paddle_y = right_paddle_y + dir;
    if (right_paddle_y < 1) right_paddle_y = 1;
    if (right_paddle_y + paddle_size - 1 > field_height - 2)
        right_paddle_y = field_height - 2 - paddle_size + 1;
}

static int paddle_touch(int by, int py) {
    if (by >= py && by < py + paddle_size) {
        return 1;
    } else
        return 0;
}

static void reset_ball(int dx) {
    ball_x = field_width / 2;
    ball_y = field_height / 2;
    ball_dir_x = dx;
    ball_dir_y = 1;
}

static void game_step(void) {
    ball_x = ball_x + ball_dir_x;
    ball_y = ball_y + ball_dir_y;

    if (ball_y <= 1 || ball_y >= field_height - 2) ball_dir_y = -ball_dir_y;

    if (ball_x == 2) {
        if (paddle_touch(ball_y, left_paddle_y)) {
            ball_dir_x = 1;
        } else {
            player2_score++;
            if (player2_score >= win_score) {
                is_running = 0;
                return;
            }
            reset_ball(1);
        }
    }

    if (ball_x == field_width - 3) {
        if (paddle_touch(ball_y, right_paddle_y)) {
            ball_dir_x = -1;
        } else {
            player1_score++;
            if (player1_score >= win_score) {
                is_running = 0;
                return;
            }
            reset_ball(-1);
        }
    }
}

static void draw(void) {
    int x;
    int y;
    int i;
    char symbol;

    printf("\033[2J\033[H");

    for (y = 0; y < field_height; y++) {
        for (x = 0; x < field_width; x++) {
            symbol = ' ';
            if (y == 0 || y == field_height - 1) {
                if (y == 0 && x == field_width / 2 - 5) {
                    symbol = '0' + player1_score / 10;
                } else if (y == 0 && x == field_width / 2 - 4) {
                    symbol = '0' + player1_score % 10;
                } else if (y == 0 && x == field_width / 2 - 3) {
                    symbol = ':';
                } else if (y == 0 && x == field_width / 2 - 2) {
                    symbol = '0' + player2_score / 10;
                } else if (y == 0 && x == field_width / 2 - 1) {
                    symbol = '0' + player2_score % 10;
                } else {
                    symbol = '-';
                }
            } else if (x == 0 || x == field_width - 1) {
                symbol = '|';
            } else if (x == ball_x && y == ball_y) {
                symbol = 'O';
            } else {
                for (i = 0; i < paddle_size; i++) {
                    if (x == 1 && y == left_paddle_y + i) {
                        symbol = '#';
                        break;
                    }
                }
                if (symbol == ' ') {
                    for (i = 0; i < paddle_size; i++) {
                        if (x == field_width - 2 && y == right_paddle_y + i) {
                            symbol = '#';
                            break;
                        }
                    }
                }
            }
            putchar(symbol);
        }
        putchar('\n');
    }
}

int main(void) {
    int tmp;
    int key;

    game_start();
    draw();

    while (is_running) {
        printf("Ход (A/Z - ракетка 1, K/M - ракетка 2, Space - пропуск): ");

        key = getchar();

        if (key != '\n' && key != '\r') {
            while ((tmp = getchar()) != '\n' && tmp != EOF) {
            }

            if (key == 'A' || key == 'a') {
                left_paddle_move(-1);
                game_step();
                draw();
            } else if (key == 'Z' || key == 'z') {
                left_paddle_move(+1);
                game_step();
                draw();
            } else if (key == 'K' || key == 'k') {
                right_paddle_move(-1);
                game_step();
                draw();
            } else if (key == 'M' || key == 'm') {
                right_paddle_move(+1);
                game_step();
                draw();
            } else if (key == ' ') {
                game_step();
                draw();
            } else {
                printf("Неверный ввод. Используйте A/Z, K/M или Space.\n");
            }
        }
    }

    if (player1_score >= win_score)
        printf("\n*** Поздравляем! Победил Игрок 1 со счётом %d:%d! ***\n", player1_score, player2_score);
    else
        printf("\n*** Поздравляем! Победил Игрок 2 со счётом %d:%d! ***\n", player1_score, player2_score);

    return 0;
}