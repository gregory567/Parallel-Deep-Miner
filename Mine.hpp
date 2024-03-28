#ifndef MINE_HPP_INCLUDED
#define MINE_HPP_INCLUDED

using std::array;

class Mine{
    public:
        Mine();
        ~Mine();

        // functions for initializing, printing and rearranging the mine and calculating the sum of the fields
        void init_mine();
        void print_mine();
        void rearrange_mine();
        int sum_mine_values() const;

        // block and tunnel counter functions for making orientation easier
        int get_block_counter() const;
        void increment_block_counter();
        void reset_block_counter();

        int get_tunnel_counter() const;
        void increment_tunnel_counter();
        void reset_tunnel_counter();

        // functions for finding and removing fields
        int get_field(const int x, const int y, const int z) const;
        void remove_field(const int x, const int y, const int z);

        // functions for finding and rearranging tunnels
        array<int, 10>& get_tunnel(const int x, const int y);
        void sort_tunnel(array<int, 10>& tunnel);
        void rsort_tunnel(array<int, 10>& tunnel);
        void shuffle_tunnel(array<int, 10>& tunnel);

        // functions for finding special effects
        int special_effect(const int x, const int y);
        int special_effect_index(const int x, const int y);

        // function for finding tunnel with the lowest entry value
        std::pair<int, int> find_lowest_tunnel() const;

    protected:

    private:
        array<array<array<int, 10>, 5>, 5> mine;
        int block_counter;
        int tunnel_counter;

};

#endif // MINE_HPP_INCLUDED
