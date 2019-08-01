#include "Item.h"
Item::Item(void)
{

}
Item::Item(QPoint p, bool black)
{
	pt = p;
	isBlack = black;
}
Item::~Item(void)
{

}