#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "Message.h"

static char *payload_str_test_1; // First test of checksum funtion

static char *payload_str_test_2; // 2nd test check sum function

static char *payload_str_test_3; // 3rd test check sum function

static uint8_t checksum_count = 0; // Checksum test success counter

int main(void)
{

    // BOARD_Init();

    // Checksum Tests

    payload_str_test_1 = "RES,1,0,3"; // One sample transmision from manual (0x5A)

    payload_str_test_2 = "SHO,2,2"; // another one (0x54)

    payload_str_test_3 = "REV,12345"; // a third sample transmison (0x5C)

    uint8_t check_test_1 = Message_CalculateChecksum(payload_str_test_1); // Checksum Test 1 Result

    uint8_t check_test_2 = Message_CalculateChecksum(payload_str_test_2); // Checksum Test 2 Result

    uint8_t check_test_3 = Message_CalculateChecksum(payload_str_test_3); // Checksum Test 3 Result

    if (check_test_1 == 0x5A)
    { // If Test 1 = Expected

        checksum_count++; // Increment counter
    }

    if (check_test_2 == 0x54)
    { // Test 2 = Expected

        checksum_count++; // Increment counter
    }

    if (check_test_3 == 0x5C)
    { // Test 3 = Expected

        checksum_count++; // Increment counter
    }

    printf("Message_CalculateChecksum() Passed: %d / 3 Tests!\n", checksum_count);
}