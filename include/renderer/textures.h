#pragma once
#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <iostream>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline unsigned int GetID() const { return ID; }
	inline std::string getPath() { return m_FilePath; }
	inline std::string getType() { return m_Type; }
private:
	unsigned int ID;
	std::string m_FilePath;
	std::string m_Type;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

};

struct	MeshTexture {
	unsigned int id;
	std::string type;
	std::string path;
};