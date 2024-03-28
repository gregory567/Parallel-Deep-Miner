#ifndef GAME_CPP_INCLUDED
#define GAME_CPP_INCLUDED

// create a global mutex
std::mutex m;

Game::Game(){
    round_counter = 1;
    level_counter = 1;
}

Game::~Game(){
    // destruction
}

int Game::get_round_counter() const{
    return round_counter;
}

void Game::increment_round_counter(){
    round_counter++;
}

int Game::get_level_counter() const{
    return level_counter;
}

void Game::increment_level_counter(){
    level_counter++;
}


void Game::runGame(Robot& robot, Mine& mine, std::vector<std::reference_wrapper<Robot>> other_robots){

    m.lock();
    auto thread_start = std::chrono::steady_clock::now();
    robot.set_thread_start(thread_start);
    m.unlock();

    do{ // repeat the rounds until all fields of the mine are extracted or the robot dies
        // STATS at the beginning of each round
        // CURRENT ROUND
        // print out the current round
        m.lock();
        std::cout << "\nRound: " << get_round_counter() << std::endl;
        m.unlock();

        // CURRENT POINTS
        // print out the robot's name and its current points
        m.lock();
        std::cout << "\nPoints of " << robot.get_name() << ": " << robot.get_points() << std::endl;
        m.unlock();

        // MOVE ROBOT
        // the robot will be moved in a random direction or it will be let to stay where it is
        m.lock();
        robot.moveRobot(robot.random_move());
        m.unlock();

        // NEW LOCATION:
        // print out the robot's name and its new coordinates
        m.lock();
        std::cout << "\nNew location of " << robot.get_name() << ": Block: " << robot.get_xCoord() << " Tunnel: " << robot.get_yCoord() << std::endl;
        m.unlock();


        // CHECK ROBOT PROXIMITY
        // check if there are robots nearby

        // we need to use .get() because other_robot is a reference to a std::reference_wrapper<Robot> object, not a Robot object itself.
        // the std::reference_wrapper class is a wrapper around a reference that provides a similar interface to a pointer, but with more safety guarantees.
        // calling .get() on a std::reference_wrapper object returns the reference it wraps, in this case, a reference to a Robot object.
        // therefore, we call .get() on other_robot to access the Robot object it references, and then call the get_yCoord() and get_xCoord() methods on the Robot object.
        for(auto& other_robot : other_robots){

            m.lock();
            int other_robot_xcoord = other_robot.get().get_xCoord();
            int other_robot_ycoord = other_robot.get().get_yCoord();
            int robot_xcoord = robot.get_xCoord();
            int robot_ycoord = robot.get_yCoord();
            m.unlock();

            if(other_robot_xcoord == robot_xcoord &&
               std::abs(other_robot_ycoord - robot_ycoord) <= 1){

                // when robot is found, warn the user
                m.lock();
                std::cout << "\nWarning: robot detected nearby!" << std::endl;
                m.unlock();

                // the robot takes 1-3 HP damage, based on a random draw
                m.lock();
                int probability = rand() % 100 + 1;
                m.unlock();
                // if-else-tree based on random number ranges
                if(probability < 16){  // random number is in the range [1, 15]
                    m.lock();
                    if(robot.get_health_points() >= 3){
                        std::cout << "\n3 HP damage taken." << std::endl;
                        robot.deduct_health_point();
                        robot.deduct_health_point();
                        robot.deduct_health_point();
                    } else if(robot.get_health_points() >= 2){
                        std::cout << "\n2 HP damage taken." << std::endl;
                        robot.deduct_health_point();
                        robot.deduct_health_point();
                    } else if(robot.get_health_points() >= 1){
                        std::cout << "\n1 HP damage taken." << std::endl;
                        robot.deduct_health_point();
                    }
                    m.unlock();
                } else if(15 < probability && probability < 41){ // random number is in the range [16, 40]
                    m.lock();
                    if(robot.get_health_points() >= 2){
                        std::cout << "\n2 HP damage taken." << std::endl;
                        robot.deduct_health_point();
                        robot.deduct_health_point();
                    } else if(robot.get_health_points() >= 1){
                        std::cout << "\n1 HP damage taken." << std::endl;
                        robot.deduct_health_point();
                    }
                    m.unlock();
                } else { // random number is in the range [40, 100]
                    m.lock();
                    if(robot.get_health_points() >= 1){
                        std::cout << "\n1 HP damage taken." << std::endl;
                        robot.deduct_health_point();
                    }
                    m.unlock();
                }
            }
        }


        // CHECK SPECIAL EFFECT
        // first, check if there are special effects in the current tunnel, and where they are
        m.lock();
        int special_effect = mine.special_effect(robot.get_xCoord(), robot.get_yCoord());
        int special_effect_index = mine.special_effect_index(robot.get_xCoord(), robot.get_yCoord());
        m.unlock();

        if(special_effect != 0){

            // when special effect is found, warn the user
            m.lock();
            std::cout << "\nSpecial mineral found at position: " << special_effect_index << std::endl;
            m.unlock();

            // switch to different cases depending on the nature of the special effect
            switch(special_effect){
                case -1:
                    // the robot is not allowed to extract in this round
                    m.lock();
                    mine.remove_field(robot.get_xCoord(), robot.get_yCoord(), special_effect_index);
                    increment_round_counter();
                    std::cout << "\nSorry " << robot.get_name() << ", you have to skip one round." << std::endl;
                    m.unlock();
                    // print the new mine
                    //mine.print_mine();
                    continue;
                    break;
                case -2:
                    // the robot will be placed at the x and y coordinates with the lowest value at z=9
                    m.lock();
                    mine.remove_field(robot.get_xCoord(), robot.get_yCoord(), special_effect_index);
                    robot.set_location(mine.find_lowest_tunnel().first, mine.find_lowest_tunnel().second);
                    std::cout << "\nAttention " << robot.get_name() << ", you will be transported to a new tunnel." << std::endl;
                    m.unlock();
                    // print out the robot's name and its new coordinates
                    m.lock();
                    std::cout << "\nNew location of " << robot.get_name() << ": Block: " << robot.get_xCoord() << " Tunnel: " << robot.get_yCoord() << std::endl;
                    m.unlock();

                    // we continue with the extraction here and do not skip it with "continue"
                    // use the overriden extraction function of each robot
                    m.lock();
                    robot.extract(mine, robot.get_xCoord(), robot.get_yCoord());
                    // print the new mine
                    mine.print_mine();
                    // increment round
                    increment_round_counter();
                    m.unlock();
                    break;
                case -3:
                    // the tunnel will be shuffled and the robot will not be allowed to extract in this round
                    m.lock();
                    mine.remove_field(robot.get_xCoord(), robot.get_yCoord(), special_effect_index);
                    mine.shuffle_tunnel(mine.get_tunnel(robot.get_xCoord(), robot.get_yCoord()));
                    increment_round_counter();
                    std::cout << "\nAttention, the current tunnel was shuffled." << std::endl;
                    m.unlock();
                    // print the new mine
                    //mine.print_mine();
                    continue;
                    break;
                default:
                    // this should never happen
                    m.lock();
                    std::cerr << "\nError: unknown special effect detected." << std::endl;
                    m.unlock();
                    break;
            }
        } else { // if there was no special effect in the respective tunnel, we proceed with extraction
            // use the overriden extraction function of each robot
            m.lock();
            robot.extract(mine, robot.get_xCoord(), robot.get_yCoord());
            // print the new mine
            mine.print_mine();
            // increment round
            increment_round_counter();
            m.unlock();
        }


        // every time the points of the robot are divisible by 50, increment the level counter and rearrange the mine
        if(robot.get_points() % 50 == 0 /*robot.get_points() % 10 == 0 || robot.get_points() % 5 == 0*/){
            m.lock();
            increment_level_counter();
            std::cout << "\nCongrats " << robot.get_name() << ", you have reached a new level!" << std::endl;
            std::cout << "\nLevel: " << get_level_counter() << std::endl;
            m.unlock();

            // rearrange the mine randomly based on 3 different rearranging techniques
            m.lock();
            mine.rearrange_mine();
            // print the mine
            mine.print_mine();
            m.unlock();
        }

    }while(mine.sum_mine_values() > 0 && robot.get_health_points() > 0);

    m.lock();
    std::cout << "\nCongrats " << robot.get_name() << ", you have reached the end of the game!" << std::endl;
    m.unlock();

    m.lock();
    auto thread_end = std::chrono::steady_clock::now();
    robot.set_thread_end(thread_end);
    m.unlock();
}



#endif // GAME_CPP_INCLUDED
