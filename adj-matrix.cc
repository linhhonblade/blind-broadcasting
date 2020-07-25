/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include <vector>
#include "ns3/log.h"
#include "adj-matrix.h"
#include <numeric>
namespace std {

/* ... */

NS_LOG_COMPONENT_DEFINE ("AdjMatrix");

AdjMatrix::AdjMatrix ()
{
  NS_LOG_FUNCTION (this);
}

AdjMatrix::AdjMatrix (uint8_t size)
{
  NS_LOG_FUNCTION (this);
  matrix = std::vector<std::vector<double>> (size, std::vector<double> (100, 0.0));
}

void
AdjMatrix::Show (void)
{
  for (uint32_t i = 0; i < matrix.size (); i++)
    {
      for (std::vector<double>::iterator it = matrix[i].begin (); it != matrix[i].end (); ++it)
        {
          std::cout << *it << " ";
        }
      std::cout << std::endl;
    }
}

vector<vector<double>>
AdjMatrix::GetMatrix (void)
{
  return AdjMatrix::matrix;
}

double
AdjMatrix::CalculateDegree ()
{
  double sum = 0.0;
  for (uint32_t i = 0; i < matrix.size (); i++)
    {
      for (std::vector<double>::iterator it = matrix[i].begin (); it != matrix[i].end (); ++it)
        {
          sum += *it;
        }
    }
  return sum;
}

void
AdjMatrix::SetEntry (uint32_t receiver, uint32_t seq, double value)
{
  matrix[receiver][seq] = value;
  return;
}

double
AdjMatrix::GetEntry (uint32_t receiver, uint32_t seq)
{
  return matrix[receiver][seq];
}

double
AdjMatrix::GetDegree (void)
{
  return degree;
}

vector<vector<double>>
AdjMatrix::GetEgoMatrix (uint32_t node)
{
  vector<uint32_t> neighbors = vector<uint32_t> (1, node);
  for (uint32_t i = 0; i < matrix.size (); i++)
    {
      if (i == node)
        continue;
      else if (matrix[i][node] == 0)
        {
          neighbors.push_back (i);
        }
    }
  vector<vector<double>> ego =
      vector<vector<double>> (neighbors.size (), vector<double> (neighbors.size (), 0.0));
  for (uint32_t i = 0; i < neighbors.size (); i++)
    {
      for (uint32_t j = 0; j < neighbors.size (); j++)
        {
          ego[i][j] = matrix[neighbors[i]][neighbors[j]];
        }
    }
  return ego;
}

double
AdjMatrix::RowSum (void)
{
  double sum = 0.0;
  for (uint32_t i = 0; i < matrix.size (); i++)
    {

      double rowsum = std::accumulate (matrix[i].begin (), matrix[i].end (), 0);
      std::cout << rowsum << std::endl;
      sum += rowsum;
    }
  double result = sum / ((matrix.size () - 1) * 100);
  std::cout << "PDR = " << result << std::endl;
  return result;
}

} // namespace std
