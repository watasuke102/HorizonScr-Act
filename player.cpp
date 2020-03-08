#include "main.h"

void _player::Init()
{
	pos.set(480, 400);
	drawPos.set(480, 400);
	hitBox.size.set(60, 60);
	pic = TextureAsset(U"player");//Texture(Emoji(U"🍎"));
	debug = false;
	didSpaceDown = false;
	scr = 0;
	speed.y = 0;
	speed.x = 0;
	jumpCnt = 0;

	afterImage.clear();
	dashingTime = 0;
	dashing = false;
	dashSp = 0;
}

void _player::Update(_mapData* map)
{
	map->SetScr(scr);
	//debug
	static int upsp;
	if ((KeyAlt + KeyS).down()) debug = !debug;
	if(KeyUp.pressed())
		speed.y = (KeyShift.pressed())? 2:1;
	Jump();
	Dash();
	Move(map);
}
void _player::Draw()
{
	drawPos.y = pos.y;
	afterImage.update();
	pic.resized(hitBox.size).draw(drawPos);
}

void _player::DebugDraw()
{
	//当たり判定が行われている場所を描画
	RectF(pos, hitBox.size).draw(ColorF(0.3, 0.8, 0.4, 0.5));
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
void _player::Dash()
{
	//ダッシュ中なら更新する
	if(dashing)
	{
		speed.set(20*dashSp, 0);
		afterImage.add([ef_tex=pic, p = drawPos, ef_size = hitBox.size](double t) {
			Point ef_pos((int)p.x, (int)p.y);
			//Rect(ef_pos, ef_size)
			ef_tex.resized(ef_size).draw(ef_pos, AlphaF(0.5 - t/0.3));//ColorF(0.3, 0.8, 0.4, 0.5 - t/0.3));
			return t < 0.5;
		});
		dashingTime++;
		if(dashingTime > 18)
		{
			dashing = false;
			dashSp = 0;
			dashingTime = 0;
		}
	}
	//ダッシュしてなかったら
	else
	{
		if(KeyD.down()) dashSp = 1;
		if(KeyA.down())	dashSp = -1;
		if(dashSp!=0)
		{
			dashing = true;
			dashingTime = 0;
		}
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
	if(!dashing)
	{
		if (KeyLeft.pressed())  speed.x = -sp;
		if (KeyRight.pressed()) speed.x =  sp;
	}
	Print << U"pos:" << pos;
	Print << U"drawPos:" << drawPos;
	Print << U"sp_y({})"_fmt(speed.y);
	//横移動
	pos.x += speed.x;
	//縦移動
	pos.y -= speed.y;
	speed.y--;
	_mapHitState hit=CheckMapHit(map,pos,hitBox,speed);
	if (hit.bottom)
		jumpCnt = 0;
	if (hit.top || hit.bottom)
		speed.y = 0;
	if (hit.left || hit.right)
	{
		speed.x = 0;
		dashingTime = 20;//次のupdateでダッシュ終了
	}

	map->SetPlayerSpeed(speed);
	hit.pos.x += scr;
	pos = hit.pos;
	scr -= speed.x;
	scr = Clamp(scr, WINDOW_X-(map->Width() * MAP_CHIPSIZE) , 0);
	speed.x = 0;
	if (pos.y >= WINDOW_Y) Init();
}
