#include <cstdio>
#include <iostream>
#include <array>
#include <cstdarg>
#include <cstring>
#include <string>
#include <vector>
#include <initializer_list>

using namespace std;

// TODO: implement voltage and amperage.

class Bruch {
    public:
        float zaehler = 0;
        float nenner = 0;

        Bruch(float z) {
            zaehler = z;
            nenner = 1;
        }

        Bruch(float z, float n) {
            zaehler = z;
            nenner = n;
        }

        Bruch reziproke() {
            float zaehlerBuffer = zaehler;
            float nennerBuffer = nenner;
            zaehler = nennerBuffer;
            nenner = zaehlerBuffer;
            return Bruch(zaehler, nenner);
        }

        void mult(float m) {
            zaehler *= m;
        }

        void mult(float mz, float mn) {
            zaehler *= mz;
            nenner *= mn;
        }

        float calc() {
            return zaehler / nenner;
        }

        Bruch operator+(Bruch bruch) {
            return Bruch(this->zaehler * bruch.nenner+bruch.zaehler*this->nenner, this->nenner*bruch.nenner);
        }
        
        Bruch operator += (Bruch bruch) {
            this->zaehler = this->zaehler * bruch.nenner+bruch.zaehler*this->nenner;
            this->nenner = this->nenner*bruch.nenner;
            return Bruch(this->zaehler, this->nenner*bruch.nenner);
        }

        friend ostream& operator<<(ostream& os, Bruch& b) {
            os << b.zaehler << '/' << b.nenner;
            return os;
        }

        operator float () {
            return this->zaehler/this->nenner;
        }
};

float parallel(vector<float> list) {
    cout << "\nparallel ";

    vector<Bruch> bruch;

    // TODO: Better way?
    for (int i = 0; i < list.size(); i++) {
        cout << list.at(i) << " ";
        bruch.push_back(Bruch(1, list.at(i)));
    }

    for (int i = 1; i < bruch.size(); i++) {
        //cout << "\n\tparallel: " << bruch.at(0) << " + " << bruch.at(i) << " = ";
        bruch.at(0) += bruch.at(i);
        cout << bruch.at(0);
    }

    bruch.at(0).reziproke();
    //cout << "\n\tparallel reziproke: " << bruch.at(0);
    
    float result = bruch.at(0).zaehler/bruch.at(0).nenner;
    
    cout << " = " << result << '\n'; 
    return result;
}

float reihe(vector<float> list) {
    cout << "\nreihe ";
    float result =0;
    for (uint i = 0; i < list.size(); i++) {
        cout  << list.at(i) << " ";
        result += list.at(i);
    }
    cout << " = " << result << '\n';
    return result;
}

template <class T>
std::vector<T>& operator+=(std::vector<T>& lhs, std::initializer_list<T> l)
{
    lhs.insert(std::end(lhs), l);
    return lhs;
}

float calc(bool rei, string input) {
    int firstColon = input.find_first_of(",");
    int lastColon = input.find_last_of(",");
    
    //cout << "\ninit calc:\n\t" << input << '\n';

    if (lastColon <= 0) { return stof(input); }
    vector<float> list;
    
    while (lastColon > 0) {
        firstColon = input.find_first_of(",");
        lastColon = input.find_last_of(",");
        list.push_back(stof(input.substr(0, firstColon)));
        input = input.substr(firstColon+1, input.length()-firstColon+1);
    }
    
    return rei ? reihe(list) : parallel(list);
}

float strrecurse(bool rei, string input) {
    cout << "\n\t" << input;
    
    /*
    int start = input.find_first_of("(") +1;
    int len = input.find_last_of(")") - start;
    */
    
    int start = 0;
    int end = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '(') { start = i+1; }
        if (input[i] == ')') { end = i; break; }
    }

    int len = end - start;
    //cout << "\n\tstart " << start << " len " << len << " end " << end;
    
    if (len <= 0) { float ret = calc(rei, input); return ret; }

    string inputB = input;
    input.replace(start-2, input.substr(start, len).length()+3, to_string(strrecurse(input[start-2] == 'r' ? true : false, input.substr(start, len))));
    
    start = input.find_first_of("(") +1;
    len = input.find_last_of(")") - start;

    float ret = strrecurse(rei, input); 
    //cout << "\nreturn strrecurse";
    return ret;
}

int main(int argc, char *argv[]) {
    cout << "Running ... \n";

    string input;
    for (int i = 1; i < argc; i++) {
        input += argv[i];
    }
    

    float result = strrecurse(true, input);
    cout << "\n" << input << "\n " << result;

    cout << "\n... comleted.";
    return 0;
}