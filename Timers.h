/*******************************************/
/* Timers.h                                */
/* Author: Greg Semeraro                   */
/* Written By: Josh Woodward               */
/* February 19, 2014                       */
/* Timers module used as part of a         */
/* performance measurement and modification*/
/* assignment.                             */
/*            				   */
/*******************************************/

#ifndef _TIMERS_H_
#define _TIMERS_H_

/*********************************************/
/* The timers are enabled when the code      */
/* is compiled. The following pre-processor  */
/* code issues a warning and includes the    */
/* necessary system header files when the    */
/* timers are enabled                        */
/*********************************************/

#if defined(EN_TIME)
	#include <stdio.h>
	#include <time.h>
	#if defined(WARNING_MSG)
		#warning Timers enabled! Execution could be adversly effected.
	#endif
#endif

/**************************************************************************
* The time instrumentation macro definitions. If EN_TIME is not defined
* the n the macros are defined as null comments to allow the code to be
* correctly compiled.
**************************************************************************/

#if defined(EN_TIME)
/*************************************************************************
* Declare the timer. Initialize the timer (particularly the accumulated
* elapsed time and the timer state.
*************************************************************************/
#define DECLARE_TIMER(A)						\
	struct{								\
	/* Start Time - set when the timer is started */		\
	clock_t Start;							\
	/* Stop Time - set when the timer is stopped */ 		\
	clock_t Stop;							\
	/* Elapsed Time - Accumulated when the timer is stopped */	\
	clock_t Elapsed;						\
	/* Timer State - set automatically; 0=stopped \ 1=running */	\
	int State;							\
	} A = { /* Elapsed time and state must be initially zero */ 	\
	/* Start = */ 0,						\
	/* Stop = */ 0, 						\
	/* Elapsed = */ 0, 						\
	/* State = */ 0, 						\
	}; /* Timer has been declared and defined */			\
	printf("\nTimer Instantiated\n");

/************************************************************************
* Start the timer. Print an error if it is already running, set
* the state to running and then start the timer
************************************************************************/
#define START_TIMER(A)							\
{									\
/* It is an error if the timer is currently running */			\
if(1 == A.State)							\
	fprintf(stderr, "Error, running timer "#A" started.\n");	\
/* Set the state to running */						\
A.State=1;								\
/* Set the start time, done last to maximize accuracy */		\
A.Start=clock();							\
printf("\nTimer Started\n");						\
} /* START_TIMER() */							\


/************************************************************************
* Reset the timer. Clear the elapsed time.
************************************************************************/
#define RESET_TIMER(A)							\
{									\
/* Reset the elapsed time to zero */					\
A.Elapsed=0;								\
printf("\nTimer reset!\n");							\
} /* RESET_TIMER(A) */




#endif /* Ifdefine EN_TIME */
#endif /* Ifdefine TIMERS */
