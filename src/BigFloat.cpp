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

bool BigFloat::isMore(const BigFloat& bf) {
    size_t lengthToDot = getValue().find('.');
    size_t lengthToDot1 = bf.getValue().find('.');
    string getFirst = getValue();
    string getFirst1 = bf.getValue();
    bool bothNegative = false;
    if(getFirst1[0] == '-' && getFirst[0] == '-') bothNegative = true;
    if((getFirst[0] != '-' && getFirst1[0] == '-' ) || lengthToDot > lengthToDot1) {
        return true;
    }
    if((getFirst[0] == '-' && getFirst1[0] != '-' ) || lengthToDot < lengthToDot1) {
        return false;
    }
    for(int i = 0; i < getFirst.length(); i++) {
        if(lengthToDot == i) {
            continue;
        }
        if(getFirst[i] > getFirst1[i]) {
            return !bothNegative;
        }
    }
    return bothNegative;
}

bool BigFloat::isLess(const BigFloat& bf) {
    size_t lengthToDot = getValue().find('.');
    size_t lengthToDot1 = bf.getValue().find('.');
    string getFirst = getValue();
    string getFirst1 = bf.getValue();
    bool bothNegative = false;
    if(getFirst1[0] == '-' && getFirst[0] == '-') bothNegative = true;
    if((getFirst[0] != '-' && getFirst1[0] == '-' ) || lengthToDot > lengthToDot1) {
        return false;
    }
    if((getFirst[0] == '-' && getFirst1[0] != '-' ) || lengthToDot < lengthToDot1) {
        return true;
    }
    for(int i = 0; i < getFirst.length(); i++) {
        if(lengthToDot == i) {
            continue;
        }
        if(getFirst[i] > getFirst1[i]) {
            return bothNegative;
        }
    }
    return !bothNegative;
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
    bool carry = false;
    char dot = '.';
    size_t lengthToDot = getValue().find(dot);
    string firstPart = getValue().substr(0, lengthToDot);
    string secondPart = getValue().substr(lengthToDot + 1);
    string bfValue = bf.getValue();
    size_t lengthToDot1 = bfValue.find(dot);
    string firstPart1 = bfValue.substr(0, lengthToDot1);
    string secondPart1 = bfValue.substr(lengthToDot1 + 1);

    vector <char> partFinal;

    for(int i = secondPart.length() - 1; i >= 0; i--) {
        int temp = 0;
        if(carry) {
            carry = false;
            temp--;
        }
        int secondPart1Num = (secondPart1.length() > i ? (secondPart1[i] - '0') : 0);
        if(secondPart1Num > (secondPart[i] - '0')) {
            carry = true;
            temp = temp + secondPart1Num - (secondPart[i] - '0');
        }
        else {
            temp = temp + (secondPart[i] - '0') - secondPart1Num;
        }
        partFinal.insert(partFinal.begin(), temp + 48);
    }

    partFinal.insert(partFinal.begin(), dot);

    int difference = firstPart.length() - firstPart1.length();

    for(int i = firstPart.length() - 1; i >= 0; i--) {
        int temp = 0;
        if(carry) {
            carry = false;
            temp--;
        }
        int firstPart1Num =  (i - difference >= 0 ? (firstPart1[i - difference] - '0') : 0);
        if(firstPart1Num > (firstPart[i] - '0')) {
            temp = temp + firstPart1Num - (firstPart[i] - '0');
        }
        else {
            temp = temp + (firstPart[i] - '0') - firstPart1Num;
        }
        partFinal.insert(partFinal.begin(), temp + 48);
    }
    if(carry)partFinal.insert(partFinal.begin(), '1');
    partFinal.insert(partFinal.begin(), '-');
    return BigFloat(string(partFinal.begin(), partFinal.end()));
}

BigFloat BigFloat::operator*(const BigFloat& bf){

}

BigFloat BigFloat::operator/(const BigFloat& bf){

}

BigFloat BigFloat::operator%(const BigFloat& bf){

}

bool BigFloat::operator==(const BigFloat& bf) {
    return getValue() == bf.getValue();
}

bool BigFloat::operator!=(const BigFloat& bf) {
    return getValue() != bf.getValue();
}

bool BigFloat::operator>(const BigFloat& bf) {
    return isMore(bf);
}

bool BigFloat::operator<(const BigFloat& bf) {
    return isLess(bf);
}

bool BigFloat::operator>=(const BigFloat& bf) {
    if(getValue() == bf.getValue()) {
        return true;
    }
    return isMore(bf);
}

bool BigFloat::operator<=(const BigFloat& bf) {
    if(getValue() == bf.getValue()) {
        return true;
    }
    return isLess(bf);
}




ostream& operator<<(ostream& os, const BigFloat& bf) {
    os << bf.getValue();
    return os;
}
