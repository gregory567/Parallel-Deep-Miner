
// libraries
#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

// file includes
#include "Robot.hpp"
#include "Mine.hpp"
#include "Mine.cpp"
#include "sortingBot.hpp"
#include "sortingBot.cpp"
#include "tripleBot.hpp"
#include "tripleBot.cpp"
#include "skilledBot.hpp"
#include "skilledBot.cpp"
#include "shuffleBot.hpp"
#include "shuffleBot.cpp"
#include "comboBot.hpp"
#include "comboBot.cpp"
#include "Game.hpp"
#include "Game.cpp"


int main(){

    // Setup:
    // Start measuring the total program execution time
    auto program_start = std::chrono::steady_clock::now();
    // call the game constructor
    Game my_game;
    // seed the random number generator with the current time
    srand(time(nullptr));
    // call the mine constructor
    Mine GameField;
    // initialize the mine
    GameField.init_mine();
    // print out the mine for the first time at the start of the game
    GameField.print_mine();
    // calculate the initial sum of the extractable values in the mine
    int initial_mine_sum = GameField.sum_mine_values();

    // initialize the 4 different robots
    sortingBot sorting_miner(0, 2, "Novak", 100, 1);
    tripleBot triple_miner(1, 2, "Rafa", 100, 2);
    skilledBot skilled_miner(3, 2, "Roger", 100, 3);
    shuffleBot shuffle_miner(4, 2, "Nick", 100, 4);
    //comboBot combo_miner(5, 2, "Dominik", 100, 5);

    // create a vector of references to the other robots
    std::vector<std::reference_wrapper<Robot>> other_robots_0{triple_miner, skilled_miner, shuffle_miner/*, combo_miner*/};

    // Start the thread and measure its execution time
    std::thread th0(&Game::runGame, std::ref(my_game), std::ref(sorting_miner), std::ref(GameField), std::ref(other_robots_0));


    // create a vector of references to the other robots
    std::vector<std::reference_wrapper<Robot>> other_robots_1{sorting_miner, skilled_miner, shuffle_miner/*, combo_miner*/};

    // Start the thread and measure its execution time
    std::thread th1(&Game::runGame, std::ref(my_game), std::ref(triple_miner), std::ref(GameField), std::ref(other_robots_1));


    // create a vector of references to the other robots
    std::vector<std::reference_wrapper<Robot>> other_robots_2{sorting_miner, triple_miner, shuffle_miner/*, combo_miner*/};

    // Start the thread and measure its execution time
    std::thread th2(&Game::runGame, std::ref(my_game), std::ref(skilled_miner), std::ref(GameField), std::ref(other_robots_2));


    // create a vector of references to the other robots
    std::vector<std::reference_wrapper<Robot>> other_robots_3{sorting_miner, triple_miner, skilled_miner/*, combo_miner*/};

    // Start the thread and measure its execution time
    std::thread th3(&Game::runGame, std::ref(my_game), std::ref(shuffle_miner), std::ref(GameField), std::ref(other_robots_3));


    /*
    // create a vector of references to the robots
    std::vector<std::reference_wrapper<Robot>> other_robots_4{sorting_miner, triple_miner, skilled_miner, shuffle_miner};

    // Start the thread and measure its execution time
    std::thread th4(&Game::runGame, std::ref(my_game), std::ref(combo_miner), std::ref(GameField), std::ref(other_robots_4));
    */

    // wait for the threads to finish before continuing the execution of the main thread
    th0.join();
    th1.join();
    th2.join();
    th3.join();
    //th4.join();

    // Calculate the execution times for each thread
    auto thread_0_time = std::chrono::duration_cast<std::chrono::milliseconds>(sorting_miner.get_thread_end() - sorting_miner.get_thread_start()).count();
    auto thread_1_time = std::chrono::duration_cast<std::chrono::milliseconds>(triple_miner.get_thread_end() - triple_miner.get_thread_start()).count();
    auto thread_2_time = std::chrono::duration_cast<std::chrono::milliseconds>(skilled_miner.get_thread_end() - skilled_miner.get_thread_start()).count();
    auto thread_3_time = std::chrono::duration_cast<std::chrono::milliseconds>(shuffle_miner.get_thread_end() - shuffle_miner.get_thread_start()).count();
    //auto thread_4_time = std::chrono::duration_cast<std::chrono::milliseconds>(combo_miner.get_thread_end() - combo_miner.get_thread_start()).count();


    int sum_of_robot_points = sorting_miner.get_points() + triple_miner.get_points() + skilled_miner.get_points() + shuffle_miner.get_points() /*+ combo_miner.get_points()*/;
    std::cout << "\nThe initial sum of the values of the mine was: " << initial_mine_sum << std::endl;
    std::cout << "The robots have collected: " << sum_of_robot_points << std::endl;

    // final points of the bots
    std::cout << std::endl;
    std::cout << "Points of sortingBot: " << sorting_miner.get_points() << std::endl;
    std::cout << "Points of tripleBot: " << triple_miner.get_points() << std::endl;
    std::cout << "Points of skilledBot: " << skilled_miner.get_points() << std::endl;
    std::cout << "Points of shuffleBot: " << shuffle_miner.get_points() << std::endl;
    //std::cout << "Points of comboBot: " << combo_miner.get_points() << std::endl;

    // final health points of the bots
    std::cout << std::endl;
    std::cout << "Health points of sortingBot: " << sorting_miner.get_health_points() << std::endl;
    std::cout << "Health points of tripleBot: " << triple_miner.get_health_points() << std::endl;
    std::cout << "Health points of skilledBot: " << skilled_miner.get_health_points() << std::endl;
    std::cout << "Health points of shuffleBot: " << shuffle_miner.get_health_points() << std::endl;
    //std::cout << "Health points of comboBot: " << combo_miner.get_health_points() << std::endl;

    // end the program time measurement
    auto program_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - program_start).count();

    // Print the execution times
    std::cout << std::endl;
    std::cout << "Thread 0 execution time: " << thread_0_time << " ms" << std::endl;
    std::cout << "Thread 1 execution time: " << thread_1_time << " ms" << std::endl;
    std::cout << "Thread 2 execution time: " << thread_2_time << " ms" << std::endl;
    std::cout << "Thread 3 execution time: " << thread_3_time << " ms" << std::endl;
    //std::cout << "Thread 4 execution time: " << thread_4_time << " ms" << std::endl;
    std::cout << "Program execution time: " << program_time << " ms" << std::endl;


    // The maximum number of threads that can be used in C++ on a given computer depends on several factors, such as the number of cores and the amount of available memory.
    // According to the output of the following function (which is only a recommendation) my system only supports 4 concurrent threads.
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << std::endl;
    std::cout << "Maximum number of threads supported: " << n << std::endl;

    return 0;
}









