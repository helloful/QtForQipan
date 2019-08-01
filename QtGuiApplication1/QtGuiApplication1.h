#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"
#include "Item.h"
#include "qmap.h"

#define CHESS_ROWS 15
#define CHESS_COLUMES 15
#define RECT_WIDTH 50
#define RECT_HEIGHT 50

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtGuiApplication1Class ui;

	QVector<Item>m_items;
	bool m_isBlackTurn;//是否轮到黑棋
protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
private:
	void DrawChessboard();
	void DrawItems();
	void DrawItemWithMouse();

	void DrawChessAtPoint(QPainter& painter, QPoint &pt);
	int CountItem(Item item, QPoint pt);
//private slots:
//	void on_pushButton_click();//按照这种定义方式，则不需要写connect函数
};
