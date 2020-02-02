#include "main.h"

void _player::Init()
{
	debugtxr = RenderTexture(WINDOW_SIZE,ColorF(0.1));
	debug = false;
	pos.set(480, 400);
	didSpaceDown = false;
	size.set(60, 60);
	scr = 0;
	speed.y = 0;
	speed.x = 0;
	jumpCnt = 0;
}

void _player::Update(_mapData* map)
{
	//debug
	static int upsp;
	if (KeyD.down())debug = !debug;
	if(KeyUp.pressed())
		speed.y = (KeyShift.pressed())? 2:1;
	Jump();
	Dash();
	Move(map);
}
void _player::Draw()
{
	debugtxr.draw(AlphaF(0.5));
	debugtxr.clear(ColorF(0.1,0.5));
	Rect(pos.x, pos.y, size).draw(ColorF(0.3, 0.8, 0.4, 0.5));
}

void _player::Dash()
{
	if(KeyD.down())
		dashing = true;
	if(KeyA.down())
		dashing = false;
}
void _player::Jump()
{
	Print << U"{}(JumpCnt)"_fmt(jumpCnt);
	if (KeySpace.pressed())
	{
		//すでに二弾ジャンプしていない、かつ押された瞬間なら
		if (!didSpaceDown)
		{
			if(jumpCnt < 2)
			{
				speed.y = 0;
				spacePressedFrame = 0;
				didSpaceDown = true;
			}
		}else //押され続けていたら
		{
			spacePressedFrame++;
			if (spacePressedFrame < 13)
				speed.y = JUMP_POWER;
		}
	}
	else
	{
		if (didSpaceDown)
			jumpCnt++;
		spacePressedFrame = 0;
		didSpaceDown = false;
	}
}
void _player::Move(_mapData* map)
{
	int sp;
	//シフトキーで速度アップ
	if (KeyShift.pressed())
		sp = PLAYER_HIGHSPEED;
	else sp = PLAYER_SPEED;
	//左右移動
	if (KeyLeft.pressed())  speed.x = -sp;
	if (KeyRight.pressed()) speed.x =  sp;
	Print << U"pos:" << pos;
	Print << U"sp_y({})"_fmt(speed.y);
	//横移動
	pos.x += speed.x;
	//縦移動
	pos.y -= speed.y;
	speed.y--;
	CheckMapHit(map);
	speed.x = 0;
	if (pos.y >= WINDOW_Y) Init();
	pos.x = Clamp(pos.x, 0.0, (double)WINDOW_X - size.x);
}
//左　Hotpink
//右　Aquamarine
//上　Purple
//下　Yellow
void _player::CheckMapHit(_mapData* mapData)
{
	int x, y;
	//プレイヤーの衝突位置と次移動すべき位置
	struct _hit
	{
		bool top, bottom, left, right;
		Vec2 pos;
	}hit;
	hit.top = false;
	hit.bottom = false;
	hit.left = false;
	hit.right = false;
	hit.pos = pos;
	hit.pos.x -= scr;
	//横方向の当たり判定
	{
		//左に移動中だったら左の当たり判定
		if (speed.x < 0)
		{
			x = hit.pos.x / MAP_CHIPSIZE;
			y = (hit.pos.y + (size.y / 2)) / MAP_CHIPSIZE;
			{
				ScopedRenderTarget2D a(debugtxr);
				if (debug)
					Rect(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
					.draw(Palette::Hotpink);
			}
			if (mapData->Get(y,x) != 0 && hit.pos != Vec2(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE))
			{
				hit.right = true;
				hit.pos.x = (x * MAP_CHIPSIZE) + MAP_CHIPSIZE;
			}
		}
		//右に移動中だったら右の当たり判定
		if (speed.x > 0)
		{
			x = (hit.pos.x + size.x) / MAP_CHIPSIZE;
			y = (hit.pos.y + (size.y / 5)) / MAP_CHIPSIZE;
			{
				ScopedRenderTarget2D a(debugtxr);
				if (debug)
					Rect(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
					.draw(Palette::Aquamarine);
			}
			if (mapData->Get(y,x) != 0 && hit.pos != Vec2(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE))
			{
				hit.left = true;
				hit.pos.x = (x * MAP_CHIPSIZE) - size.x;
			}
		}
	}
	//縦方向の当たり判定
	{
		//上：上昇中だったら上の当たり判定
		if (speed.y > 0)
		{
			//マップチップの境目にいないなら
			if ((int)hit.pos.x % MAP_CHIPSIZE == 0)
			{
				//真下
				x = (hit.pos.x + (size.x / 2)) / MAP_CHIPSIZE;
				y = hit.pos.y / MAP_CHIPSIZE;
				{
					ScopedRenderTarget2D a(debugtxr);
					if (debug)
						Rect(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
						.draw(Palette::Purple);
				}
				if (mapData->Get(y,x) != 0)
				{
					hit.top = true;
					hit.pos.y = (y * MAP_CHIPSIZE) - size.y;
				}
			}
			else
			{
				//左上
				x = (hit.pos.x + size.x) / MAP_CHIPSIZE;
				y = hit.pos.y / MAP_CHIPSIZE;
				{
					ScopedRenderTarget2D a(debugtxr);
					if (debug)
						Rect(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
						.draw(Palette::Purple);
				}
				if (mapData->Get(y,x) != 0)
				{
					hit.top = true;
					hit.pos.y = (y * MAP_CHIPSIZE) + MAP_CHIPSIZE;
				}
				//右上
				x = hit.pos.x / MAP_CHIPSIZE;
				y = hit.pos.y / MAP_CHIPSIZE;
				{
					ScopedRenderTarget2D a(debugtxr);
					if (debug)
						Rect(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
						.draw(Palette::Purple);
				}
				if (mapData->Get(y,x) != 0)
				{
					hit.top = true;
					hit.pos.y = (y * MAP_CHIPSIZE) + MAP_CHIPSIZE;
				}
			}
		}
		//下：落下中だったら下の当たり判定
		if (speed.y < 0)
		{
			//マップチップの境目にいないなら
			if ((int)hit.pos.x % MAP_CHIPSIZE == 0)
			{
				//真下
				x = (hit.pos.x + (size.x / 2)) / MAP_CHIPSIZE;
				y = (hit.pos.y + size.y) / MAP_CHIPSIZE;
				{
					ScopedRenderTarget2D a(debugtxr);
					if (debug)
						Rect(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
						.draw(Palette::Yellow);
				}
				if (mapData->Get(y,x) != 0)
				{
					hit.bottom = true;
					hit.pos.y = (y * MAP_CHIPSIZE) - size.y;
				}
			}
			else
			{
				//左下
				x = (hit.pos.x + size.x) / MAP_CHIPSIZE;
				y = (hit.pos.y + size.y) / MAP_CHIPSIZE;
				{
					ScopedRenderTarget2D a(debugtxr);
					if (debug)
						Rect(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
						.draw(Palette::Yellow);
				}
				if (mapData->Get(y,x) != 0)
				{
					hit.bottom = true;
					hit.pos.y = (y * MAP_CHIPSIZE) - size.y;
				}
				//右下
				x = hit.pos.x / MAP_CHIPSIZE;
				y = (hit.pos.y + size.y) / MAP_CHIPSIZE;
				{
					ScopedRenderTarget2D a(debugtxr);
					if (debug)
						Rect(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
						.draw(Palette::Yellow);
				}
				if (mapData->Get(y,x) != 0)
				{
					hit.bottom = true;
					hit.pos.y = (y * MAP_CHIPSIZE) - size.y;
				}
			}
		}
	}

	//当たり判定

	if (hit.top || hit.bottom)
		speed.y = 0;
	if (hit.left || hit.right)
		speed.x = 0;
	if (hit.bottom)
		jumpCnt = 0;
	hit.pos.x += scr;
	pos = hit.pos;
	scr -= speed.x;
	if (scr > 0) scr = 0;
}
