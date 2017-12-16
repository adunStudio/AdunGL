#pragma once

#include "mesh.h"
#include "../maths/maths.h"
#include "../utils/stringutils.h"
#include "../utils/fileutils.h"
#include <unordered_map>
#include <vector>

using namespace std;

namespace AdunGL
{
	namespace graphics
	{
		class Model : public IRenderable
		{
		private:
			Mesh* m_mesh;

		public:
			Model(const string& path, MaterialInstance* materialInstance);
			~Model();

			void render(Renderer3D& renderer) override;

			inline Mesh* getMesh() const { return m_mesh;  }

		private:
			struct VertexSet
			{
				std::vector<maths::vec3> positions;
				std::vector<maths::vec3> normals;
				std::vector<maths::vec2> uvs;
			};

			struct IndexSet
			{
				unsigned int position;
				unsigned int uv;
				unsigned int normal;

				bool operator==(const IndexSet& other) const
				{
					return position == other.position && uv == other.uv && normal == other.uv;
				}
			};

			friend struct std::hash<IndexSet>;

			void load(const string& path);
			void insertVertex(vector<Vertex>& vertices, vector<GLuint>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet);
		};
	}
}