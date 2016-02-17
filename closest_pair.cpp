#include <iostream>
#include <cstdlib> // std::rand
#include <vector>
#include <ctime> // seed for random numbers
#include <algorithm> // std::sort
#include <cmath> // std::sqrt

const int MAX_DIST = 1000; // maximum distance from (0, 0)

struct Point
{
  int x;
  int y;
};

struct Pair
{
  Point first;
  Point second;
};

std::vector<Point> generate_random_points(int number) {
  std::vector<Point> point_vector;
  Point new_point;
 
  for (int i = 0; i < number; ++i) {
    new_point.x = std::rand() % MAX_DIST;
    new_point.y = std::rand() % MAX_DIST;
    point_vector.push_back(new_point);
  }

  return point_vector;
}

void print_points(std::vector<Point> const& vec) {
  for (int i=0; i < vec.size(); ++i) {
    std::cout << "vec[" << i << "] = (" << vec[i].x << ", " << vec[i].y << ")\n";
  }
  std::cout << "vec.size() = " << vec.size() << "\n";
}

int distance(Point lhs, Point rhs) {
  // calculates distance between two points via pythagoras
  return std::sqrt( (lhs.x-rhs.x)*(lhs.x-rhs.x) + (lhs.y-rhs.y)*(lhs.y-rhs.y) ); 
}
int distance(Pair p) { return distance(p.first, p.second); }

bool sort_by_x(Point left, Point right) { return left.x < right.x; }

Pair closest_pair(std::vector<Point> & vec, int start, int end) {
  //? TODO: implement sorting ?
  int length = end-start;
  int median = (start+end)/2; 
  Pair l_pair{0, 0}, r_pair{0, 0};
  std::sort(vec.begin()+start, vec.begin()+end, sort_by_x);

  // TODO: Split into two
  // TODO: Divide
  if (length > 3) {
    l_pair = closest_pair(vec, start, median);
    r_pair = closest_pair(vec, median, end); 
  } else if (length == 3) {
    l_pair = {vec[start], vec[median]};
    r_pair = {vec[median], vec[end]};
  } else if (length == 2) {
    return Pair{vec[start], vec[end]};
  } else {
    return Pair{vec[start], 0};  //only one point in vector
  }

  // TODO: Conquer
  // TODO: Choose final

  return (distance(l_pair) < distance(r_pair)) ? l_pair : r_pair;
}

int main(int argc, char* argv[]) {
	
  std::srand(std::time(NULL));
  std::vector<Point> vec = generate_random_points(100);

  Pair winner = closest_pair(vec, 0, vec.size());
  print_points(vec);

  std::cout << "First: " << "(" << winner.first.x << ", " << winner.first.y << ")\n"
            << "Second: " << "(" << winner.second.x << ", " << winner.second.y << ")\n";
  
  return 0;
}