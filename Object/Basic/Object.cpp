#include "Framework.h"
#include "Object.h"

Object::Object(XMFLOAT2 pos, XMFLOAT2 size, XMFLOAT4 color)
    :alpha(color.z)
{
    float left   = pos.x - size.x * 0.5f;
    float right  = pos.x + size.x * 0.5f;
    float top    = pos.y + size.y * 0.5f;
    float bottom = pos.y - size.y * 0.5f;

	vertices =
    {
        VertexTexture(Vector2( left,    top), Vector2(0, 0)),
        VertexTexture(Vector2(right,    top), Vector2(1, 0)),
        VertexTexture(Vector2( left, bottom), Vector2(0, 1)),
        VertexTexture(Vector2(right, bottom), Vector2(1, 1)),
    };

    indices =
    {
        0, 1, 2,
        2, 1, 3
    };

    vertexBuffer = new VertexBuffer(vertices);
     indexBuffer = new  IndexBuffer(indices);

    vertexShader = new VertexShader(L"VertexTexture");
     pixelShader = new  PixelShader(L"PixelTexture");

     worldBuffer = new MatrixBuffer();
     colorBuffer = new  ColorBuffer();
}

Object::Object(wstring file, Vector2 uvStart, Vector2 uvEnd)
{
    texture = Texture::Add(file);

    Vector2 pos  = { 0, 0 };

    size =
    {
        texture->GetSize().x * (uvEnd - uvStart).x,
        texture->GetSize().y * (uvEnd - uvStart).y
    };

    float left   = pos.x - size.x * 0.5f;
    float right  = pos.x + size.x * 0.5f;
    float top    = pos.y + size.y * 0.5f;
    float bottom = pos.y - size.y * 0.5f;

    vertices =
    {
        VertexTexture(Vector2( left,    top), Vector2(uvStart.x, uvStart.y)),
        VertexTexture(Vector2(right,    top), Vector2(  uvEnd.x, uvStart.y)),
        VertexTexture(Vector2( left, bottom), Vector2(uvStart.x,   uvEnd.y)),
        VertexTexture(Vector2(right, bottom), Vector2(  uvEnd.x,   uvEnd.y)),
    };

    indices =
    {
        0, 1, 2,
        2, 1, 3
    };

    vertexBuffer = new VertexBuffer(vertices);
     indexBuffer = new  IndexBuffer(indices);

    vertexShader = new VertexShader(L"VertexTexture");
     pixelShader = new  PixelShader(L"PixelTexture");

    worldBuffer = new MatrixBuffer();
    colorBuffer = new  ColorBuffer();
}

Object::~Object()
{
    delete colorBuffer;
    delete worldBuffer;

    delete  pixelShader;
    delete vertexShader;

    delete  indexBuffer;
    delete vertexBuffer;
}

void Object::Update()
{
    Transform::Update();

    if (fadeInOut)
    {
        if (alpha < 1.0f)
        {
            alpha += 0.2f * Time::Delta();
            this->SetColor(colorBuffer->GetColor().x, colorBuffer->GetColor().y, colorBuffer->GetColor().z, alpha);
        }
    }
    else if (!fadeInOut)
    {
        if (alpha > 0.0f)
        {
            alpha -= 0.2f * Time::Delta();
            this->SetColor(colorBuffer->GetColor().x, colorBuffer->GetColor().y, colorBuffer->GetColor().z, alpha);
        }
    }
}

void Object::Render()
{
    vertexBuffer->SetBuffer();
     indexBuffer->SetBuffer();
    vertexShader->SetShader();
     pixelShader->SetShader();

     worldBuffer->SetData(world);
     worldBuffer->SetVSBuffer(0);

     colorBuffer->SetPSBuffer(0);

     if (texture != nullptr)
         texture->SetPS();

    
    Device::Get()->GetDC()->DrawIndexed(indices.size(), 0, 0);
}

