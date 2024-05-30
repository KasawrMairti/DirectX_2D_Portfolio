#include "Framework.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	background->Update();

	selectImage->Update();

	titleName->Update();
	titleImage->Update();

	if (fadeEventTime < 2 && Time::OneTimed())
	{
		fadeEventTime++;
		Time::OneTimed() = false;
	}
	else if (fadeEventTime == 2 && Time::OneTimed())
	{
		fadeEventTime++;
		titleName->FadeInOut() = true;
		titleImage->FadeInOut() = true;
		Time::OneTimed() = false;
	}
	else if (fadeEventTime > 2 && fadeEventTime < 5 && Time::OneTimed())
	{
		fadeEventTime++;
		Time::OneTimed() = false;
	}
}

void TitleScene::Render()
{
	background->Render();

	selectImage->Render();

	titleName->Render();
	titleImage->Render();

	if (fadeEventTime >= 1)
	{
		wstring str;
		str = L"Start";
		FONT->RenderText(str, "D2CodingTitle", Vector2(980, 310), Vector2(400, 200));
		str = L"EXIT";
		FONT->RenderText(str, "D2CodingTitle", Vector2(980, 500), Vector2(400, 200));
		selectImage->Translation() = point[selectPoint];
	}

	if (KEY_DOWN(VK_UP)) selectPoint = 0;
	else if (KEY_DOWN(VK_DOWN)) selectPoint = 1;

	if (KEY_DOWN('Z'))
	{
		if (selectPoint == 0) SCENE->ChangeScene("FirstScene");
		else if (selectPoint == 1) SendMessage(hWnd, WM_CLOSE, 0, 0);;
	}
}

void TitleScene::Initialize()
{
	InitialImage();

	SCENE->LoadComplete() = true;
}

void TitleScene::Release()
{
	delete background;
	delete titleName;
	delete titleImage;

	delete selectImage;
}

void TitleScene::InitialImage()
{
	background = new IdleImage(L"UI/WhiteBox.png", 1, 1);
	background->Translation().x = WIN_WIDTH * 0.5f;
	background->Translation().y = WIN_HEIGHT * 0.5f;
	background->Scale().x *= 200;
	background->Scale().y *= 200;
	background->SetColor(0.0f, 0.0f, 0.0f, 1.0f);
	background->FadeInOut() = false;

	titleName = new Object(L"UI/TitleName.png");
	titleName->Translation().x = 370.0f;
	titleName->Translation().y = 550.0f;
	titleName->Scale().x = 1.5f;
	titleName->Scale().y = 1.5f;
	titleName->SetColor(1.0f, 1.0f, 1.0f, 0.0f);

	titleImage = new IdleImage(L"UI/MainImage.png", 2, 2);
	titleImage->Translation().x = 370.0f;
	titleImage->Translation().y = 280.0f;
	titleImage->Scale().x /= 2;
	titleImage->Scale().y /= 2;
	titleImage->SetColor(1.0f, 1.0f, 1.0f, 0.0f);

	point[0] = Vector2(980, 460);
	point[1] = Vector2(980, 275);
	selectImage = new SelectImage();
	selectImage->Scale().x /= 4;
	selectImage->Scale().y /= 4;
	selectImage->Translation() = { -9999, -9999 };
}
