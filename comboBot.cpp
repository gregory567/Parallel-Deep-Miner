

comboBot::comboBot(int x, int y, std::string name, int health_points, int threadNum) : Robot(x, y, name, health_points, threadNum) {
    // construction
}

comboBot::~comboBot() {
    // destruction
}


void comboBot::extract(Mine& m, const int x, const int y){

    // sort the array in descending order
    m.sort_tunnel(m.get_tunnel(x, y));

    // generate a random number between 0 and 9
    int rand_num_1 = rand() % 10;
    int rand_field_1 = m.get_field(x, y, rand_num_1);

    int rand_num_2 = rand() % 10;
    int rand_field_2 = m.get_field(x, y, rand_num_2);

    // check if the field is not a special effect
    if(rand_field_1 > 0 && rand_field_2 > 0){
        // the 2 highest numbers in the array are tunnel[9] and tunnel[8]
        // add the highest numbers to the points of comboBot
        points += rand_field_1;
        points += rand_field_2;
        // set the field of the mine equal to 0
        m.remove_field(x, y, rand_num_1);
        m.remove_field(x, y, rand_num_2);
    } else {
        std::cout << std::endl;
        std::cout << "Could not extract special effect." << std::endl;
    }
}
