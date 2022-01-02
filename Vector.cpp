//
//  Vector.cpp
//  Project_v1217
//
//  Created by Lu on 2021/12/18.
//

#include "Vector.hpp"
#include <ostream>

using namespace std;

Vector operator+(const Vector& V, const Vector& W) {
    int d = (int)V.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = V[j] + W[j];
    return U;
}

Vector operator-(const Vector& V, const Vector& W) {
    int d = (int)V.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = V[j] - W[j];
    return U;
}

Vector calculateReturn(Vector V) {
    int size = (int)V.size();
    Vector result;
    for (int i = 0; i < size - 1; i++) {
        result.push_back((V[i + 1] - V[i]) / V[i]);
    }
    return result;
}

Vector calculateCumReturn(Vector V) {
    int size = (int)V.size();
    Vector result;
    double cumsum = 0.0;
    for (int i = 0; i < size; i++) {
        cumsum += V[i];
        result.push_back(cumsum);
    }
    return result;
}
ostream& operator<<(ostream& out, Vector& V)
{
    for (Vector::iterator itr = V.begin(); itr != V.end(); itr++)
        out << *itr << " ";
    out << endl;
    return out;
}
