/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 * Author: Junling Bu <linlinjavaer@gmail.com>
 */
#include "ns3/command-line.h"
#include "ns3/node.h"
#include "ns3/packet.h"
#include "ns3/simulator.h"
#include "ns3/node-container.h"
#include "ns3/net-device-container.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/mobility-helper.h"
#include "ns3/seq-ts-header.h"
#include "ns3/wave-net-device.h"
#include "ns3/wave-mac-helper.h"
#include "ns3/wave-helper.h"
#include "ns3/mobility-module.h"
#include "adj-matrix.h"
#include "position.h"
#include "my-header.h"

using namespace ns3;
/**
 * This simulation is to show the routing service of WaveNetDevice described in IEEE 09.4.
 *
 * note: although txPowerLevel is supported now, the "TxPowerLevels"
 * attribute of YansWifiPhy is 1 which means phy devices only support 1
 * levels. Thus, if users want to control txPowerLevel, they should set
 * these attributes of YansWifiPhy by themselves..
 */
class WaveNetDeviceExample
{
public:
  /// Send WSMP example function
  double SendExample (const std::string &posfile, uint32_t lanes, double lane_width,
                      uint32_t nodeNum, const std::string &MobilityModel, double maxVelocity,
                      double minVelocity, uint64_t sendNode);

  void ShowMatrix (void);

private:
  /**
   * Send one WSMP packet function
   * \param channel the channel to use
   * \param seq the sequence
   */
  void SendOnePacket (uint32_t channel, uint32_t seq, uint32_t senderNode, uint16_t forwardCount,
                      uint64_t origin);

  /**
   * Receive function
   * \param dev the device
   * \param pkt the packet
   * \param mode the mode
   * \param sender the sender address
   * \returns true if successful
   */
  bool Receive (Ptr<NetDevice> dev, Ptr<const Packet> pkt, uint16_t mode, const Address &sender);

  /// Create WAVE nodes function
  void CreateWaveNodes (const std::string &posfile, uint32_t lanes, double lane_width,
                        uint32_t nodeNum, const std::string &mobilityModel, double maxVelocity,
                        double minVelocity);

  NodeContainer nodes; ///< the nodes
  NetDeviceContainer devices; ///< the devices
  std::AdjMatrix adjMatrix;
};
void
WaveNetDeviceExample::CreateWaveNodes (const std::string &posfile, uint32_t lanes,
                                       double lane_width, uint32_t nodeNum,
                                       const std::string &mobilityModel, double maxVelocity,
                                       double minVelocity)
{
  PosInfo posInfo = PosInfo (posfile);
  nodes = posInfo.GetNodeContainer (lanes, lane_width, nodeNum, mobilityModel, maxVelocity,
                                    minVelocity);

  YansWifiChannelHelper waveChannel = YansWifiChannelHelper::Default ();
  YansWavePhyHelper wavePhy = YansWavePhyHelper::Default ();
  wavePhy.SetChannel (waveChannel.Create ());
  wavePhy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11);
  QosWaveMacHelper waveMac = QosWaveMacHelper::Default ();
  WaveHelper waveHelper = WaveHelper::Default ();
  devices = waveHelper.Install (wavePhy, waveMac, nodes);

  for (uint32_t i = 0; i != devices.GetN (); ++i)
    {
      Ptr<WaveNetDevice> device = DynamicCast<WaveNetDevice> (devices.Get (i));
      device->SetReceiveCallback (MakeCallback (&WaveNetDeviceExample::Receive, this));
      //device->SetWaveVsaCallback (MakeCallback (&WaveNetDeviceExample::ReceiveVsa, this));
    }
}

bool
WaveNetDeviceExample::Receive (Ptr<NetDevice> dev, Ptr<const Packet> pkt, uint16_t mode,
                               const Address &sender)
{
  MyHeader header;
  pkt->PeekHeader (header);
  Ptr<Node> myNode = dev->GetNode ();
  uint32_t seq = header.GetSeq ();
  uint16_t forwardCount = header.GetData ();
  // std::cout << "forwardCount = " << forwardCount << std::endl;
  uint64_t origin = header.GetOrigin ();
  if (myNode->GetId () != origin)
    {
      adjMatrix.SetEntry (myNode->GetId (), seq, 1.0);
      // switch (forwardCount)
      //   {
      //     case 0: {
      //       WaveNetDeviceExample::SendOnePacket (SCH1, seq, myNode->GetId (), forwardCount + 1,
      //                                            origin);
      //       break;
      //     }
      //   default:
      //     break;
      //   }
      if (forwardCount < 3)
        {
          WaveNetDeviceExample::SendOnePacket (SCH1, seq, myNode->GetId (), forwardCount + 1,
                                               origin);
        }
      // WaveNetDeviceExample::SendOnePacket (SCH1, seq, myNode->GetId (), forwardCount + 1,
      //                                            origin);
    }
  return true;
}

void
WaveNetDeviceExample::SendOnePacket (uint32_t channel, uint32_t seq, uint32_t senderNode,
                                     uint16_t forwardCount, uint64_t origin)
{
  Ptr<WaveNetDevice> sender = DynamicCast<WaveNetDevice> (devices.Get (senderNode));
  Mac48Address bssWildcard = Mac48Address::GetBroadcast ();
  // std::cout << senderNode << "send forwardcount = " << forwardCount << std::endl;
  Ptr<Packet> p = Create<Packet> (1000);
  MyHeader newHeader;
  newHeader.SetOrigin (origin);
  newHeader.SetData (forwardCount);
  newHeader.SetSeq (seq);
  p->AddHeader (newHeader);
  const TxProfile txProfile = TxProfile (SCH1);
  sender->RegisterTxProfile (txProfile);
  if (sender->Send (p, bssWildcard, 0))
    {
      // sender->DeleteTxProfile (SCH1);
    }
}

double
WaveNetDeviceExample::SendExample (const std::string &posfile, uint32_t lanes, double lane_width,
                                   uint32_t nodeNum, const std::string &mobilityModel,
                                   double maxVelocity, double minVelocity, uint64_t origin)
{
  CreateWaveNodes (posfile, lanes, lane_width, nodeNum, mobilityModel, maxVelocity, minVelocity);
  adjMatrix = std::AdjMatrix (nodes.GetN ());
  // Alternating access without immediate channel switch
  const SchInfo schInfo = SchInfo (SCH1, false, EXTENDED_CONTINUOUS);
  for (uint32_t i = 0; i != nodes.GetN (); i++)
    {

      Ptr<WaveNetDevice> dev = DynamicCast<WaveNetDevice> (devices.Get (i));
      Simulator::Schedule (Seconds (0.0), &WaveNetDevice::StartSch, dev, schInfo);
    }
  for (uint32_t i = 0; i != 100; i++)
    {
      Simulator::Schedule (Seconds (0.1 + 0.3 * i), &WaveNetDeviceExample::SendOnePacket, this,
                           SCH1, i, origin, 0, origin);
    }

  Simulator::Stop (Seconds (30.2));
  Simulator::Run ();
  Simulator::Destroy ();
  return adjMatrix.RowSum ();
}

int
main (int argc, char *argv[])
{
  double minVelocity = 10.3535;
  double maxVelocity =  11.8686;
  // uint64_t sendNode = 0;
  uint32_t nodeNum = 5;
  CommandLine cmd;
  cmd.AddValue ("nodeNum", "number of node in simulation", nodeNum);
  cmd.Parse (argc, argv);

  WaveNetDeviceExample example;
  std::cout << "run WAVE WSMP routing service case:" << std::endl;
  double sumOfEachAvg = 0.0;
  for (uint32_t i = 0; i != nodeNum; i++)
    {
      sumOfEachAvg +=
          example.SendExample ("position_v_3.txt", 3, 4.0, nodeNum,
                               "ns3::ConstantPositionMobilityModel", maxVelocity, minVelocity, i);
    }
  std::cout << sumOfEachAvg / nodeNum << std::endl;
  return 0;
}
