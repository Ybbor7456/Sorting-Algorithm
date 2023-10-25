#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>


using namespace std;
using namespace chrono;

vector<int> selection_sort(vector<int> input) {
    vector<int> sorted;

    int input_size = input.size();
    int smallest_index;
    for (int i = 0; i < input_size; i++) {
        int jMin = 0;
        smallest_index = 0;
        for (int j = 1; j < input.size(); j++) {

            if (input[j] < jMin) {
                jMin = input[j];
                smallest_index = j;
            }
        }

        sorted.push_back(jMin);
        input.erase(input.begin() + smallest_index);
    }

    return sorted;
}


vector<int> merge_selection_sort(vector<int> v1, vector<int> v2) {
    vector<int> v3;
    int i = 0;
    int j = 0;

    while ((i < v1.size()) && (j < v2.size())) {
        if (v1[i] <= v2[j]) {
            v3.push_back(v1[i]);
            i++;
        }
        else {
            v3.push_back(v2[j]);
            j++;
        }
    }
    while (i < v1.size()) {
        v3.push_back(v1[i]);
        i++;
    }
    while (j < v2.size()) {
        v3.push_back(v2[j]);
        j++;
    }
    return v3;
}


int main() {

    vector<int> input;

    std::ifstream ifs("random_numbers.txt", std::ifstream::in);

    string myText;

    while (getline(ifs, myText)) {
        input.push_back(stoi(myText));
    }

    vector<int> v1(input.begin(), input.begin() + 25000);
    vector<int> v2(input.begin() + 25000, input.end());
    vector<int> v3;

    auto start = high_resolution_clock::now();
    vector<int> output = selection_sort(input);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(end - start); 
    cout << "Number of seconds for selection sort: " << duration.count() << endl;

    start = high_resolution_clock::now();
    v1 = selection_sort(v1);
    v2 = selection_sort(v2);
    v3 = merge_selection_sort(v1, v2);
    end = high_resolution_clock::now();

    duration = duration_cast<seconds>(end - start); 
    cout << "Number of seconds for merged selection sort: " << duration.count() << endl;

    ifs.close();

    return 0;
}
