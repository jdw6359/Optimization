/******************************************************************************
* Dynamic Arrays Module  - public interface
*
* data types: struct Data stores payload; change according to application
*             struct DArray stores the Dynamic Array Header
*
* functions: CreateDArray, PushToDArray, DestroyDArray
*
* Author: Greg Semeraro
* Revised: JCCK 2/6/2014
******************************************************************************/

#ifndef _DYNAMIC_ARRAYS_H_
#define _DYNAMIC_ARRAYS_H_

/**************************  modify as needed *************************/
/** Data typemark to store payload: Modify according to application  ***/
typedef struct Data
  {
	/* An Instance of Data represents a point, having both an x and y value */
	double X;
	double Y;
  } Data;

/************** Nothing else in the module needs to be modified *************/

/* Growth Policy : Constant Size, modify as necessary */
#define GROWTH_AMOUNT (100)  

/*****************************************************************************
 * DArray - Dynamic Array Header struture to keep track of its "state" 
 *          The "state" of the Dynamic Array is: its Capacity and EntriesUsed
 *****************************************************************************/
typedef struct DArray
  {
   unsigned int Capacity;     /* Max Number of elements array can hold */
   unsigned int EntriesUsed;  /* Number of array elements "used"       */
   Data *Payload;     /* Pointer to array that actally holds the data  */
  } DArray;

/******************************************************************************
 * CreateDArray 
 *   Allocates memory and initializes DArray with specified initial size.
 ******************************************************************************/
void CreateDArray(DArray *DArrayPtr, unsigned int InitialSize);

/******************************************************************************
 * PushToDArray
 *   Adds data to the end (push) of the dynamic array and updated ElementsUSed 
 *   If full, realocates memory space according to growth policy
 *   postcond: returns the index to the last element added 
 ******************************************************************************/
unsigned int PushToDArray(DArray *DArrayPtr, Data *PayloadPtr);

/******************************************************************************
* DestroyDArray
*   Returns memory to head and resets state of the Dynamic Array
*   by setting to zero Capacity and ElementsUsed
******************************************************************************/
void DestroyDArray(DArray *DArrayPtr);

#endif /* _DYNAMIC_ARRAYS_H_ */
