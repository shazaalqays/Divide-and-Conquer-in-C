// A divide and conquer Algorithm to find the smallest distance from a given set of points in cartesian coordinates.  
#include <stdio.h> 
#include <float.h> 
#include <stdlib.h> 
#include <math.h> 
  
// A structure to represent a point in cartesian coordinates.
struct point{ 
    int y, x; 
}; 


int compare_y(const void* a, const void* b); // This function is used in the library of qsort() function.
int compare_x(const void* a, const void* b); // This function is used in the library of qsort() function.
float mini(float x, float y);
float distant(struct point p1, struct point p2);
float bruteForce(struct point p[], int n);
float barClosest(struct point bar[], int size, float d);
float smallestDistance(struct point p[], int n);
float closest(struct point p[], int n);


// Main function.
int main(){
    struct point p[] = {{3, 6}, {10, 9}, {23, 40}, {5, 11}, {2, 10}, {3, 4}, {39, 4}}; // x,y 
    int n = sizeof(p) / sizeof(p[0]); 
    printf("The smallest distance is %f ", closest(p, n)); 
    return 0; 
} 



// Function needed to sort array of points according to Y coordinate.
int compare_y(const void* a, const void* b){ 
    struct point *p1 = (struct point *)a,   *p2 = (struct point *)b; 
    return (p1->y - p2->y); // distance between two points
} 

// Function needed to sort array of points according to X coordinate.
int compare_x(const void* a, const void* b){ 
    struct point *p1 = (struct point *)a,  *p2 = (struct point *)b;
    return (p1->x - p2->x); // distace between two points.
} 

// A function to find a minimum of two float values.
float mini(float x, float y){ 
    return (x < y)? x : y; // if x < y return x otherwise return y.
} 
  
// A function to find the distance between two points.
float distant(struct point p1, struct point p2){ 
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y)); // ((x1-x2)^2 + (y1-y2)^2)^1/2
} 
  
// A Brute Force method to return the smallest distance between two points in p[] of size n.
float bruteForce(struct point p[], int n){ 
    float min = FLT_MAX; // Maximum representable finite floating point number.
    int i,j;
    for(i = 0; i < n; ++i){
    	for (j = i+1; j < n; ++j) {
    		if (distant(p[i], p[j]) < min){
    			min = distant(p[i], p[j]);
			}
		}
	}
    return min;
}
  
  
// A function to find the distance between the closest points of 
// bar of a given size. All points in bar[] are sorted according to 
// y coordinate. They all have an upper bound on minimum distance as d. 
float barClosest(struct point bar[], int size, float d){ 
    float min = d;  // Initialize the minimum distance as d 
    int i, j;
  
    qsort(bar, size, sizeof(struct point), compare_y);  // Function of quicksort, sort points according y axis.
  
    // Pick all points one by one and try the next points till the difference 
    // between y coordinates is smaller than d. 
    for (i = 0; i < size; ++i){
        for (j = i+1; j < size && (bar[j].y - bar[i].y) < min; ++j){
        	if (distant(bar[i],bar[j]) < min){
				min = distant(bar[i], bar[j]);
			}    
		}
	}
    return min; 
} 
  
// A recursive function to find the smallest distance. The array p contains all points sorted according to x coordinate.
float smallestDistance(struct point p[], int n) { 
    // If there are 2 or 3 points, then use brute force.
    if (n <= 3){
    	return bruteForce(p, n); 
	}
  
    // Find the middle point.
    int mid = n/2; 
    struct point midPoint = p[mid]; 
  
    // Consider the vertical line passing through the middle point calculate the smallest distance dl on left of middle point and 
    // dr on right side.
    float dl = smallestDistance(p, mid); 
    float dr = smallestDistance(p + mid, n-mid); 
  
    // Find the smaller of two distances.
    float d = mini(dl, dr); 
  
    // Build an array bar[] that contains points close (closer than d) to the line passing through the middle point.
    struct point bar[n]; 
    int j = 0, i; 
    for (i = 0; i < n; i++){
    	if (abs(p[i].x - midPoint.x) < d){ // abs() function returns the absolute value of an integer. 
    		bar[j] = p[i], j++; 
		}   
	}
         
    // Find the closest points in bar.  Return the minimum of d and closest distance is bar[].
    return mini(d, barClosest(bar, j, d)); 
} 
  
// The main function that finds the smallest distance. This method mainly uses smallestDistance().
float closest(struct point p[], int n) { 
    qsort(p, n, sizeof(struct point), compare_x); // Sorting array according x axis.
  
    // Use recursive function closest() to find the smallest distance 
    return smallestDistance(p, n); 
} 
