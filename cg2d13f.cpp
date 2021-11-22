#include "Graphics2D_v1.h"
#include "bezier.h"
#include "matrix.h"

int main(){
	std::vector<vec2> CP = loadCurve("borboleta.txt");
	std::vector<vec2> P = sample_cubic_bezier_spline(CP, 30);

	float t = 0.5;
	mat3 Rot = {
		cos(t), -sin(t), 0.0,
		sin(t),  cos(t), 0.0,
		   0.0,     0.0, 1.0
	};
	mat3 Cis = {
		1.0, 1.2, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	};

	LineStrip L{P.size()};
	
	Graphics2D G(800, 600);
	G.clear();
	G.draw(P, L, red);
	G.draw((Cis*Rot)*P, L, blue);
	G.savePNG("output.png");
}
