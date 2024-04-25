#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <numeric>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Studentas {
private:
  std::string vardas_;
  std::string pavarde_;
  double egzaminas_;
  std::vector<double> nd_;
  double galutinis_;
public:
  Studentas() : egzaminas_(0) { }  // default konstruktorius
  Studentas(std::istream& is);
    inline double egzaminas() const { return egzaminas_; }  // getter for egzaminas_
    inline std::vector<double> nd() const { return nd_; }  // getter for nd_

    string vardas() const { return vardas_; }
    string pavarde() const { return pavarde_; }

    void calculateGalutinis(bool useMedian) {
        if (useMedian) {
            sort(nd_.begin(), nd_.end());
            if (nd_.size() % 2 == 0) {
                galutinis_ = (nd_[nd_.size() / 2 - 1] + nd_[nd_.size() / 2]) / 2;
            }
            else {
                galutinis_ = nd_[nd_.size() / 2];
            }
        }
        else {
            double nd_sum = accumulate(nd_.begin(), nd_.end(), 0);
            galutinis_ = 0.4 * (nd_sum / nd_.size()) + 0.6 * egzaminas_;
        }
    }

    vector<double> getNd() const { return nd_; }
    double getGalutinis() const { return galutinis_; }
    double getEgzaminas() const { return egzaminas_; }

    void setVardas(const std::string& vardas) { vardas_ = vardas; }  // setter for vardas_
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }  // setter for pavarde_
    void setEgzaminas(double egzaminas) { egzaminas_ = egzaminas; }  // setter for egzaminas_
    void setNd(const std::vector<double>& nd) { nd_ = nd; }  // setter for nd_
};

bool compare(const Studentas&, const Studentas&);
bool comparePagalPavarde(const Studentas&, const Studentas&);
bool comparePagalEgza(const Studentas&, const Studentas&);

void Ivedimas(vector<Studentas>& stud, bool randomNames = false, bool randomGrades = false, bool studentCount = false);
void Pasirinkimai(vector<Studentas>& students);
void Spausdinimas(const vector<Studentas>& students, bool Mediana);
bool isNumber(const string& str);
double useMediana(const vector<int>& grades);
void Generacija(int Pas);

#endif // STUDENT_H
// Path: v0.3/v0.3.cpp