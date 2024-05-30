#pragma once

//Vertex : 3차원 공간에서의 한 점

struct Vertex
{
    Vertex(float x, float y)
    {
        pos = { x, y, 0.0f };
    }

    Vertex(Vector2 pos)
    {
        this->pos.x = pos.x;
        this->pos.y = pos.y;
        this->pos.z = 0.0f;
    }

    XMFLOAT3 pos;
};

struct VertexColor
{
    VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
        :pos(pos), color(color)
    {
    }

    VertexColor(XMFLOAT2 pos, XMFLOAT4 color)
        :color(color)
    {
        this->pos.x = pos.x;
        this->pos.y = pos.y;
        this->pos.z = 0.0f;
    }

    VertexColor(float x, float y, float r, float g, float b, float a = 1.0f)
    {
        pos   = XMFLOAT3(x, y, 0.0f);
        color = XMFLOAT4(r, g, b, a);
    }

    XMFLOAT3 pos   = {};
    XMFLOAT4 color = {};
};


struct VertexTexture
{
    VertexTexture(Vector2 pos, Vector2 uv)
        :uv(uv)
    {
        this->pos.x = pos.x;
        this->pos.y = pos.y;
    }

    Vector3 pos = {};
    Vector2 uv  = {};
};