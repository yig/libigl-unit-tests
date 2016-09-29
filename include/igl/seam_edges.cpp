#include <iostream>
#include <Eigen/Core>
#include <igl/seam_edges.h>

using namespace std;
using namespace Eigen;

template< typename DerivedV, typename DerivedTC, typename DerivedF >
void test_mesh( const DerivedV& V, const DerivedTC& TC, const DerivedF& F, const DerivedF& FTC ) {
	MatrixXi seams, boundaries, foldovers;
	igl::seam_edges( V, TC, F, FTC, seams, boundaries, foldovers );
	
	cout << "seams:\n";
	cout << seams << "\n\n";
	
	cout << "boundaries:\n";
	cout << boundaries << "\n\n";
	
	cout << "foldovers:\n";
	cout << foldovers << "\n\n";
}

void test_one_triangle() {
	MatrixXd V( 3, 3 );
	V.row(0) << 0, 0, 0;
	V.row(1) << 1, 0, 0;
	V.row(2) << 0, 1, 0;
	
	MatrixXd TC( 3, 2 );
	TC = V.block< 3, 2 >( 0, 0 );
	
	MatrixXi F( 1, 3 );
	F << 0, 1, 2;
	
	// Should print every edge of triangle 0 as a boundary:
	/*
    0 0
    0 1
    0 2
	*/
	test_mesh( V, TC, F, F );
}

void test_cube() {
	MatrixXd V( 8, 3 );
	V.row(0) << 0.0, 0.0, 0.0;
	V.row(1) << 0.0, 0.0, 1.0;
	V.row(2) << 0.0, 1.0, 0.0;
	V.row(3) << 0.0, 1.0, 1.0;
	V.row(4) << 1.0, 0.0, 0.0;
	V.row(5) << 1.0, 0.0, 1.0;
	V.row(6) << 1.0, 1.0, 0.0;
	V.row(7) << 1.0, 1.0, 1.0;
	
	MatrixXd TC( 14, 2 );
    TC.row(0)  << 0.25 , 0.75;
    TC.row(1)  << 0.5  , 0.75;
    TC.row(2)  << 0    , 0.5;
    TC.row(3)  << 0.25 , 0.5;
    TC.row(4)  << 0.5  , 0.5;
    TC.row(5)  << 0.75 , 0.5;
    TC.row(6)  << 1.0  , 0.5;
    TC.row(7)  << 0.0  , 0.25;
    TC.row(8)  << 0.25 , 0.25;
    TC.row(9)  << 0.5  , 0.25;
    TC.row(10) << 0.75 , 0.25;
    TC.row(11) << 1.0  , 0.25;
    TC.row(12) << 0.25 , 0.0;
    TC.row(13) << 0.5  , 0.0;
	
	MatrixXi F( 12, 3 );
    F.row(0)    << 0, 6, 4;
    F.row(1)    << 0, 2, 6;
    F.row(2)    << 0, 3, 2;
    F.row(3)    << 0, 1, 3;
    F.row(4)    << 2, 7, 6;
    F.row(5)    << 2, 3, 7;
    F.row(6)    << 4, 6, 7;
    F.row(7)    << 4, 7, 5;
    F.row(8)    << 0, 4, 5;
    F.row(9)    << 0, 5, 1;
    F.row(10)   << 1, 5, 7;
    F.row(11)   << 1, 7, 3;
    
	MatrixXi FTC( 12, 3 );
    FTC.row(0)  << 9  , 12 , 13;
    FTC.row(1)  << 9  , 8  , 12;
    FTC.row(2)  << 9  , 3  , 8;
    FTC.row(3)  << 9  , 4  , 3;
    FTC.row(4)  << 8  , 2  , 7;
    FTC.row(5)  << 8  , 3  , 2;
    FTC.row(6)  << 10 , 11 , 6;
    FTC.row(7)  << 10 , 6  , 5;
    FTC.row(8)  << 9  , 10 , 5;
    FTC.row(9)  << 9  , 5  , 4;
    FTC.row(10) << 4  , 1  , 0;
    FTC.row(11) << 4  , 0  , 3;
    
	// Should find only seams:
    /*
    1  1  4  2
    6  1  4  1
    8  0  0  2
    10 1  7  1
    10 0  9  1
    6  0  0  1
    5  1 11  1
    */
	test_mesh( V, TC, F, FTC );
}

int main(int argc, char *argv[]) {
    cout << "=> test_one_triangle()\n";
	test_one_triangle();
    
    cout << endl << endl;
    
    cout << "=> test_cube()\n";
    test_cube();
}
