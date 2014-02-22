/****************************************************************/
/* Josh Woodward						*/
/* jdw6359@rit.edu						*/
/* Applied Programming CMPE - 380				*/
/* Spring 2014							*/
/*								*/
/* Homework 2							*/
/*							        */
/* Program has same base as that of hw1 with exceptions         */
/* Input is gathered from static txt file rather than Data_c.o  */
/****************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include "DynamicArrays.h"
#include "Timers.h"

#define INITIAL_CAPACITY (0)

/* Function that will compute and store the coefficients A and B
   Function is passed a reference to A and B, as well as a reference
   to the DArray struct */
void ComputeCoefficients(double *A, double *B, DArray *DArrayPtr){

	/* Initialize variables to hold computations */
	double S_XX = 0.0;
	double S_XY = 0.0;
	double S_X = 0.0;
	double S_Y = 0.0;

	/* Variable to keep track of index while looping */
	int counter;

	/* Increment through array and compute coefficients */
	for(counter=0;counter < DArrayPtr->EntriesUsed; counter++){

		/* Increment temporary sums of X Y combinations */
		S_XX += DArrayPtr -> Payload[counter].X * DArrayPtr -> Payload[counter].X;
		S_XY += DArrayPtr -> Payload[counter].X * DArrayPtr -> Payload[counter].Y;
		S_X += DArrayPtr -> Payload[counter].X;
		S_Y += DArrayPtr -> Payload[counter].Y;


	}
	/* End for loop */


	/* Compute the coefficients */
	/* Compute the constant */
	*B = (((S_XX * S_Y) - (S_XY * S_X)) / ((DArrayPtr->EntriesUsed * S_XX) - (S_X * S_X)));

	/* Compute the linear coefficient */
	*A = (((DArrayPtr->EntriesUsed * S_XY) - (S_X * S_Y)) / ((DArrayPtr->EntriesUsed * S_XX) - (S_X * S_X)));


}
/* End ComputerCoefficients() */


/* Main method */
int main(int argc, char *argv[]){

	/* Check to make sure there are no additional cmdline args */
	if(argc==2){

		/* Declare FILE variable */
		FILE* dFile;

		/* Attempt to open file provided in command line arg */
		dFile=fopen(argv[1],"r");

		/* Check to make sure file was opened properly */
		if(dFile==NULL){
			/* Alert user that there was an issue opening file */
			printf("File cannot be opened\n");
		}else{
			/* File was opened properly, perform calculations */

			/* Declare Timer */
			DECLARE_TIMER(DataTimer);

			/* Initialize double values X and Y that will store the
			values found with scanf  */
			double X, Y;

			/* Initialize double values A and B that represent the coefficients for
			the line of best fit. Passed into ComputeCoefficients by refence */
			double A, B;

			/* Loop Control Variable */
			int lcv;

			/* Start the counter */
			START_TIMER(DataTimer);

			for(lcv=0;lcv<NUM_ITERATIONS;lcv++){
				rewind(dFile);

				/* Initialize variable for Dynamic Array */
				DArray array;

				/* Call CreateDArray to initialize array */
				CreateDArray(&array, INITIAL_CAPACITY);

				while(fscanf(dFile, "%lf %lf", &X, &Y) == 2){
					/* Initialize Data Object With values from DataPoints function */
					Data point;
					point.X=X;
					point.Y=Y;

					/* Send the data point to the dynamic Array */
					PushToDArray(&array, &point);

				}/* End While */

				/* Compute the coefficients (Stores both A AND B) */
				ComputeCoefficients(&A, &B, &array);

				/* Destroy the DArray object, and free associated memory */
				DestroyDArray(&array);
			}/* end NUM_ITERATIONS for */

			/* Stop the timer */
			STOP_TIMER(DataTimer);


			/* Produce Output */
			printf("\nThe line is: Y = %f * X + %f\n", A, B);

			PRINT_TIMER(DataTimer);

			/* Reset the timer */
			RESET_TIMER(DataTimer);

		} /* End check for file being opened */

	}else{

		/* Improper amount of cmdline args entered, alert user */
		printf("\nUsage: %s <TextFile>.txt\n\n", argv[0]);

	}
	/* End Cmdline args check */

	/* Return 1 to the operating system */
	return 1;
}
