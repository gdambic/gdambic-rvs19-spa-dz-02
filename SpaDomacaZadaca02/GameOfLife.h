
class GameOfLife
{
public:
	void start();
private:
	static const unsigned int COLUMS = 40;
	static const unsigned int ROWS = 20;
	char trenutna[ROWS][COLUMS];
	char sljedeca[ROWS][COLUMS];


	void ploca();
	


	void cRandom();
	void prikaz();
	void sljedecaPloca();
	void kopiraj();
	int provjerisusjeda(int row, int column);
	int randumO(int max, int min);
	
};