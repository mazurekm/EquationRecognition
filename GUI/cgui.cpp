#include "cgui.h"
#include "ui_cgui.h"
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QImage>

CGUI::CGUI(QWidget *parent) : QMainWindow(parent), ui(new Ui::CGUI)
{
    ui->setupUi(this);
    
	QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadImage()));
	QObject::connect(ui->performButton, SIGNAL(clicked()), this, SLOT(perform()));

	ui->imageView->setScene(&m_scene);
}

void CGUI::loadImage()
{
    QString pathToFile = QFileDialog::getOpenFileName(this,tr("Open Image"),"/home",
                                tr("Image Files (*.png *.jpg *.bmp)"));
    
	if(true == pathToFile.isEmpty())
	{
		m_ocr.reset();
		return;
	}

	if(nullptr == m_ocr)
	{
		m_ocr.reset(new COCR(pathToFile.toStdString()));
	}


	QImage image(pathToFile);
    m_scene.clear();
    m_scene.addPixmap(QPixmap::fromImage(image));
    ui->imageView->show();
}

void CGUI::perform()
{
	if(nullptr != m_ocr)
	{
		QString score = m_ocr->perform().c_str();
		ui->evulationScore->setText(score);
	}
}

CGUI::~CGUI()
{
    delete ui;
}
