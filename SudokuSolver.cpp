#include <iostream>

using namespace std;

const int N = 9;

bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if we find the same num in the similar row, we haven't placed the num yet.
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;

    // Check if we find the same num in the similar column, we haven't placed the num yet.
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // Check if we find the same num in the particular 3x3 matrix, we haven't placed the num yet.
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool solveSudoku(int grid[N][N], int row, int col) {
    // Check if we have reached 8th row and 9th column (0 indexed matrix)
    if (row == N - 1 && col == N)
        return true;

    // Check if column value becomes 9 then the next row and column starts from 0
    if (col == N) {
        row++;
        col = 0;
    }

    // Check if the current position of the grid already contains value greater than 0, then iterate for next column
    if (grid[row][col] > 0)
        return solveSudoku(grid, row, col + 1);

    // Iterate for 1 to 9 to fill the grid
    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid, row, col + 1))
                return true;
            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    int grid[N][N];
    cout << "Enter the Sudoku grid (0 for empty cells):" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> grid[i][j];

    if (solveSudoku(grid, 0, 0)) {
        cout << "Solved Sudoku:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << grid[i][j] << " ";
            cout << endl;
        }
    } else {
        cout << "No solution exists." << endl;
    }
    return 0;
}
