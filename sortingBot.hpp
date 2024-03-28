#ifndef SORTINGBOT_HPP_INCLUDED
#define SORTINGBOT_HPP_INCLUDED

class sortingBot: public Robot{
    public:
        sortingBot(int x, int y, std::string name, int health_points, int threadNum);
        virtual ~sortingBot();

        void extract(Mine& m, const int x, const int y) override;


    protected:

    private:

};

#endif // SORTINGBOT_HPP_INCLUDED
