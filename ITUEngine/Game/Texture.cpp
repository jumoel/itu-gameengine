#include <Game/Texture.hpp>


Texture::Texture()
{
}

Texture::Texture(GLenum TextureTarget, char* FileName)
{
    textureTarget = TextureTarget;
    filename	  = FileName;
}


Texture::~Texture()
{
}

void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(textureTarget, texID);
}
