#include <iostream>
#include <charconv> 
#include <cstdint>
#include <optional>
#include <system_error>
#include <string_view>
#include <string>
#include <cmath>

//Write a program which tests if two rectangles have nonempty intersection. If intersection
//is nonempty,return the rectangle formed by their intersection.



struct Rectangle {
    int x, y, width, height;
};

bool Intersecting(const Rectangle A,const Rectangle B){
	//Takes input two rectangles A,B and outputs if there is an intersection
	//To say that a rectangle A does not intersect with rectangle B, 1 ot of cases must be true
	//C1:A endX < B  StartX
	//C2:A startX > B endX
	//C3:A endY < B  StartY
	//C4:A startY > B endY
	//so notOverlapping = C1 or C2 or C3 or C4
	//Overlapping = not (C1 or C2 or C3 or C4) 
	//Time Complexity O(1), constant checks
	
	//Cases Calculation
	bool C1 = (A.x + A.width)  < (B.x);
	bool C2 = (A.x) > (B.x + B.width);
	bool C3 = (A.y + A.height) < (B.y);
	bool C4 = (A.y)  > (B.y+ B.height);
	bool Intersecting = not (C1 or C2 or C3 or C4) ;
	
	return Intersecting;
}

Rectangle IntersectRectangles(const Rectangle A,const Rectangle B){
	//Takes input two Rectangles A,B and returns the Intersecting Rectangle if Intersecting
	//We check if We are intersecting
	//to compute the x,y we take the max
	//to compute the width,height we do the min and substract the x,y
	
	
	//Checking for Intersection
	if (Intersecting(A,B)){
		
		//Definitions and Calculations
		int x 		= std::max(A.x,B.x);
		int y 		= std::max(A.y,B.y);
		int width 	= std::min(A.x+A.width,B.x+B.width) - x;
		int height 	= std::max(A.y+A.height,B.y+B.height) - y;
		
		
		return {x,y,width,height};
	}
	
	return {0,0,-1,-1}	;
}

int main() {
	
	//Creating test Rectangles
    Rectangle A{0, 0, 4, 4};
    Rectangle B{2, 2, 4, 4};
    
    //Outputing the Intersecting Rectangle. Case it exits
    Rectangle R = IntersectRectangles(A, B);
    std::cout << R.x << " " << R.y << " " << R.width << " " << R.height << "\n";
   
	//Outputing the Intersecting Rectangle. Case it does not exist
    Rectangle C{10, 10, 1, 1};
    Rectangle D = IntersectRectangles(A, C);
    std::cout << D.width << "\n"; 
    
    return 0;
}
