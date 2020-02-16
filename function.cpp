#include"main.h"

//3桁ごとにカンマで区切る
String SeparateString(String num)
{
	int length = num.length();
	String result;
	for (auto i:step(length))
	{
		result += num[(length-1)-i];
		if ((i+1)%3 == 0 && (i+1) != length && (i+1) != 0)
			result += U',';
	}
	return result.reverse();
}

//↓引数どうにかしろ
//_mapDataと座標とRect(hitBox)とVec2(スピード)を引数に入れるだけで
//mapHitSate型で接触乗法を返してくれるべんりかんすう（白目）
_mapHitState CheckMapHit(_mapData *mapData, Vec2 pos, Rect hitBox, Vec2 speed)
{
	int x, y;
	//プレイヤーの衝突位置と次移動すべき位置
	_mapHitState hit;
	hit.top = false;
	hit.bottom = false;
	hit.left = false;
	hit.right = false;
	hit.pos = pos;
	hit.pos.x -= mapData->GetScr();
	//横方向の当たり判定
	{
		//左に移動中だったら左の当たり判定
		if (speed.x < 0)
		{
			x = hit.pos.x / MAP_CHIPSIZE;
			y = (hit.pos.y + (hitBox.size.y / 2)) / MAP_CHIPSIZE;
			if (mapData->Get(y,x) != 0 && hit.pos != Vec2(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE))
			{
				hit.right = true;
				hit.pos.x = (x * MAP_CHIPSIZE) + MAP_CHIPSIZE;
				speed.x = hit.pos.x-pos.x;
			}
		}
		//右に移動中だったら右の当たり判定
		if (speed.x > 0)
		{
			x = (hit.pos.x + hitBox.size.x) / MAP_CHIPSIZE;
			y = (hit.pos.y + (hitBox.size.y / 5)) / MAP_CHIPSIZE;
			if (mapData->Get(y,x) != 0 && hit.pos != Vec2(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE))
			{
				hit.left = true;
				hit.pos.x = (x * MAP_CHIPSIZE) - hitBox.size.x;
				speed.x = hit.pos.x-pos.x;
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
				//真上
				x = (hit.pos.x + (hitBox.size.x / 2)) / MAP_CHIPSIZE;
				y = hit.pos.y / MAP_CHIPSIZE;
				if (mapData->Get(y,x) != 0)
				{
					hit.top = true;
					hit.pos.y = (y * MAP_CHIPSIZE) + MAP_CHIPSIZE;
				}
			}
			else
			{
				//左上
				x = (hit.pos.x + hitBox.size.x) / MAP_CHIPSIZE;
				y = hit.pos.y / MAP_CHIPSIZE;
				if (mapData->Get(y,x) != 0)
				{
					hit.top = true;
					hit.pos.y = (y * MAP_CHIPSIZE) + MAP_CHIPSIZE;
				}
				//右上
				x = hit.pos.x / MAP_CHIPSIZE;
				y = hit.pos.y / MAP_CHIPSIZE;
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
				x = (hit.pos.x + (hitBox.size.x / 2)) / MAP_CHIPSIZE;
				y = (hit.pos.y + hitBox.size.y) / MAP_CHIPSIZE;
				if (mapData->Get(y,x) != 0)
				{
					hit.bottom = true;
					hit.pos.y = (y * MAP_CHIPSIZE) - hitBox.size.y;
				}
			}
			else
			{
				//左下
				x = (hit.pos.x + hitBox.size.x) / MAP_CHIPSIZE;
				y = (hit.pos.y + hitBox.size.y) / MAP_CHIPSIZE;
				if (mapData->Get(y,x) != 0)
				{
					hit.bottom = true;
					hit.pos.y = (y * MAP_CHIPSIZE) - hitBox.size.y;
				}
				//右下
				x = hit.pos.x / MAP_CHIPSIZE;
				y = (hit.pos.y + hitBox.size.y) / MAP_CHIPSIZE;
				if (mapData->Get(y,x) != 0)
				{
					hit.bottom = true;
					hit.pos.y = (y * MAP_CHIPSIZE) - hitBox.size.y;
				}
			}
		}
	}
	return hit;
}
