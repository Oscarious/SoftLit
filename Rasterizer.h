#pragma once

namespace softlit
{
	typedef std::vector<glm::vec4> FrameBuffer;
	typedef std::vector<float> DepthBuffer;

	class Primitive;
	class VertexBuffer;
	class IndexBuffer;

	class Rasterizer
	{
	public:
		Rasterizer(const RasterizerSetup& setup);
		~Rasterizer();

		const FrameBuffer& getFrameBuffer() const { return m_frameBuffer; }
		const DepthBuffer& getZBuffer() const { return m_depthBuffer; }

		/*
		* Rasterize given primitive set
		*/
		void Draw(Primitive* prim, const glm::mat4& view, const glm::mat4& proj);

	private:
		FrameBuffer m_frameBuffer; // Used to hold rasterized primitives color buffer, colors in [0.f, 1.f]
		DepthBuffer m_depthBuffer; // Used as depth buffer

		RasterizerSetup m_setup;

		float PixelCoverage(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);

		void InvalidateBuffers()
		{
			fill(m_frameBuffer.begin(), m_frameBuffer.end(), glm::vec4(1, 1, 1, 1));
			fill(m_depthBuffer.begin(), m_depthBuffer.end(), FLT_MAX);
		}

		struct Triangle
		{
			glm::vec3 v0;
			glm::vec3 v1;
			glm::vec3 v2;

			Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) : v0(a), v1(b), v2(c) {}
		};

		/*
		* Set ups a triangle based on index into the index buffer of primitive and triangle topology e.g TRIANGLE_LIST, TRIANGLE_STRIP
		*/
		Triangle setupTriangle(const std::vector<glm::vec3>& vbo, const std::vector<uint64_t>&  ibo, const uint64_t idx) const;
	};
}