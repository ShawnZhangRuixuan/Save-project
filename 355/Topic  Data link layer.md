# Topic : Data link layer

- Data Link layer

  - The Data Link layer tends to transfer Data through connected nodes. These nodes can

    consist of calculators, routers, or switches.

- Media Access Control

  - By converting wired, optical, or wireless data into signals

  - After receiving the signal at the physical layer, the signal is converted into bits and

    arranged

  - If transmission is required, the bits are also converted into a final signal

- Logical Link Control

  - LLC is higher than the media Access control sub-layer and also acts as an interface

    between the media access control and the network layer. After receiving upper-layer

    messages, the LLC sends the data to the corresponding network interface. Where

    necessary, it will use multiplexing to ensure the coexistence of network layer protocols.

    Finally, the header is wrapped and sent to the MAC. The MAC executes backwards when

    it receives a frame.

  - A frame is a packaged packet of data.

  - There are two main protocol families: 802.3 and 802.11. These protocols are updated

    with one or two letter suffixes.

- Ethernet (IEEE802.3)

  - Ethernet uses copper cables and optical fiber connections. Frames contain six or seven

    fields. Each frame uses a 12-byte interval separation to facilitate synchronization

  - Leading code (8 bytes)

    - The first eight bytes are the leading codes, which alternate ones and zeros to

      synchronize the clock. The last byte of the 8 bytes will be changed to 1 to indicate

      the beginning of the next section.

- The MAC address

  - MAC addresses are used to help the data link layer find them. MAC address is the only

    field that represents all devices. MAC addresses have 48 digits that make up 281 trillion

    combinations. Each network device has its own unique MAC address. The first 24 bits

    are unique to the organization and the second 24 bits are assigned to the supplier. One

    can determine the source of a device's manufacture by looking up its OUI.

  - Special MAC Address

    - Most routes are one-way. Only sender and receiver. But broadcast addresses allow

      messages to be sent to the entire local network. Some MAC addresses are

      multicast addresses.

- IEEE 802.1Q(4 bytes)

  - Provides VLAN and quality of service support. VLAN means virtual LOCAL area network.

    It solves the mismatch between physical topology and virtual topology. VlAN allow

    multiple private networks to be created on a physical device to work for a large number

    of people.

  - Quality of service (QOS) allows the network to queue frames under specified

    circumstances or discard them altogether to give priority to software such as voice over 

    IP, competitive games or stock trading.

- Frame check sequence (4 bytes)

  - It uses a 32-bit cyclic redundancy check algorithm to generate a summary of the

    obtained data and add it to the frame.

  - After receiving the data, the receiver will use the cyclic redundancy check algorithm to

    calculate the digest and compare it with the original digest. If they do not match, they

    are considered corrupted and discarded.

- Switch

  - A network switch is a network device that connects data. It checks each frame and

    sends the information to a physical port at the appropriate target MAC address.

  - For example, if device 1 wants to send a message to device 3, it will also send the

    message to device 2, but device 2 will clear the message.

  - The switch records known devices and stores them on the local network. When a device

    wants to reply to a message, the switch knows which port to send it to.

- Wifi Frame

  - The main categories of frameworks are management, control and data.

    Management frames have beacons, probes, authentication, and associations.

    Controls include ACK, block-acks, RTS, and CTS