#ifndef CGUI_H
#define CGUI_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <OCR/OCR.h>
#include <memory>

namespace Ui {
class CGUI;
}

class CGUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CGUI(QWidget *parent = 0);
    ~CGUI();
    
public slots:
    void loadImage();
	void perform();

private:
    QGraphicsScene m_scene;
    Ui::CGUI *ui;
	std::shared_ptr<COCR> m_ocr;
};

#endif // CGUI_H
