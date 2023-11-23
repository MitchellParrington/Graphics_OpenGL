#pragma once
#include "bmpch.hpp"

#include "Vendor/Glm.hpp"

namespace Bam
{
	using Vec1 = glm::vec<1, f32ut, glm::qualifier::packed_highp>;
	using Vec2 = glm::vec<2, f32ut, glm::qualifier::packed_highp>;
	using Vec3 = glm::vec<3, f32ut, glm::qualifier::packed_highp>;
	using Vec4 = glm::vec<4, f32ut, glm::qualifier::packed_highp>;

	using Float1 = glm::vec<1, f32ut, glm::qualifier::packed_highp>;
	using Float2 = glm::vec<2, f32ut, glm::qualifier::packed_highp>;
	using Float3 = glm::vec<3, f32ut, glm::qualifier::packed_highp>;
	using Float4 = glm::vec<4, f32ut, glm::qualifier::packed_highp>;

	using Int1 = glm::vec<1, i32t, glm::qualifier::packed_highp>;
	using Int2 = glm::vec<2, i32t, glm::qualifier::packed_highp>;
	using Int3 = glm::vec<3, i32t, glm::qualifier::packed_highp>;
	using Int4 = glm::vec<4, i32t, glm::qualifier::packed_highp>;

	using Uint1 = glm::vec<1, ui32t, glm::qualifier::packed_highp>;
	using Uint2 = glm::vec<2, ui32t, glm::qualifier::packed_highp>;
	using Uint3 = glm::vec<3, ui32t, glm::qualifier::packed_highp>;
	using Uint4 = glm::vec<4, ui32t, glm::qualifier::packed_highp>;
}