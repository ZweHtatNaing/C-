// 07_2d_vectors.cpp
// Topic: 2D Vectors (vector of vectors)
//        Creation, access, modification, ragged grids, common patterns

#include <iostream>
#include <vector>
#include <iomanip>   // for setw
using namespace std;

// Helper: print a 2D vector as a grid
void print2D(const string& label, const vector<vector<int>>& grid) {
    cout << label << ":\n";
    for (const auto& row : grid) {
        for (int val : row) cout << setw(4) << val;
        cout << "\n";
    }
}

int main() {
    // =====================================================================
    // CREATING 2D VECTORS
    // =====================================================================

    // --- 1. Initialiser list ---
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    print2D("Initialiser list", matrix);

    // --- 2. Construct with known dimensions (rows x cols), fill with 0 ---
    int rows = 4, cols = 5;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    print2D("\nZero-filled 4x5", grid);

    // --- 3. Construct with known dimensions, fill with custom value ---
    vector<vector<int>> filled(3, vector<int>(3, 7));
    print2D("\nFilled 3x3 with 7", filled);

    // =====================================================================
    // ACCESSING ELEMENTS
    // =====================================================================

    // --- 4. Row-column access: [row][col] ---
    // matrix[row] returns a reference to the inner vector (one row).
    // matrix[row][col] then accesses the element within that row.
    cout << "\nmatrix[1][2] = " << matrix[1][2] << endl;  // 6
    cout << "matrix[0][0] = " << matrix[0][0] << endl;  // 1

    // --- 5. Safe access with at() ---
    cout << "matrix.at(2).at(1) = " << matrix.at(2).at(1) << endl;  // 8

    // --- 6. Number of rows and columns ---
    cout << "\nRows    : " << matrix.size()    << endl;  // 3
    cout << "Cols[0] : " << matrix[0].size() << endl;  // 3  (row 0 has 3 cols)

    // =====================================================================
    // MODIFYING ELEMENTS
    // =====================================================================

    // --- 7. Direct assignment ---
    grid[1][2] = 99;
    cout << "\ngrid[1][2] after assignment: " << grid[1][2] << endl;

    // --- 8. Fill grid with row*cols + col values ---
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            grid[r][c] = r * cols + c;
    print2D("\nFilled 4x5 grid", grid);

    // =====================================================================
    // ADDING AND REMOVING ROWS / COLUMNS
    // =====================================================================

    // --- 9. Add a new row with push_back ---
    vector<int> newRow = {10, 11, 12};
    matrix.push_back(newRow);
    print2D("\nAfter push_back new row", matrix);

    // --- 10. Remove the last row with pop_back ---
    matrix.pop_back();
    print2D("After pop_back", matrix);

    // --- 11. Add a column to every row ---
    for (auto& row : matrix)
        row.push_back(0);  // append 0 to each row
    print2D("After adding a column", matrix);

    // --- 12. Remove a column from every row ---
    for (auto& row : matrix)
        row.pop_back();
    print2D("After removing a column", matrix);

    // =====================================================================
    // RAGGED (JAGGED) VECTORS
    // Each row can have a DIFFERENT number of columns.
    // =====================================================================

    // --- 13. Build a triangular grid ---
    vector<vector<int>> triangle(5);
    for (int r = 0; r < 5; r++) {
        triangle[r].resize(r + 1);    // row r has r+1 elements
        for (int c = 0; c <= r; c++)
            triangle[r][c] = r * (r + 1) / 2 + c + 1;  // sequential numbers
    }
    cout << "\nTriangular (ragged) grid:\n";
    for (const auto& row : triangle) {
        for (int val : row) cout << setw(3) << val;
        cout << "\n";
    }

    // =====================================================================
    // COMMON PATTERNS
    // =====================================================================

    // --- 14. Transpose a matrix ---
    vector<vector<int>> src = {{1,2,3},{4,5,6}};  // 2 rows x 3 cols
    int srcR = src.size(), srcC = src[0].size();
    vector<vector<int>> transposed(srcC, vector<int>(srcR));
    for (int r = 0; r < srcR; r++)
        for (int c = 0; c < srcC; c++)
            transposed[c][r] = src[r][c];
    print2D("\nOriginal 2x3", src);
    print2D("Transposed 3x2", transposed);

    // --- 15. Row sums ---
    vector<vector<int>> m = {{1,2,3},{4,5,6},{7,8,9}};
    cout << "\nRow sums:\n";
    for (int r = 0; r < (int)m.size(); r++) {
        int sum = 0;
        for (int val : m[r]) sum += val;
        cout << "  row " << r << " sum = " << sum << "\n";
    }

    // --- 16. Pass a 2D vector to a function ---
    // Always pass by const reference to avoid copying.
    auto sumAll = [](const vector<vector<int>>& g) {
        int total = 0;
        for (const auto& row : g)
            for (int v : row) total += v;
        return total;
    };
    cout << "\nTotal sum of m: " << sumAll(m) << endl;  // 45

    return 0;
}
