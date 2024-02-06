//================================ Definition ================================ 

bool isGameOver();
bool isWinner();
void loadLevel(int level_id);
void loadSettings();
void saveSettings();
bool isColor(int n);
time_t time();
int cannonBall();
bool isValidPosition(int row, int col);
void fallBalls(int row, int col);
void popBalls(int row, int col, int color, bool first = false);
void ballPlacement(int row, int col, int color);
bool isSame(int one, int two);
void resetFallingBalls();
void generateRandomGame(int n, int mode = 1);
void saveScore();
unordered_map<string, int> sortedScores();
bool ballCollision();
// these are implemented in front end
void ShowPoping(double x,double y);
void ShowFalling(double x,double y,int color);
void explodeBalls(int row, int col);
void laserEffect();
//================================ Implementation ================================

bool isGameOver() {
    if (is_timer_on)
        if (tim=="time = 00:00"){
            return true;
        }

    int last_row = data.size() - 1;
    for (int i = last_row; i >= 0; i--)
        for (int j = 0; j < MAX_BALLS; j++)
            if (data[i][j].color)
                return (data[i][j].y + R + added_y >= BASE_Y);
}

bool isWinner() {
    bool flag = 1;
    for (int i = 0; i < data.size(); i++)
        for (int j = 0; j < data[i].size(); j++)
            if (data[i][j].color)
                flag = 0;
    return flag;
}

void loadSettings() {
    string filename = "../data/user-setting.txt";
    string line;

    ifstream file(filename);

    if (!file.good()) {
        cerr << "Error opening the file: " << filename << endl;
        return;
    }

    getline(file, line);
    settings["music_mode"] = stoi(line);

    getline(file, line);
    settings["music_volume"] = stoi(line);

    getline(file, line);
    settings["sound_mode"] = stoi(line);

    getline(file, line);
    settings["sound_volume"] = stoi(line);

    getline(file, line);
    settings["theme"] = stoi(line);

    file.close();

}

void saveSettings() {
    string filename = "../data/user-setting.txt";
    string line;

    ofstream file(filename);

    if (!file.good()) {
        cerr << "Error opening the file: " << filename << endl;
        return;
    }

    file << settings["music_mode"] << endl;
    file << settings["music_volume"] << endl;
    file << settings["sound_mode"] << endl;
    file << settings["sound_volume"] << endl;
    file << settings["theme"] << endl;

    file.close();
}

void loadLevel(int level_id) {
    data.clear();

    string filename = "../data/level-" + to_string(level_id) + ".csv";

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
        // int limit = (i%2) ? MAX_BALLS - 1 : MAX_BALLS ;
        for (int j = 0; j < data[i].size(); ++j) {
            float added = (i%2) ? 2*R : R ;
            data[i][j].x = 2*j*R + added;
            data[i][j].y = START_Y - ((data.size()-1 - i) * sqrt(3) * R + R);
        }
    }
    level_row_count = data.size();
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

int cannonBall() {
    set<int> uniqueColors = accumulate(data.begin(), data.end(), set<int>(), [](const set<int>& acc, const vector<Ball>& balls) {
        set<int> result = acc;
        for (const Ball& ball : balls)
            if (ball.color)
                result.insert(ball.color);

        return result;
    });

    // removing black

    if (uniqueColors.find(13) != uniqueColors.end())
        uniqueColors.erase(13);


    int color = 0;

    if (uniqueColors.size() == 1) {
        int onlyColor = *uniqueColors.begin();
        color = onlyColor;
    } else if (uniqueColors.size() > 1) {
        vector<int> shuffledColors(uniqueColors.begin(), uniqueColors.end());
        random_shuffle(shuffledColors.begin(), shuffledColors.end());
        color = shuffledColors[0];
    }

    return color;
}

bool isValidPosition(int row, int col) {
    return (row >= 0 && row < data.size() && col >= 0 && col < (10 - row%2));
}

void ballPlacement(int row, int col, int color) {

    if (color == 17) {
        explodeBalls(row, col);
    } else {
        data[row][col].color = color;
        float added = (row%2) ? 2*R : R ;
        data[row][col].x = 2*col*R + added;
        data[row][col].y = START_Y - ((level_row_count-1 - row) * sqrt(3) * R + R);

        popBalls(row, col, color, true);
    }

    for (int i = 0; i < data[0].size(); ++i) {
        if (data[0][i].color && !data[0][i].falling_tmp) {
            data[0][i].falling_tmp = true;
            fallBalls(0, i);
        }
    }
    resetFallingBalls();
}

void popBalls(int row, int col, int color, bool first) {

    if (!first) {
        ShowPoping(data[row][col].x, data[row][col].y + added_y);
        data[row][col].color = 0;
        score += 20;
    }

    int offsets[6][2];
    if (row % 2) {
        int temp[][2] = {{-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 0}, {1, 1}};
        copy_n(&temp[0][0], 6 * 2, &offsets[0][0]);
    } else {
        int temp[][2] = {{-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0}};
        copy_n(&temp[0][0], 6 * 2, &offsets[0][0]);
    }
    for (int i = 0; i < 6; ++i) {
        int newRow = row + offsets[i][0];
        int newCol = col + offsets[i][1];

        if (isValidPosition(newRow, newCol) && data[newRow][newCol].color && isSame(color, data[newRow][newCol].color)) {
            if (first){
                ShowPoping(data[row][col].x, data[row][col].y + added_y);
                data[row][col].color = 0;
                score += 20;
            }
            popBalls(newRow, newCol, color);
        }
    }
    return;
}

void explodeBalls(int row, int col) {

    int offsets[6][2];
    if (row % 2) {
        int temp[][2] = {{-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 0}, {1, 1}};
        copy_n(&temp[0][0], 6 * 2, &offsets[0][0]);
    } else {
        int temp[][2] = {{-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0}};
        copy_n(&temp[0][0], 6 * 2, &offsets[0][0]);
    }
    for (int i = 0; i < 6; ++i) {
        int newRow = row + offsets[i][0];
        int newCol = col + offsets[i][1];

        if (isValidPosition(newRow, newCol) && data[newRow][newCol].color) {
            ShowPoping(data[row][col].x, data[row][col].y + added_y);

            // TO DO: Change it to explode animation

            data[row][col].color = 0;
            score += 20;
        }
    }
    return;
}

bool isSame(int one, int two) {
    return (one % two == 0 || two % one == 0);
}

void fallBalls(int row, int col) {
    int offsets[6][2];
    if (row % 2) {
        int temp[][2] = {{-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 0}, {1, 1}};
        copy_n(&temp[0][0], 6 * 2, &offsets[0][0]);
    } else {
        int temp[][2] = {{-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0}};
        copy_n(&temp[0][0], 6 * 2, &offsets[0][0]);
    }
    for (int i = 0; i < 6; ++i) {
        int newRow = row + offsets[i][0];
        int newCol = col + offsets[i][1];

        if (isValidPosition(newRow, newCol) && data[newRow][newCol].color && !data[newRow][newCol].falling_tmp) {
            data[newRow][newCol].falling_tmp = true;
            fallBalls(newRow, newCol);
        }
    }
}

void resetFallingBalls() {
    for (int i = 0; i < data.size(); ++i)
        for (int j = 0; j < data[i].size(); ++j) {
            if (!data[i][j].falling_tmp) {
                score += 30;
                data[i][j].is_falling = true;
                ShowFalling(data[i][j].x,data[i][j].y+added_y,data[i][j].color);
                data[i][j].color = 0;
            }
            data[i][j].falling_tmp = false;
        }
}

void generateRandomGame(int n, int mode) {
    if (mode) {
        data.clear();
    }
    srand(time(NULL));
    for (int i = n-1; i >= 0; --i) {
        vector<Ball> row;
        int limit = (i%2) ? MAX_BALLS - 1 : MAX_BALLS ;
        int prevColor = -1;
        for (int j = 0; j < limit; ++j) {
            Ball ball;
            int color;
            if (prevColor != -1 && rand() % 2 == 0) {
                color = prevColor;
            } else {
                color = colors[rand() % colors.size(  )];
                prevColor = color;
            }
            ball.color = color;
            row.push_back(ball);
        }
        data.insert(data.begin(), row);
        // data.push_back(row);
    }
    for (int i = 0; i < data.size(); i++) {
        int limit = (i%2) ? MAX_BALLS - 1 : MAX_BALLS ;
        for (int j = 0; j < limit; ++j) {
            float added = (i%2) ? 2*R : R ;
            data[i][j].x = 2*j*R + added;
            data[i][j].y = START_Y - ((data.size()-1 - i) * sqrt(3) * R + R);
        }
    }
}

void saveScore() {
    string filename = "../data/scores.csv";
    ofstream file(filename, ios::app);
    if (!file.good()) {
        cerr << "Error opening the file: " << filename << endl;
        return;
    }
    file << name << "," << score << endl;
    file.close();
}

unordered_map<string, int> sortedScores() {
    string filename = "../data/scores.csv";
    ifstream file(filename);
    if (!file.good()) {
        cerr << "Error opening the file: " << filename << endl;
        return {};
    }
    string line;
    unordered_map<string, int> scores;
    while (getline(file, line)) {
        stringstream ss(line);
        string username;
        string score;
        getline(ss, username, ',');
        getline(ss, score, ',');
        scores[username] = stoi(score);
    }
    file.close();

    vector<pair<string, int>> sortedScoresVec(scores.begin(), scores.end());
    sort(sortedScoresVec.begin(), sortedScoresVec.end(), [](const auto &a, const auto &b) {return a.second > b.second;});
    unordered_map<string, int> sortedMap(sortedScoresVec.begin(), sortedScoresVec.end());

    return sortedMap;
}

bool ballCollision() {
    float sx = shooted_ball.x, sy = shooted_ball.y;
    for (int i = data.size(); i >= 0; i--) {
        for (int j = data[i].size()-1; j >= 0; j--) {
            Ball ball = data[i][j];
            float x = ball.x, y = ball.y + added_y;
            sx = shooted_ball.x, sy = shooted_ball.y;
            if (!ball.color || abs(x - sx) > 2.5*R || abs(y - sy) > 2.5*R) continue;

            float d = pow(x - sx, 2) + pow(y - sy, 2);

            if (d <= pow(2*R, 2)) {

                int fi = 0, fj = 0;

                fi = (sy < y+R/2) ? i : i+1;
                fj = (sx > x) ? j+(i%2)  : j -1 + (i%2);

                if (fi == data.size()) {
                    Ball empty;
                    empty.color = 0;
                    data.emplace_back();
                    for (int k = 0; k < MAX_BALLS - (fi%2); k++) {
                        data[fi].push_back(empty);
                    }
                }
                if (isValidPosition(fi, fj) && !data[fi][fj].color) {
                    ballPlacement(fi,fj,shooted_ball.color);
                    return true;
                }
            }
        }
    }

    return false;
}


void laserEffect() {
    for (int i = data.size(); i >= 0; i--) {
        for (int j = data[i].size()-1; j >= 0; j--) {
            Ball ball = data[i][j];
            float x = ball.x, y = ball.y + added_y;
            float sx = shooted_laser.x, sy = shooted_laser.y;
            if (!ball.color || abs(x - sx) > 2.5*R || abs(y - sy) > 2.5*R) continue;

            float d = pow(x - sx, 2) + pow(y - sy, 2);

            if (d <= pow(2*R, 2)) {
                ShowPoping(x, y);
                data[i][j].color = 0;
            }
        }
    }
    if (sy <= 0) shooting_laser = false;
    return;
}