#include "Framework.h"
#include "Texture.h"

map<wstring, Texture*> Texture::textures = {};

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	:srv(srv), image(move(image))
{
}

Texture::~Texture()
{
	srv->Release();
}

Texture* Texture::Add(wstring file)
{
	file = L"_Texture/" + file;

	if (textures.count(file) > 0)
		return textures[file];

	ScratchImage tempImage;
	LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, tempImage);

	ID3D11ShaderResourceView* tempSRV;

	CreateShaderResourceView
	(
		DEVICE,
		tempImage.GetImages(),
		tempImage.GetImageCount(),
		tempImage.GetMetadata(),
		&tempSRV
	);

	Texture* texture = new Texture(tempSRV, tempImage);

	textures.emplace(file, texture);

	return texture;
}

void Texture::Delete()
{
	for (pair<wstring, Texture*> pair : textures)
		delete pair.second;

	textures.clear();
}

void Texture::SetPS(UINT slot)
{
	DC->PSSetShaderResources(slot, 1, &srv);
}

Vector2 Texture::GetSize()
{
	return Vector2(image.GetMetadata().width, image.GetMetadata().height);
}
