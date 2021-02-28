#include <iostream>
#include <BigFloat.hpp>

using namespace std;

int main(){
    BigFloat bigFloatas1("-10.0");
    BigFloat bigFloatas2("-10.1");
    cout << (bigFloatas1 + bigFloatas2) << endl;
    return 0;
}
