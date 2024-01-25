
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
    string filename = "level-" + to_string(level_id) + ".csv"; 

    ifstream file(filename);

    if (!file.good()) {
        cerr << "Error opening the file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<Ball> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            int color = stoi(cell);
            Ball ball;
            ball.color = color;
            ball.x = 0;
            ball.y = 0;

            row.push_back(ball);
        }

        data.push_back(row);
    }

    file.close();
}   