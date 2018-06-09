//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#include <infra/Strung.h>
#include <math/Vec.h>
#include <geom/Primitive.h>
#include <geom/Aabb.h>
#endif
#include <gfx/Forward.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ struct MUD_GFX_EXPORT GpuMesh
	{
		const bgfx::Memory* m_vertex_memory = nullptr;
		const bgfx::Memory* m_index_memory = nullptr;

		array<ShapeVertex> m_vertices = {};
		array<ShapeIndex> m_indices = {};
	};

	export_ class refl_ MUD_GFX_EXPORT Mesh
	{
	public:
		Mesh(cstring name, bool readback = false);
		~Mesh();

		Mesh(Mesh&& other) = default;
		Mesh& operator=(Mesh&& other) = default;

		attr_ string m_name;
		attr_ uint16_t m_index;
		attr_ DrawMode m_draw_mode = PLAIN;
		attr_ Aabb m_aabb = {};
		attr_ float m_radius = 0.f;
		attr_ vec3 m_origin = Zero3;
		attr_ bool m_readback = false;

		attr_ size_t m_vertexCount = 0;
		attr_ size_t m_indexCount = 0;

		attr_ Material* m_material = nullptr;

		bgfx::VertexBufferHandle m_vertex_buffer = BGFX_INVALID_HANDLE;
		bgfx::IndexBufferHandle m_index_buffer = BGFX_INVALID_HANDLE;

		std::vector<ShapeVertex> m_vertices;
		std::vector<ShapeIndex> m_indices;

		void read(MeshData& data, const mat4& transform) const;
		void write(DrawMode draw_mode, array<ShapeVertex> vertices, array<ShapeIndex> indices);
		GpuMesh allocate(DrawMode draw_mode, size_t numVertices, size_t numIndices);
		void upload(const GpuMesh& gpu_mesh);
		void conserve(const GpuMesh& gpu_mesh);
		uint64_t submit() const;
	};
}
