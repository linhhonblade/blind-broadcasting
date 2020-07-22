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
#ifndef MY_NODE_CONTAINER_H
#define MY_NODE_CONTAINER_H

#include <stdint.h>
#include <vector>
#include "my-node.h"
#include "ns3/node-container.h"
namespace ns3 {

class MyNodeContainer;

class MyNodeContainer : public NodeContainer {
  public:
    MyNodeContainer ();
    void Create (uint32_t n);
  private:
    std::vector<Ptr<MyNode>> m_nodes;
};

} // namespace ns3

#endif /* MY_NODE_CONTAINER_H */
