## Routing

- In previous lectures, the topic of routing we've talked about how its IP is wrapped and how

  traffic is sent through ports.

- Autonomous System(AS)

  - Autonomous systems can control the range of IP addresses and the list of connection

    routes (AS), and helps router control and filtering.

- Interior vs. Exterior Routing Protocols

  - Interior Gateway Protocols: Communicate within the autonomous system.
    - Routing information Protocol
    - Open shortest path first
    - Intermediate system to intermediate system
    - mainly talk about this part
  - Exterior Gateway Protocols: Communicate between different autonomous systems
    - Border Gateway Protocol
    - added trust and traffic management

- Routing Tables

  - The router has its own memory to store in an initially blank routing table. The gateway

    receives external traffic, which is recorded in the routing table. If it encounters an

    unknown IP address, it sends the request to a higher-level ISP. ISP are divided into three

    tiers, from the smallest tier 3 to tier 1. Layer 1 providers form a network group and

    connect to other networks through non-clearing peers to find out who is responsible for

    the IP address.

  - The routing table contains: destination network, interface, and Metrix

    - Destination network: Router known range
    - Interface: An endpoint that transmits data
    - Metrix: Helps routing algorithms select paths

- Shortest Simple Path Problem

  - This problem has been studied by Dijkstra in CSCI313, finding the shortest path for

    graphs that minimize the sum of their weights without forming a cycle.

- Dynamic shortest simple path algorithms

  - The Internet is a dynamic graph, and Bellman-Ford is a more efficient algorithm than

    Dijkstra because Dijkstra needs to know the full graph first.

  - The Distance Vector Routing Protocol is a protocol based on bellman-Ford algorithm

- Distance vector algorithm

  - Assuming that each network knows its address and the cost of connecting to other

    networks, the distance vector is a summary of the routing table that routers periodically

    share to know the best known path for the network.

  - Adding other networks through the protocol results in the presence of nodes that are

    not directly connected.

  - The new distance vectors are then parsed using bellman-Ford equations and the

    routing table is updated to accommodate network changes more quickly.

  - Fill all the resulting distance vectors into a table to find the best known route.

- Link-state routing protocol

  - The disadvantage of distance vector protocols is that they are too slow to respond to

    distances because they send information through the adjacency of vertices

  - The link-state routing protocol allows faster convergence without worrying about

    infinity. It will replace Bellman-Ford.

  - The information is stored in the link state database. Expired or missing data can be

    obtained by sending link status request to obtain LSA. Then, Dijkstra is used to calculate

    the shortest path from all networks to AS.

- OSPF (Open Shortest Path First) and IS-IS(Intermediate system to Intermediate System)

  - Both use link-state routing

  - The difference is running on a different layer. Is-is IS becoming more popular because it

    runs at the data link layer and supports IPv6

- Link state defect

  - O(n^3) Backbone routers, area border routers, and internal routers are created by OSPF

    and IS-IS. OSPF uses subnets. Network changes in an area are transmitted only in this

    area. Keep the LSDB small and fewer LSA.

    

