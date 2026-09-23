#include <iostream>
#include "transistor.h"

using namespace std;

int main() {
    cout << "===== STVORENNYA NABORU TRANZYSTORIV =====" << endl;
    Transistor set;

    cout << endl << "===== DODAVANNYA TRANZYSTORIV (zavdani znachennya) =====" << endl;
    set.addTransistor("KT315B", 200.0, 0.1);
    set.addTransistor("IRF540N", 1500.0, 33.0);
    set.addTransistor("2N3055", 20.0, 15.0);
    set.addTransistor("BC547", 110.0, 0.1);

    cout << endl << "===== INTERAKTYVNE DODAVANNYA (vvedennya z klaviatury) =====" << endl;
    cout << "Vvedit dani shche odnoho tranzystora:" << endl;
    set.inputOne();

    cout << endl << "===== POCHATKOVI DANI =====" << endl;
    set.printAll();

    cout << endl << "===== PEREVIRKA VALIDNOSTI (nekorektni sprob dodavannya/zminy) =====" << endl;
    set.addTransistor("", 100.0, 1.0);        
    set.addTransistor("Test", -5.0, 1.0);     
    set.setGain(0, -50.0);                    
    set.setMaxCurrent(1, 250.0);             

    cout << endl << "===== ZMINA POLIV ZA ZNACHENNYAM =====" << endl;
    set.setType(0, "KT315G");
    set.setGain(0, 220.0);
    set.printAll();

    cout << endl << "===== VYVID ZA KRYTERIYEM (punkt 8) =====" << endl;
    set.printByMinGain(150.0);   
    set.printByMinGain(5000.0);  
    cout << endl << "===== REZULTAT OBCHYSLENNYA POTUZHNOSTI =====" << endl;
    double voltage = 12.0;
    for (int idx = 0; idx < set.getCount(); idx++) {
        cout << "  \"" << set.getType(idx) << "\" pry " << voltage << " V vytrymuye "
             << set.power(idx, voltage) << " Vt" << endl;
    }

    cout << endl << "===== ZAVERSHENNYA PROHRAMY =====" << endl;
    return 0;
}
