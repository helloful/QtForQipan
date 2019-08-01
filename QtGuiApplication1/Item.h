#include<qpoint.h>
class Item
{
public:
	QPoint pt;//表示棋的坐标
	bool isBlack;//表示棋的颜色
	
	Item(void);
	~Item(void);
	Item(QPoint p, bool black);
	bool operator==(const Item &pt1) const
	{
		return (pt == pt1.pt&& isBlack == pt1.isBlack);
	}
};