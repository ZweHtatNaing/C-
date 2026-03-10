#include <iostream>
#include <fstream>   // for reading files (ifstream)
#include <sstream>   // for splitting CSV lines (stringstream)
#include <string>
#include <vector>
#include <map>       // for mapping each filename to its own vector
using namespace std;

// ─────────────────────────────────────────────
// FUNCTION 1: readDataSources
//   Reads data_source.txt line by line.
//   Each line is a CSV filename (e.g. "students.csv").
//   Returns a vector of those filenames.
// ─────────────────────────────────────────────
vector<string> readDataSources(const string& sourceFile) {
    vector<string> fileNames; // will hold the list of CSV filenames

    ifstream file(sourceFile); // open the data_source.txt file for reading

    if (!file.is_open()) {
        cerr << "Error: cannot open " << sourceFile << endl;
        return fileNames; // return empty vector if file not found
    }

    string line;
    while (getline(file, line)) {      // read one line at a time
        if (!line.empty()) {           // skip any blank lines
            fileNames.push_back(line); // add the filename to the vector
        }
    }

    file.close(); // always close the file when done
    return fileNames;
}

// ─────────────────────────────────────────────
// FUNCTION 2: readCSVFiles
//   Takes the list of CSV filenames from Function 1.
//   Reads each CSV file row by row, splits each row by comma,
//   and stores each row (as a vector<string>) into a
//   per-file vector.
//   Returns a map: filename -> vector of rows (each row is a vector of fields).
// ─────────────────────────────────────────────
map<string, vector<vector<string>>> readCSVFiles(const vector<string>& fileNames) {
    // map: key = filename, value = all rows of that file
    map<string, vector<vector<string>>> allData;

    for (const string& fileName : fileNames) { // loop through each CSV filename
        ifstream file(fileName);               // open the CSV file

        if (!file.is_open()) {
            cerr << "Warning: cannot open " << fileName << " — skipping." << endl;
            continue; // skip this file and move to the next one
        }

        vector<vector<string>> rows; // holds all rows for this file
        string line;

        while (getline(file, line)) { // read one row at a time
            if (line.empty()) continue; // skip blank lines

            vector<string> row;          // holds the individual fields of this row
            stringstream ss(line);       // wrap the line in a stringstream for splitting
            string field;

            while (getline(ss, field, ',')) { // split by comma
                row.push_back(field);         // add each field to the row vector
            }

            rows.push_back(row); // add the completed row to this file's rows
        }

        file.close();              // close the file when done reading
        allData[fileName] = rows;  // store all rows under the filename key
    }

    return allData;
}

// ─────────────────────────────────────────────
// Helper: prints all data in a readable format
// ─────────────────────────────────────────────
void printData(const map<string, vector<vector<string>>>& allData) {
    for (const auto& entry : allData) {          // loop through each file's data
        const string& fileName               = entry.first;  // CSV filename
        const vector<vector<string>>& rows   = entry.second; // its rows

        cout << "\n[ " << fileName << " ]" << endl;

        for (size_t i = 0; i < rows.size(); i++) {
            if (i == 0) {
                // First row is the header
                cout << "  Header: ";
            } else {
                cout << "  Row " << i << ": ";
            }

            for (size_t j = 0; j < rows[i].size(); j++) {
                cout << rows[i][j];
                if (j < rows[i].size() - 1) cout << " | "; // separate fields
            }
            cout << endl;
        }
    }
}

// ─────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────
int main() {
    // Step 1: read data_source.txt to get the list of CSV filenames
    vector<string> csvFiles = readDataSources("data_source.txt");

    cout << "Found " << csvFiles.size() << " data source(s) in data_source.txt:" << endl;
    for (const string& f : csvFiles) {
        cout << "  - " << f << endl; // print each filename found
    }

    // Step 2: read each CSV file and load data into vectors
    map<string, vector<vector<string>>> allData = readCSVFiles(csvFiles);

    // Print all loaded data
    printData(allData);

    return 0;
}
