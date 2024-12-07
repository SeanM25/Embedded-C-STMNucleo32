#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "Message.h"
#include "BattleBoats.h"
#include "BOARD.h"

#define length_check_sum 2 // Length of the checksum always 2
#define CHA_DATA_AMT 1     // Amount of data within the CHA string
#define ACC_DATA_AMT 1     // Amount of data within the ACC string
#define REV_DATA_AMT 1     // Amount of data within the REV string
#define SHO_DATA_AMT 2     // Amount of data within the SHO string
#define RES_DATA_AMT 3     // Amount of data within the RES string

static const char *CHA = "CHA"; // Message ID for Challenge for Comparison
static const char *ACC = "ACC"; // Message ID for Accept for Comparison
static const char *REV = "REV"; // Message ID for Reveal for Comparison
static const char *SHO = "SHO"; // Message ID for Shot for Comparison
static const char *RES = "RES"; // Message ID for Result for Comparison

typedef enum
{

    WAIT_FOR_DELIM, // Waiting State

    RECORDING_PAYLOAD, // Record Payload State

    RECORDING_CHECKSUM // Record checksum state

} Message_Decode_State; // The three possible states of the Message FSM

static Message_Decode_State Message_FSM_STATE = WAIT_FOR_DELIM; // Intial state of the Message FSM is the waiting state since until we recieve a message with $ nothing should be done

uint8_t Message_CalculateChecksum(const char *payload)
{ // Checksum function

    uint8_t result_Check_Sum = 0; // Gets final result of the checksum

    for (int i = 0; i < strlen(payload); i++)
    { // Iterate through payload string

        result_Check_Sum ^= payload[i]; // Add the XOR result for each character in the payload to the check sum result EX: RES,1,0,3 = 90 or 0x5A
    }

    return result_Check_Sum;
}

int Message_ParseMessage(const char *payload, const char *checksum_string, BB_Event *message_event)
{

    // Reset msg event parameters each time this function is called. param0-2 gets 1-3 fields of data depending on what type of message we have as indicated by msg_id

    message_event->param0 = 0; // Reset param 0

    message_event->param1 = 0; // Reset param 1

    message_event->param2 = 0; // Reset param 2

    // Standard Error Cases:

    if (strlen(checksum_string) != length_check_sum)
    { // If the length of the checksum is not equal to the expected length of 2

        message_event->type = BB_EVENT_ERROR; // Signal a Battle Boat Error Event

        return STANDARD_ERROR; // Return Standard Error
    }

    uint8_t check_sum_Payload_Actual = Message_CalculateChecksum(payload); // Get actual checksum of payload from check sum functiom

    uint8_t given_check_sum = (uint8_t)strtoul(checksum_string, NULL, 16); // We need to check the passed checksum with the payload to see if they match. To do this we can use strtoul

    // which is the C equivalent of something like stoi. strtoul specifies string, ending pointer, and base for parameters. I suppose calling checksum might work too
    // However that sounds like a bad idea to use a function intended for payload for a checksum

    if (check_sum_Payload_Actual != given_check_sum)
    { // If the given check sum doesn't equal the calculated payload checksum

        message_event->type = BB_EVENT_ERROR; // Return an BB event error

        return STANDARD_ERROR; // Return standard error
    }

    // Check for valid message templates (5 Possibilites):

    // Challenge (CHA) 1 Piece Data: hash_a
    // Accept (ACC) 1 Piece Data: B from Player B
    // Reveal (REV) 1 Piece Data: A from Player A
    // Shot (SHO) 2 Pieces Data: Row, Col Coords
    // Result (RES) 3 Pieces Data: Row, Col, Guess Result

    uint8_t expected_amount_msg_data = 0; // Data counter for different messages

    char *get_msg_ID; // String to get message id

    get_msg_ID = strtok(payload, ","); // Get Message Id from the payload

    // See if the message matches any of the 5 templates and if they do update the param values as approrpiate otherwise return an error.

    // A string comparison of some sort along with perhaps a loop to append the data seems appropriate
}

int Message_Encode(char *message_string, Message message_to_encode)
{

    // Message Encode function skeleton

    return 0;
}

// Message State Machine goes in Message_Decode()

int Message_Decode(unsigned char char_in, BB_Event *decoded_message_event)
{

    // Message State Machine Skeleton Code

    switch (Message_FSM_STATE)
    {

    case WAIT_FOR_DELIM: // Waiting State

        break;

    case RECORDING_PAYLOAD: // Record Payload State

        break;

    case RECORDING_CHECKSUM: // Record Checksum State

        break;
    }

    return 0;
}
