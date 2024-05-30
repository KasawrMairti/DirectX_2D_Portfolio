#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	vBuffer = new MatrixBuffer();

	transform = new Transform();
}

Camera::~Camera()
{
	delete transform;
	delete vBuffer;
}

void Camera::Update()
{
	if (target == nullptr)
		FreeMode();
	else
		TargetMode();

	transform->Update();

	Matrix view = XMMatrixInverse(nullptr, transform->GetWorld());

	vBuffer->SetData(view);
	vBuffer->SetVSBuffer(1);
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('A'))
		{
			transform->Translation() += Vector2(-1, 0) * speed * Time::Delta();
		}

		if (KEY_PRESS('D'))
		{
			transform->Translation() += Vector2(+1, 0) * speed * Time::Delta();
		}

		if (KEY_PRESS('S'))
		{
			transform->Translation() += Vector2(0, -1) * speed * Time::Delta();
		}

		if (KEY_PRESS('W'))
		{
			transform->Translation() += Vector2(0, +1) * speed * Time::Delta();
		}
	}
}

void Camera::TargetMode()
{
	Vector2 destination = target->Translation() - offset;

	for (Area area : area)
	{
		if (area.L < OBJECT->GetPlayer()->Translation().x &&
			area.R > OBJECT->GetPlayer()->Translation().x &&
			area.T > OBJECT->GetPlayer()->Translation().y &&
			area.B < OBJECT->GetPlayer()->Translation().y)
		{
			if (destination.x < area.L)
				destination.x = area.L;

			if (destination.y < area.B)
				destination.y = area.B;

			if (destination.x > area.R - WIN_WIDTH)
				destination.x = area.R - WIN_WIDTH;

			if (destination.y > area.T - WIN_HEIGHT)
				destination.y = area.T - WIN_HEIGHT;

			break;
		}
	}

	transform->Translation() = Vector2::Lerp(transform->Translation(), destination, speed * Time::Delta());
}

void Camera::SetTranslation(Transform* target)
{
	transform->Translation() = target->Translation() - offset;
}
