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
#include <random>
#include <iterator>
#include <functional>
#include <stdexcept>
#include "mVector.h"


using namespace std;
using namespace std::chrono;

class Zmogus{
    public: 
    virtual ~Zmogus() = default;

    //geteriai
    virtual std::string getVardas() const = 0;
    virtual std::string getPavarde() const = 0;
    virtual const mVector<int>& getND() const = 0;
    virtual double getEgzaminas() = 0;
};

class Studentas: public Zmogus{
private:
    std::string vardas_;
    std::string pavarde_;
    double egzaminas_;
    mVector<int> nd_;
    bool useMedian;
public:
        // Default constructor
        Studentas();

        // Constructor with parameters
        Studentas(const std::string& vardas_, const std::string& pavarde_, double egzaminas_, const mVector<int>& nd_);

        // Copy constructor
        Studentas(const Studentas& other);

        // Copy assignment operator
        Studentas& operator=(const Studentas& other);

        // Move constructor
        Studentas(Studentas&& other) noexcept;

        // Move assignment operator
        Studentas& operator=(Studentas&& other) noexcept;

        // Destructor
        ~Studentas();

        // Getters
        inline std::string getVardas() const { return vardas_; } 
        inline std::string getPavarde() const { return pavarde_; }
        const mVector<int>& getND() const { return nd_; }
        double getEgzaminas() { return egzaminas_; }

        // Setters
        void setVardas(const std::string& vardas) { vardas_ = vardas; }
        void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
        void setEgzaminas(double egzaminas) { egzaminas_ = egzaminas; }
        void setNd(const mVector<int>& nd) { nd_ = nd; }

        // Other functions
        void setUseMedian(bool useMedian) {this -> useMedian = useMedian; }
        bool getUseMedian() const { return useMedian; }
        // Calculate the final grade
        double calculateGalutinis() const; // Add the missing implementation
};

// Comparison functions for sorting
bool compare(const Studentas&, const Studentas&);
bool comparePagalPavarde(const Studentas&, const Studentas&);
bool comparePagalEgza(const Studentas&, const Studentas&);

// Input function
void Ivedimas(mVector<Studentas>& stud, bool randomNames = false, bool randomGrades = false, bool studentCount = false);

// Menu function
void Pasirinkimai(mVector<Studentas>& students);

// Output function
void Spausdinimas(const mVector<Studentas>& students, bool Mediana);

// Check if a string is a number
bool isNumber(const string& str);

// Calculate the final grade using median
double useMediana(const mVector<int>& grades);

// Generate random data
void Generacija(int Pas);

#endif // STUDENT_H
// Path: v0.3/v0.3.cpp