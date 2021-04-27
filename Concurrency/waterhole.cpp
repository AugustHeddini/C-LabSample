#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>
#include <functional>
#include "waterhole.h"

using namespace std;
int NR_TRIALS = 1;
unordered_map<thread::id, string> THREAD_ID;
bool trace = false;

const int WaterManager::nrGnus() {
    return gnusInside;
}

const int WaterManager::nrHyenas() {
    return hyenasInside;
}


void WaterManager::hyenaEnters() {
    unique_lock<mutex> hyenaLock(threadlock);
    CONDITIONVAR.wait(hyenaLock, [this]{ return gnusInside == 0; });
    hyenasInside++;
}

void WaterManager::gnuEnters() {
    unique_lock<mutex> gnuLock(threadlock);
    CONDITIONVAR.wait(gnuLock, [this]{ return hyenasInside == 0; });
    gnusInside++;
}

void WaterManager::hyenaLeaves() {
    hyenasInside--;
    //threadlock.lock();
    CONDITIONVAR.notify_all();
}

void WaterManager::gnuLeaves() {
    gnusInside--;
    //threadlock.lock();
    CONDITIONVAR.notify_all();
    
}

void Gnu::operator ()(WaterManager& wm) {
    int i = 0;
    while (i < NR_TRIALS) {
        this_thread::sleep_for(chrono::seconds(rand() % 6));
        if (trace) {
            //cout << THREAD_ID.find(this_thread::get_id())->second << " is thirsy." << endl;
            cout << *this << " is thirsty." << endl;
        }
        wm.gnuEnters();
        if (trace) {
            //cout << THREAD_ID.find(this_thread::get_id())->second << " is entering the waterhole.";
            cout << *this << " is entering the waterhole.";
            cout << "       Current status: Gnus inside: " << wm.nrGnus() << ", Hyenas inside: " << wm.nrHyenas() << endl;
        }
        this_thread::sleep_for(chrono::seconds(rand() % 5));
        wm.gnuLeaves();
        if (trace) {
            //cout << THREAD_ID.find(this_thread::get_id())->second << " is leaving the waterhole." << endl;
            cout << *this << " is leaving the waterhole." << endl;
        }
        i++;
    }
}

ostream& operator <<(ostream& out, const Gnu& g) {
    out << "Gnu nr " << g.id;
    return out;
}

void hyena(WaterManager& wm) {
    int i = 0;
    while (i < NR_TRIALS) {
        this_thread::sleep_for(chrono::seconds(rand() % 8));
        if (trace) {
            cout << THREAD_ID.find(this_thread::get_id())->second << " is thirsty." << endl;
        }
        wm.hyenaEnters();
        if (trace) {
            cout << THREAD_ID.find(this_thread::get_id())->second << " is entering the waterhole.";
            cout << "       Current status: Gnus inside: " << wm.nrGnus() << ", Hyenas inside: " << wm.nrHyenas() << endl;
        }
        this_thread::sleep_for(chrono::seconds(rand() % 3));
        wm.hyenaLeaves();
        if (trace) {
            cout << THREAD_ID.find(this_thread::get_id())->second << " is leaving the waterhole." << endl;
        }
        i++;
    }
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        if (strcmp(argv[1], "-t") == 0) {
            trace = true;
        }
    }
    int nrGnus = 4;
    int nrHyenas = 4;
    WaterManager wm;

    // Create and populate the thread vector
    vector<thread> threadvec;
    for (int i = 0; i < nrGnus; i++) {
        Gnu g = Gnu(i);
        function<void(WaterManager&)> threadfunc = g;
        threadvec.push_back(thread(threadfunc, ref(wm)));
        if (trace) {
            //THREAD_ID.insert( {threadvec.back().get_id(), g.id} );
        }
    }
    for (int i = 0; i < nrHyenas; i++) {
        threadvec.push_back(thread(hyena, ref(wm)));
        if (trace) {
            string id = "Hyena nr " + to_string(i);
            THREAD_ID.insert( {threadvec.back().get_id(), id} );
        }
    }

    // Join the threads
    for (int i = 0; i < threadvec.size(); i++) {
        if (threadvec[i].joinable()) {
            threadvec[i].join();
        }
    }

    return 1;
}