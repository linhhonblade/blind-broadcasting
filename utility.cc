/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "utility.h"
#include "ns3/log.h"
#include <string>
#include "ns3/address.h"
#include <vector>

namespace ns3 {

/* ... */

NS_LOG_COMPONENT_DEFINE ("Utility");

std::string MacToString (const Address& sender) {
  AddressValue addVal = AddressValue(sender);
  Ptr<const AttributeChecker> addChecker = MakeAddressChecker();
  std::string macStr = addVal.SerializeToString(addChecker);
  return macStr;
}

uint32_t MacToInt (std::string& s) {
  std::string sub = s.substr(6, 17);
  unsigned u[6];
  std::sscanf(sub.c_str(), "%x:%x:%x:%x:%x:%x", u, u+1, u+2, u+3, u+4, u+5);
  uint32_t r = 0;
  for (int i = 0; i < 6; i++) r = (r<<8)+u[i];
  return r;
}

}

