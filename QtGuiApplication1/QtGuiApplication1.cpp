#include "QtGuiApplication1.h"
#include "ui_QtGuiApplication1.h"
#include "qpainter.h"
#include "qevent.h"
#include "qpoint.h"
#include "qmessagebox.h"
QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	ui.mainToolBar->hide();
	ui.menuBar->hide();
	resize((CHESS_COLUMES + 1)*RECT_WIDTH, (CHESS_ROWS + 1)*RECT_HEIGHT);
	m_isBlackTurn = true;//黑棋先手
	//如何没有按照命名规则，则需要写槽与信号的连接函数
	//connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_click()));
}
void QtGuiApplication1::paintEvent(QPaintEvent *e)
{
	DrawChessboard();//画棋盘
	DrawItems();//画棋子
	DrawItemWithMouse();//画鼠标
	update();
}
void QtGuiApplication1::DrawChessboard()
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::HighQualityAntialiasing, true);//给与提示
	painter.setBrush(QColor(215,172,138));//Qt::darkYellow
	painter.setPen(QPen(QColor(Qt::black), 2));

	for (int i = 0; i < CHESS_COLUMES; i++)
	{
		for (int j = 0; j < CHESS_ROWS; j++)
		{
			painter.drawRect((i + 0.5)*RECT_WIDTH, (j + 0.5)*RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT);
		}
	}
}
void QtGuiApplication1::DrawItems()
{
	QPainter painter(this);
	painter.setPen(QPen(QColor(Qt::transparent)));
	for (int i = 0; i < m_items.size(); i++)
	{
		Item item = m_items[i];
		if (item.isBlack)
		{
			painter.setBrush(Qt::black);
		}
		else
		{
			painter.setBrush(Qt::white);
		}
		DrawChessAtPoint(painter, item.pt);
	}
}
void QtGuiApplication1::DrawChessAtPoint(QPainter &painter, QPoint &pt)
{
	QPoint ptCenter((pt.x() + 0.5)*RECT_WIDTH, (pt.y() + 0.5)*RECT_HEIGHT);
	painter.drawEllipse(ptCenter, RECT_WIDTH / 2, RECT_HEIGHT / 2);
}
void QtGuiApplication1::DrawItemWithMouse()
{
	QPainter painter(this);
	painter.setPen(QPen(QColor(Qt::transparent)));
	if (m_isBlackTurn)
	{
		painter.setBrush(Qt::black);
	}
	else
	{
		painter.setPen(Qt::white);
	}
	painter.drawEllipse(mapFromGlobal(QCursor::pos()), RECT_WIDTH / 2, RECT_HEIGHT / 2);
}

void QtGuiApplication1::mousePressEvent(QMouseEvent *e)
{
	//求鼠标点击出的棋子的坐标
	QPoint pt;
	pt.setX((e->pos().x()) / RECT_WIDTH);
	pt.setY((e->pos().y()) / RECT_HEIGHT);

	//如果已经存在棋子
	for (int i = 0; i < m_items.size(); i++)
	{
		Item item = m_items[i];
		if (item.pt == pt)
		{
			//已经有棋子；
			return;
		}
	}
	//不存在棋子，就下一个
	Item item(pt, m_isBlackTurn);
	m_items.append(item);

	//统计8个方向是否满足5个了
	int nLeft = CountItem(item, QPoint(-1, 0));
	int nLeftUp = CountItem(item, QPoint(-1, -1));
	int nUp = CountItem(item, QPoint(0, -1));
	int nRightUp = CountItem(item, QPoint(1, -1));
	int nRight = CountItem(item, QPoint(1, 0));
	int nRightDown = CountItem(item, QPoint(1, 1));
	int nDown = CountItem(item, QPoint(0, 1));
	int nLeftDown = CountItem(item, QPoint(-1, 1));

	if ((nLeft + nRight) >= 4 || (nLeftUp + nRightDown) >= 4 || (nUp + nDown) >= 4 || (nRightUp + nLeftDown) >= 4)
	{
		QString str = m_isBlackTurn ? "Black" : "White";
		str += " Win!";
		QMessageBox::information(NULL, "GAME OVER", str, QMessageBox::Yes, QMessageBox::Yes);
		m_items.clear();
		return;
	}
	m_isBlackTurn = !m_isBlackTurn;
}
int QtGuiApplication1::CountItem(Item item, QPoint pt)
{
	int n = 0;
	item.pt += pt;
	while (m_items.contains(item))
	{
		n++;
		item.pt += pt;
	}
	return n;
}

/*
测试专用
void QtGuiApplication1::on_pushButton_click()
{
	QString a = ui.lineEdit->text();
	QString b = ui.lineEdit_2->text();
	double aa = a.toDouble();
	double bb = b.toDouble();
	double cc = aa + bb;
	QString c;
	c.setNum(cc);
	ui.lineEdit_3->setText(c);
}
*/