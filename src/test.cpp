#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream file;
    file.open("boarddata.txt");

        int val;
        int rowSize, colSize;
        file >> rowSize >> colSize;
        
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                file >> val;
                cout << val << " ";
            }
        }
        file.close();
}
