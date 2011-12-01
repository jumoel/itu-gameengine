#ifndef ITUENGINE_MODEL_H
#define ITUENGINE_MODEL_H

#include <vector>
#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <GL/glew.h>
#include <Game/Texture.hpp>
#include <Math/Vector3f.hpp>
#include <Vector2f.hpp>
#include <Game/Material.hpp>

struct Vert
{
    Vector3f m_pos;
	Vector2f m_tex;
    Vector3f m_normal;

    Vert() {}

    Vert(const Vector3f& pos, Vector2f& tex, const Vector3f& normal)
    {
        m_pos    = pos;
        m_tex	 = tex;
        m_normal = normal;
    }
};




class Model
{
public:
	Model();
	~Model();

    void Render();
    bool InitFromScene(const aiScene* pScene, const std::string& Filename);

private:
    void InitModel(unsigned int Index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

    struct ModelEntry {
        ModelEntry();

        ~ModelEntry();

        void Init(const std::vector<Vert>& Vertices,
                  const std::vector<unsigned int>& Indices);

        GLuint VB;
        GLuint IB;
		std::vector<Vert> Verts;
		unsigned int NumVertices;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::vector<ModelEntry> m_Entries;
    std::vector<Material*> m_Materials;

};

#endif