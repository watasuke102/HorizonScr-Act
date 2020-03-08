#include"main.h"

void _enemy::Init()
{
	pos.set(400, 400);
	pos.set(400, 400);
	hitBox.size.set(60, 60);
	speed.set(5,0);
}
void _enemy::Update(_mapData* map)
{
	//横移動
	pos.x += speed.x;
	//縦移動
	pos.y -= speed.y;
	speed.y--;

	_mapHitState hit=CheckMapHit(map,pos,hitBox,speed);
	if (hit.top || hit.bottom)
		speed.y = 0;
	if(hit.left || hit.right)
		speed.y = 20;
	if(pos.y>1080)
		speed.y = 50;

	hit.pos.x += map->GetScr();
	if(map->GetScr() != 0)
		hit.pos.x -= map->GetPlayerSpeed().x;
	pos = hit.pos;

	//speed.set(-5, hit.right||hit.left ? 5 : 0);
}
void _enemy::Draw()
{
	hitBox.setPos(pos);
	hitBox.draw(ColorF(0.8, 0.3, 0.4, 0.5));
}