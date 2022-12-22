#define MAX_STRING_LENGTH 4

char rxString[MAX_STRING_LENGTH];  // buffer to store received string
int rxIndex = 0;                   // index to store next character in rxString

while (1) {
    // Check if a character has been received
    if (UCA0RXBUF != EOF) {
        // Store the character in the rxString buffer
        rxString[rxIndex] = UCA0RXBUF;
        rxIndex++;

        // If the end of the string has been reached, terminate it and reset the index
        if (rxIndex == MAX_STRING_LENGTH) {
            rxString[rxIndex] = '\0';
            rxIndex = 0;
        }
    }
}
