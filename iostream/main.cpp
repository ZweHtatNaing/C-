#include <iostream>
#include <fstream>   // for reading files (ifstream)
#include <sstream>   // for splitting CSV lines (stringstream)
#include <string>
#include <vector>
#include <map>       // for mapping each filename to its own vector
using namespace std;

// ─────────────────────────────────────────────
// FUNCTION 2: readCSV
//   Reads a single CSV file row by row.
//   Splits each row by comma and stores fields into a vector<string>.
//   Returns all rows as vector<vector<string>>.
// ─────────────────────────────────────────────
vector<vector<string>> readCSV(const string& fileName) {
    vector<vector<string>> rows; // holds all rows for this file

    ifstream file(fileName); // open the CSV file

    if (!file.is_open()) {
        cerr << "Warning: cannot open " << fileName << " — skipping." << endl;
        return rows; // return empty if file not found
    }

    string line;
    while (getline(file, line)) { // read one row at a time
        if (line.empty()) continue; // skip blank lines

        vector<string> row;     // holds the individual fields of this row
        stringstream ss(line);  // wrap the line in a stringstream for splitting
        string field;

        while (getline(ss, field, ',')) { // split by comma
            row.push_back(field);         // add each field to the row vector
        }

        rows.push_back(row); // add the completed row to this file's rows
    }

    file.close(); // always close the file when done
    return rows;
}

// ─────────────────────────────────────────────
// FUNCTION 1: readDataSources
//   Reads data_source.txt line by line.
//   For each CSV filename found, directly calls readCSV()
//   and stores the result in a map.
//   Returns a map: filename -> vector of rows.
// ─────────────────────────────────────────────
map<string, vector<vector<string>>> readDataSources(const string& sourceFile) {
    map<string, vector<vector<string>>> allData; // will hold data from all CSV files

    ifstream file(sourceFile); // open data_source.txt

    if (!file.is_open()) {
        cerr << "Error: cannot open " << sourceFile << endl;
        return allData; // return empty map if file not found
    }

    string line;
    while (getline(file, line)) {  // read one CSV filename at a time
        if (line.empty()) continue; // skip blank lines

        // Directly call readCSV for this filename — no intermediate vector
        allData[line] = readCSV(line);
    }

    file.close(); // close data_source.txt when done
    return allData;
}

// ─────────────────────────────────────────────
// Helper: prints all data in a readable format
// ─────────────────────────────────────────────
void printData(const map<string, vector<vector<string>>>& allData) {
    for (const auto& entry : allData) {
        const string& fileName             = entry.first;  // CSV filename
        const vector<vector<string>>& rows = entry.second; // its rows

        cout << "\n[ " << fileName << " ]" << endl;

        for (size_t i = 0; i < rows.size(); i++) {
            cout << (i == 0 ? "  Header: " : "  Row " + to_string(i) + ": ");

            for (size_t j = 0; j < rows[i].size(); j++) {
                cout << rows[i][j];
                if (j < rows[i].size() - 1) cout << " | ";
            }
            cout << endl;
        }
    }
}

// ─────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────
int main() {
    // readDataSources reads data_source.txt and internally calls readCSV for each file
    map<string, vector<vector<string>>> allData = readDataSources("data_source.txt");

    cout << "Loaded " << allData.size() << " file(s)." << endl;

    printData(allData);

    return 0;
}
