#ifndef COMBOBOT_HPP_INCLUDED
#define COMBOBOT_HPP_INCLUDED

class comboBot: public Robot{
    public:
        comboBot(int x, int y, std::string name, int health_points, int threadNum);
        virtual ~comboBot();

        void extract(Mine& m, const int x, const int y) override;


    protected:

    private:

};

#endif // COMBOBOT_HPP_INCLUDED
