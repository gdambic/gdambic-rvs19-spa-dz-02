#include <iostream>
#include <ctime>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;


class cell {
private:
	bool alive = 0;
	
public:
	int neighborCount = 0;

	void init(bool initValue){
		alive = initValue;
	}
	void generateNewStatus() {
		if (alive == 1 && (neighborCount == 2 || neighborCount == 3)) { alive = 1; }
		else if (alive == 1 && (neighborCount < 2)) { alive = 0; }
		else if (alive == 1 && (neighborCount > 3)) { alive = 0; }
		else if (alive == 0 && (neighborCount == 3)) { alive = 1; }
	}
	
	bool getstatus() {
		return alive;
	}
};


int main() {
	#define mapsize 40
	cell Grid[mapsize][mapsize];
	
	//initiate world
	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {
			Grid[i][j].init((rand() % 2) == 1 ? 1 : 0);
		}
	}
	
	while (true) {
		//display world
		system("cls");
		for (int i = 0; i < mapsize; i++) {
			for (int j = 0; j < mapsize; j++) {
				Grid[i][j].getstatus() == 1 ? cout << "# " : cout << "  ";
				//cout << Grid[i][j].neighborCount;
				Grid[i][j].neighborCount = 0;
			}
			cout << endl;
		}


		//count neighbours and set neigbour count
		for (int i = 0; i < mapsize; i++) {
			for (int j = 0; j < mapsize; j++) {

				
				//gornji susjedi
				if (i != 0) {
					if (j != 0) {
						if (Grid[i - 1][j - 1].getstatus()) { Grid[i][j].neighborCount++; }
					}
					if (j != mapsize - 1) {
						if (Grid[i - 1][j + 1].getstatus()) { Grid[i][j].neighborCount++; }
					}

					if (Grid[i - 1][j].getstatus()) { Grid[i][j].neighborCount++; }
				}
				//srednji susjedi
				if (j != 0) {
					if (Grid[i][j - 1].getstatus()) { Grid[i][j].neighborCount++; }
				}
				if (j != mapsize - 1) {
					if (Grid[i][j + 1].getstatus()) { Grid[i][j].neighborCount++; }
				}
				
				//doljnji susjedi
				if (i != mapsize - 1) {
					if (j != 0) {
						if (Grid[i + 1][j - 1].getstatus()) { Grid[i][j].neighborCount++; }
					}
					if (j != mapsize - 1) {
						if (Grid[i + 1][j + 1].getstatus()) { Grid[i][j].neighborCount++; }
					}
					if (Grid[i + 1][j].getstatus()) { Grid[i][j].neighborCount++; }
				}
			}
		}

		//generate next generation 
		for (int i = 0; i < mapsize; i++) {
			for (int j = 0; j < mapsize; j++) {
				Grid[i][j].generateNewStatus();
			}
		}

		cout << endl << endl;
		cout << "Press enter for next generation" << endl;
		string in;
		getline(cin, in);
	}



	return 0;
}