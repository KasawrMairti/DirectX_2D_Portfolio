#pragma once

class Texture
{
public:
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

	static Texture* Add(wstring file);

	static void Delete();

	void SetPS(UINT slot = 0);

	Vector2 GetSize();

	ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
	ID3D11ShaderResourceView* srv; //Shader에서 이미지 정보를 읽을 수 있게 해주는 객체

	ScratchImage image;

	static map<wstring, Texture*> textures;
};
