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
	ID3D11Device*        device;        //CPU�� �ٷ�� ��ü, ���𰡸� ���� �� ���, Create
	ID3D11DeviceContext* deviceContext; //GPU�� �ٷ�� ��ü, ���𰡸� �׸� �� ���, Set
	
	IDXGISwapChain* swapChain; //������۸��� ���ִ� ��ü
	
	ID3D11RenderTargetView* renderTargetView; //����۸� �����ϴ� ��ü - View = GPU
};
