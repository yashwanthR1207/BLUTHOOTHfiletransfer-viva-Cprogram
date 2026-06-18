#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHUNK_SIZE 32
#define MAX_RETRIES 3
#define LOSS_CHANCE 20      // 20% packet loss
#define CORRUPT_CHANCE 10   // 10% corruption chance

typedef struct {
    int packetNo;
    int size;
    unsigned char data[CHUNK_SIZE];
    unsigned char checksum;
} Packet;

unsigned char calculateChecksum(unsigned char data[], int size) {
    unsigned char sum = 0;
    for (int i = 0; i < size; i++) {
        sum ^= data[i];   // XOR checksum
    }
    return sum;
}

int simulateBluetoothChannel(Packet *sent, Packet *received) {
    int loss = rand() % 100;

    if (loss < LOSS_CHANCE) {
        return 0; // packet lost
    }

    *received = *sent;

    int corrupt = rand() % 100;
    if (corrupt < CORRUPT_CHANCE && received->size > 0) {
        received->data[0] ^= 1; // corrupt one bit
    }

    return 1; // packet delivered
}

int receiver(Packet *packet, FILE *outputFile) {
    unsigned char newChecksum = calculateChecksum(packet->data, packet->size);

    if (newChecksum != packet->checksum) {
        printf("Receiver: Packet %d corrupted. NACK sent.\n", packet->packetNo);
        return 0;
    }

    fwrite(packet->data, 1, packet->size, outputFile);
    printf("Receiver: Packet %d received correctly. ACK sent.\n", packet->packetNo);
    return 1;
}

int main() {
    FILE *inputFile, *outputFile;
    Packet packet, receivedPacket;
    int packetNo = 1;

    srand(time(NULL));

    inputFile = fopen("input.txt", "rb");
    outputFile = fopen("received.txt", "wb");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (1) {
        packet.size = fread(packet.data, 1, CHUNK_SIZE, inputFile);

        if (packet.size == 0) {
            break;
        }

        packet.packetNo = packetNo;
        packet.checksum = calculateChecksum(packet.data, packet.size);

        int success = 0;
        int retries = 0;

        while (!success && retries < MAX_RETRIES) {
            printf("\nSender: Sending packet %d...\n", packet.packetNo);

            if (simulateBluetoothChannel(&packet, &receivedPacket)) {
                success = receiver(&receivedPacket, outputFile);
            } else {
                printf("Channel: Packet %d lost. No ACK received.\n", packet.packetNo);
            }

            if (!success) {
                retries++;
                printf("Sender: Retrying packet %d. Attempt %d\n",
                       packet.packetNo, retries);
            }
        }

        if (!success) {
            printf("Transfer failed at packet %d.\n", packet.packetNo);
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        packetNo++;
    }

    printf("\nFile transfer completed successfully.\n");
    printf("Check received.txt for reconstructed file.\n");

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}