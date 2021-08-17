#include <iostream>
#include <new>

typedef bool (*FunctPtr) (const unsigned, const unsigned);

const short moveX[] = { 0,1,0,-1 };
const short moveY[] = { 1,0,-1,0 };
const short movesNum = sizeof(moveX) / sizeof(short);

const char goalSymbow = 'X';
const char wallSymbow = '1';
const char freePathSymbow = '0';

bool isBigger(const unsigned first, const unsigned second) {
	return first > second;
}

bool isSmaller(const unsigned first, const unsigned second) {
	return first < second;
}

void copyAns(int*& ansPath, int*& curPath, const unsigned size) {
	delete[] ansPath;
	ansPath = new (std::nothrow) int[size];
	if (!ansPath) {
		std::cout << "Error allocating memory for answer\n";
		std::cout << "Found path with lenght: " << size << std::endl;
		throw - 1;
	}
	for (unsigned i = 0; i < size; ++i) {
		ansPath[i] = curPath[i];
	}
}

void pathRec(char**& maze,const unsigned size, const unsigned curLen, const int curX, const int curY,
	unsigned& curAnswer, const FunctPtr checker,int *& curPath, int*& ansPath) {
	
	if (maze[curX][curY] == goalSymbow) {
		if (curAnswer==0 || checker(curLen, curAnswer)) {
			copyAns(ansPath, curPath, curLen);
			curAnswer = curLen;
		}
		return;
	}
	//optimization for min
	//if (curAnswer!=0 && !checker(curLen, curAnswer)) {
	//	return; //no use , even if we get there , we wont find it as ans
	//}

	if (maze[curX][curY] == wallSymbow || maze[curX][curY]==0) {
		return;
	}
	maze[curX][curY] = 0;
	curPath[curLen] = size * curX + curY;

	for (short i = 0; i < movesNum; ++i) {
		if (curX + moveX[i] >= 0 && curX + moveX[i] < size
			&& curY + moveY[i] >= 0 && curY + moveY[i] < size) 
		{
			pathRec(maze, size, curLen+1, curX + moveX[i], curY + moveY[i], curAnswer, checker, curPath, ansPath);
		}
	}
	curPath[curLen] = -1;
	maze[curX][curY] = '0';
}

void printAns(int*& ans, const unsigned size,const unsigned mazeSize) {
	for (unsigned i = 0; i < size; ++i) {
		std::cout << "(" << ans[i] / mazeSize << "," << ans[i] % mazeSize << ") ";
	}
	
}


void getInput(unsigned& x,unsigned& y,unsigned& size, char**& maze) {
	
	std::cout << "Size:\n";
	std::cin >> size;
	std::cout << "\nMaze:\n(Use 0 for empty cell, 1 for wall , X for goal!)\n";

	maze = new (std::nothrow) char* [size];
	if (!maze) {
		std::cout << "Couldnt allocate memory.";
		throw - 1;
	}
	for (unsigned i = 0; i < size; ++i) {
		maze[i] = new (std::nothrow) char[size];
		if (!maze[i]) {
			for (unsigned j = 0; j < i; ++j) {
				delete[] maze[j];
			}
			delete[] maze;
			std::cout<< "Couldnt allocate memory.";
			throw - 1;
		}
		for (unsigned j = 0; j < size; ++j) {
			std::cin >> maze[i][j];
		}
	}
	std::cout << "Start pos x and y:\n";
	std::cin >> x;
	std::cin >> y;
}

bool allocate(int*& arr, const unsigned size) {
	arr = new (std::nothrow) int[size];
	return arr;
}

void deleteMaze(char**& maze, const unsigned size)
{
	for (unsigned i = 0; i < size; ++i) {
		delete[] maze[i];
	}
	delete[] maze;
	maze = nullptr;
}


void nullify(int*& arr, const unsigned size) {
	for (unsigned i = 0; i < size; ++i) {
		arr[i] = -1;
	}
}

int main() {
	unsigned startX = 0;
	unsigned startY = 0;
	char** maze = nullptr;
	unsigned size = 0;
	int* curPath = nullptr;
	int* curAnswer = nullptr;
	unsigned answer = 0;
	//
	try {
		getInput(startX, startY, size, maze);
	}
	catch (...) {
		return -1;
	}

	if (!allocate(curPath, size*size)) {
		deleteMaze(maze, size);
		std::cout << "Couldnt allocate enough memory.";
		return -1;
	}
	
	if (startX < size && startY < size && maze[startX][startY] == goalSymbow) {
		std::cout << "Shortest and Longest are equal to 0 \n";
	}
	else {
		//
		nullify(curPath, size * size);
		try {
			pathRec(maze, size, 0, startX, startY, answer, isSmaller, curPath, curAnswer);
		}
		catch (...) {//we couldnt allocate for answer and we print the last we found
			printAns(curPath, answer, size);
		}
		std::cout << "\nShortest path with len:" << answer - 1 << std::endl;
		printAns(curAnswer, answer, size);
		answer = 0;
		//
		nullify(curPath, size * size);
		try {
			pathRec(maze, size, 0, startX, startY, answer, isBigger, curPath, curAnswer);
		}catch (...) {//we couldnt allocate for answer and we print the last we found
			printAns(curPath, answer, size);
		}
		std::cout << "\nLongest path with len:" << answer - 1 << std::endl;
		printAns(curAnswer, answer, size);
		std::cout << "\n";
		//
	}
	deleteMaze(maze, size);
	delete[] curPath;
	delete[] curAnswer;
	return 0;
}




/*
const char goalSymbow = 'X';
const char wallSymbow = '1';
const char freePathSymbow = '0';

Tests:

6
000100
001100
000000
010010
01000X
000000
0 0


3
000
001
00X
0 0

*/
