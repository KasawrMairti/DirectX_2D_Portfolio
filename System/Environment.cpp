#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
	CreateProjection();
	CreateSamplerState();
	CreateAlphaBlend();
	CreateRasterizeState();
}

Environment::~Environment()
{
	delete pBuffer;

	samplerState->Release();
}

void Environment::CreateProjection()
{
	pBuffer = new MatrixBuffer();

	XMMATRIX projection = XMMatrixOrthographicOffCenterLH
	(
		0.0f, WIN_WIDTH,
		0.0f, WIN_HEIGHT,
		0.0f, 1.0f
	);

	pBuffer->SetData(projection);


	pBuffer->SetVSBuffer(2);
}

void Environment::CreateSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc = {};

	samplerDesc.Filter         = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD		   = 0;
	samplerDesc.MaxLOD         = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&samplerDesc, &samplerState);

	DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateAdditive()
{
	D3D11_BLEND_DESC blendDesc = {};

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&blendDesc, &alphaBlendState);

	DC->OMSetBlendState(alphaBlendState, nullptr, D3D11_DEFAULT_SAMPLE_MASK);
}

void Environment::CreateAlphaBlend()
{
	D3D11_BLEND_DESC blendDesc = {};

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&blendDesc, &alphaBlendState);

	DC->OMSetBlendState(alphaBlendState, nullptr, D3D11_DEFAULT_SAMPLE_MASK);
}

void Environment::CreateRasterizeState()
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_NONE; //backface culling 
	desc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&desc, &rasterizerState);

	DC->RSSetState(rasterizerState);
}
