#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HRPS_HT_MEAS_MAX_LEN            (13)

#define HRPS_MANDATORY_MASK             (0x0F)
#define HRPS_BODY_SENSOR_LOC_MASK       (0x30)
#define HRPS_HR_CTNL_PT_MASK            (0xC0)

/* Attributes State Machine */
enum
{
    HRS_IDX_SVC,

    HRS_IDX_HR_MEAS_CHAR,
    HRS_IDX_HR_MEAS_VAL,
    HRS_IDX_HR_MEAS_NTF_CFG,

    HRS_IDX_BOBY_SENSOR_LOC_CHAR,
    HRS_IDX_BOBY_SENSOR_LOC_VAL,

    HRS_IDX_HR_CTNL_PT_CHAR,
    HRS_IDX_HR_CTNL_PT_VAL,

    HRS_IDX_NB,
};

class BTServer {

public:
    BTServer() {};
    bool start();
    bool stop();

};