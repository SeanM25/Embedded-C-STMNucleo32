#include <stdint.h>
#include "Message.h"
#include "BattleBoats.h"
#include "Agent.h"

typedef enum
{

    Start,

    Challenging,

    Accepting,

    End_Screen,

    Wait_To_Send,

    Attacking,

    Defending

} Agent_States; // Various states of the Agent State Machine

// Agent.c functions go here

void AgentInit(void)
{

    // Skeleton code
}

AgentState AgentGetState(void)
{

    // Skeleton code

    AgentState Agent_SM_State;

    return Agent_SM_State;
}

Message AgentRun(BB_Event event)
{

    // Agent SM Here

    Message event_msg;

    return event_msg;
}