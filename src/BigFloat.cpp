#include "BigFloat.hpp"

BigFloat::BigFloat(string input) {
    input.erase(0, input.find_first_not_of('0'));
    if(input[0] == '.' ) {
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

int BigFloat::getValueAt(int index) {
    if(index < 0) {
        index = (index * -1);
        return getSecondPart()[index-1] - '0';
    }
    return getFirstPart()[index-1] - '0';
}

int BigFloat::getLengthOfValue() {
    return getValue().length(); // with dot
}

int BigFloat::getSecondPartLength() {
    return getSecondPart().length(); // everything before dot
}

int BigFloat::getFirstPartLength() {
    return getFirstPart().length(); // everything after dot
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
    //before dot
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
    //after dot
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
    int differenceAfter = getSecondPart().length() - bf.getSecondPart().length();
    int carry = 0;
    for (int i = getSecondPart().length() - 1; i >= 0; i--) {
        int temp = ((getSecondPart()[i + differenceAfter] - 48) - (bf.getSecondPart().length() > i ? (bf.getSecondPart()[i] - '0') : 0) - carry);
        if (temp < 0) {
            temp += 10;
            carry = 1;
        }
        else
            carry = 0;
        partFinal.insert(partFinal.begin(), temp + 48);
    }
    for (int i = differenceAfter - 1; i >= 0; i--) {
        if (getSecondPart()[i] == '0' && carry) {
            partFinal.insert(partFinal.begin(), '9');
            continue;
        }
        int temp = ((getSecondPart()[i] - '0') - carry);
        if (i > 0 || temp > 0)
            partFinal.insert(partFinal.begin(), temp + 48);
        carry = 0;
    }
    partFinal.insert(partFinal.begin(), '.');
    for (int i = getFirstPart().length() - 1; i >= 0; i--) {
        int temp = ((getFirstPart()[i + difference] - 48) - (i - difference >= 0 ? (bf.getFirstPart()[i - difference] - '0') : 0) - carry);
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

BigFloat BigFloat::operator*(const BigFloat& bf) {
    bool isNegative;
    vector <char> partFinal;
    if ((getFirstPart()[0] == '0' && getSecondPart()[0] == '0') || (bf.getFirstPart()[0] == '0' && bf.getSecondPart()[0] == '0' )) {
        partFinal.insert(partFinal.begin(), '0');
        partFinal.insert(partFinal.begin(), '.');
        partFinal.insert(partFinal.begin(), '0');
        return BigFloat(string(partFinal.begin(), partFinal.end()));
    }
    string stringValue;
    string bfStringValue;
    if((getValue()[0] == '-' && bf.getValue()[0] == '-') || (getValue()[0] != '-' && bf.getValue()[0] != '-')) {
        stringValue = getValue().substr(0, getLengthToDot()) + getValue().substr(getLengthToDot() + 1);
        bfStringValue = bf.getValue().substr(0, bf.getLengthToDot()) + bf.getValue().substr(bf.getLengthToDot() + 1);
    }
    else if(getValue()[0] == '-') {
        stringValue = getValue().substr(1, getLengthToDot() - 1) + getValue().substr(getLengthToDot() + 1);
        bfStringValue = bf.getValue().substr(0, bf.getLengthToDot()) + bf.getValue().substr(bf.getLengthToDot() + 1);
        isNegative = true;
    }
    else if(bf.getValue()[0] == '-') {
        stringValue = getValue().substr(0, getLengthToDot()) + getValue().substr(getLengthToDot() + 1);
        bfStringValue = bf.getValue().substr(1, bf.getLengthToDot() - 1) + bf.getValue().substr(bf.getLengthToDot() + 1);
        isNegative = true;
    }
    vector<int> temp(stringValue.length() + bfStringValue.length(), 0);
    int index1 = 0;
    int index2 = 0;
    for (int i = stringValue.length() - 1; i >= 0; i--) {
        int carry = 0;
        int value1 = stringValue[i] - 48;
        index2 = 0;
        for (int k = bfStringValue.length() - 1; k >= 0; k--) {
            int value2 = bfStringValue[k] - 48;
            int answ = value1*value2 + temp[index1 + index2] + carry;
            carry = answ / 10;
            temp[index1 + index2] = answ % 10;
            index2++;
        }
        if (carry > 0) {
            temp[index1 + index2] += carry;
        }
        index1++;
    }
    int zero = temp.size() - 1;
    while (zero >= 0 && temp[zero] == 0) {
        zero--;
    }
    while (zero >= 0) {
        partFinal.insert(partFinal.end(), temp[zero--] + 48);
    }
    partFinal.insert((getSecondPart().length() >= bf.getSecondPart().length() ? partFinal.end() - getSecondPart().length() - 1 : partFinal.end() - bf.getSecondPart().length() - 1), '.');
    if(isNegative) {
        partFinal.insert(partFinal.begin(), '-');
    }
    return BigFloat(string(partFinal.begin(), partFinal.end()));
}

BigFloat BigFloat::operator/(const BigFloat& bf) {
    //To do
}

BigFloat BigFloat::operator%(const BigFloat& bf){
    //To do
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
