#ifndef MAX_CURVATURE_H
#define MAX_CURVATURE_H

#include <Eigen/Core>
#include <modcam/mesh/concepts.h>
#include <modcam/mesh/principal_curvature_rus2004.h>

using RowMatrixX3d = Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>;

namespace modcam_cmake_example {

/**
 * Compute the maximum curvature on a triangle mesh.
 *
 * @param[in] vertices V-by-3 matrix of mesh vertex Cartesian coordinates
 * @param[in] faces F-by-3 matrix of face (triangle) indices. Each row
 * represents a triangle by indexing three vertices (rows) from the \p vertices
 * array.
 * @returns The maximum curvature
 */
template <Vertices3D DerivedV, TriangleFaces DerivedF>
double max_curvature(const Eigen::MatrixBase<DerivedV> &vertices,
                     const Eigen::MatrixBase<DerivedF> &faces)
{
	assert(vertices.cols() == 3 && "vertices must have 3 columns");
	assert(faces.cols() == 3 && "faces must have 3 columns");

	if (vertices.size() == 0) {
		return 0.0;
	}

	if (faces.size() == 0) {
		return 0.0;
	}

	RowMatrixX3d pd1;
	RowMatrixX3d pd2;
	Eigen::VectorXd pv1;
	Eigen::VectorXd pv2;
	modcam::mesh::principal_curvature_rus2004(pd1, pd2, pv1, pv2, vertices,
	                                          faces);
	return pv1.maxCoeff();
}

} // namespace modcam_cmake_example

#endif
