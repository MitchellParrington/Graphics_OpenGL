#include "bmpch.hpp"
#include "Transform.hpp"

#include "Vendor/Glm.hpp"

namespace Bam
{
	Status InitTransform(Transform& t, f32ut x, f32ut y, f32ut z, f32ut yaw, f32ut pitch, f32ut roll, f32ut xs, f32ut ys, f32ut zs)
	{
		t.translation = glm::vec3{ x, y, z };
		t.scale = glm::vec3{ xs, ys, zs };
		t.rotationEuler = glm::vec3{ yaw, pitch, roll };
		t.rotationQuat = glm::quat{ glm::vec3{yaw, pitch, roll} };
		return Status::Success;
	}

	Status UpdateTransformQuat(Transform& t)
	{
		t.rotationQuat = glm::quat{ t.rotationEuler };
		return Status::Success;
	}

	glm::vec3 EvalTransformOnPoint(Transform& t, glm::vec3 p)
	{
		return (t.rotationQuat * (p * t.scale)) + t.translation;
	}
}