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
#include <string>
#include <vector>
#include "my-node.h"
#include "ns3/log.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("MyNode");
NS_OBJECT_ENSURE_REGISTERED (MyNode);

TypeId
MyNode::GetTypeId (void)
{
  static TypeId tid =
      TypeId ("ns3::MyNode")
          .SetParent<Node> ()
          .AddConstructor<MyNode> ();
  return tid;
}

MyNode::MyNode ()
  : m_dRSU (INFINITY),
    m_NeighborList (std::vector<uint32_t>(0,0)),
    m_G (std::vector<uint32_t>(0,0)),
    m_state ("UD"),
    m_Twait (INFINITY),
    m_CID (-1),
    m_Ci (-1)
{
  NS_LOG_FUNCTION (this);
}

MyNode::~MyNode ()
{
}

void MyNode::SetdRSU (double dRSU) {
  NS_LOG_FUNCTION (this << dRSU);
  m_dRSU = dRSU;
}

double MyNode::GetdRSU (void)
{
  NS_LOG_FUNCTION (this);
  return m_dRSU;
}

std::string MyNode::GetState (void)
{
  NS_LOG_FUNCTION (this);
  return m_state;
}

void
MyNode::SetState (std::string& state)
{
  m_state = state;
}

double
MyNode::GetTwait (void)
{
  // we reserve 2 bytes for our header data
  // 4 bytes for seq
  // 8 bytes for timestamp
  NS_LOG_FUNCTION (this);
  return m_Twait;
}

void
MyNode::SetTwait (double Twait)
{
  NS_LOG_FUNCTION (this);
  m_Twait = Twait;
}

uint32_t
MyNode::GetCID (void)
{
  // we can deserialize two bytes from the start of the buffer.
  // we read them in network byte order and store them
  // in host byte order.
  NS_LOG_FUNCTION (this);
  return m_CID;
}

void
MyNode::SetCID (uint32_t CID)
{
  NS_LOG_FUNCTION (this);
  m_CID = CID;
}

double
MyNode::GetCi (void)
{
  NS_LOG_FUNCTION (this);
  return m_Ci;
}

void
MyNode::SetCi (double Ci)
{
  NS_LOG_FUNCTION (this);
  m_Ci = Ci;
}


std::vector<uint32_t>
MyNode::GetNeighborList (void)
{
  NS_LOG_FUNCTION (this);
  return m_NeighborList;
}

std::vector<uint32_t>
MyNode::GetGraph (void)
{
  NS_LOG_FUNCTION (this);
  return m_G;
}

void
MyNode::PushToGraph (uint32_t node)
{
  NS_LOG_FUNCTION (this);
  m_G.push_back(node);
}

void
MyNode::PushToNeighborList (uint32_t node)
{
  NS_LOG_FUNCTION (this);
  m_NeighborList.push_back (node);
}

void
MyNode::ResetNodeInfo (void)
{
  m_dRSU = INFINITY;
  m_G.clear ();
  m_NeighborList.clear ();
  m_state = "UD";
  m_Twait = INFINITY;
  m_CID = -1;
  m_Ci = -1;
}

}
