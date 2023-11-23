#pragma once
#include "bmpch.hpp"

#include "Vendor/Glm.hpp"

namespace Bam
{
	// Reference:
	// math http://nklein.com/2009/06/quaternions-for-rotating-scaling-and-translating-space/
	// code http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
	// quaternian layout https://github.com/clemense/quaternion-conventions

	struct BM_API Transform
	{
		glm::quat rotationQuat; // rotation quaternian
		glm::vec3 rotationEuler; // rotation XYZ
		glm::vec3 translation; // translation
		glm::vec3 scale; // scale
	};

	Status BM_API InitTransform(Transform& t, f32ut x, f32ut y, f32ut z, f32ut yaw, f32ut pitch, f32ut roll, f32ut xs, f32ut ys, f32ut zs);
	Status BM_API UpdateTransformQuat(Transform&);
	glm::vec3 BM_API EvalTransformOnPoint(Transform&);
}