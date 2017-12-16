#include "model.h"

template<>
struct std::hash<AdunGL::graphics::Model::IndexSet>
{
	const size_t operator()(const AdunGL::graphics::Model::IndexSet& key) const
	{
		return (key.position) ^ (key.normal << 14) ^ (key.uv << 23);
	}
};

namespace AdunGL
{
	namespace graphics
	{
		using namespace maths;

		Model::Model(const string& path, MaterialInstance* materialInstance)
		{
			load(path);
			m_mesh->setMaterial(materialInstance);
		}

		Model::~Model()
		{
			delete m_mesh;
		}

		void Model::load(const string& path)
		{
			// vt => uv
			// vn => normal
			// v  => position
			// f  => index
			vector<string> lines = utils::split_string(utils::FileUtils::read_file(path), '\n');

			VertexSet inputVertices;

			vector<Vertex> vertices;
			vector<GLuint> indices;

			unordered_map<IndexSet, int> mapping;


			// obj파일 파싱
			for (string line : lines)
			{
			
				const char* cstr = line.c_str();
				if (strstr(cstr, "#"))
				{
					// 주석
					continue;
				}
				else if (strstr(cstr, "v"))
				{
					if (strstr(cstr, "vt"))
					{
						vec2 uv;
						int result = sscanf(cstr, "%*s %f %f", &uv.x, &uv.y);
						if (result == 0)
							continue;
						inputVertices.uvs.push_back(uv);
					}
					else if (strstr(cstr, "vn"))
					{
						vec3 normal;
						int result = sscanf(cstr, "%*s %f %f %f", &normal.x, &normal.y, &normal.z);
						if (result == 0)
							continue;
						inputVertices.normals.push_back(normal);
					}
					else
					{
						vec3 position;
						int result = sscanf(cstr, "%*s %f %f %f", &position.x, &position.y, &position.z);
						if (result == 0)
							continue;
						inputVertices.positions.push_back(position);
					}
				}
				else if (strstr(cstr, "f"))
				{
					IndexSet indexSet[3];
					string a;
					int result = sscanf(cstr, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
						&indexSet[0].position, &indexSet[0].uv, &indexSet[0].normal,
						&indexSet[1].position, &indexSet[1].uv, &indexSet[1].normal,
						&indexSet[2].position, &indexSet[2].uv, &indexSet[2].normal);
					if (result == 0)
						continue;

					//cout << "1" << endl;
					insertVertex(vertices, indices, mapping, inputVertices, indexSet[0]);
					//cout << "2" << endl;

					insertVertex(vertices, indices, mapping, inputVertices, indexSet[1]);
					//cout << "3" << endl;

					insertVertex(vertices, indices, mapping, inputVertices, indexSet[2]);
				}
			}

			Buffer* buffer = new Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
			
			buffer->bind();
			buffer->setData(vertices.size() * sizeof(Vertex), &vertices[0]);

			buffer->layout.push<vec3>("position");
			buffer->layout.push<vec3>("normal");
			buffer->layout.push<vec2>("uv");

			VertexArray* va = new VertexArray();
			va->bind();
			va->pushBuffer(buffer);

			IndexBuffer* ib = new IndexBuffer(&indices[0], indices.size());
			m_mesh = new Mesh(va, ib, nullptr);
		}

		void Model::insertVertex(vector<Vertex>& vertices, vector<GLuint>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet)
		{
			auto lookup = mapping.find(indexSet);

			if (lookup != mapping.end())
			{ // 존재
				//cout << "존" << endl;

				indices.push_back(lookup->second);
			}
			else
			{
				//cout << "비존" << endl;
				mapping[indexSet] = (int)vertices.size();
				indices.push_back(vertices.size());

				//cout << "---------------------------------------" << endl;
	
				//cout << indexSet.position << endl;
				//cout << indexSet.uv << endl;
				//cout << indexSet.normal << endl;
				//cout << "---------------------------------------" << endl;


				Vertex vertex = { inputVertices.positions[indexSet.position - 1], inputVertices.normals[indexSet.normal - 1], inputVertices.uvs[indexSet.uv - 1] };
				vertices.push_back(vertex);
			}
		}

		void Model::render(Renderer3D& renderer)
		{
			m_mesh->render(renderer);
		}

	}
}