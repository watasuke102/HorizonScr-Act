#include"main.h"

void _enemy::Init()
{
	pos.set(2400, 400);
	hitBox.size.set(60, 60);
	speed.set(5,0);
}
void _enemy::Update(_mapData* map)
{
	Print << U"--ENEMY--";
	Print <<U"pos"<< pos;
	//横移動
	pos.x += speed.x;
	//縦移動
	pos.y -= speed.y;
	speed.y--;

	_mapHitState hit=CheckMapHit(map,pos,hitBox,speed);
	Print <<U"right({}),left({})"_fmt(hit.right,hit.left);
	if (hit.top || hit.bottom)
		speed.y = 0;

	hit.pos.x += map->GetScr();
	pos = hit.pos;
	speed.set(-5, hit.right||hit.left ? 5 : 0);
	Print << U"Speed" << speed;
}
void _enemy::Draw()
{
	hitBox.setPos(pos);
	hitBox.draw(ColorF(0.8, 0.3, 0.4, 0.5));
}