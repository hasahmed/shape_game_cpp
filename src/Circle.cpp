#include "math.h"
#include "shapegame.hpp"

using namespace shapegame;

Circle::Circle(Position pos, double size, int fidelity, Color color): MultiShape(pos) {
	double const radius = size / 2;
	std::vector<Point> pts(fidelity);
	double const wedgeAngle = 360 / fidelity;
	double currentAngle = 0;
	for (int i = 0; i < fidelity; i++) {
		Point pt;
		pt.x = pos.x + sin(currentAngle * M_PI / 180) * radius;
		pt.y = pos.y + cos(currentAngle * M_PI / 180) * radius;
		pts[i] = pt;
		// std::cout << pt << std::endl;
		currentAngle += wedgeAngle;
	}
	Point prevPoint;
	bool firstIteration = true;
	int counter = 0;

	for(int i = 0; i < pts.size(); i++) {
		if (i != 0) {
			std::cout << "Second Iteration" << std::endl;
		  auto triangle = std::make_unique<Triangle>(pts[i], pos, prevPoint);
			this->addShape(std::move(triangle));
		}
		if (i == pts.size() -1) {
		  auto triangle = std::make_unique<Triangle>(pts[0], pts[i], pos);
			this->addShape(std::move(triangle));
			std::cout << "Last Iteration" << std::endl;
		}
		prevPoint = pts[i];
	}
	// for (auto pt : pts) {
	// 	if (!firstIteration) {
	// 	  auto triangle = std::make_unique<Triangle>(pt, pos, prevPoint);
	// 		this->addShape(std::move(triangle));
	// 		// if (counter == 4) {
	// 		// 	break;
	// 		// }
	// 	}
	// 	prevPoint = pt;
	// 	firstIteration = false;
	// 	counter++;
	// }
}
std::ostream& operator<< (std::ostream& stream, const shapegame::Circle& rObj) {
	using namespace std;
	cout << "[shapegame::Circle]" << endl;
	return stream;
}