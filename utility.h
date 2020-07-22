/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef UTILITY_H
#define UTILITY_H

#include "ns3/address.h"
#include <vector>

namespace ns3 {

/* ... */


std::string MacToString (const Address& sender);
uint32_t MacToInt (std::string& s);

}

#endif /* UTILITY_H */

