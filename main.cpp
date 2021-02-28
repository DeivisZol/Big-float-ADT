#include <iostream>
#include <BigFloat.hpp>

using namespace std;

int main(){
    BigFloat bigFloatas1("-1.0");
    BigFloat bigFloatas2("1.0");
    cout << (bigFloatas1 == bigFloatas2) << endl;
    return 0;
}
