#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:
	MatrixBuffer()
		:ConstantBuffer(&data, sizeof(Data))
	{
		data.matrix = XMMatrixIdentity();
	}

	void SetData(XMMATRIX value)
	{
		data.matrix = XMMatrixTranspose(value);
	}

private:
	struct Data
	{
		XMMATRIX matrix;
	} data;
};


class ColorBuffer : public ConstantBuffer
{
public:
	ColorBuffer()
		:ConstantBuffer(&data, sizeof(Data))
	{
		data.color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	void SetData(Vector4 color)
	{
		data.color = color;
	}

	void SetData(float r, float g, float b, float a = 1.0f)
	{
		data.color = Vector4(r, g, b, a);
	}

	Vector4 GetColor() { return data.color; }

private:
	struct Data
	{
		Vector4 color;
	} data;
};