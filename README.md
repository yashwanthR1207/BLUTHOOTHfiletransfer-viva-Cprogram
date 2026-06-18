# BLUTHOOTHfiletransfer-viva-Cprogram
# Bluetooth File Transfer Simulation using Stop-and-Wait ARQ

A C-based simulation of Bluetooth file transfer implementing the Stop-and-Wait ARQ (Automatic Repeat Request) protocol. The program ensures reliable file transmission by detecting packet loss and corruption using checksum verification and retransmission mechanisms.

---

## Features

- File transfer using packet-based communication
- Stop-and-Wait ARQ protocol implementation
- XOR checksum for error detection
- Simulated packet loss
- Simulated packet corruption
- ACK/NACK communication
- Automatic retransmission
- Reliable file reconstruction at receiver side
- Transfer statistics display

---

## Project Structure

```text
Bluetooth-File-Transfer/
│
├── bluetooth_transfer.c
├── input.txt
├── received.txt
└── README.md
```

---

## Configuration

The following parameters can be modified in the source code:

```c
#define CHUNK_SIZE 32
#define MAX_RETRIES 3
#define LOSS_CHANCE 20
#define CORRUPT_CHANCE 10
```

| Parameter | Description |
|------------|------------|
| CHUNK_SIZE | Number of bytes per packet |
| MAX_RETRIES | Maximum retransmission attempts |
| LOSS_CHANCE | Probability of packet loss (%) |
| CORRUPT_CHANCE | Probability of packet corruption (%) |

---

## How It Works

### Sender

1. Reads data from `input.txt`.
2. Divides the file into packets of 32 bytes.
3. Calculates an XOR checksum.
4. Sends packets through the simulated Bluetooth channel.

### Channel

The channel randomly:

- Drops packets (20% chance)
- Corrupts packets (10% chance)

### Receiver

1. Receives the packet.
2. Recalculates checksum.
3. Compares it with the received checksum.
4. Sends:
   - ACK if the packet is correct
   - NACK if the packet is corrupted

### Retransmission

If a packet is lost or corrupted:

- The sender retransmits the packet.
- Maximum 3 retry attempts are allowed.

---

## Compilation

Using GCC:

```bash
gcc bluetooth_transfer.c -o transfer
```

---

## Execution

Run the program:

```bash
./transfer
```

---

## Input Example

Create an `input.txt` file:

```text
Hello World!
This file is transferred using Stop-and-Wait ARQ simulation.
```

---

## Sample Output

```text
====================================
 Bluetooth File Transfer Simulation
 Stop-and-Wait ARQ Protocol
====================================

Sender   : Sending Packet 1
Receiver : Packet 1 RECEIVED -> ACK

Sender   : Sending Packet 2
Channel  : Packet 2 LOST
Sender   : Retransmitting Packet 2 (Attempt 1)

Sender   : Sending Packet 2
Receiver : Packet 2 RECEIVED -> ACK

====================================
 File Transfer Completed Successfully
====================================

Total Packets Sent      : 2
Total Retransmissions   : 1
Output File             : received.txt
```

---

## Stop-and-Wait ARQ Flow

```text
+---------+
| Sender  |
+---------+
     |
     v
 Send Packet
     |
     v
+------------------+
| Bluetooth Channel|
+------------------+
     |
     v
+---------+
| Receiver|
+---------+
     |
  +--+--+
  |     |
 ACK   NACK
  |     |
  |  Retransmit
  |
 Next Packet
```

---

## Learning Objectives

This project demonstrates:

- Data Communication Principles
- Stop-and-Wait ARQ Protocol
- Error Detection Techniques
- Reliable Data Transfer
- Packet Loss Recovery
- File Handling in C
- Network Communication Concepts

---

## Future Enhancements

- CRC-based error detection
- Sliding Window Protocol
- Go-Back-N ARQ
- Selective Repeat ARQ
- Real Bluetooth communication
- GUI interface
- Transfer speed statistics

---

## Author

**Yashwanth R**

Engineering Student | IoT Enthusiast | Networking & Embedded Systems Developer

---

## License

This project is released under the MIT License.

Feel free to use, modify, and distribute it for educational purposes.
