#include "transistor.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

Transistor::Transistor() {
    count = 0;
    cout << "[Konstruktor] stvoreno nabir tranzystoriv (mistkist " << SIZE << ")" << endl;
}

Transistor::~Transistor() {
    cout << "[Destruktor] znyshcheno nabir z " << count << " tranzystoriv" << endl;
}

bool Transistor::addTransistor(const std::string& type, double gain, double maxCurrent) {
    if (count >= SIZE) {
        cout << "  ! Pomylka: masyv tranzystoriv zapovneno (max " << SIZE << "). Dodavannya nemozhlyve." << endl;
        return false;
    }
    if (type.empty()) {
        cout << "  ! Pomylka: typ tranzystora ne mozhe buty porozhnim. Obyekt ne dodano." << endl;
        return false;
    }
    if (gain <= 0 || gain > 10000) {
        cout << "  ! Pomylka: koefitsiyent pidsylennya " << gain << " nekorektnyy (0 < gain <= 10000). Obyekt ne dodano." << endl;
        return false;
    }
    if (maxCurrent <= 0 || maxCurrent > 100) {
        cout << "  ! Pomylka: strum " << maxCurrent << " A nekorektnyy (0 < I <= 100). Obyekt ne dodano." << endl;
        return false;
    }

    transistors[count].id = count;
    transistors[count].type = type;
    transistors[count].gain = gain;
    transistors[count].maxCurrent = maxCurrent;
    cout << "  > dodano tranzystor #" << count << " \"" << type << "\"" << endl;
    count++;
    return true;
}

bool Transistor::inputOne() {
    if (count >= SIZE) {
        cout << "  ! Pomylka: masyv zapovneno, vvedennya nemozhlyve." << endl;
        return false;
    }
    string t;
    double g, i;
    cout << "Vvedit typ tranzystora: ";
    getline(cin, t);
    cout << "Vvedit koefitsiyent pidsylennya: ";
    cin >> g;
    cout << "Vvedit maksymalnyy strum (A): ";
    cin >> i;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return addTransistor(t, g, i);
}

void Transistor::printAll() const {
    if (count == 0) {
        cout << "  (masyv porozhniy, nemaye tranzystoriv dlya vyvodu)" << endl;
        return;
    }
    for (int idx = 0; idx < count; idx++) {
        cout << "  [" << setw(2) << transistors[idx].id << "] "
             << "Typ: " << left << setw(12) << transistors[idx].type
             << " | Koef. pidsylennya: " << right << setw(7) << fixed << setprecision(1) << transistors[idx].gain
             << " | Max strum: " << setw(6) << setprecision(2) << transistors[idx].maxCurrent << " A" << endl;
    }
}

bool Transistor::setType(int index, const std::string& t) {
    if (index < 0 || index >= count) {
        cout << "  ! Pomylka: nevirnyy indeks " << index << "." << endl;
        return false;
    }
    if (t.empty()) {
        cout << "  ! Pomylka: typ tranzystora ne mozhe buty porozhnim. Znachennya ne zmineno." << endl;
        return false;
    }
    transistors[index].type = t;
    return true;
}

bool Transistor::setGain(int index, double g) {
    if (index < 0 || index >= count) {
        cout << "  ! Pomylka: nevirnyy indeks " << index << "." << endl;
        return false;
    }
    if (g <= 0) {
        cout << "  ! Pomylka: koefitsiyent pidsylennya maye buty bilshym za 0 (zadano " << g << "). Znachennya ne zmineno." << endl;
        return false;
    }
    if (g > 10000) {
        cout << "  ! Pomylka: koefitsiyent pidsylennya " << g << " zanadto velykyy (max 10000). Znachennya ne zmineno." << endl;
        return false;
    }
    transistors[index].gain = g;
    return true;
}

bool Transistor::setMaxCurrent(int index, double i) {
    if (index < 0 || index >= count) {
        cout << "  ! Pomylka: nevirnyy indeks " << index << "." << endl;
        return false;
    }
    if (i <= 0) {
        cout << "  ! Pomylka: strum maye buty bilshym za 0 (zadano " << i << " A). Znachennya ne zmineno." << endl;
        return false;
    }
    if (i > 100) {
        cout << "  ! Pomylka: strum " << i << " A perevyshchuye dopustymu mezhu 100 A. Znachennya ne zmineno." << endl;
        return false;
    }
    transistors[index].maxCurrent = i;
    return true;
}

std::string Transistor::getType(int index) const {
    if (index < 0 || index >= count) return "";
    return transistors[index].type;
}

double Transistor::getGain(int index) const {
    if (index < 0 || index >= count) return 0.0;
    return transistors[index].gain;
}

double Transistor::getMaxCurrent(int index) const {
    if (index < 0 || index >= count) return 0.0;
    return transistors[index].maxCurrent;
}

void Transistor::printByMinGain(double minGain) const {
    bool found = false;
    cout << "  Tranzystory z koefitsiyentom pidsylennya >= " << minGain << ":" << endl;
    for (int idx = 0; idx < count; idx++) {
        if (transistors[idx].gain >= minGain) {
            cout << "    [" << transistors[idx].id << "] " << transistors[idx].type
                 << " (gain = " << transistors[idx].gain << ")" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "    Zhodnoho tranzystora z takym koefitsiyentom pidsylennya ne znaydeno." << endl;
    }
}

double Transistor::power(int index, double voltage) const {
    if (index < 0 || index >= count) return 0.0;
    return voltage * transistors[index].maxCurrent;
}
