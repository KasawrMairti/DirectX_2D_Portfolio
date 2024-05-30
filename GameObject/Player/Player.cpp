#include "Framework.h"
#include "Player.h"


Player::Player()
{
	OBJECT->SetPlayer(this);
	bullets = new PlayerBulletManager();

	AddAction();

	curAction = actions[IDLE];
	curAction->Play();

	collider = new ColliderRect({20.0f, 42.0f});
	collider->SetParent(this);
}

Player::~Player()
{
	delete collider;
	delete bullets;
}

void Player::Update()
{
	Character::Update();
	collider->Update();
	bullets->Update();

	if (damaged) DamageEvent();
	if (damageTime > 0.2f || damageTime == 0.0f)
	{
		Move();
		Jump();
	}

	Attack();

}

void Player::Render()
{
	Character::Render();
	collider->Render();
	bullets->Render();
}

void Player::Damaged(UINT damage, bool isRight)
{
	if (!damaged)
	{
		for (UINT i = 0; i < damage; i++)
		{
			UI->hearts_remove();
		}

		if (isRight)
		{
			damageRight = true;
		}
		else
		{
			damageRight = false;
		}

		damaged = true;
	}
}

void Player::DamageEvent()
{
	damageTime += Time::Delta();


	if (damageTime >= 1.0f)
	{
		damageTime = 0.0f;
		damaged = false;
	}
	else if (damageTime <= 0.2f)
	{
		float x = 0.0f;
		float y = +1.0f;

		if (damageRight) x = +1.0f;
		else x = -1.0f;

		// TODO 피격 받고 벽 판정 검사하면서 뒤로 밀러나는 이벤트
		for (Wall* wall : OBJECT->GetWall()->GetWalls())
		{
			if (wall->GetCollider()->Collision(collider) && wall->GetType() == Wall::TOP)
				y = 0.0f;

			if (damageRight)
				if (wall->GetCollider()->Collision(collider) && wall->GetType() == Wall::RIGHT)
					x = 0.0f;
				else if (wall->GetCollider()->Collision(collider) && wall->GetType() == Wall::LEFT)
					x = 0.0f;
		}

		lTranslation += Vector2(x, y) * 400.0f * Time::Delta();
		gravity = 0.0f;
	}
}

void Player::Move()
{
	// Left Right Up Move
	if (KEY_PRESS(VK_LEFT))
	{
		isRight = false;

		if (!jumping)
		{
			if (KEY_PRESS(VK_UP))
				SetAction(State::RUNUP);
			else
				SetAction(State::RUN);
		}

		lRotation.y = XM_PI;

		moveSpeed = movePower;

		for (auto tile : OBJECT->GetWall()->GetWalls())
		{
			if (tile->GetType() == Wall::LEFT)
			{
				Vector2 LT = Vector2(collider->L(), collider->T());
				Vector2 L = Vector2(collider->L(), GlobalPosition().y);
				Vector2 LB = Vector2(collider->L(), collider->B());

				if (tile->GetCollider()->Collision(LT) ||
					tile->GetCollider()->Collision(L) ||
					tile->GetCollider()->Collision(LB))
				{
					moveSpeed = 0;

					break;
				}
			}
		}

		lTranslation += Vector2(-1, 0) * moveSpeed * Time::Delta();
	}
	else if (KEY_PRESS(VK_RIGHT))
	{
		isRight = true;

		if (!jumping)
		{
			if (KEY_PRESS(VK_UP))
				SetAction(State::RUNUP);
			else
				SetAction(State::RUN);
		}

		lRotation.y = 0.0f;

		moveSpeed = movePower;

		for (auto tile : OBJECT->GetWall()->GetWalls())
		{
			if (tile->GetType() == Wall::RIGHT)
			{
				Vector2 RT = Vector2(collider->R(), collider->T());
				Vector2 R = Vector2(collider->R(), lTranslation.y);
				Vector2 RB = Vector2(collider->R(), collider->B());

				if (tile->GetCollider()->Collision(RT) ||
					tile->GetCollider()->Collision(R) ||
					tile->GetCollider()->Collision(RB))
				{
					moveSpeed = 0;

					break;
				}
			}
		}

		lTranslation += Vector2(+1, 0) * moveSpeed * Time::Delta();
	}

	if (KEY_PRESS(VK_UP) && !KEY_PRESS(VK_RIGHT) && !KEY_PRESS(VK_LEFT))
	{
		if (!jumping)
		{
			SetAction(State::IDLEUP);
		}

	}

	if (!KEY_PRESS(VK_UP) && !KEY_PRESS(VK_RIGHT) && !KEY_PRESS(VK_LEFT) && state != State::IDLE && !jumping)
	{
		SetAction(State::IDLE);
	}
	// Left Right Up Move End
}

void Player::Jump()
{
	// Jump
	if (KEY_DOWN('X') && jumpCount < 2)
	{
		gravity = 0.0f;
		jumpSpeed = jumpPower;

		jumpCount++;

		SetAction(State::JUMP);

		jumping = true;
	}

	// Hit Ground
	for (auto tile : OBJECT->GetWall()->GetWalls())
	{
		if (tile->GetType() == Wall::BOTTOM && jumpSpeed < gravity)
		{
			Vector2 LB = Vector2(collider->L(), collider->B());
			Vector2 B = Vector2(lTranslation.x, collider->B());
			Vector2 RB = Vector2(collider->R(), collider->B());

			if (tile->GetCollider()->Collision(LB) ||
				tile->GetCollider()->Collision(B) ||
				tile->GetCollider()->Collision(RB))
			{
				GravityStop();
				break;
			}
		}		
	}
	// Hit Ground End
	
	if (jumping)
	{
		for (auto tile : OBJECT->GetWall()->GetWalls())
		{
			if (tile->GetType() == Wall::TOP)
			{
				Vector2 LT = Vector2(collider->L(), collider->T());
				Vector2 T = Vector2(lTranslation.x, collider->T());
				Vector2 RT = Vector2(collider->R(), collider->T());

				if (tile->GetCollider()->Collision(LT) ||
					tile->GetCollider()->Collision(T) ||
					tile->GetCollider()->Collision(RT))
					break;
			}
		}
	}
	// Jump End

	lTranslation += Vector2(0, +1) * jumpSpeed * Time::Delta();
	lTranslation += Vector2(0, -1) * gravity * Time::Delta();
	gravity += gravityPower * Time::Delta();
	//lTranslation += fallPower * Time::Delta();
}

void Player::Attack()
{
	Vector2 dir = isRight ? Vector2(+1, 0) : Vector2(-1, 0);
	
	if (KEY_DOWN('Z'))
	{
		if (weaponCount == 1)
			bullets->Fire(this->globalPosition, dir, 300.0f, PlayerBullet::NORMAL);
		else if (weaponCount == 2)
			bullets->Fire(this->lTranslation, dir, 300.0f, PlayerBullet::FIRE);
		else if (weaponCount == 3)
			bullets->Fire(this->lTranslation, dir, 300.0f, PlayerBullet::ICE);
		else if (weaponCount == 4)
			bullets->Fire(this->lTranslation, dir, 300.0f, PlayerBullet::THURNDER);
	}
}

void Player::GravityStop()
{
	gravity = 0;
	jumpSpeed = 0;
	jumpCount = 0;

	jumping = false;
}

void Player::AddAction()
{
	actions.emplace(State::IDLE, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::IDLE]->SetPart(0, 3);

	actions.emplace(State::IDLEUP, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::IDLEUP]->SetPart(5, 8);

	actions.emplace(State::RUN, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::RUN]->SetPart(10, 13);

	actions.emplace(State::RUNUP, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::RUNUP]->SetPart(15, 18);

	actions.emplace(State::JUMP, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::JUMP]->SetPart(20, 22, false);
	actions[State::JUMP]->SetEndEvent(bind(&Player::SetAction, this, JUMPING));

	actions.emplace(State::JUMPING, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::JUMPING]->SetPart(25, 28);

	actions.emplace(State::JUMPUP, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::JUMPUP]->SetPart(30, 32, false);
	actions[State::JUMPUP]->SetEndEvent(bind(&Player::SetAction, this, JUMPINGUP));

	actions.emplace(State::JUMPINGUP, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::JUMPINGUP]->SetPart(35, 38);

	actions.emplace(State::JUMPDOWN, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::JUMPDOWN]->SetPart(40, 42, false);
	actions[State::JUMPDOWN]->SetEndEvent(bind(&Player::SetAction, this, JUMPINGDOWN));

	actions.emplace(State::JUMPINGDOWN, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::JUMPINGDOWN]->SetPart(45, 48);

	actions.emplace(State::SIT, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::SIT]->SetPart(50, 52, false);
	actions[State::SIT]->SetEndEvent(bind(&Player::SetAction, this, SITTING));

	actions.emplace(State::SITTING, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::SITTING]->SetPart(52, 52);

	actions.emplace(State::SITWALK, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::SITWALK]->SetPart(55, 58);

	actions.emplace(State::DIE, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::DIE]->SetPart(60, 63, false);
	actions[State::DIE]->SetEndEvent(bind(&Player::SetAction, this, DIED));

	actions.emplace(State::DIED, new Animation(L"Player/Player_00.png", 10, 7, 65));
	actions[State::DIED]->SetPart(63, 63);
}

void Player::SetAction(int state)
{
	if (this->state == state)
		return;

	this->state = (State)state;

	curAction = actions[state];
	curAction->Play();
}
