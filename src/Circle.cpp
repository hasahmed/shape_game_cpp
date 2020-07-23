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
	int counter = 1;
	for (auto pt : pts) {
		std::cout << "Here: " << counter << std::endl;
		if (counter % 2 == 0 && counter != 0) { // event
			auto triangle = std::make_unique<Triangle>(pt, pos, prevPoint);
			this->addShape(std::move(triangle));
			if (counter == 4) {
				break;
			}
		}
		else { // odd
			prevPoint = pt;
		}
		counter++;
	}
}
std::ostream& operator<< (std::ostream& stream, const shapegame::Circle& rObj) {
	using namespace std;
	cout << "[shapegame::Circle]" << endl;
	return stream;
}