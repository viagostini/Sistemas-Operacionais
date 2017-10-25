#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int total, virt, s, p;
    cout << "hello";
    ifstream file("trace.txt");
    string line, word;

    file >> total >> virt >> s >> p;

    while (getline(file, line)) {
        vector<string> tokens;
        int t0, tf, b, pi, ti;
        string nome;
        istringstream iss(line);

        while (iss >> word)
            tokens.push_back(word);

        t0 = stoi(tokens[0]);
        tf = stoi(tokens[1]);
        nome = tokens[2];
        b = stoi(tokens[3]);


        for (int i = 4; i < tokens.size(); i += 2) {
            pi = stoi(tokens[i]);
            ti = stoi(tokens[i+1]);
        }
    }
}
