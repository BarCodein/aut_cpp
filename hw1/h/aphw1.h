#ifndef _aphw1_h
#define _aphw1_h

#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<stdexcept>
#include<string>
#include<cmath>
using Matrix = std::vector<std::vector<double> >;
Matrix multiply(const Matrix& a, const Matrix& b);
Matrix transpose(const Matrix& a);
double det(Matrix& a);
Matrix inv(Matrix& a);
void show(Matrix& a);

Matrix getData(char* filename);
Matrix getX(Matrix& data);
Matrix gety(Matrix& data);

Matrix solve(char* filename);

#endif