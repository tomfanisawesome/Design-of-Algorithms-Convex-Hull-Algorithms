/* * * * * * *
 * Implementation of the Inside Hull algorithm for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2019
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Xicheng Fan>
 */

//                   WRITE YOUR IMPLEMENTATION HERE
//
// You should fill in the function definitions for orientation() and
// inside_hull() in this file.
//
// Don't be shy to add any extra functions or types you may need.

#include <stdio.h>
#include <stdlib.h>

#include "convex-hull.h"

// Returns the orientation of Point p2 in relation to the line segment p0p1.
// If p2 is to the left of p0p1 then it returns LEFT ('l'), if p2 is to the
// right it returns RIGHT ('r').
// If p0, p1 and p2 are collinear then COLLINEAR ('c') is returned.
char orientation(Point p0, Point p1, Point p2)
{
  // TODO: Implement orientation()
  //an algorithms that determines whether a point p2 is left or right  of the line P0P1
  double determinant = (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
  if (determinant > 0)
  {
    return LEFT;
  }
  else if (determinant < 0)
  {
    return RIGHT;
  }
  else
  {
    return COLLINEAR;
  }
}

// Takes a polygon (i.e. an array of points) given in counter-clockwise order
// with n points.
//
// Stores the points of the convex hull into the hull array (the last point
// should NOT be the same as the first point), and returns the number of
// points which are in the convex hull.
//
// If three successive points in the polygon are collinear then the algorithm
// should terminate and COLLINEAR_POINTS should be returned.
//
// If an error occurs this function should return INSIDE_HULL_ERROR.
int inside_hull(Point *polygon, int n, Point *hull)
{
  // TODO: Implement the InsideHull algorithm
  int i = 0;
  int j = 0;
  Deque *deque = new_deque();
  // if input is empty or less than 3 , return error message and abort program
  if (polygon == NULL || n < 3)
  {
    return INSIDE_HULL_ERROR;
  }
  else if (orientation(polygon[i], polygon[i + 1], polygon[i + 2]) == LEFT)
  {
    deque_insert(deque, polygon[2]);
    deque_insert(deque, polygon[0]);
    deque_insert(deque, polygon[1]);
    deque_insert(deque, polygon[2]);
  }
  else if (orientation(polygon[i], polygon[i + 1], polygon[i + 2]) == RIGHT)
  {
    deque_insert(deque, polygon[2]);
    deque_insert(deque, polygon[1]);
    deque_insert(deque, polygon[0]);
    deque_insert(deque, polygon[2]);
  }
  else
  {
    return COLLINEAR_POINTS;
  }
  i=4;
  while (i < n )
   {  if(get_head_data==get_tail_data){
      break;
    }

    /*if (orientation(polygon[i], polygon[i + 1], polygon[i + 2]) == COLLINEAR)
    {
      return COLLINEAR_POINTS;
    }*/
    if(orientation(get_head_next_data(deque), get_head_data(deque), polygon[i]) == LEFT &&
             orientation(get_tail_data(deque), get_tail_prev_data(deque), polygon[i]) == LEFT)
    {
      i++;
      continue;
    }
    while (orientation(get_head_next_data(deque), get_head_data(deque), polygon[i]) == RIGHT)
    {
      deque_pop(deque);
    }
    deque_push(deque, polygon[i]);
    while (orientation(get_tail_data(deque), get_tail_prev_data(deque), polygon[i]) == RIGHT)
    {
      deque_remove(deque);
    }
    deque_insert(deque, polygon[i]);
    i++;
  }
  int count = deque_size(deque);
  while (j < count)
  {
    hull[j] = deque_remove(deque);
    j++;
  }
  return count-1;
}
