#ifndef CONFIG_H
#define CONFIG_H
#define _DEF_SPEEDRING  (0)

#define _DEF_ANGLERING  (1)

#define _DEF_GYRORING   (2)

#define _DEF_SERVORING  (3)

#define _DEF_KP         (0)

#define _DEF_KI         (1)

#define _DEF_KD         (2)

#define _DEF_TARGET     (3)

#define _FUNC_ABS(value)    (value<0?(-value):value)

#define _FUNC_LIMIT(min,max,value)  (value>max?max:(value<min?min:(value)))

#define _FUNC_POLE(value)   (value<0?(-1):1)

#define _DEF_STEP_SPEEDKP (0.1)

#define _DEF_STEP_SPEEDKI   (0.1)

#define _DEF_STEP_SPEEDKD   (0.1)

#define _DEF_STEP_SPEEDTARGET   (0.1)

#define _DEF_STEP_ANGLEKP   (0.1)

#define _DEF_STEP_ANGLEKI   (0.1)

#define _DEF_STEP_ANGLEKD   (0.1)

#define _DEF_STEP_ANGLETARGET   (0.1)

#define _DEF_STEP_GYROKP   (0.1)

#define _DEF_STEP_GYROKI   (0.1)

#define _DEF_STEP_GYROKD   (0.1)

#define _DEF_STEP_GYROTARGET   (0.1)

#define _DEF_STEP_SERVOKP   (0.1)

#define _DEF_STEP_SERVOKI   (0.1)

#define _DEF_STEP_SERVOKD   (0.1)

#define _DEF_STEP_TARGET   (0.1)


#define _DEF_CMD_SPEEDKP    (0xAAFF000B)

#define _DEF_CMD_SPEEDKI    (0xAAFF000C)

#define _DEF_CMD_SPEEDKD    (0xAAFF000D)

#define _DEF_CMD_SPEEDTARGET    (0)

#define _DEF_CMD_ANGLEKP    (0xAAFF0006)

#define _DEF_CMD_ANGLEKI    (0xAAFF0007)

#define _DEF_CMD_ANGLEKD    (0xAAFF0008)


#define _DEF_CMD_ANGLETARGET    (0)

#define _DEF_CMD_GYROKP     (0xAAFF0000)

#define _DEF_CMD_GYROKI     (0xAAFF0001)

#define _DEF_CMD_GYROKD     (0xAAFF0002)

#define _DEF_CMD_GYROTARGET     (0)

#define _DEF_CMD_SERVOKP        (0)

#define _DEF_CMD_SERVOKI        (0)

#define _DEF_CMD_SERVOKD        (0)

#define _DEF_CMD_SERVOTARGET    (0)

#define _DEF_CMD_MOTOR        (0xAAFF0104)

#define _DEF_MOTOR_START        (0)

#define _DEF_MOTOR_STOP         (1)

#define _DEF_MAX_GYROKP        (20)

#define _DEF_MAX_GYROKI        (1)

#define _DEF_MAX_GYROKD        (40)

#define _DEF_MAX_GYROTARGET    (1)

#define _DEF_MAX_ANGLEKP        (40)

#define _DEF_MAX_ANGLEKI        (1)

#define _DEF_MAX_ANGLEKD        (40)

#define _DEF_MAX_ANGLETARGET    (2)

#define _DEF_MAX_SPEEDKP        (0.5)

#define _DEF_MAX_SPEEDKI        (1)

#define _DEF_MAX_SPEEDKD        (0.1)

#define _DEF_MAX_SPEEDTARGET    (50)

#define _DEF_MAX_SERVOKP        (0.5)

#define _DEF_MAX_SERVOKI        (1)

#define _DEF_MAX_SERVOKD        (0.1)

#define _DEF_MAX_SERVOTARGET    (50)

//------------

#define _DEF_DEFUALT_GYROKP        (9.59)

#define _DEF_DEFUALT_GYROKI        (0.5586)

#define _DEF_DEFUALT_GYROKD        (28.42)

#define _DEF_DEFUALT_GYROTARGET    (0)

#define _DEF_DEFUALT_ANGLEKP        (25.01)

#define _DEF_DEFUALT_ANGLEKI        (0)

#define _DEF_DEFUALT_ANGLEKD        (-30.37)

#define _DEF_DEFUALT_ANGLETARGET    (0)

#define _DEF_DEFUALT_SPEEDKP        (-0.1782)

#define _DEF_DEFUALT_SPEEDKI        (0)

#define _DEF_DEFUALT_SPEEDKD        (0.061)

#define _DEF_DEFUALT_SPEEDTARGET    (50)

#define _DEF_DEFUALT_SERVOKP        (0)

#define _DEF_DEFUALT_SERVOKI        (0)

#define _DEF_DEFUALT_SERVOKD        (0)

#define _DEF_DEFUALT_SERVOTARGET    (0)



struct VMotorMsg{

    unsigned int type;
    union{
    float data;
    int cmd;
    }buf;



    VMotorMsg(unsigned int TYPE,float DATA){

        type=TYPE;

        buf.data=DATA;
    }
    VMotorMsg(unsigned int TYPE,int CMD){

        type=TYPE;

        buf.cmd=CMD;
    }


};



#endif // CONFIG_H
