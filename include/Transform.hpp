#pragma once
namespace shapegame {
    class Transform {
			public:
        Point scale = Point(0, 0);
        Point translation = Point(0, 0);
        int rotation = 0;
    };
}
