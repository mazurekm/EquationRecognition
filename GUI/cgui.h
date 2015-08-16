#ifndef CGUI_H
#define CGUI_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include <OCR/OCR.h>
#include <memory>
#include <OCR/SolverFactory.h>

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
	QImage mat2QImage(const cv::Mat &src);
    QGraphicsScene m_scene;
   	QGraphicsScene m_procScene;
    Ui::CGUI *ui;
	std::shared_ptr<COCR> m_ocr;
	std::unique_ptr<CSolverFactory> m_solverFactory;
};

#endif // CGUI_H
