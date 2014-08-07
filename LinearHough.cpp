// LinearHough.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Standard headers
#include <cv.h>
#include <highgui.h>
#include <math.h>

// The main function
int main()
{
	IplImage* img = cvLoadImage("C:\\goal_arena.jpg", 0);			// Load an image
	IplImage* edges = cvCreateImage(cvGetSize(img), 8, 1);			// Create an image for the edges
	IplImage* imgHough = cvCreateImage(cvSize(360, 1000), 8, 1);	// Create an image for the parameter space

	// Explicitly set all accumulator cells to 0
	cvZero(imgHough);

	// Detect edges
	cvCanny(img, edges, 200, 0);

	// Show the edges
	cvNamedWindow("test");
	cvShowImage("test", edges);

	// Iterate through each pixel
	for(int x=0;x<img->width;x++)
	{
		for(int y=0;y<img->height;y++)
		{
			// If the current pixel is an edge
			if(cvGetReal2D(edges, y, x)>0)
			{
				// Do the hough thingy
				for(int theta=0;theta<360;theta++)
				{
					// cos, sin work in radians, so convert degrees into radians
					// the imgHough->height/2 is to ensure values dont go negative

					// p = x*cos(theta) + y*sin(theta)
					int p = x*cos(theta*3.1412/180) + y*sin(theta*3.1412/180)+imgHough->height/2;

					// cast a "vote" in the corresponding accumulator cell
					int value = cvGetReal2D(imgHough, p, theta);
					cvSetReal2D(imgHough, p, theta, value+1);
				}
			}
		}
	}
	
	// Show the hough image
	cvNamedWindow("Hough");
	cvShowImage("Hough", imgHough);

	// Uncomment to save the hough image into a file
	//cvSaveImage("C:\\hough.jpg", imgHough);

	cvWaitKey(0);

	return 0;
}

