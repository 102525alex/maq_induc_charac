/*
 * async1.c qdo model of the induction machine in general reference frame  
 * Author: Alberto Sanchez
 * 17/03/2012
 *
 * ver 1.0
 *
 * Model Description in this version. 
 * Note: All variables refered to the stator.
 *
 * States:  x = [Psi_qs Psi_ds Psi_qr Psi_dr wr/wb]
 * Inputs:  u = [v_qs v_ds Tmech Tdamp]
 * Outputs: y = [Tem wr i_qs i_ds Psi_qs Psi_ds Psi_qr Psi_dr]
 *
 * PAR = [xls xm xlr rs rr J P]
 * REF = [w wb]
 *
 */

#define S_FUNCTION_NAME async1

#include "simstruc.h"
#include <math.h>

#define XINIT   ssGetArg(S,0)
#define PAR	ssGetArg(S,1)
#define REF	ssGetArg(S,2)

/*
 * mdlInitializeSizes - initialize the sizes array
 */
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumContStates(S, 5);       /* number of continuous states           */
    ssSetNumDiscStates(S, 0);       /* number of discrete states             */
    ssSetNumInputs(S, 4);           /* number of inputs                      */
    ssSetNumOutputs(S, 8);          /* number of outputs                     */
    ssSetDirectFeedThrough(S, 1);   /* direct feedthrough flag               */
    ssSetNumSampleTimes(S, 1);      /* number of sample times                */
    ssSetNumSFcnParams(S, 3);       /* number of input arguments             */
    ssSetNumRWork(S, 0);            /* number of real work vector elements   */
    ssSetNumIWork(S, 0);            /* number of integer work vector elements*/
    ssSetNumPWork(S, 0);            /* number of pointer work vector elements*/
}

/*
 * mdlInitializeSampleTimes - initialize the sample times array
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}


/*
 * mdlInitializeConditions - initialize the states
 */
static void mdlInitializeConditions(double *x0, SimStruct *S)
{
int i;

for (i = 0; i < 5; i++) {
   x0[i] = mxGetPr(XINIT)[i];
}
}

/*
 * mdlOutputs - compute the outputs
 */

static void mdlOutputs(double *y, double *x, double *u, SimStruct *S, int tid)
{
double xls, xm, xlr, rs, rr, J, P, wb, w;
double Tem, i_qs, i_ds, XM, Psi_mq, Psi_md;

xls = mxGetPr(PAR)[0];
xm = mxGetPr(PAR)[1];
xlr = mxGetPr(PAR)[2];
rs = mxGetPr(PAR)[3];
rr = mxGetPr(PAR)[4];
J = mxGetPr(PAR)[5];
P = mxGetPr(PAR)[6];
//w = x[4]*120*3.1415925;
w = mxGetPr(REF)[0];
wb = mxGetPr(REF)[1];
  
XM = (xlr*xls*xm)/(xlr*xls + xm*xlr + xm*xls);
Psi_mq = XM*(x[0]/xls + x[2]/xlr);
Psi_md = XM*(x[1]/xls + x[3]/xlr);
i_qs = (x[0]-Psi_mq)/xls;
i_ds = (x[1]-Psi_md)/xls;
Tem = (x[1]*i_qs-x[0]*i_ds)*3*P/(4*wb);
  
y[0] = Tem;
y[1] = x[4]*2/P;
y[2] = i_qs;
y[3] = i_ds;
y[4] = x[0];
y[5] = x[1];
y[6] = x[2];
y[7] = x[3];
}

/*
 * mdlUpdate - perform action at major integration time step
 */

static void mdlUpdate(double *x, double *u, SimStruct *S, int tid)
{
}

/*
 * mdlDerivatives - compute the derivatives
 */
static void mdlDerivatives(double *dx, double *x, double *u, SimStruct *S, int tid)
{

double xls, xm, xlr, rs, rr, J, P, wb, w;
double Tem, i_qs, i_ds, XM, Psi_mq, Psi_md;

xls = mxGetPr(PAR)[0];
xm = mxGetPr(PAR)[1];
xlr = mxGetPr(PAR)[2];
rs = mxGetPr(PAR)[3];
rr = mxGetPr(PAR)[4];
J = mxGetPr(PAR)[5];
P = mxGetPr(PAR)[6];
//w = x[4]*120*3.1415925;
w = mxGetPr(REF)[0];

wb = mxGetPr(REF)[1];

XM = (xlr*xls*xm)/(xlr*xls + xm*xlr + xm*xls);
Psi_mq = XM*(x[0]/xls + x[2]/xlr);
Psi_md = XM*(x[1]/xls + x[3]/xlr);
i_qs = (x[0]-Psi_mq)/xls;
i_ds = (x[1]-Psi_md)/xls;
Tem = (x[1]*i_qs-x[0]*i_ds)*3*P/(4*wb);

dx[0] = wb*(u[0] - x[1]*w/wb + (Psi_mq - x[0])*rs/xls);
dx[1] = wb*(u[1] + x[0]*w/wb + (Psi_md - x[1])*rs/xls);
dx[2] = wb*(-((w/wb) - x[4])*x[3] + (Psi_mq - x[2])*rr/xlr);
dx[3] = wb*(((w/wb) - x[4])*x[2] + (Psi_md - x[3])*rr/xlr);
dx[4] = (Tem + u[2] - u[3])*P/(2*J*wb);
}


//States:  x = [Psi_qs Psi_ds Psi_qr Psi_dr wr/wb]

/*
 * mdlTerminate - called when the simulation is terminated.
 */
static void mdlTerminate(SimStruct *S)
{
}

#ifdef	MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
