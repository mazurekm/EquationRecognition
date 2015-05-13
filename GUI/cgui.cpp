#include "cgui.h"
#include "ui_cgui.h"
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QDir>
#include <vector>

CGUI::CGUI(QWidget *parent) : QMainWindow(parent), ui(new Ui::CGUI)
{
    ui->setupUi(this);
    
	QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadImage()));
	QObject::connect(ui->performButton, SIGNAL(clicked()), this, SLOT(perform()));

	ui->imageView->setScene(&m_scene);
	ui->evulationScore->setReadOnly(true);
}

void CGUI::loadImage()
{
	QString currentDir = QDir::currentPath(); 
    QString pathToFile = QFileDialog::getOpenFileName(this,tr("Open Image"),currentDir,
                                tr("Image Files (*.png *.jpg *.bmp)"));
    
	if(true == pathToFile.isEmpty())
	{
		m_ocr.reset();
		return;
	}

	m_ocr.reset(new COCR(pathToFile.toStdString()));
	m_ocr->init(currentDir.toStdString(), "eng");

	
	ui->evulationScore->setText("");

	QImage image(pathToFile);
    m_scene.clear();
    m_scene.addPixmap(QPixmap::fromImage(image));
    ui->imageView->show();
}

void CGUI::perform()
{
	if(nullptr != m_ocr)
	{
		auto scores = m_ocr->perform();
		std::string out;

		for(auto iter = scores.begin(); iter!=scores.end(); ++iter)
		{
			out += iter->first + "\n";
		}

		ui->evulationScore->setText(QString(out.c_str()));
	}
}

CGUI::~CGUI()
{
    delete ui;
}
