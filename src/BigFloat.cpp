#include "BigFloat.hpp"

BigFloat::BigFloat(string input) {
    input.erase(0, input.find_first_not_of('0'));
    if(input[0] == '.') {
        input = "0" + input;
    }
    reverse(input.begin(),input.end());
    input.erase(0, input.find_first_not_of('0'));
    reverse(input.begin(), input.end());
    if(input[input.length() - 1] == '.') {
        input += "0";
    }
    value = new vector<char>(input.begin(), input.end());
}

BigFloat::~BigFloat()
{
    //dtor
}

string BigFloat::getFirstPart() const {
    return getValue().substr(0, getLengthToDot());
}

string BigFloat::getSecondPart() const {
    return getValue().substr(getLengthToDot() + 1);
}

string BigFloat::getValue() const {
    return string(value->begin(), value->end());
}

size_t BigFloat::getLengthToDot() const {
    return getValue().find('.');
}

bool BigFloat::isMore(const BigFloat& bf) {
    bool bothNegative = false;
    if(bf.getValue()[0] == '-' && getValue()[0] == '-') bothNegative = true;
    if((getValue()[0] != '-' && bf.getValue()[0] == '-' ) || getLengthToDot() > bf.getLengthToDot()) {
        return true;
    }
    if((getValue()[0] == '-' && bf.getValue()[0] != '-' ) || getLengthToDot() < bf.getLengthToDot()) {
        return false;
    }
    for(int i = 0; i < getValue().length(); i++) {
        if(getLengthToDot() == i) {
            continue;
        }
        if(getValue()[i] > bf.getValue()[i]) {
            return !bothNegative;
        }
    }
    return bothNegative;
}

bool BigFloat::isLess(const BigFloat& bf) {
    bool bothNegative = false;
    if(bf.getValue()[0] == '-' && getValue()[0] == '-') bothNegative = true;
    if((getValue()[0] != '-' && bf.getValue()[0] == '-' ) || getLengthToDot() > bf.getLengthToDot()) {
        return false;
    }
    if((getValue()[0] == '-' && bf.getValue()[0] != '-' ) || getLengthToDot() < bf.getLengthToDot()) {
        return true;
    }
    for(int i = 0; i < getValue().length(); i++) {
        if(getLengthToDot() == i) {
            continue;
        }
        if(getValue()[i] > bf.getValue()[i]) {
            return bothNegative;
        }
    }
    return !bothNegative;
}

BigFloat BigFloat::operator+(const BigFloat& bf){
    bool carry = false;
    bool bothNegative = false;
    if(getFirstPart()[0] == '-' && bf.getFirstPart()[0] == '-') {
        getFirstPart() = getFirstPart().substr(1);
        bf.getFirstPart() = bf.getFirstPart().substr(1);
        bothNegative = true;
    }
    vector <char> partFinal;
    if(bf.getSecondPart().length() > getSecondPart().length()) {
        string temp = getSecondPart();
        getSecondPart() = bf.getSecondPart();
        bf.getSecondPart() = temp;
    }
    if(bf.getFirstPart().length() > getFirstPart().length()) {
        string temp = getFirstPart();
        getFirstPart() = bf.getFirstPart();
        bf.getFirstPart() = temp;
    }
    int difference = getFirstPart().length() - bf.getFirstPart().length();

    for(int i = getSecondPart().length() - 1; i >= 0; i--) {
        int temp = 0;
        if(carry) {
            carry = false;
            temp++;
        }
        temp = temp + (bf.getSecondPart().length() > i ? (bf.getSecondPart()[i] - '0') : 0) + (getSecondPart()[i] - '0');
        if(temp >= 10) {
            carry = true;
            temp = temp - 10;
        }
        partFinal.insert(partFinal.begin(), temp + 48);
    }
    partFinal.insert(partFinal.begin(), '.');

    for(int i = getFirstPart().length() - 1; i >= 0; i--) {
        int temp = 0;
        if(carry) {
            carry = false;
            temp++;
        }
        temp = temp + (i - difference >= 0 ? (bf.getFirstPart()[i - difference] - '0') : 0) + (getFirstPart()[i] - '0');
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
    vector <char> partFinal;
    int difference = getLengthToDot() - bf.getLengthToDot();
    int carry = 0;
    for (int i = bf.getLengthToDot() - 1; i >= 0; i--) {
        int temp = ((getFirstPart()[i + difference] - 48) - (bf.getFirstPart()[i] - 48) - carry);
        if (temp < 0) {
            temp += 10;
            carry = 1;
        }
        else
            carry = 0;
        partFinal.insert(partFinal.begin(), temp + 48);
    }
    for (int i = difference - 1; i >= 0; i--) {
        if (getFirstPart()[i] == '0' && carry) {
            partFinal.insert(partFinal.begin(), '9');
            continue;
        }
        int temp = ((getFirstPart()[i] - '0') - carry);
        if (i > 0 || temp > 0)
            partFinal.insert(partFinal.begin(), temp + 48);
        carry = 0;
    }
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
