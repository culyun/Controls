#include "os.h"
#include "Tasks.h"
#include <bsp.h>
#include "config.h"
#include "common.h"
#include "Pedals.h"
#include "Minions.h"
#include "Contactors.h"
#include "CANbus.h"
#include "CAN_Queue.h"

static OS_TCB Task1TCB;
static CPU_STK Task1Stk[DEFAULT_STACK_SIZE];

void Task1(void *arg)
{   
    CPU_Init();
    
    CANbus_Init(CARCAN);
    CAN_Queue_Init();
    // BSP_UART_Init(UART_2);
    Pedals_Init();
    Minions_Init();
    Contactors_Init();

    OS_CPU_SysTickInit(SystemCoreClock / (CPU_INT32U)OSCfg_TickRate_Hz);

    OS_ERR err;

    // Initialize Telemetry
    OSTaskCreate(
        (OS_TCB*)&Telemetry_TCB,
        (CPU_CHAR*)"Telemetry",
        (OS_TASK_PTR)Task_Telemetry,
        (void*)NULL,
        (OS_PRIO)TASK_TELEMETRY_PRIO,
        (CPU_STK*)Telemetry_Stk,
        (CPU_STK_SIZE)WATERMARK_STACK_LIMIT,
        (CPU_STK_SIZE)TASK_TELEMETRY_STACK_SIZE,
        (OS_MSG_QTY)0,
        (OS_TICK)0,
        (void*)NULL,
        (OS_OPT)(OS_OPT_TASK_STK_CLR),
        (OS_ERR*)&err
    );
    assertOSError(err);

    bool lightState = false;
    State contactorState = OFF;

    CANDATA_t msg;
    
    while (1){
        // Switches can be modified through hardware

        // Check light
        lightState = !lightState;
        Minions_Write(BRAKELIGHT, lightState);

        // Check contactors (HAVE NOTHING HOOKED UP TO CONTACTORS)
        contactorState = contactorState == OFF ? ON : OFF;
        Contactors_Set(MOTOR_CONTROLLER_BYPASS_PRECHARGE_CONTACTOR, contactorState, true);
        Contactors_Set(ARRAY_PRECHARGE_BYPASS_CONTACTOR, contactorState, true);

        CANbus_Read(&msg, CAN_BLOCKING, CARCAN);

        OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
        // Use a logic analyzer to read the CAN line and see if the data shows up correctly    
    }
}

int main()
{
    OS_ERR err;
    OSInit(&err);

    // create tester thread
    OSTaskCreate(
        (OS_TCB *)&Task1TCB,
        (CPU_CHAR *)"Task 1",
        (OS_TASK_PTR)Task1,
        (void *)NULL,
        (OS_PRIO)5,
        (CPU_STK *)Task1Stk,
        (CPU_STK_SIZE)DEFAULT_STACK_SIZE / 10,
        (CPU_STK_SIZE)DEFAULT_STACK_SIZE,
        (OS_MSG_QTY)0,
        (OS_TICK)NULL,
        (void *)NULL,
        (OS_OPT)(OS_OPT_TASK_STK_CLR),
        (OS_ERR *)&err);
    assertOSError(err);

    OSStart(&err);
}