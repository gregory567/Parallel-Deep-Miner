#ifndef TRIPLEBOT_HPP_INCLUDED
#define TRIPLEBOT_HPP_INCLUDED

class tripleBot: public Robot{
    public:
        tripleBot(int x, int y, std::string name, int health_points, int threadNum);
        virtual ~tripleBot();

        void extract(Mine& m, const int x, const int y) override;


    protected:

    private:

};


#endif // TRIPLEBOT_HPP_INCLUDED
