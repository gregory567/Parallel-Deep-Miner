

tripleBot::tripleBot(int x, int y, std::string name, int health_points, int threadNum): Robot(x, y, name, health_points, threadNum){
    // construction
}

tripleBot::~tripleBot() {
    // destruction
}

void tripleBot::extract(Mine& m, const int x, const int y){


    int field_9 = m.get_field(x, y, 9);
    int field_8 = m.get_field(x, y, 8);
    int field_7 = m.get_field(x, y, 7);

    // check if the fields are not special effects
    if(field_9 > 0 && field_8 > 0 && field_7 > 0){
        // add the 3 fields to the points of tripleBot
        points += field_9;
        points += field_8;
        points += field_7;
        // set the 3 fields of the mine equal to 0
        m.remove_field(x, y, 9);
        m.remove_field(x, y, 8);
        m.remove_field(x, y, 7);
    } else {
        std::cout << std::endl;
        std::cout << "Could not extract special effect." << std::endl;
    }

}
