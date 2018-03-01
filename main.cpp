
#include<iostream>
#include<vector>
#include<cassert>
#include "boost/graph/graph_traits.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

//using namespace boost;


struct Ride {
    int start_row;
    int start_column;
    int finish_row;
    int finish_column;
    int earliest_start;
    int latest_finish;

    void print() {
        std::cout << "start_row: " << start_row << '\n';
        std::cout << "start_column: " << start_column << '\n';
        std::cout << "finish_row: " << finish_row << '\n';
        std::cout << "finish_column: " << finish_column << '\n';
        std::cout << "earliest_start: " << earliest_start << '\n';
        std::cout << "latest_finish: " << latest_finish << '\n';
    }
};


struct Vehicle {
    int x;
    int y;
    std::vector<Ride> history;
    Vehicle() : x(0), y(0) {}

};


int main() {
    int rows, columns, no_of_vehicles, no_of_rides, bonus, steps;

    std::vector<Ride> rides;

    std::cin >> rows >> columns >> no_of_vehicles >> no_of_rides >> bonus >> steps;
    std::cin.ignore();
    for (int i{0}; i < no_of_rides; ++i) {
        Ride ride;
        std::cin >> ride.start_row >> ride.start_column >> ride.finish_row >> ride.finish_column >> ride.earliest_start >> ride.latest_finish;
        std::cin.ignore();
        ride.print();
        rides.emplace_back(ride);
    }

	return 0;
}