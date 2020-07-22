/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef MY_TAG_H
#define MY_TAG_H

#include "ns3/tag.h"

namespace ns3 {

/* ... */

class ForwardCountTag;

class ForwardCountTag : public Tag
{
private:
  uint8_t m_forwardCount;
public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (TagBuffer i) const;
  virtual void Deserialize (TagBuffer i);
  virtual void Print (std::ostream &os) const;

  uint8_t GetForwardCount (void) const;
  void SetForwardCount (uint32_t count);
};

} // namespace ns3

#endif /* MY_TAG_H */
