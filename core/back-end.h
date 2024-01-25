//================================ Definition ================================ 

bool isGameOver();
bool isWinner();
void loadLevel(int level_id);
void loadSettings();
void saveSettings();
bool isColor(int n);
time_t time();
vector<int> cannonBalls();

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

vector<int> cannonBalls() {
    set<int> uniqueColors = accumulate(data.begin(), data.end(), set<int>(), [](const set<int>& acc, const vector<Ball>& balls) {
        set<int> result = acc;
        for (const Ball& ball : balls)
            if (ball.color)
                result.insert(ball.color);
        
        return result;
    });

    vector<int> balls = {};

    if (!uniqueColors.size()) {
        balls = {0,0};
    } else if (uniqueColors.size() == 1) {
        int onlyColor = *uniqueColors.begin();
        balls = {onlyColor, onlyColor};
    } else {
        vector<int> shuffledColors(uniqueColors.begin(), uniqueColors.end());
        random_shuffle(shuffledColors.begin(), shuffledColors.end());
        balls = {shuffledColors[0], shuffledColors[1]};
    }

    return balls;
}

void ballPlacement(int i, int j, int color) {
    
}

void popBalls(int i, int j, int color) {
    if (i != data.size() -1) { // check next row
        
    }

    if (i != 0) { // check previous row 
        
    }
}