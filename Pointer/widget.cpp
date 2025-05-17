#include "widget.h"
#include "./ui_widget.h"
#include <QFile>
#include <QGraphicsScene>
#include <QDebug>
#include "hexagonitems.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{


    ui->setupUi(this);
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->viewport()->setMouseTracking(true);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    qDebug() << "Created";
    QFile file(":/grids/grid1.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QStringList lines;
        QTextStream in(&file);
        while (!in.atEnd()) {
            lines << in.readLine();
        }
        file.close();

        for (int row = 0; row < lines.size()-1; row++) {
            const QString &line = lines[row];
            for (int col = 0; col < line.length()-1; ) {
                if (line[col] == '/') {
                    QChar ch = line[col+1];
                    if (ch == '\\' || ch == '_' || ch == '|') {
                        col += 2;
                        continue;
                    }

                    qreal x = (col / 6.0) * hexWidth * 1.5;
                    qreal y = row * hexHeight * 0.5;
                    createHexagon(x, y, ch, row, col / 6);
                    col += 5;
                }
                else {
                    col++;
                }
            }
        }
    }
}

void Widget::createHexagon(qreal x, qreal y, QChar ch, int row, int col)
{
    QPolygonF hexagon;
    hexagon << QPointF(hexWidth*0.25, 0)
            << QPointF(hexWidth*0.75, 0)
            << QPointF(hexWidth, hexHeight*0.5)
            << QPointF(hexWidth*0.75, hexHeight)
            << QPointF(hexWidth*0.25, hexHeight)
            << QPointF(0, hexHeight*0.5);

    HexagonItems *hexItem = new HexagonItems(hexagon, row, col);
    hexItem->setPos(x, y);

    if (ch == '1') {
        hexItem->setProperties(1, false, '1');
        hexItem->setBrush(QColor(100, 255, 100));
    } else if (ch == '2') {
        hexItem->setProperties(2, false, '2');
        hexItem->setBrush(QColor(255, 255, 100));
    } else if (ch == '#') {
        hexItem->setProperties(0, true, '#');
        hexItem->setBrush(QColor(32, 107, 186));
    } else if (ch == '~') {
        hexItem->setProperties(0, true, '~');
        hexItem->setBrush(QColor(189, 40, 117));
    } else {
        hexItem->setBrush(Qt::white);
    }

    hexMap[{row, col}] = hexItem;

    hexItem->setPen(QPen(Qt::black, 1));
    scene->addItem(hexItem);
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->graphicsView->viewport()) {
        if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF scenePos = ui->graphicsView->mapToScene(mouseEvent->pos());

            // Reset previous hover if needed
            if (lastHoveredHex && lastHoveredHex != getHexagonAtPosition(scenePos)) {
                lastHoveredHex->resetColor();  // You define this!
                lastHoveredHex = nullptr;
            }

            HexagonItems* hex = getHexagonAtPosition(scenePos);
            if (hex && hex != lastHoveredHex) {
                hex->setBrush(Qt::cyan);  // or another hover color
                lastHoveredHex = hex;
            }

            return true;
        }

        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF scenePos = ui->graphicsView->mapToScene(mouseEvent->pos());
            HexagonItems* hex = getHexagonAtPosition(scenePos);
            if (hex) {
                qDebug() << "Clicked hex at grid:" << QPair(hex->row, hex->col);
            } else {
                qDebug() << "No hexagon at that position.";
            }
            return true;
        }
    }

    return QWidget::eventFilter(obj, event);
}



HexagonItems* Widget::getHexagonAtPosition(const QPointF &pos)
{
    for (auto hex : hexMap) {
        if (hex->contains(hex->mapFromScene(pos))) {
            return hex;
        }

    }
    return nullptr;
}

Widget::~Widget()
{
    delete ui;
}
