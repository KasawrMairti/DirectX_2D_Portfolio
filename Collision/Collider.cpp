#include "Framework.h"
#include "Collider.h"

bool Collider::hiddenInGame = false;

Collider::Collider()
{
    vertexShader = new VertexShader(L"VertexLine");
     pixelShader = new  PixelShader(L"PixelLine");

     worldBuffer = new MatrixBuffer();
     colorBuffer = new  ColorBuffer();
     colorBuffer->SetData(Vector4(0, 1, 0, 1));
}

Collider::~Collider()
{
    delete vertexBuffer;

    delete vertexShader;
    delete  pixelShader;

    delete worldBuffer;
    delete colorBuffer;
}

void Collider::Render()
{
    if (hiddenInGame)
        return;

    vertexBuffer->SetBuffer(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    vertexShader->SetShader();
     pixelShader->SetShader();

     worldBuffer->SetData(world);
     worldBuffer->SetVSBuffer(0);

     colorBuffer->SetPSBuffer(0);
    
    Device::Get()->GetDC()->Draw(vertices.size(), 0);
}

bool Collider::Collision(Collider* other)
{
    switch (other->type)
    {
    case Collider::RECT:
        return Collision((ColliderRect*)other);
        break;
    case Collider::CIRCLE:
        return Collision((ColliderCircle*)other);
        break;
    default:
        break;
    }

    return false;
}
