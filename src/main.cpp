#include <Eigen/Core>
#include <modcam/mesh/principal_curvature_rus2004.h>

#include <cmath>
#include <numbers>

using RowMatrixX3d = Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>;
using RowMatrixX3i = Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::RowMajor>;

int main(int argc, char *argv[])
{
	constexpr auto pi = std::numbers::pi;
	const auto r = 1.0 / (2.0 * std::sin(pi / 5.0));
	using Array12d = Eigen::Array<double, 12, 1>;
	using Array5d = Eigen::Array<double, 5, 1>;
	Array12d phi = Array12d::Zero();
	phi(Eigen::seq(1, 5)) = Array5d::Constant(std::asin(r));
	phi(Eigen::seq(6, 10)) = Array5d::Constant(-std::asin(r));
	phi(11) = pi;
	Array12d theta = Array12d::Zero();
	theta(Eigen::seq(1, 5)) = Array5d::LinSpaced(5, 0.0, 8.0 * pi / 5.0);
	theta(Eigen::seq(6, 10)) = Array5d::LinSpaced(5, pi / 5.0, 9.0 * pi / 5.0);
	RowMatrixX3d vertices = RowMatrixX3d::Zero(12, 3);
	vertices.col(0) = Eigen::sin(phi) * Eigen::cos(theta);
	vertices.col(1) = Eigen::sin(phi) * Eigen::sin(theta);
	vertices.col(2) = Eigen::cos(phi);
	constexpr auto radius = 2.0;
	vertices *= radius;
	const RowMatrixX3i faces{{0, 1, 2},  {0, 2, 3},  {0, 3, 4},   {0, 4, 5},
	                         {0, 5, 1},  {2, 1, 6},  {3, 2, 7},   {4, 3, 8},
	                         {5, 4, 9},  {1, 5, 10}, {6, 7, 2},   {7, 8, 3},
	                         {8, 9, 4},  {9, 10, 5}, {10, 6, 1},  {11, 7, 6},
	                         {11, 8, 7}, {11, 9, 8}, {11, 10, 9}, {11, 6, 10}};
	RowMatrixX3d pd1;
	RowMatrixX3d pd2;
	Eigen::VectorXd pv1;
	Eigen::VectorXd pv2;
	modcam::mesh::principal_curvature_rus2004(pd1, pd2, pv1, pv2, vertices,
	                                          faces);
	std::cout << "Max curvature: " << pv1.maxCoeff() << "\n";
	std::cout << "Min curvature: " << pv2.minCoeff() << "\n";
	return 0;
}
