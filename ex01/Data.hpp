#pragma once

class Data {
 public:
    Data();
    explicit Data(int value);
    Data(const Data& other);
    Data& operator=(const Data& other);
    ~Data();

    int getValue() const;

 private:
    int _value;
};
