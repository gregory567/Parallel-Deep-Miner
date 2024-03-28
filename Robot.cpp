

Robot::Robot(int x, int y, std::string name, int health_points, int threadNum) : threadNumber(threadNum) {
    x_coord = x;
    y_coord = y;
    z_coord = 9;
    this->name = name;
    points = 0;
    this->health_points = health_points;
}


Robot::~Robot(){
    // destruction
}

char Robot::random_move() const{
    int randNum = rand() % 5 + 1; // generates random number between 1 and 5
    char robot_move;
    if (randNum == 1) {
        robot_move = 'a';
    } else if (randNum == 2) {
        robot_move = 'w';
    } else if (randNum == 3) {
        robot_move = 's';
    } else if (randNum == 4) {
        robot_move = 'd';
    } else {
        robot_move = 'e';
    }

    return robot_move;
}

void Robot::moveRobot(const char direction){
    switch(direction){
        case 'w':
            if(y_coord < 4){
                y_coord++;
            } else {
                y_coord = 0;
            }
            break;
        case 'a':
            if(x_coord > 0){
                x_coord--;
            } else {
                x_coord = 4;
            }
            break;
        case 's':
            if(y_coord > 0){
                y_coord--;
            } else {
                y_coord = 4;
            }
            break;
        case 'd':
            if(x_coord < 4){
                x_coord++;
            } else {
                x_coord = 0;
            }
            break;
        default:
            std::cout << "\n" << name << " does not move in this round." << std::endl;
            break;
    }
}

int Robot::get_xCoord() const{
    return x_coord;
}

int Robot::get_yCoord() const{
    return y_coord;
}

std::string Robot::get_name() const{
    return name;
}

int Robot::get_points() const{
    return points;
}

void Robot::set_location(const int x, const int y){
    x_coord = x;
    y_coord = y;
}

void Robot::deduct_health_point(){
    health_points--;
}

int Robot::get_health_points() const{
    return health_points;
}

void Robot::set_thread_start(std::chrono::time_point<std::chrono::steady_clock> thread_start){
    this->thread_start = thread_start;
}

void Robot::set_thread_end(std::chrono::time_point<std::chrono::steady_clock> thread_end){
    this->thread_end = thread_end;
}

std::chrono::time_point<std::chrono::steady_clock> Robot::get_thread_start() const{
    return thread_start;
}

std::chrono::time_point<std::chrono::steady_clock> Robot::get_thread_end() const{
    return thread_end;
}










