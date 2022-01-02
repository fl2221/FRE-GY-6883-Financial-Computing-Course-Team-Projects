//
//  Vector.hpp
//  Project_v1217
//
//  Created by Lu on 2021/12/18.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <stdio.h>

#endif /* Vector_hpp */
#pragma once

#include<vector>
#include <ostream>

using namespace std;

typedef vector<double> Vector;

Vector operator+(const Vector& V, const Vector& W);
Vector operator-(const Vector& V, const Vector& W);
Vector calculateReturn(Vector V);
Vector calculateCumReturn(Vector V);
ostream& operator<<(ostream& out, Vector& V);


