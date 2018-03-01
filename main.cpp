
#include<iostream>
#include<vector>
#include<cassert>
#include <algorithm>
#include "boost/graph/graph_traits.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

//using namespace boost;

using namespace std;


int X_RIDES;
int rows, columns, no_of_vehicles, no_of_rides, bonus, max_steps;

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
    int index;

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
    int m_index;
    int m_x;
    int m_y;
    Ride current_ride;
    bool is_busy;
    std::vector<Ride> history;
    Vehicle(int index) : m_index(index), m_x(0), m_y(0), is_busy(false) {}

    void update() {
        switch (current_ride.ride_status) {
            case Ride::PENDING:
				if (go_to(current_ride.start_row, current_ride.start_column)) {
					current_ride.ride_status = Ride::ACTIVE;
				}
                break;
            case Ride::ACTIVE:
				if (go_to(current_ride.finish_row, current_ride.finish_column)) {
					finish_ride();
				}
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
		current_ride.ride_status = Ride::PENDING;
    }

    void finish_ride() {
		current_ride.ride_status = Ride::FINISHED;
        history.push_back(current_ride);
        is_busy = false;
    }

};

int calculate_distance(int start_x, int start_y, int end_x, int end_y) {
    return std::abs(start_x - end_x) + std::abs(start_y - end_y);
}


vector<Vehicle> g_Vechicles;
std::vector<Ride> g_Rides;


struct Solution {

	vector<pair<Vehicle, Ride>> m_solutionCandidate;
	int m_score;
};



int calculateCost(Vehicle& vehicle, Ride& ride, int t) {

	int cost = 0;
	int distToTarget = calculate_distance(vehicle.m_x, vehicle.m_y, ride.start_row, ride.start_column);
	int routeDist = calculate_distance(ride.start_row, ride.start_column, ride.finish_row, ride.finish_column);

	// bonus
	if (distToTarget < ride.earliest_start - t) {
		cost += bonus;
	}

	// route cost
	if (distToTarget + routeDist < ride.latest_finish - t) {
		cost += routeDist;
	}

	return cost;
}


void Scheduler(int t){

	vector<Vehicle> freeCars;
	for (auto& v : g_Vechicles) {

		if (!v.is_busy) {
			freeCars.push_back(v);
		}
	}

//	vector<Solution> solutions;

	vector<Ride> currentRides;
	for (auto& r : g_Rides){
		if (currentRides.size() > max(X_RIDES, (int)freeCars.size())) {
			return;
		}
		if (r.earliest_start > t && r.ride_status == Ride::NOT_TAKEN) {
			currentRides.push_back(r);
		}
	}

	for (auto& car : freeCars) {

		int bestCost = 0;
		int bestCostIndex = 99999999999;

		for (int i =0; i < currentRides.size(); ++i) {

			int cost = calculateCost(car, currentRides[i], t);

			if (cost > bestCost) {
				bestCost = cost;
				bestCostIndex = i;
			}
		}

		car.assign_ride(currentRides[bestCostIndex]);
		currentRides.erase(currentRides.begin() + bestCostIndex);
	}

}


	
	




void Update(int t) {

	for (auto& vehicle : g_Vechicles) {
		vehicle.update();
	}

}

void print_results() {
    std::stringstream ss;
    for (const auto& vehicle : g_Vechicles) {
        ss << vehicle.m_index << ' ';
        for (const auto& ride : vehicle.history) {
            ss << ride.index << ' ';
        }
    }

    std::cout << ss.str() << std::endl;
}

int main() {
   

    std::cin >> rows >> columns >> no_of_vehicles >> no_of_rides >> bonus >> max_steps;
    std::cin.ignore();
    for (int i{0}; i < no_of_rides; ++i) {
        Ride ride;
        ride.index = i;
        std::cin >> ride.start_row >> ride.start_column >> ride.finish_row >> ride.finish_column >> ride.earliest_start >> ride.latest_finish;
        std::cin.ignore();
        ride.print();
		g_Rides.emplace_back(ride);
    }


	sort(g_Rides.begin(), g_Rides.end(), [](auto a, auto b) {
		return a.earliest_start < b.earliest_start;
	});

    for (int i{0}; i < no_of_vehicles ; ++i) {
        g_Vechicles.emplace_back(Vehicle(i));
    }

	// Update
    for (int step{0}; step < max_steps; ++step) {
		Scheduler(step);
		Update(step);
    }

	return 0;
}