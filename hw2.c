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

#define INITIAL_CAPACITY 0

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
		S_Y += DArrayPtr -> Payload[counter].X;

		/* Compute the coefficients */
		/* Compute the constant */
		*B = (((S_XX * S_Y) - (S_XY * S_X)) / ((DArrayPtr->EntriesUsed * S_XX) - (S_X * S_X)));

		/* Compute the linear coefficient */
		*A = (((DArrayPtr->EntriesUsed * S_XY) - (S_X * S_Y)) / ((DArrayPtr->EntriesUsed * S_XX) - (S_X * S_X)));

	}
	/* End for loop */
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

			/* Initialize double values X and Y that will store the point values
			returned from the call to Data Points */
			double X, Y;

			/* Initialize double values A and B that represent the coefficients for
			the line of best fit. Passed into ComputeCoefficients by refence */
			double A, B;

			/* Variable that represents the index of the last element added to Payload  */

			/* Initialize variable for Dynamic Array */
			DArray array;

			/* Call CreateDArray to initialize array */
			CreateDArray(&array, INITIAL_CAPACITY);


			/* Initialize Data Object With values from DataPoints function */
			Data point;
			point.X=3.567;
			point.Y=23.6789;


			/* Send the data point to the dynamic array */
			PushToDArray(&array, &point);


			/* Compute the coefficients (Stores both A AND B) */
			ComputeCoefficients(&A, &B, &array);

			/* Produce Output */
			printf("\nThe line is: Y = %f * X + %f\n", A, B);
			printf("There were %d points in the data set\n\n", array.EntriesUsed);

			/* Destroy the DArray object, and free associated memory */
			DestroyDArray(&array);

		} /* End check for file being opened */

	}else{

		/* Improper amount of cmdline args entered, alert user */
		printf("\nUsage: %s <TextFile>.txt\n\n", argv[0]);

	}
	/* End Cmdline args check */

	/* Return 1 to the operating system */
	return 1;
}
