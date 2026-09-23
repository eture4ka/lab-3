#pragma once

#include <array>
#include <string>

const int SIZE = 10;

struct transistor_s_t {
    int id;                 
    std::string type;       
    double gain;            
    double maxCurrent;       
};

class Transistor {
private:
    std::array<transistor_s_t, SIZE> transistors; 
    int count;                                     

public:
    Transistor();   
    ~Transistor();  


    bool addTransistor(const std::string& type, double gain, double maxCurrent);

   
    bool inputOne();

    
    void printAll() const;

    
    bool setType(int index, const std::string& t);
    bool setGain(int index, double g);
    bool setMaxCurrent(int index, double i);

   
    std::string getType(int index) const;
    double getGain(int index) const;
    double getMaxCurrent(int index) const;

    int getCount() const { return count; }

    
    void printByMinGain(double minGain) const;


    double power(int index, double voltage) const;
};
