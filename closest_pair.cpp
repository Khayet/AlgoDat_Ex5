#include <iostream>
#include <cstdlib> // std::rand
#include <vector>
#include <ctime> // seed for random numbers

const int MAX_DIST = 1000; // maximum distance from (0, 0)


struct Point
{
  int x;
  int y;
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

int main(int argc, char* argv[]) {
	
  std::srand(std::time(NULL));
  std::vector<Point> vec = generate_random_points(100);
  
  print_points(vec);

  return 0;
}