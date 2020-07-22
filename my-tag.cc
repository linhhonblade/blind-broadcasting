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
#include "ns3/tag.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include <iostream>
#include "my-tag.h"
#include "ns3/log.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("ForwardMode");

TypeId
ForwardCountTag::GetTypeId (void)
{
  static TypeId tid =
      TypeId ("ns3::ForwardCountTag")
          .SetParent<Tag> ()
          .AddConstructor<ForwardCountTag> ()
          .AddAttribute ("ForwardCount", "A value specified how many times the packet forwarded",
                         EmptyAttributeValue (),
                         MakeUintegerAccessor (&ForwardCountTag::GetForwardCount),
                         MakeUintegerChecker<uint8_t> ());
  return tid;
}

TypeId
ForwardCountTag::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}

uint32_t
ForwardCountTag::GetSerializedSize (void) const
{
  return 1;
}

void
ForwardCountTag::Serialize (TagBuffer i) const
{
  i.WriteU8 (m_forwardCount);
}
void
ForwardCountTag::Deserialize (TagBuffer i)
{
  m_forwardCount = i.ReadU8 ();
}

void
ForwardCountTag::Print (std::ostream &os) const
{
  os << "v=" << (uint32_t) m_forwardCount;
}

void
ForwardCountTag::SetForwardCount (uint32_t count)
{
  m_forwardCount = count;
}

uint8_t
ForwardCountTag::GetForwardCount (void) const
{
  return m_forwardCount;
}

}
