#define _USE_MATH_DEFINES
#include "math.h"
#include "shapegame.hpp"

using namespace shapegame;

Circle::Circle(Position pos, double size, Color color): Circle(pos, size, 60, color)  {}

Circle::Circle(Position pos, double size, int fidelity, Color color): MultiShape(pos) {
	double const radius = size / 2;
	std::vector<Point> pts(fidelity);
	double const wedgeAngle = 2 * M_PI / fidelity;
	double currentAngle = 0;
	for (int i = 0; i < fidelity; i++) {
		Point pt;
		pt.x = pos.x + sin(currentAngle) * radius;
		pt.y = pos.y + cos(currentAngle) * radius;
		pts[i] = pt;
		currentAngle += wedgeAngle;
	}
	Point prevPoint;
	bool firstIteration = true;

	for(int i = 0; i < pts.size(); i++) {

		if (i != 0) {
		  auto triangle = std::make_unique<Triangle>(pts[i], pos, prevPoint);
			this->addShape(std::move(triangle));
		}
		if (i == pts.size() -1) {
		  auto triangle = std::make_unique<Triangle>(pts[0], pts[i], pos);
			this->addShape(std::move(triangle));
		}
		prevPoint = pts[i];


	}
}
std::ostream& operator<< (std::ostream& stream, const shapegame::Circle& rObj) {
	using namespace std;
	cout << "[shapegame::Circle]" << endl;
	return stream;
}