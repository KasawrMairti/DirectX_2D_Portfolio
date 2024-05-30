#pragma once

class Device : public Singleton<Device>
{
private:
	friend class Singleton;

private:
	Device();
	~Device();

public:
	void Clear();
	void Present();

	ID3D11Device*        GetDevice() { return device; }
	ID3D11DeviceContext* GetDC()     { return deviceContext; }

	IDXGISwapChain* GetSwapChain() { return swapChain; }

	void InitDevice();

private:
	ID3D11Device*        device;        //CPU를 다루는 객체, 무언가를 만들 때 사용, Create
	ID3D11DeviceContext* deviceContext; //GPU를 다루는 객체, 무언가를 그릴 때 사용, Set
	
	IDXGISwapChain* swapChain; //더블버퍼링을 해주는 객체
	
	ID3D11RenderTargetView* renderTargetView; //백버퍼를 관리하는 객체 - View = GPU
};
