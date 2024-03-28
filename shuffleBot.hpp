#ifndef SHUFFLEBOT_HPP_INCLUDED
#define SHUFFLEBOT_HPP_INCLUDED

class shuffleBot: public Robot{
    public:
        shuffleBot(int x, int y, std::string name, int health_points, int threadNum);
        virtual ~shuffleBot();

        void extract(Mine& m, const int x, const int y) override;


    protected:

    private:

};

#endif // SHUFFLEBOT_HPP_INCLUDED
