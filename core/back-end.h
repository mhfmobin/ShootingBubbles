
bool isGameOver();
bool isWinner();
void loadLevel(int level_id);


bool isGameOver() {
    int last_row = data.size() - 1;
    for (int i = 0; i < MAX_BALLS; i++)
        if (data[last_row][i].y >= BASE_Y)
            return true;
    return false;
}

bool isWinner() {
    return (data.size()) ? true : false;
}


void loadLevel(int level_id) {

}