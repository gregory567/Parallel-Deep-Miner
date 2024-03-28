#ifndef ROBOT_HPP_INCLUDED
#define ROBOT_HPP_INCLUDED

// forward declaration of the Mine class (to avoid circular dependency)
class Mine;

class Robot{
    public:
        Robot(int x, int y, std::string name, int health_points, int threadNum);
        virtual ~Robot();

        // functions to move the robot one field at a time and to teleport from one place to another
        char random_move() const;
        void moveRobot(const char direction);
        void set_location(const int x, const int y);

        // pure virtual function for extraction (will be initialized in each specific robot class)
        virtual void extract(Mine& mine, const int x, const int y) = 0;

        // getter functions for x- and y-coordinates, name, and points
        int get_xCoord() const;
        int get_yCoord() const;
        std::string get_name() const;
        int get_points() const;
        int get_health_points() const;

        // function for deducting health points
        void deduct_health_point();

        //functions for setting thread start and end timestamps
        void set_thread_start(std::chrono::time_point<std::chrono::steady_clock> thread_start);
        void set_thread_end(std::chrono::time_point<std::chrono::steady_clock> thread_end);
        std::chrono::time_point<std::chrono::steady_clock> get_thread_start() const;
        std::chrono::time_point<std::chrono::steady_clock> get_thread_end() const;

    protected:
        int x_coord;
        int y_coord;
        int z_coord;
        std::string name;
        int points;
        int health_points;
        int threadNumber;
        std::chrono::time_point<std::chrono::steady_clock> thread_start;
        std::chrono::time_point<std::chrono::steady_clock> thread_end;

    private:

};

#endif // ROBOT_HPP_INCLUDED
