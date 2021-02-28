#include "BigFloat.hpp"

BigFloat::BigFloat(string input) {
    value = new vector<char>(input.begin(), input.end());
}

BigFloat::~BigFloat()
{
    //dtor
}

string BigFloat::getValue() const{
    return string(value->begin(), value->end());
}

BigFloat BigFloat::operator+(const BigFloat& bf){
    bool carry = false;
    bool bothNegative = false;
    char dot = '.';
    size_t lengthToDot = getValue().find(dot);
    string firstPart = getValue().substr(0, lengthToDot);
    string secondPart = getValue().substr(lengthToDot + 1);
    string bfValue = bf.getValue();
    size_t lengthToDot1 = bfValue.find(dot);
    string firstPart1 = bfValue.substr(0, lengthToDot1);
    string secondPart1 = bfValue.substr(lengthToDot1 + 1);
    if(firstPart[0] == '-' && firstPart1[0] == '-') {
        firstPart = firstPart.substr(1);
        firstPart1 = firstPart1.substr(1);
        bothNegative = true;
    }

    vector <char> partFinal;

    if(secondPart1.length() > secondPart.length()) {
        string temp = secondPart;
        secondPart = secondPart1;
        secondPart1 = temp;
    }
    if(firstPart1.length() > firstPart.length()) {
        string temp = firstPart;
        firstPart = firstPart1;
        firstPart1 = temp;
    }
    int difference = firstPart.length() - firstPart1.length();

    for(int i = secondPart.length() - 1; i >= 0; i--) {
        int temp = 0;
        if(carry) {
            carry = false;
            temp++;
        }
        temp = temp + (secondPart1.length() > i ? (secondPart1[i] - '0') : 0) + (secondPart[i] - '0');
        if(temp >= 10) {
            carry = true;
            temp = temp - 10;
        }
        partFinal.insert(partFinal.begin(), temp + 48);
    }
    partFinal.insert(partFinal.begin(), dot);

    for(int i = firstPart.length() - 1; i >= 0; i--) {
        int temp = 0;
        if(carry) {
            carry = false;
            temp++;
        }
        temp = temp + (i - difference >= 0 ? (firstPart1[i - difference] - '0') : 0) + (firstPart[i] - '0');
        if(temp >= 10) {
            carry = true;
            temp = temp - 10;
        }
        partFinal.insert(partFinal.begin(), temp + 48);
    }
    if(carry)partFinal.insert(partFinal.begin(), '1');
    if(bothNegative)partFinal.insert(partFinal.begin(), '-');
    return BigFloat(string(partFinal.begin(), partFinal.end()));
}

BigFloat BigFloat::operator-(const BigFloat& bf){

}

BigFloat BigFloat::operator*(const BigFloat& bf){

}

BigFloat BigFloat::operator/(const BigFloat& bf){

}

BigFloat BigFloat::operator%(const BigFloat& bf){

}

ostream& operator<<(ostream& os, const BigFloat& bf) {
    os << bf.getValue();
    return os;
}

