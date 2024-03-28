

shuffleBot::shuffleBot(int x, int y, std::string name, int health_points, int threadNum) : Robot(x, y, name, health_points, threadNum) {
    // construction
}

shuffleBot::~shuffleBot() {
    // destruction
}


void shuffleBot::extract(Mine& m, const int x, const int y){

    // sort the array in descending order
    m.shuffle_tunnel(m.get_tunnel(x, y));

    // generate a random number between 0 and 9
    int rand_num = rand() % 10;
    int rand_field = m.get_field(x, y, rand_num);

    // check if the field is not a special effect
    if(rand_field > 0){
        // the highest number in the array is tunnel[9]
        // add the highest number to the points of sortingBot
        points += rand_field;
        // set the field of the mine equal to 0
        m.remove_field(x, y, rand_num);
    } else {
        std::cout << std::endl;
        std::cout << "Could not extract special effect." << std::endl;
    }
}
