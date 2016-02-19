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

const Pair MAX_PAIR{ Point{0,0}, Point{MAX_DIST, MAX_DIST} };

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

int distance(Point lhs, Point rhs) {
  // Calculates distance between two points via pythagoras
  return std::sqrt( (lhs.x-rhs.x)*(lhs.x-rhs.x) + (lhs.y-rhs.y)*(lhs.y-rhs.y) ); 
}
int distance(Pair p) { return distance(p.first, p.second); }

void print_points(std::vector<Point> const& vec) {
  // Prints all points in a vector
  for (int i=0; i < vec.size(); ++i) {
    std::cout << " vec[" << i << "] = (" << vec[i].x << ", " << vec[i].y << ");";
    if (i % 3 == 0) std::cout << "\n"; 
  }
  std::cout << "vec.size() = " << vec.size() << "\n";
}

void print_pair(Pair const& pair) {
  std::cout << "First: " << "(" << pair.first.x << ", " << pair.first.y << ")\n"
            << "Second: " << "(" << pair.second.x << ", " << pair.second.y << ")\n"
            << "Distance = " << distance(pair) << "\n";
}

Pair closest_pair_by_brute_force(std::vector<Point> & vec, int start, int end) {
  // Fin closest pair by considering each pair --> runtime O(n^2)
  if (vec.size() < 2) return MAX_PAIR;
  Pair winner{vec[0], vec[1]};

  for (int i=start; i < end; ++i) {
    for (int j=start; j < end; ++j) {
      if (distance(vec[i], vec[j]) < distance(winner) && (i != j)) {
        winner = Pair{vec[i], vec[j]};
      }
    }
  }

  return winner;
}

bool sort_by_x(Point left, Point right) { return left.x < right.x; }
bool sort_by_y(Point left, Point right) { return left.y < right.y; }

Pair closest_pair_rec(std::vector<Point> & vec, int start, int end) {
  // This is the recursive part of the algorithm

  int length = end-start;
  int median = (start+end)/2; 
  Pair l_pair = MAX_PAIR, r_pair = MAX_PAIR;

  // Divide-step:
  if (length > 3) {
    l_pair = closest_pair_rec(vec, start, median);
    r_pair = closest_pair_rec(vec, median, end); 
  } else {
    return closest_pair_by_brute_force(vec, start, end);
  }

  // Conquer step: Discover possible winning pairs, 
  // where one point lies left-side to the median and the other right-side.

  std::vector<Point> left_strip, right_strip; // Construct two halves of the strip around the median
  int reaching_dist = std::min(distance(l_pair), distance(r_pair));
  for (int i=0; i < vec.size(); ++i) {
    if ( (vec[i].x < (vec[median].x + reaching_dist)) && (vec[i].x >= vec[median].x) ) {
      left_strip.push_back(vec[i]);
    }
    if ( (vec[i].x > (vec[median].x - reaching_dist)) && (vec[i].x < vec[median].x) ) {
      right_strip.push_back(vec[i]);
    }
  }

  // We don't need to merge the two sides if there are no possible winning pairs
  if (left_strip.empty() || right_strip.empty()) return ( (distance(l_pair) < distance(r_pair)) ? l_pair : r_pair );

  // Sort points in strip by their y-coordinates
  std::sort(left_strip.begin(), left_strip.end(), sort_by_y);
  std::sort(right_strip.begin(), right_strip.end(), sort_by_y);

  Pair m_pair{left_strip[0], right_strip[0]};
  for (int i=0; i < left_strip.size(); ++i) { // Consider all points on the left sidde of the strip 
    for (int j=0; j < right_strip.size() && right_strip[j].y < (left_strip[i].y + reaching_dist); ++j) {
      if (distance(left_strip[i], right_strip[j]) < distance(m_pair)) {
        m_pair = Pair{left_strip[i], right_strip[j]}; 
      }
    }
  }

  // Choose winning pair:
  if (distance(l_pair) <= distance(m_pair) && distance(l_pair) <= distance(r_pair)) { return l_pair; }  
  if (distance(m_pair) < distance(l_pair) && distance(m_pair) <= distance(r_pair)) { return m_pair; }
  if (distance(r_pair) < distance(l_pair) && distance(r_pair) < distance(m_pair)) { return r_pair; }
}

Pair closest_pair(std::vector<Point> & vec, int start, int end) {
  // Wrapping method for recursive part, so we only have to sort all points once
  std::sort(vec.begin()+start, vec.begin()+end, sort_by_x);

  return closest_pair_rec(vec, start, end);
}

int main(int argc, char* argv[]) {
	
  std::srand(std::time(NULL));
  std::vector<Point> vec = generate_random_points(100);

  Pair winner = closest_pair(vec, 0, vec.size());
  print_points(vec);

  Pair winner_bf = closest_pair_by_brute_force(vec, 0, vec.size());
  if (distance(winner) != distance(winner_bf)) {
    std::cout << "Something went wrong: " << "Winning pair by divide-and-conquer: " << "\n";
    print_pair(winner);
    std::cout << "Winning pair by brute force: " << "\n";
    print_pair(winner_bf);
  }

  print_pair(winner);
  std::cout << "Minimal distance: " << distance(winner) << "\n";
  
  return 0;
}