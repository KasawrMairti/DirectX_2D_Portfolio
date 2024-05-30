#include "Framework.h"
#include "Device.h"

Device::Device()
{
    InitDevice();
}

Device::~Device()
{
              device->Release();
       deviceContext->Release();
           swapChain->Release();
    renderTargetView->Release();
}

void Device::Clear()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
}

void Device::Present()
{
    swapChain->Present(0, 0);
}

void Device::InitDevice()
{
	UINT width  = WIN_WIDTH;
    UINT height = WIN_HEIGHT;

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    swapChainDesc.BufferCount = 1; 
    swapChainDesc.BufferDesc.Width  = width;
    swapChainDesc.BufferDesc.Height = height;

    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //UNORM = unsigned normal : 0 ~ 1, RGBA 8��Ʈ * 4��

    swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60; //Numerator   = ����
    swapChainDesc.BufferDesc.RefreshRate.Denominator =  1; //Denominator = �и�

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    swapChainDesc.OutputWindow = hWnd;

    swapChainDesc.SampleDesc.Count   = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    swapChainDesc.Windowed = true;

    D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );

    ID3D11Texture2D* backBuffer;

    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);

    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

    //OM = Output Merger : Rendering Pipeline�� ���� ������ �ܰ�, ��� �����͸� ��ġ�� ��

    D3D11_VIEWPORT viewPort;
    viewPort.Width    = width;
    viewPort.Height   = height;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;


    deviceContext->RSSetViewports(1, &viewPort);
}

