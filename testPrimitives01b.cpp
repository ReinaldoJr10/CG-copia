#include "Primitives.h"
#include "rasterization.h"
#include "Image.h"

int main(){
	std::vector<vec2> P = {
		{20, 20},
		{80, 60},
		{220, 30},
		{350, 90},
		{70, 300},
		{320, 150}
	};
	
	std::vector<unsigned int> indices = {
		0, 4, 5, 3, 2, 1
	};

	Elements<Lines> L{indices};
	//Elements<LineStrip> L{indices};
	//Elements<LineLoop> L{indices};

	Image Img(400, 400);
	Img.fill(white);

	for(Line<vec2> line: assemble(L, P))
		for(Pixel p : rasterizeLine(line))
			Img(p.x, p.y) = red;

	Img.savePNG("output.png");
}

