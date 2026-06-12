static void draw(void) {
    int x;
    int y;
    int i;
    char symbol;

    printf("\033[2J\033[H");

    y = 0;
    while (y < field_height) {
        x = 0;
        while (x < field_width) {
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
                i = 0;
                while (i < paddle_size && symbol == ' ') {
                    if (x == 1 && y == left_paddle_y + i) symbol = '#';
                    i++;
                }
                i = 0;
                while (i < paddle_size && symbol == ' ') {
                    if (x == field_width - 2 && y == right_paddle_y + i) symbol = '#';
                    i++;
                }
            }
            putchar(symbol);
            x++;
        }
        putchar('\n');
        y++;
    }
}