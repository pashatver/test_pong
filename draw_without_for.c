void draw(void) {
    int x;
    int y;
    char symbol;

    y = 0;
    while (y < field_heigth) {
        x = 0;
        while (x < field_weidth) {
            symbol = ' '; 

            // 1. Верхняя и нижняя границы (Рамка + Счет)
            if (y == 0 || y == field_heigth - 1) {
                if (y == 0 && x == field_weidth / 2 - 5) { 
                    symbol = '0' + player1_score / 10;
                } else if (y == 0 && x == field_weidth / 2 - 4) {
                    symbol = '0' + player1_score % 10; 
                } else if (y == 0 && x == field_weidth / 2 - 3) {
                    symbol = ':';
                } else if (y == 0 && x == field_weidth / 2 - 2) {
                    symbol = '0' + player2_score / 10;
                } else if (y == 0 && x == field_weidth / 2 - 1) {
                    symbol = '0' + player2_score % 10;
                } else {
                    symbol = '-';
                }
            } 
            // 2. Левая и правая границы рамки
            else if (x == 0 || x == field_weidth - 1) {
                symbol = '|';                
            } 
            // 3. Мяч
            else if (x == ball_x && y == ball_y) {
                symbol = 'O';
            } 
            // 4. Ракетки (без циклов и без break)
            else {
                // Левая ракетка: проверяем, лежит ли y между left_paddle_y и left_paddle_y + paddle_size
                if (x == 1 && y >= left_paddle_y && y < left_paddle_y + paddle_size) { 
                    symbol = '#'; 
                }
                // Правая ракетка: проверяем аналогичный диапазон по высоте
                else if (x == field_weidth - 2 && y >= right_paddle_y && y < right_paddle_y + paddle_size) { 
                    symbol = '#'; 
                }
            }

            putchar(symbol);
            x++; 
        }
        putchar('\n');
        y++; 
    }
}
