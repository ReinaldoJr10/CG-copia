#ifndef CLIP2D_H
#define CLIP2D_H

#include "Primitives.h"
#include "VertexUtils.h"

struct ClipRectangle{
	float x0, y0, x1, y1;
};

struct Semiplane{
	vec2 A;
	vec2 n;
	bool has(vec2 P){
		return dot(P-A, n) >= 0;
	}
	float intersect(vec2 P, vec2 Q){
		return dot(A-P, n)/dot(Q-P,n);
	}
};


bool clip(Line<Vec2Col>& line, ClipRectangle rect){
	/**************** TAREFA - AULA 09 **************/
	return true;
}

std::vector<Line<Vec2Col>> clip(const std::vector<Line<Vec2Col>>& lines, ClipRectangle rect){
	std::vector<Line<Vec2Col>> res;
	for(Line<Vec2Col> line: lines)
		if(clip(line, rect))
			res.push_back(line);
	return res;
}

std::vector<Vec2Col> clip(const std::vector<Vec2Col>& polygon, Semiplane S){
	std::vector<Vec2Col> R;

	for(unsigned int i = 0; i < polygon.size(); i++){
		Vec2Col P = polygon[i];
		Vec2Col Q = polygon[(i+1)%polygon.size()];
	
		bool Pin = S.has(P.position);
		bool Qin = S.has(Q.position);

		if(Pin != Qin)
			R.push_back(lerp(S.intersect(P.position, Q.position), P, Q));
		
		if(Qin)
			R.push_back(Q);
	}
	return R;
}


std::vector<Vec2Col> clip(const std::vector<Vec2Col>& polygon, ClipRectangle rect){
	Semiplane sides[4] = {
		{ {rect.x0, rect.y0}, { 1,  0} }, // left
		{ {rect.x1, rect.y0}, {-1,  0} }, // right
		{ {rect.x0, rect.y0}, { 0,  1} }, // down
		{ {rect.x1, rect.y1}, { 0, -1} }, // up
	};

	std::vector<Vec2Col> R = polygon;

	for(Semiplane S: sides)
		R = clip(R, S);

	return R;
}

std::vector<Triangle<Vec2Col>> clip(const std::vector<Triangle<Vec2Col>>& tris, ClipRectangle R){
	std::vector<Triangle<Vec2Col>> res;

	for(Triangle<Vec2Col> tri: tris){
		std::vector<Vec2Col> polygon = {tri[0], tri[1], tri[2]};
		polygon = clip(polygon, R);
		TriangleFan T{polygon.size()};
		for(Triangle<Vec2Col> tri: assemble(T, polygon))
			res.push_back(tri);
	}

	return res;
}

#endif
