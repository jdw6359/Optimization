//////////////////////////////////////////////////////////////////////////////
// Linear Curve Fitting - This program fits a line to the data points in the
// file provided on the command line (one data point per line of text in the
// file).
//////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <list>
using namespace std;
#include <iostream>
#include "Timers.h"

//////////////////////////////////////////////////////////////////////////////
//  Class declaration for determining the "best" line for a given set of X-Y
// data points.
//////////////////////////////////////////////////////////////////////////////
class LinearFit
  {
   public:
     // Constructor
     LinearFit(void);

     // Accepts a single X-Y data point and adds it to the collection of points
     // used to determine the line.
     void AddPoint(double X, double Y);

     // Returns the number of data points collected
     int GetNumberOfPoints(void);

     // Returns the constant 'B' in Y = A * X + B
     double GetConstant(void);

     // Returns the coefficient to the linear term 'A' in Y = A * X + B
     double GetLinearCoefficient(void);
   private:
     // Computes the coefficients (when needed)
     void ComputeCoefficients(void);

     // X data list
     list<double> Data_X;

     // Y data list
     list<double> Data_Y;

     // The constant 'B'
     double B;

     // The coefficient to the linear term 'A'
     double A;

     // Flag indicating that the coefficients have been computed
     int CoefficientsComputed;
  }; // LinearFit Class

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////
LinearFit::LinearFit(void)
  {
   // Initialize the flag indicating that the coefficients have not been computed
   CoefficientsComputed = 0;
  } // Constructor
   
//////////////////////////////////////////////////////////////////////////////
//  AddPoint() - Accepts a single point and adds it to the lists
//////////////////////////////////////////////////////////////////////////////
void LinearFit::AddPoint(double X, double Y)
  {
   // Store the data point into the lists
   Data_X.push_back(X);
   Data_Y.push_back(Y);
  } // AddPoint()
   
//////////////////////////////////////////////////////////////////////////////
//  GetNumberOfPoints() - Returns the number of points collected
//////////////////////////////////////////////////////////////////////////////
int LinearFit::GetNumberOfPoints(void)
  {
   return Data_X.size();
  } // GetNumberOfPoints()
   
//////////////////////////////////////////////////////////////////////////////
//  ComputeCoefficients() - Calculate the value of the linear coefficient
// 'A' and the constant term 'B' in Y = A * X + B
//////////////////////////////////////////////////////////////////////////////
void LinearFit::ComputeCoefficients(void)
  {
   // Declare and initialize sum variables
   double S_XX = 0.0;
   double S_XY = 0.0;
   double S_X  = 0.0;
   double S_Y  = 0.0;

   // Iterators
   list<double>::const_iterator lcv_X, lcv_Y;

   // Compute the sums
   lcv_X = Data_X.begin();
   lcv_Y = Data_Y.begin();
   while ((lcv_X != Data_X.end()) && (lcv_Y != Data_Y.end()))
     {
      S_XX += (*lcv_X) * (*lcv_X);
      S_XY += (*lcv_X) * (*lcv_Y);
      S_X  += (*lcv_X);
      S_Y  += (*lcv_Y);
 
      // Iterate
      lcv_X++; lcv_Y++;
     } // while()
 
   // Compute the constant
   B = (((S_XX * S_Y) - (S_XY * S_X)) / ((Data_X.size() * S_XX) - (S_X * S_X)));
   // Compute the linear coefficient
   A = (((Data_X.size() * S_XY) - (S_X * S_Y)) / ((Data_X.size() * S_XX) - (S_X * S_X)));

   // Indicate that the Coefficients have been computed
   CoefficientsComputed = 1;
  } // ComputeCoefficients()

//////////////////////////////////////////////////////////////////////////////
//  GetConstant() - Calculate the value of the constant 'B' in Y = A * X + B
//////////////////////////////////////////////////////////////////////////////
double LinearFit::GetConstant(void)
  {
   if (CoefficientsComputed == 0)
     {
      ComputeCoefficients();
     } // if()

   return B;
  } // GetConstant()
   
//////////////////////////////////////////////////////////////////////////////
//  GetLinearCoefficient() - Calculate the value of the linear coefficient
// 'A' in Y = A * X + B
//////////////////////////////////////////////////////////////////////////////
double LinearFit::GetLinearCoefficient(void)
  {
   if (CoefficientsComputed == 0)
     {
      ComputeCoefficients();
     } // if()

   return A;
  } // GetLinearCoefficient()

//////////////////////////////////////////////////////////////////////////////
// Main program to fit a line to the data.
//////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
  {
   // Declare a pointer to the LinearFit object
   LinearFit *DataSet;

   // Constant defining the number of times to perform calculations

   DECLARE_TIMER(DataTimer);

   // Check that a command line argument was provided
   if (argc != 1)
     {
      // Boolean variable to indicate all data has been read.
      bool Done;

      // Declare an input stream
      ifstream InputFile;

      // Variables to hold the constant and linear coefficients of the line
      double A, B;

      // Start the timer
      START_TIMER(DataTimer);

      // Perform the calculations many times
      for (int Iteration=NUM_ITERATIONS; Iteration!=0; Iteration--)
        {
         // Attach the input stream to the command line argument (it should be a
         // filename).
         InputFile.open(argv[1]);

         // Instantiate and object for determining the line
         DataSet = new LinearFit;

         // Read all of the data from the file
         do
           {
            // Temporary variables to hold data read from file
            double X, Y;
   
            // Read the X-Y data point
            InputFile >> X >> Y;
   
            // If read did not go beyond end-of-file, add it to the data set
            if (!InputFile.eof()) 
              {
               // Add the data point
               DataSet->AddPoint(X, Y);
               Done = false;
              } // if()
            else
              {
               // Set the flag indicating that all the data is gone
               Done = true;
              } // if...else()
           } while (!Done);

         // Save the constant value and the linear coefficent
         A = DataSet->GetLinearCoefficient();
         B = DataSet->GetConstant();

         // Destroy the data set object
         delete DataSet;
         
         // Disconnect the input file from the stream
         InputFile.close();
         InputFile.clear();
       } // for()

      // Stop the timer
      STOP_TIMER(DataTimer);

      // Print out the line that fits the data set.
      cout << "\nThe line is: Y = " << A << " * X + " << B << endl;

      // Print out elapsed time per iteration.
      PRINT_TIMER(DataTimer);
     } // if()
   else
     {
      // Display program usage information
      cout << "Usage: " << argv[0] << " Filename" << endl;
     } // if...else()
   RESET_TIMER(DataTimer);
   return 0;
  } // main()
