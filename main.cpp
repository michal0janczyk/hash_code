
#include<iostream>
#include<vector>
#include<cassert>
#include "boost/graph/graph_traits.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

//using namespace boost;


struct Ride {
    int a;
    int b;
    int x;
    int y;
    int s;
    int f;

    void print() {
        std::cout << "a: " << a << '\n';
        std::cout << "b: " << b << '\n';
        std::cout << "x: " << x << '\n';
        std::cout << "y: " << y << '\n';
        std::cout << "s: " << s << '\n';
        std::cout << "f: " << f << '\n';
    }
};


struct Vehicle {
    int x;
    int y;
    std::vector<Ride> history;
    Vehicle() : x(0), y(0) {}

};


int main() {
    int r, c, f, n, b, t;

    std::vector<Ride> rides;

    std::cin >> r >> c >> f >> n >> b >> t;
    std::cin.ignore();
    for (int i{0}; i < n; ++i) {
        Ride ride;
        std::cin >> ride.a >> ride.b >> ride.x >> ride.y >> ride.s >> ride.f;
        std::cin.ignore();
//        ride.print();
        rides.emplace_back(ride);
    }

	return 0;
}