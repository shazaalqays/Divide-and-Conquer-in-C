# Divide-and-Conquer-in-C
## Closest pair of points using divide and conquer algorithm
We are given an array of n points in the plane, and the problem is to find out the closest pair of points in the array. The Brute force solution is O(n^2), compute the distance between each pair and return the smallest. We can calculate the smallest distance in O(nLogn) time using Divide and Conquer strategy. 
## Algorithm
As a pre-processing step, the input array is sorted according to x coordinates. 
```
1.	Find the middle point in the sorted array, we can take p[n/2] as middle point.
2.	Divide the given array in two halves. The first sub array contains points from p[0] to p[n/2]. The second sub array contains points from p[n/2+1] to p[n-1].
3.	Recursively find the smallest distances in both sub arrays. Let the distances be dl and dr. Find the minimum of dl and dr. Let the minimum be d.
4.	From the above 3 steps, we have an upper bound d of minimum distance. Now we need to consider the pairs such that one point in pair is from the left half and the other is from the right half. Consider the vertical line passing through p[n/2] and find all points whose x coordinate is closer than d to the middle vertical line. Build an array bar[] of all such points.
5.	Sort the array bar[] according to y coordinates. This step is O(nLogn). It can be optimized to O(n) by recursively sorting and merging.
6.	Find the smallest distance in bar[]. This is tricky. From the first look, it seems to be a O(n^2) step, but it is actually O(n). It can be proved geometrically that for every point in the bar, we only need to check at most 7 points after it (note that bar is sorted according to Y coordinate). 
7.	Finally return the minimum of d and distance calculated in the above step (step 6).
```
## Time Complexity

T(n) = 2T(n/2) + O(n) + O(nLogn) + O(n)
T(n) = 2T(n/2) + O(nLogn)
T(n) = T(n x Logn x Logn)


## Examples
p1 {5, 3}, p2 {12, 3}, p3 {43, 50}, p4 {5, 11}, p5 {2, 10}, p6 {3, 4} = 2.236068
![Result1](https://github.com/shazaalqays/Divide-and-Conquer-in-C/blob/main/images/6_points.jpg)<br/><br/>
p1 {3, 6}, p2 {10, 9}, p3{23, 40} = 7.615773
![Result1](https://github.com/shazaalqays/Divide-and-Conquer-in-C/blob/main/images/3_points.jpg)<br/><br/>
