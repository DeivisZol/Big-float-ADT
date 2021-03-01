#include <iostream>
#include <BigFloat.hpp>

using namespace std;

int main() {
    BigFloat bigFloatas1("25.04");
    BigFloat bigFloatas2("22.05");
    cout << (bigFloatas1 + bigFloatas2) << endl;
    return 0;
}
