#include <iostream>
#include <string>
using namespace std;

int main() {
    double x = 0;
    double fac = 0;
    double n = 0;

    cin >> n;
    fac = 1;
    x = 1;
    if (x <= n) {
    fac = fac * x;
    x = x + 1;
    } else {
    cout << fac << endl;
    return 0;
    }
    return 0;
}
