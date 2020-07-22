/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006,2007 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include <iostream>
#include "ns3/log.h"
#include "my-header.h"
#include "ns3/simulator.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("MyHeader");

NS_OBJECT_ENSURE_REGISTERED (MyHeader);

TypeId
MyHeader::GetTypeId (void)
{
  static TypeId tid =
      TypeId ("ns3::MyHeader")
          .SetParent<Header> ()
          .AddConstructor<MyHeader> ();
  return tid;
}

MyHeader::MyHeader ()
  : m_seq (0),
    m_ts (Simulator::Now ().GetTimeStep ())
{
  NS_LOG_FUNCTION (this);
}

MyHeader::~MyHeader ()
{
}

void MyHeader::SetSeq (uint32_t seq) {
  NS_LOG_FUNCTION (this << seq);
  m_seq = seq;
}

uint32_t MyHeader::GetSeq (void) const
{
  NS_LOG_FUNCTION (this);
  return m_seq;
}

Time MyHeader::GetTs (void) const
{
  NS_LOG_FUNCTION (this);
  return TimeStep (m_ts);
}

TypeId
MyHeader::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}

uint32_t
MyHeader::GetSerializedSize (void) const
{
  // we reserve 2 bytes for our header data
  // 4 bytes for seq
  // 8 bytes for timestamp
  return 2+4+8+8;
}

void
MyHeader::Serialize (Buffer::Iterator start) const
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;
  i.WriteHtonU16 (m_data);
  i.WriteHtonU32 (m_seq);
  i.WriteHtonU64 (m_ts);
  i.WriteHtonU64 (m_origin);
}

uint32_t
MyHeader::Deserialize (Buffer::Iterator start)
{
  // we can deserialize two bytes from the start of the buffer.
  // we read them in network byte order and store them
  // in host byte order.
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;
  m_data = i.ReadNtohU16 ();
  m_seq = i.ReadNtohU32 ();
  m_ts = i.ReadNtohU64 ();
  m_origin = i.ReadNtohU64 ();
  // we return the number of bytes effectively read.
  return GetSerializedSize ();
}

void
MyHeader::SetData (uint16_t data)
{
  m_data = data;
}

uint16_t
MyHeader::GetData (void) const
{
  return m_data;
}

uint64_t
MyHeader::GetOrigin (void) const
{
  return m_origin;
}

void
MyHeader::SetOrigin (uint64_t origin)
{
  m_origin = origin;
}

void MyHeader::Print (std::ostream &os) const
{
  os << "data = " << std::endl << "seq = " << m_seq << std::endl << "timestamps = " << m_ts << std::endl;
}

}
