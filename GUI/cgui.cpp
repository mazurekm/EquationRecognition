#include "cgui.h"
#include "ui_cgui.h"
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QDir>
#include <vector>

CGUI::CGUI(QWidget *parent) : 
	QMainWindow(parent), 
	ui(new Ui::CGUI),
	m_solverFactory( new CSolverFactory() )
{
    ui->setupUi(this);
    
	QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadImage()));
	QObject::connect(ui->performButton, SIGNAL(clicked()), this, SLOT(perform()));

	ui->imageView->setScene(&m_scene);
	ui->procImgView->setScene(&m_procScene);
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
  	ui->imageView->fitInView(m_scene.itemsBoundingRect() ,Qt::KeepAspectRatio);
    ui->imageView->show();
}

QImage CGUI::mat2QImage(const cv::Mat &src)
{
     cv::Mat temp; 
     cv::cvtColor(src, temp,CV_BGR2RGB); 
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, 
     				QImage::Format_RGB888);
     dest.bits();
     return dest;
}

void CGUI::perform()
{
	if(nullptr != m_ocr)
	{
		auto scores = m_ocr->perform();
		std::string out;

		for(auto iter = scores.begin(); iter!=scores.end(); ++iter)
		{
			try
			{
				std::unique_ptr<IAbstractSolver> solver ( m_solverFactory->create(iter->first) );
				out += solver->solveAndToStr() + "\n\n";
			}
			catch(std::runtime_error &ex)
			{
				std::stringstream sst;
				sst << ex.what();
				std::string err = sst.str();
				err.erase(err.end()-1);
				out += sst.str() + "\n\n";
			}
		}

		QImage procImg = mat2QImage( m_ocr->getProcessedImg() );
		m_procScene.clear();
		m_procScene.addPixmap( QPixmap::fromImage(procImg) );
		ui->procImgView->fitInView(m_scene.itemsBoundingRect() ,Qt::KeepAspectRatio);
		ui->procImgView->show();
		ui->evulationScore->setText(QString(out.c_str()));
	}
}

CGUI::~CGUI()
{
    delete ui;
}
