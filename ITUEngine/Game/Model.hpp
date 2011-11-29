#ifndef ITUENGINE_MODEL_H
#define ITUENGINE_MODEL_H

#include <vector>
#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <GL/glew.h>
#include <Game/Texture.hpp>
#include <Math/Vector3f.hpp>
#include <Game/Material.hpp>

struct Vert
{
    Vector3f m_pos;
    float m_texX;
	float m_texY;
    Vector3f m_normal;

    Vert() {}

    Vert(const Vector3f& pos, const float texX, const float texY, const Vector3f& normal)
    {
        m_pos    = pos;
        m_texX   = texX;
		m_texX   = texY;
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
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::vector<ModelEntry> m_Entries;
    std::vector<Material*> m_Materials;

};

#endif