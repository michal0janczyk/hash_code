#include<iostream>
#include<vector>
#include<cassert>

using namespace std;

int R, C, L, H;
char** pizza;

bool** taken;

class Slice;
class Solution;


void clearTaken(){
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			taken[i][j] = false;
		}
	}
}

class Slice {

public:

	Slice() {};
	Slice(int r1, int c1, int r2, int c2): _r1(r1), _c1(c1), _r2(r2), _c2(c2){}

	bool canExtendRight(){

		if (_c2 + 1 >= C) {
			return false;
		}
		
		++_c2;
		bool res = !isTooBig();
		if (res) {
			for (int i = _r1; i <= _r2; ++i) {
				if (taken[i][_c2]) {
					res = false;
					break;
				}
			}
		}
		--_c2;
		return res;
	}

	bool canExtendDown() {

		if (_r2 + 1 >= R) {
			return false;
		}

		++_r2;
		bool res = !isTooBig();
		if (res) {
			for (int i = _c1; i <= _c2; ++i) {
				if (taken[_r2][i]) {
					res = false;
					break;
				}
			}
		}
		--_r2;
		return res;
	}

	bool isTooBig() {
		if (getArea() <= H) {
			return false;
		}
		return true;
	}

	bool isGood() {
		
		/*bool isT = false;
		bool isM = false;*/

		int counterT = 0;
		int counterM = 0;

		for (int i = _r1; i <= _r2; ++i) {
			for (int j = _c1; j <= _c2; ++j) {
				if (pizza[i][j] == 'T') {
					//isT = true;
					++counterT;
				}
				else if (pizza[i][j] == 'M') {
					//isM = true;
					++counterM;
				}
				else {
					assert(false);
				}

				if (counterT >= L && counterM >= L) {
					return true;
				}
			}
		}
		return false;
	}
	
	void extendRight() {
		++_c2;
	}

	void extendDown() {
		++_r2;
	}

	int getArea() {
		return (_r2 - _r1 + 1) * (_c2 - _c1 + 1);
	}

	int _r1;
	int _c1;
	int _r2;
	int _c2;
};

class Solution {
public:
	void addSlice(Slice& slice) {
		slices.push_back(slice);

		for (int i = slice._r1; i <= slice._r2; ++i) {
			for (int j = slice._c1; j <= slice._c2; ++j) {
				taken[i][j] = true;
			}
		}
		score += slice.getArea();
	}

	void outputResult() {
		cout << slices.size() << endl;
		for (auto& slice : slices) {
			cout << slice._r1 << " " << slice._c1 << " " << slice._r2 << " " << slice._c2 << endl;
		}
	}

	vector<Slice> slices;
	int score = 0;
};


bool findNextSlice(int r, int c, Slice& slice) {

	for (int i = r; i < R; ++i) {
		for (int j = 0; j < C; ++j) {

			if (i == r && j < c) {
				continue;
			}

			if ((i != r || j != c) && taken[i][j] == false) {
				slice = Slice(i, j, i, j);
				return true;
			}
		}
	}
	return false;
}

//Slice currentSlice;

Solution currentSolution;
Solution bestSolution;

bool preferRight = true;
int backTrakccounter = 0;

bool visitSquare(Slice& slice) {

	if (preferRight) {
		if (slice.canExtendRight()) {
			slice.extendRight();
			visitSquare(slice);
			//to change
			return true;
		}
		if (slice.canExtendDown()) {
			slice.extendDown();
			visitSquare(slice);
			//to change
			return true;
		}
	}
	else {
		if (slice.canExtendDown()) {
			slice.extendDown();
			visitSquare(slice);
			//to change
			return true;
		}
		if (slice.canExtendRight()) {
			slice.extendRight();
			visitSquare(slice);

			//to change
			return true;
		}
	}

	//can not extend
	if (slice.isGood()) {
		currentSolution.addSlice(slice);

		// find next slice
		Slice newSlice;
		if (!findNextSlice(slice._r1, slice._c2, newSlice)) {
			return false;
		}
		visitSquare(newSlice);
	}
	else {

		// get rid of current slice
		// create new slice next to previous one
		++backTrakccounter;

		if (backTrakccounter % 2 == 0) { // already tried two times, go on
			Slice newSlice;
			if (!findNextSlice(slice._r1, slice._c1, newSlice)) {
				return false;
			}
			visitSquare(newSlice);

		}
		else { //one try, lets change somthing and ry again
			preferRight = !preferRight;
			visitSquare(slice);
		}
	
	}
	return true;
}


int main() {

	
	cin >> R >> C >> L >> H;

	//cout << R << C << L << H;

	// load file
	pizza = new char*[R];
	for (int i = 0; i < R; ++i) {
		pizza[i] = new char[C];
	}

	taken = new bool*[R];
	for (int i = 0; i < R; ++i) {
		taken[i] = new bool[C];
	}

	for (int i = 0; i < R; ++i) {
		cin >> pizza[i];
	}

	clearTaken();


	/// show PIZZA!
	//cout << endl;
	//cout << endl;
	//for (int i = 0; i < R; ++i) {
	//	for (int j = 0; j < C; ++j) {
	//		cout << pizza[i][j];
	//	}
	//	cout << endl;
	//}


	// do magic!

	//for (int i = 0; i < R; ++i) {

	//	for (int j = 0; j < C; ++j) {

			visitSquare(Slice(0, 0, 0, 0));

			if (currentSolution.score > bestSolution.score) {
				bestSolution = currentSolution;
			}

			currentSolution = Solution();
		//}
	//}

	cout << "score: " << bestSolution.score << endl;
	cout << "ratio: " << (float)bestSolution.score / (R*C) << endl << endl;

	bestSolution.outputResult();

	return 0;
}