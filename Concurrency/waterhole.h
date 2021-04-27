#ifndef WATERHOLE
#define WATERHOLE

#include <condition_variable>
#include <mutex>
#include <atomic>

using namespace std;

class WaterManager {
    private:
        mutex threadlock;
        atomic_int gnusInside;
        atomic_int hyenasInside;
    public:
        condition_variable CONDITIONVAR;
        WaterManager() : gnusInside(0), hyenasInside(0) {};
        const int nrGnus();
        const int nrHyenas();
        void hyenaEnters();
        void gnuEnters();
        void hyenaLeaves();
        void gnuLeaves();
};

class Gnu {
    public:
        int id;
        Gnu(int x) : id(x) {};
        void operator ()(WaterManager&);
};

ostream& operator <<(ostream&, const Gnu&);

void gnu(WaterManager& wm);
void hyena(WaterManager& wm);

int main(int argc, char* argv[]);


#endif // WATERHOLE