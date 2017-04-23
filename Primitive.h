#pragma once

namespace softlit
{
	typedef void* UniformBuffer;

	// vertex_shader to be run per-vertex to transform vertices to clip-coordinates
	typedef glm::vec4(*vertex_shader)(const glm::vec3& pos, UniformBuffer ubo);

	// fragment_shader to output final render target values
	typedef glm::vec4(*fragment_shader)();

	class Primitive
	{
	public:
		Primitive(vertex_shader vs, fragment_shader fs, const PrimitiveTopology top);
		~Primitive();

		const std::vector<glm::vec3>& getVertexBuffer() const { return m_vertexBuffer; }
		const std::vector<uint64_t>& getIndexBuffer() const { return m_indexBuffer; }

		void setVertexBuffer(const std::vector<glm::vec3>& vb) { m_vertexBuffer = vb; }
		void setIndexBuffer(const std::vector<uint64_t>& ib) { m_indexBuffer = ib; }

		const PrimitiveTopology getPrimitiveTopology() const { return m_topology; }

		vertex_shader VS() { return m_VS; }
		fragment_shader FS() { return m_FS; }

		UniformBuffer UBO() { return m_ubo; }
		void UBO(UniformBuffer ubo) { m_ubo = ubo; }

	private:
		std::vector<glm::vec3> m_vertexBuffer;
		std::vector<uint64_t> m_indexBuffer;

		PrimitiveTopology m_topology;

		UniformBuffer m_ubo;
		vertex_shader m_VS;
		fragment_shader m_FS;
	};
}