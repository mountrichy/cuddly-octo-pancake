#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

class Grocer {
public:
    int grocerMenu();   // Function to display the grocer menu and handle user interactions
    int openFile();     // Function to read input from a file and populate the itemFreq map
    int choice = 0;     // User's menu choice

private:
    string item;        // Temporary storage for reading items from file
    int freq = 0;       // Temporary storage for item frequency
    map<string, int> itemFreq;  // Map to store item frequencies
};

int Grocer::grocerMenu() {
    do {
        cout << "---- Corner Grocer Application ----" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Print item frequencies" << endl;
        cout << "3. Print item frequencies in histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string searchItem;
            cout << "Enter item name: ";
            cin >> searchItem;

            if (itemFreq.count(searchItem) > 0) {
                cout << searchItem << " - " << itemFreq[searchItem] << endl;
            }
            else {
                cout << "Item not found!" << endl;
            }
            break;
        }
        case 2: {
            // Print item frequencies
            for (auto&& item : itemFreq) {
                cout << item.first << " - " << item.second << endl;
            }
            break;
        }
        case 3: {
            // Print item frequencies in histogram form
            for (auto&& item : itemFreq) {
                cout << item.first << " ";
                for (int i = 1; i <= item.second; i++) {
                    cout << "*";
                }
                cout << endl;
            }
            break;
        }
        case 4: {
            cout << "Exiting program..." << endl;
            break;
        }
        default: {
            cout << "Invalid choice! Try Again." << endl;
        }
        }
    } while (choice != 4);

    ofstream outFS; // Output file stream

    // Open file for writing
    outFS.open("frequency.dat");

    if (!outFS.is_open()) {
        cout << "Could not open file frequency.dat." << endl;
        return 1;
    }
    // Write item frequencies to file
    for (auto&& item : itemFreq) {
        outFS << item.first << " - " << item.second << endl;
    }
    // Close file
    outFS.close();

    return 0;
}

int Grocer::openFile() {
    ifstream inputFile("CS210_Project_Three_Input_File.txt");
    if (!inputFile) {
        cout << "Error opening input file!" << endl;
        return 1;
    }

    string line, word;
    while (getline(inputFile, line)) {
        // Process each line
        istringstream iss(line);
        while (iss >> word) {
            // Process each word and update its frequency in the map
            itemFreq[word]++;
        }
    }

    inputFile.close(); // Close the input file

    return 0;
}

int main() {
    // Create an object of Grocer as g
    Grocer g;

    // Read input from file and populate the itemFreq map
    g.openFile();

    // Display the grocer menu and handle user interactions
    g.grocerMenu();

    return 0;
}
