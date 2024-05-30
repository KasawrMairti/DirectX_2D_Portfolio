#include "Framework.h"
#include "Transform.h"

Transform::Transform()
{
		S = XMMatrixIdentity();
		R = XMMatrixIdentity();
		T = XMMatrixIdentity();
	world = XMMatrixIdentity();
}

Transform::~Transform()
{
}

void Transform::Update()
{
	UpdateWorld();
}

void Transform::UpdateWorld()
{
	S = XMMatrixScaling(lScale.x, lScale.y, 1.0f);
	R = XMMatrixRotationRollPitchYaw(lRotation.x, lRotation.y, lRotation.z);
	T = XMMatrixTranslation(lTranslation.x, lTranslation.y, 0.0f);

	 P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
	IP = XMMatrixInverse(nullptr, P);

	world = IP * S * R * T * P;

	if (parent != nullptr)
		world *= parent->world;

	XMFLOAT4X4 floatWorld;
	XMStoreFloat4x4(&floatWorld, world);

	right = Vector2(floatWorld._11, floatWorld._12).GetNormal();
	   up = Vector2(floatWorld._21, floatWorld._22).GetNormal();

	XMVECTOR outS, outR, outT;

	XMMatrixDecompose(&outS, &outR, &outT, world);

	XMStoreFloat2(&globalScale,    outS);
	XMStoreFloat2(&globalPosition, outT);
}

void Transform::Debug()
{
	if (ImGui::BeginMenu(label.c_str()))
	{
		ImGui::DragFloat2 ("Scale",       (float*)&lScale,       0.1f,       0.1f,     50.0f);
		ImGui::SliderAngle("Rotation",            &lRotation.z);
		ImGui::DragFloat2 ("Translation", (float*)&lTranslation, 1.0f, -WIN_WIDTH, WIN_WIDTH);
		ImGui::EndMenu();
	}
}

void Transform::Debug(string label)
{
	if (ImGui::BeginMenu(label.c_str()))
	{
		ImGui::DragFloat2 ("Scale",       (float*)&lScale,       0.1f,       0.1f,     50.0f);
		ImGui::SliderAngle("Rotation",            &lRotation.z);
		ImGui::DragFloat2 ("Translation", (float*)&lTranslation, 1.0f, -WIN_WIDTH, WIN_WIDTH);
		ImGui::EndMenu();
	}
}

