/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
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
#include "ns3/node-container.h"
#include "ns3/node-list.h"
#include "ns3/names.h"
#include "my-node.h"
#include "my-node-container.h"

namespace ns3 {

MyNodeContainer::MyNodeContainer ()
{
}

void
MyNodeContainer::Create (uint32_t n)
{
  for (uint32_t i = 0; i < n; i++)
    {
      m_nodes.push_back (CreateObject<MyNode> ());
    }
}

} // namespace ns3
