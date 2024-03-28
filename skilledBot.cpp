

skilledBot::skilledBot(int x, int y, std::string name, int health_points, int threadNum): Robot(x, y, name, health_points, threadNum){
    // construction
}

skilledBot::~skilledBot() {
    // destruction
}


void skilledBot::extract(Mine& m, const int x, const int y){


    int field_9 = m.get_field(x, y, 9);
    int field_8 = m.get_field(x, y, 8);

    // check if the fields are not a special effects
    if(field_9 > 0 && field_8 > 0){

        // add the field's value times 2 to the points of skilledBot
        points += field_9;
        points += field_8;
        // set the field of the mine equal to 0
        m.remove_field(x, y, 9);
        m.remove_field(x, y, 8);

    } else if(field_9 > 0){

        points += field_9;
        m.remove_field(x, y, 9);

    } else if(field_8 > 0){

        points += m.get_field(x, y, 8);
        m.remove_field(x, y, 8);

    } else {
        std::cout << std::endl;
        std::cout << "Could not extract special effect." << std::endl;
    }

}




