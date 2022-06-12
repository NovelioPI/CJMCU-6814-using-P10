#include <DataTransaction.hpp>

Stream *stream = &Serial;

void waitForBytes(const int numBytes) {
    unsigned long startTime = millis();
    unsigned long timeout = 10 * numBytes;
    while (stream->available() < numBytes) {
        if (millis() - startTime >= timeout) {
            return;
        }
    }
}

// OPTIMZATION NOTE : Serial.readBytes is SLOW
// this one is much faster, but has no timeout
void readSignedBytes(int8_t *buffer, size_t n) {
    size_t i = 0;
    int c;
    while (i < n) {
        c = stream->read();
        if (c < 0)
            break;
        *buffer++ = (int8_t) c; // buffer[i] = (int8_t)c;
        i++;
    }
}

void write_data(float data)
{
    BinaryFloat bf;
    bf.floatingPoint = data;
    stream->write(bf.binary, 4);
}

float read_data()
{
    BinaryFloat bf;
    waitForBytes(4);
    readSignedBytes((int8_t*) bf.binary, 4);
    return bf.floatingPoint;
}
