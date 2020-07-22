/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef MY_HEADER_H
#define MY_HEADER_H

#include "ns3/header.h"
#include "ns3/timer.h"

namespace ns3{

/* ... */

class MyHeader;

class MyHeader : public Header
{
private:
  uint16_t m_data;  //!< Header data
  uint32_t m_seq;   //!< Sequence number
  uint64_t m_ts;    //!< Timestamp
  uint64_t m_origin;
public:
  MyHeader ();
  virtual ~MyHeader ();

  /**
   * Set the header data.
   * \param data The data.
   */
  void SetData (uint16_t data);
  /**
   * Get the header data.
   * \return The data.
   */
  uint16_t GetData (void) const;

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  /**
   * \param seq the sequence number
   */
  void SetSeq (uint32_t seq);

  /**
   * \return the sequence number
   */
  uint32_t GetSeq (void) const;
  /**
   * \return the timestamp
   */
  Time GetTs (void) const;

  void SetOrigin (uint64_t origin);
  uint64_t GetOrigin (void) const;



  virtual TypeId GetInstanceTypeId (void) const;
  virtual void Print (std::ostream &os) const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);
  virtual uint32_t GetSerializedSize (void) const;

};

} // namespace ns3

#endif /* MY_HEADER_H */
