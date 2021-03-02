#include <iostream>
#include <BigFloat.hpp>

using namespace std;

int main() {
    BigFloat bigFloatas1("2213124.015321");
    BigFloat bigFloatas2("-0056.05");
    cout << bigFloatas1 * bigFloatas2 << endl;
    BigFloat bigFloatas3("-43212132.0");
    BigFloat bigFloatas4("51252216.05012421432");
    cout << bigFloatas4 * bigFloatas3 << endl;
    return 0;
}
