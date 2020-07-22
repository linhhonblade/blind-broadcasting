/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef MY_NODE_H
#define MY_NODE_H

#include <string>
#include <vector>
#include "ns3/node.h"
#include "ns3/timer.h"


namespace ns3 {

/* ... */

class MyNode;

class MyNode : public Node {
  private:
    double m_dRSU;
    std::vector<uint32_t> m_NeighborList;
    std::vector<uint32_t> m_G;
    std::string m_state;
    double m_Twait;
    uint32_t m_CID;
    double m_Ci;

  public:
    static TypeId GetTypeId (void);
    MyNode (void);
    virtual ~MyNode ();

    double GetdRSU ();
    std::string GetState ();
    double GetTwait ();
    uint32_t GetCID ();
    double GetCi ();
    std::vector<uint32_t> GetNeighborList ();
    std::vector<uint32_t> GetGraph ();

    void SetdRSU (double dRSU);
    void SetState (std::string& state);
    void SetTwait (double Twait);
    void SetCID (uint32_t CID);
    void SetCi (double Ci);
    void PushToNeighborList (uint32_t node);
    void PushToGraph (uint32_t node);
    void ResetNodeInfo (void);
};

}

#endif /* MY_NODE_H */

