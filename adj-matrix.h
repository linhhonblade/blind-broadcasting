/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include <string>
#include <vector>
#include "adj-matrix.h"


namespace std {

/* ... */

class AdjMatrix;

class AdjMatrix {
  private:
    vector<vector<double>> matrix;
    int degree;
    double closeness;
    double betweeness;
  public:
    AdjMatrix();
    AdjMatrix(uint8_t size);
    void Show();
    double CalculateDegree();
    double CalculateBetweeness(uint32_t node);
    void CalculateCloseness();
    double GetDegree();
    double GetBetweeness();
    vector<vector<double>> GetMatrix();
    vector<vector<double>> GetEgoMatrix(uint32_t node);
    void SetEntry(uint32_t receiver, uint32_t seq, double value);
    double GetEntry(uint32_t receiver, uint32_t seq);
    void DeleteRow(uint32_t row);
    void DeleteCol(uint32_t col);
    double RowSum (void);
};

}

#endif /* ADJ_MATRIX_H */

