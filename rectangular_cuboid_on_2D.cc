//A simple program that generates a 2D representation of a rectangular cuboid via standard output
//using a string as the sides of the rectangular cuboid (seed).
//Different constants may be used to generate different rectangular cuboids.
//David Qian 

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//simple struct with x and y properties to represent (x,y)
struct Coordinate {
	int x;
	int y;
};

//simple struct that has 4 coordinate properties to represent 4 corners of a square
struct Square {
	Coordinate top_left;
	Coordinate top_right;
	Coordinate bottom_left;
	Coordinate bottom_right;
};

void generate_2D_grid( vector< vector<string> >* grid, int square_width, int grid_const) {
	vector<string> temp;
	for (int i = 0; i < square_width*grid_const; i++) {
		for (int j = 0; j < square_width*grid_const; j++) {
			temp.push_back(" ");
		}
		(*grid).push_back(temp);
		temp.clear();
	}
}

void generate_square_on_grid(vector< vector<string> >* grid, int square_width, string seed, Coordinate top_left_corner_coordinate_of_square) {
	for (int i = 0; i < square_width; i++) {
		//generate two sides extending from top left corner
		(*grid)[top_left_corner_coordinate_of_square.y + i][top_left_corner_coordinate_of_square.x] = seed[i];
		(*grid)[top_left_corner_coordinate_of_square.y][top_left_corner_coordinate_of_square.x + i] = seed[i];
		//generate two sides extending from top right
		(*grid)[top_left_corner_coordinate_of_square.y + square_width][top_left_corner_coordinate_of_square.x + i] = seed[i];
		(*grid)[top_left_corner_coordinate_of_square.y + i][top_left_corner_coordinate_of_square.x + square_width] = seed[i];
	}
}

void generate_sides_of_square_on_grid(vector< vector<string> >* grid, int square_width,  string seed, Square top_most_square) {
	for (int i = 0; i < square_width; i++) {
		(*grid)[top_most_square.top_left.y+i][top_most_square.top_left.x+i] = seed[i];
		(*grid)[top_most_square.top_right.y+i][top_most_square.top_right.x+i] = seed[i];
		(*grid)[top_most_square.bottom_left.y+i][top_most_square.bottom_left.x+i] = seed[i];
		(*grid)[top_most_square.bottom_right.y+i][top_most_square.bottom_right.x+i] = seed[i];
	}
}

void print_2D_grid(vector< vector<string> >* grid) {
	for (int i = 0; i < (*grid).size(); i++) {
		for (int j = 0 ; j < (*grid).size(); j++ ) {
			cout << (*grid)[i][j];
		}
		cout << endl;
	}
}

void generate_rectangular_cuboid_on_2D_grid(vector< vector<string> >* grid, string seed, int square_width, int grid_const) {
	//generate first square
	//always start at (0,0) of grid
	Coordinate xy_top_left_top_most_square = {0, 0};
	generate_square_on_grid(grid, square_width, seed, xy_top_left_top_most_square);


	//generate connecting sides
	Square top_most_square = { 
		{xy_top_left_top_most_square.x, xy_top_left_top_most_square.y}, 
		{xy_top_left_top_most_square.x+square_width, xy_top_left_top_most_square.y}, 
		{xy_top_left_top_most_square.x, xy_top_left_top_most_square.y+square_width}, 
		{xy_top_left_top_most_square.x+square_width, xy_top_left_top_most_square.y+square_width}
	};
	generate_sides_of_square_on_grid(grid, square_width, seed, top_most_square);

	//generate second square
	Coordinate xy_top_left_bottom_most_square = {top_most_square.top_left.y+square_width-1, top_most_square.top_left.x+square_width-1};
	generate_square_on_grid(grid, square_width, seed, xy_top_left_bottom_most_square);

	//print grid
	print_2D_grid(grid);

}

int main() {
	//Default constants

	//string seed to generate sides (recommended to be 30 chars or less)
	const string seed = "ILOVESPACEX";

	//grid_constant to generate size of grid (loosely represents how many times the grid is bigger than the rectangular_cuboid)
	//MUST BE GREATER THAN 1 and recommended to be 2 for small-medium sized seeds.
	//An exceptionally large grid_const might cause a row to  "visually overflow" into another,
	//although it is only a visual limitation of some text editors.
	//Larger seeds need a proportionally higher grid_const.
	const int grid_const = 2;
	//width of square faces of rectangular cuboid
	const int square_width = seed.size();

	//generate 2D grid etc. grid[y][x]
	vector< vector<string> >* grid = new vector< vector<string> >;
	generate_2D_grid(grid, square_width, grid_const);

	//generate 2D representation of rectangular_cuboid on grid
	generate_rectangular_cuboid_on_2D_grid(grid, seed, square_width, grid_const);
}