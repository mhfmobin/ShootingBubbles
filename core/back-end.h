
struct Ball {
    int color;
    bool is_falling;
    float x, y;
};

vector<vector<Ball>> data;
 

bool isGameOver() {
    int last_row = data.size() - 1;
    for (int i = 0; i < MAX_BALLS; i++)
        if (data[last_row][i].y >= BASE_Y)
            return true;
    return false;
}

