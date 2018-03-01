
#include<iostream>
#include<vector>
#include<cassert>
#include "boost/graph/graph_traits.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

//using namespace boost;

using namespace std;


struct Ride {
    enum RIDE_STATUS {
        NOT_TAKEN,
        PENDING,
        ACTIVE,
        FINISHED
    } ride_status;

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

    Ride() : ride_status(NOT_TAKEN) {}
};


struct Vehicle {
    int m_x;
    int m_y;
    Ride current_ride;
    bool is_busy;
    std::vector<Ride> history;
    Vehicle() : m_x(0), m_y(0), is_busy(false) {}

    void update() {
        switch (current_ride.ride_status) {
            case Ride::PENDING:
                go_to(current_ride.start_row, current_ride.start_column);
                break;
            case Ride::ACTIVE:
                go_to(current_ride.finish_row, current_ride.finish_column);
                break;
            default:
                throw 42;
        }
    }

    bool go_to(int x, int y) {
        if (x != m_x) {
            if (x < m_x) {
                --m_x;
            } else {
                ++m_x;
            }
        } else if (y != m_y) {
            if (y < m_y) {
                --m_y;
            } else {
                ++m_y;
            }
        } else {
            return true;
        }

        return false;
    }

    void assign_ride(const Ride& ride) {
        current_ride = ride;
        is_busy = true;
    }

    void finish_ride() {
        history.push_back(current_ride);
        is_busy = false;
    }

};

int calculate_distance(int start_x, int start_y, int end_x, int end_y) {
    return std::abs(start_x - end_x) + std::abs(start_y - end_y);
}


vector<Vehicle> g_Vechicles;


void Update(int t) {

	for (auto& vehicle : g_Vechicles) {
		vehicle.update();
	}

}



int main() {
    int rows, columns, no_of_vehicles, no_of_rides, bonus, max_steps;

    std::vector<Ride> rides;

    std::cin >> rows >> columns >> no_of_vehicles >> no_of_rides >> bonus >> max_steps;
    std::cin.ignore();
    for (int i{0}; i < no_of_rides; ++i) {
        Ride ride;
        std::cin >> ride.start_row >> ride.start_column >> ride.finish_row >> ride.finish_column >> ride.earliest_start >> ride.latest_finish;
        std::cin.ignore();
        ride.print();
        rides.emplace_back(ride);
    }


	// Update
    for (int step{0}; step < max_steps; ++max_steps) {

		Update(step);






    }

	return 0;
}