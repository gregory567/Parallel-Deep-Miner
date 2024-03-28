

/*
The rand() function generates a random integer value between 0 and RAND_MAX (a constant defined in the cstdlib header file),
so by taking the result of rand() % 9, we get a random integer between 0 and 8.
Adding 1 to this value ensures that we get a random integer between 1 and 9.
*/

Mine::Mine() {
    block_counter = 0;
    tunnel_counter = 0;
}

Mine::~Mine(){
    // destruction
}

int Mine::get_block_counter() const{
    return block_counter;
}

void Mine::increment_block_counter(){
    block_counter++;
}

void Mine::reset_block_counter(){
    block_counter = 0;
}

int Mine::get_tunnel_counter() const{
    return tunnel_counter;
}

void Mine::increment_tunnel_counter(){
    tunnel_counter++;
}

void Mine::reset_tunnel_counter(){
    tunnel_counter = 0;
}


void Mine::init_mine(){
    for(auto& x : mine){
        for(auto& y : x){
            for(auto& z : y){
                // values between -3 and 9
                z = rand() % 13 - 3;
            }
        }
    }
}


// this function prints the blocks of the mine horizontally
void Mine::print_mine(){
    for(auto x = mine.begin(); x != mine.end(); x++){
        std::cout << "Block " << this->get_block_counter() << std::endl;
        this->increment_block_counter();
        for(auto y = x->begin(); y != x->end(); y++){
            for(auto z = y->begin(); z!= y->end(); z++){
                std::cout << *z << " ";
            }
            std::cout << "   Tunnel " << this->get_tunnel_counter();
            this->increment_tunnel_counter();
            std::cout << std::endl;
        }
        this->reset_tunnel_counter();
        std::cout << std::endl;
    }
    this->reset_block_counter();
}

/*
// this function prints the blocks of the mine vertically
void Mine::print_mine(){
    for(auto x = mine.begin(); x != mine.end(); x++){
        for(int z = 0; z < 10; z++){
            for(auto y = x->begin(); y != x->end(); y++){
                if(y->at(z) >= 0){
                    std::cout << " ";
                }
                std::cout << y->at(z) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
*/

int Mine::sum_mine_values() const {
    int sum = 0;
    for (auto x = mine.begin(); x != mine.end(); x++) {
        for (auto y = x->begin(); y != x->end(); y++) {
            for (auto z = y->begin(); z != y->end(); z++) {
                if (*z > -1) {
                    sum += *z;
                }
            }
        }
    }
    return sum;
}


int Mine::get_field(const int x, const int y, const int z) const{
    return mine[x][y][z];
}


void Mine::remove_field(const int x, const int y, const int z){
    mine[x][y][z] = 0;
}

array<int, 10>& Mine::get_tunnel(const int x, const int y){
    return mine[x][y];
}

void Mine::sort_tunnel(array<int, 10>& tunnel){
    // sort the array in ascending order
    std::sort(tunnel.begin(), tunnel.end());
}

void Mine::rsort_tunnel(array<int, 10>& tunnel){
    // sort the array in descending order
    std::sort(tunnel.rbegin(), tunnel.rend());
}

void Mine::shuffle_tunnel(array<int, 10>& tunnel){
    // shuffle the array randomly
    std::random_shuffle(tunnel.begin(), tunnel.end());
}

/*
// this function uses traditional for loops to rearrange the tunnels of the mine
void Mine::rearrange_mine(){
    // loop over all pairs of x and y coordinates
    for(int x = 0; x < 5; x++){
        for(int y = 0; y < 5; y++){
            // randomly select an operation to perform
            int op = rand() % 3;
            switch(op){
                case 0:
                    // shuffle the z-values randomly
                    this->shuffle_tunnel(this->get_tunnel(x, y));
                    break;
                case 1:
                    // sort the z-values in ascending order
                    this->sort_tunnel(this->get_tunnel(x, y));
                    break;
                case 2:
                    // sort the z-values in descending order
                    this->rsort_tunnel(this->get_tunnel(x, y));
                    break;
                default:
                    // this should never happen
                    std::cerr << "Error: invalid operation selected in rearrange_mine()" << std::endl;
                    break;
            }
        }
    }
}
*/

// this function uses range-based for loops to rearrange the tunnels of the mine
void Mine::rearrange_mine(){
    // loop over all pairs of x and y coordinates
    for(auto& block : mine){
        for(auto& tunnel : block){
            // randomly select an operation to perform
            int op = rand() % 3;
            switch(op){
                case 0:
                    // shuffle the z-values randomly
                    this->shuffle_tunnel(tunnel);
                    break;
                case 1:
                    // sort the z-values in ascending order
                    this->sort_tunnel(tunnel);
                    break;
                case 2:
                    // sort the z-values in descending order
                    this->rsort_tunnel(tunnel);
                    break;
                default:
                    // this should never happen
                    std::cerr << "Error: invalid operation selected in rearrange_mine()" << std::endl;
                    break;
            }
        }
    }
}


int Mine::special_effect(const int x, const int y){
    for(const auto& field : this->get_tunnel(x, y)){
        if(field == -1 || field == -2 || field == -3){
            return field;
        }
    }
    //return 0 if there is no special effect to be found
    return 0;
}

int Mine::special_effect_index(const int x, const int y){
    int index = 0;
    for(const auto& field : this->get_tunnel(x, y)){
        if(field == -1 || field == -2 || field == -3){
            return index;
        }
        index++;
    }
    //indicate that no special effect was found
    return -1;
}


/*
// this function finds the tunnel with the lowest value at position z=9 with traditional for loops
std::pair<int, int> Mine::find_lowest_tunnel() const{
    int min_val = INT_MAX;
    std::pair<int, int> min_coords;
    for(int x = 0; x < 5; x++){
        for(int y = 0; y < 5; y++){
            int curr_val = this->get_field(x, y, 9);
            if(curr_val < min_val){
                min_val = curr_val;
                min_coords = std::make_pair(x, y);
            }
        }
    }
    return min_coords;
}
*/


/*
The way the coordinates are obtained is a bit tricky.
The variable min_coords is a pair of integers representing the x and y coordinates of the current minimum tunnel.
These coordinates are initially set to (0,0) but will be updated if a new minimum value is found.
The std::make_pair() function is used to create a new pair of coordinates.
The first value is the difference between the address of the current row and the address of the first row in the mine (&row - &mine[0]).
This gives the index of the current row in the mine vector.
The second value is the difference between the address of the current tunnel and the address of the first tunnel in the current row (&tunnel - &row[0]).
This gives the index of the current tunnel in the row vector.
By subtracting the address of the first row/tunnel from the address of the current row/tunnel, we obtain the distance (in terms of memory addresses) between them.
Dividing this distance by the size of the objects being pointed to (which is the size of an integer in this case) gives the index of the current row/tunnel.
*/

// this function finds the tunnel with the lowest value at position z=9 with traditional for loops
std::pair<int, int> Mine::find_lowest_tunnel() const{
    int min_val = INT_MAX;
    std::pair<int, int> min_coords;
    for(auto& row: mine) {
        for(auto& tunnel: row) {
            int curr_val = tunnel[9];
            if(curr_val < min_val){
                min_val = curr_val;
                min_coords = std::make_pair(&row - &mine[0], &tunnel - &row[0]);
            }
        }
    }
    return min_coords;
}






