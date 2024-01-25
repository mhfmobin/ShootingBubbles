#ifndef BOUNCINGBALLS_BACK_END_H
#define BOUNCINGBALLS_BACK_END_H

//================================ Definition ================================ 

bool isGameOver();
bool isWinner();
void loadLevel(int level_id);
bool isColor(int n);

//================================ Implementation ================================

bool isGameOver() {
    if (is_timer_on)
        if (!timer)
            return true;

    int last_row = data.size() - 1;
    for (int i = last_row; i >= 0; i--)
        for (int j = 0; j < MAX_BALLS; j++)
            if (data[i][j].color)
                return (data[i][j].y + R + added_y >= BASE_Y);
}
 
bool isWinner() {
    for (int i = 0; i < data.size(); i++)
        for (int j = 0; j < data[i].size(); j++)
            if (data[i][j].color)
                return false;
    return false;
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

            row.push_back(ball);
        }

        data.push_back(row);
    }

    file.close();

    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < MAX_BALLS; ++j) {
            float added = (i%2) ? 2*R : R ;
            data[i][j].x = 2*j*R + added;
            data[i][j].y = START_Y - ((data.size()-1 - i) * sqrt(3) * R + R);
        }
    }
}
bool isColor(int n) {
    for (int i = 0; i < colors.size(); ++i)
        if (colors[i] == n)
            return true;
    return false;
}

time_t time() {
    return chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
}

#endif //BOUNCINGBALLS_BACK_END_H