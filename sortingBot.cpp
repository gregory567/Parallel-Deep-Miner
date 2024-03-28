
#include "Robot.cpp"

sortingBot::sortingBot(int x, int y, std::string name, int health_points, int threadNum) : Robot(x, y, name, health_points, threadNum) {
    // construction
}

sortingBot::~sortingBot() {
    // destruction
}


void sortingBot::extract(Mine& m, const int x, const int y){

    // sort the array in descending order
    m.sort_tunnel(m.get_tunnel(x, y));

    // check if the field is not a special effect
    int field_9 = m.get_field(x, y, 9);

    if(field_9 > 0){
        // the highest number in the array is tunnel[9]
        // add the highest number to the points of sortingBot
        points += field_9;
        // set the field of the mine equal to 0
        m.remove_field(x, y, 9);
    } else {
        std::cout << std::endl;
        std::cout << "Could not extract special effect." << std::endl;
    }
}

