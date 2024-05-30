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
	ID3D11ShaderResourceView* srv; //Shader���� �̹��� ������ ���� �� �ְ� ���ִ� ��ü

	ScratchImage image;

	static map<wstring, Texture*> textures;
};
