# Topic: network Layer

- Network Layer

  - In this lesson, we will discuss the architecture of the Internet, how routers work, and the

    structure of Internet protocols and IP packets. The function of the network layer is to

    forward packets for different network devices and communicate with each other in an

    end-to-end manner.

- Local Area Network (LAN)

  - A LAN is a platform for the interconnection of a single physical network. If you want to

    communicate with devices outside the local network on the LAN, you need to use

    special devices. Routers act as gateways between networks. If the topology of each

    network is known, the network bridge can be used to connect the entire network to

    communicate.

- Internet Protocol

  - IP is the most common Internet word we hear in our daily life. It is available in both ipv4

    and ipv6 versions. There is also an ICMP for reporting errors. When a host wants to

    send a message to the Internet, the beginning of the message is given a header by IP.

    This header does not change with each hop. The most important things in the IP header

    are the source and destination addresses

    - IP addresses help ipv4 find addresses. Each device connected to the Internet has

      its own IP address. The SOURCE of the IP address is the network provider. IP

      addresses remain the same unless there is a special extra charge for IP addresses.

    - IP address consists of four groups of eight bytes each. Each group is divided by

      points. Each group of numbers ranges from 0 to 255. Numbers are expressed in

      decimal notation. But since the number is a 32 digit number, it has an upper limit.

      Coupled with the popularity of modern networks, IP addresses are facing the

      problem of exhaustion.

    - The IP address is assigned by the network component and the host component

      Network components give different addresses but host components allow

      common address prefixes.

- Classful Addressing

  - In the earliest days, network addresses were divided into eight-bit network/host

    components. There are three types of addresses.

  - Class A: The network has one octet and the host has three. Each network can have a

    maximum of 16,777,214 devices. The first octet identifier in the range 0-123.

  - Class B: The network has two octets and the host has two. A maximum of 65534

    devices. The first octet identifier in the 128-191 range.

  - Class C: The network has three octets and the host has one. Maximum of 254 hosts. The

    first octet identifier in the 192-223 range.

  - The downside is that there are only three types of IP addresses. Small companies that

    need more than a Class C address have to either get a class C address or upgrade to a

    class B address.

- Classless Interdomain Routing

  - CIDR is by far the most commonly used in modern applications. CIDR does not change

    the entire octet at once. Instead, a single bit is moved from the network to the host. The

    same four groups of eight numbers. Convert it to binary. The first 20 represent the

    network and the last 12 represent the host.

- IP packet structure

  - Version (4 bits) Determines the IP version used by the packet.

    The IHL (4 bits) represents the length of the Internet header.

    Service type specifies data about QoS technology.

    Total length specifies the length of the entire packet (up to 65535)

  - The identifier (16 bits) is used to group messages. Flags (3 bits) The first digit is always 0, the second indicates whether to segment. The third place is just whether there are more segments. Fragment offsets (13 bits) sort according to the receiving device's instructions to help put the message into the pointing fragment.

- Dynamic IP and static IP

  - Dynamic IP addresses are assigned by DHCP. It will expire and revert to the DHCP

    server. Applies to devices that do not need to communicate with other devices.

    (Desktop or laptop).

  - Static IP is suitable for devices that need to communicate (printers). Static IP never

    expires, and static IP addressing can also be set up through the router.

- How Routers Encapsulate and De-encapsulate data.

  - All routers have a special entry called a gateway. TTL is reduced by the router at each

    hop. When its value is 0, the packet is discarded. At each hop, a new header is appended to the IP packet. After each hop, its header is discarded because it only supports single-hop transmission. 

    

    