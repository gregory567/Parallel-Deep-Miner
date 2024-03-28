#ifndef SKILLEDBOT_HPP_INCLUDED
#define SKILLEDBOT_HPP_INCLUDED

class skilledBot: public Robot{
    public:
        skilledBot(int x, int y, std::string name, int health_points, int threadNum);
        virtual ~skilledBot();

        void extract(Mine& m, const int x, const int y) override;


    protected:

    private:

};

#endif // SKILLEDBOT_HPP_INCLUDED
