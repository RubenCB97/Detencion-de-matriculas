/***************************************************************************
 *   Copyright (C) 2019 by Paco Andrés and Pilar Bachiller                 *
 *   pacoan@unex.es pilarb@unex.es                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "pracaoc.h"
#include <QString>

pracAOC::pracAOC(): QWidget()
{
    mainWin=new QMainForm();
	mainWin->setupUi(this);

	ctable.resize(256);
	for(int i=0; i < 256; i++)
		ctable[i] = qRgb(i,i,i);

	imgO=new uchar[320*100]; // matriz de imagen origen
	imgM=new uchar[320*100]; // se usa solo para mostrar datos
	imgD=new uchar[320*100]; // matriz de imagen destino de los procesos

	for (int i=0; i<7;i++)
		imgdigit[i]=new uchar[32*55]; //grupo de siete matrices para matching final

	qimgOrig = new QImage(imgO,320, 100, QImage::Format_Indexed8);
	qimgOrig->setColorTable(ctable);

	qimgDest = new QImage(imgM,320, 100, QImage::Format_Indexed8);
	qimgDest->setColorTable(ctable);

    for (int i=0; i<7; i++)
    {
        qimgDigit[i] = new QImage(imgdigit[i],32, 55, QImage::Format_Indexed8);
        qimgDigit[i]->setColorTable(ctable);
	}


    for(int i=0; i<320;i++)
        Vhor[i]=0; //guarda la integral proyectiva de cada columna

    Hmin=0;  //almacena la fila inferior y superior donde se encuentran los caracteres
    Hmax=0;

    for(int j=0; j<7; j++)
    {
    	for(int i=0; i<32*55;i++)
    		imgdigit[j][i]=0;
    }

	for(int i=0; i<320*100;i++)
	{
		imgO[i]=0;
		imgM[i]=0;
		imgD[i]=0;
	}
    init_digit();
    v=0;

	connect ( mainWin->pushButtonCargar, SIGNAL (clicked()), this, SLOT( cargar() ) );
	connect ( mainWin->pushButtonCopiarO, SIGNAL (clicked()), this, SLOT( copiarOrigen() ) );
	connect ( mainWin->pushButtonCopiarD, SIGNAL (clicked()), this, SLOT( copiarDestino() ) );
	connect ( mainWin->pushButtonBorrar, SIGNAL (clicked()), this, SLOT( borrar() ) );	
	connect ( mainWin->pushButtonNegar, SIGNAL (clicked()), this, SLOT( negar() ) );
	connect ( mainWin->pushButtonUmbralizar, SIGNAL (clicked()), this, SLOT( umbralizar() ) );
    connect ( mainWin->pushButtonEliminarRuido, SIGNAL (clicked()), this, SLOT( eliminarRuido() ) );
	connect ( mainWin->pushButtonDetectarV, SIGNAL (clicked()), this, SLOT( detectarv() ) );
	connect ( mainWin->pushButtonDetectarH, SIGNAL (clicked()), this, SLOT( detectarh() ) );
	connect ( mainWin->pushButtonRecortar, SIGNAL (clicked()), this, SLOT( recortar() ) );
	connect ( mainWin->pushButtonMatching, SIGNAL (clicked()), this, SLOT( matching() ) );
    connect ( mainWin->pushButtonTodo, SIGNAL (clicked()), this, SLOT( procesoCompleto() ) );
	connect ( mainWin->pushButtonSalir, SIGNAL (clicked()), this, SLOT( close() ) );

}


pracAOC::~pracAOC()
{
}


void pracAOC::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	painter.drawImage(QPoint(mainWin->frameOrig->x(), mainWin->frameOrig->y()), *qimgOrig);
	painter.drawImage(QPoint(mainWin->frameDest->x(), mainWin->frameDest->y()), *qimgDest);
	painter.drawImage(QPoint(mainWin->frameD0->x(), mainWin->frameD0->y()), *qimgDigit[0]);
	painter.drawImage(QPoint(mainWin->frameD1->x(), mainWin->frameD1->y()), *qimgDigit[1]);
	painter.drawImage(QPoint(mainWin->frameD2->x(), mainWin->frameD2->y()), *qimgDigit[2]);
	painter.drawImage(QPoint(mainWin->frameD3->x(), mainWin->frameD3->y()), *qimgDigit[3]);
	painter.drawImage(QPoint(mainWin->frameD4->x(), mainWin->frameD4->y()), *qimgDigit[4]);
	painter.drawImage(QPoint(mainWin->frameD5->x(), mainWin->frameD5->y()), *qimgDigit[5]);
	painter.drawImage(QPoint(mainWin->frameD6->x(), mainWin->frameD6->y()), *qimgDigit[6]);

	painter.end();
}
void pracAOC::init_digit(){
	digit[0]='0'; digit[1]='1'; digit[2]='2'; digit[3]='3'; digit[4]='4';
	digit[5]='5'; digit[6]='6'; digit[7]='7'; digit[8]='8'; digit[9]='9';
	digit[10]='B'; digit[11]='C'; digit[12]='D'; digit[13]='F'; digit[14]='G';
	digit[15]='H'; digit[16]='J'; digit[17]='K'; digit[18]='L'; digit[19]='M';
	digit[20]='N'; digit[21]='P'; digit[22]='Q'; digit[23]='R'; digit[24]='S';
	digit[25]='T'; digit[26]='V'; digit[27]='W'; digit[28]='X'; digit[29]='Y';
	digit[30]='Z';

    for (int i=0;i<31;i++)
    {
    	Idigit[i]= new uchar [32*55];
    	cargar_digit(Idigit[i],digit[i]);
    }

}
void pracAOC::cargar_digit(uchar *d,char name)
{
	QImage qimgRead(32,55,QImage::Format_Indexed8);
	QImage qimgCRead(32,55,QImage::Format_Indexed8);
	QString fn =QString("letras/%1.jpg").arg(name);
    fn="../pracaoc/"+fn;
	if(qimgRead.load(fn))
	{
		qDebug()<<"cargando "<<fn;
		qimgCRead=qimgRead.convertToFormat(QImage::Format_Indexed8, ctable);

		for(int y=0; y<55 && y<qimgRead.height();y++)
			for(int x=0; x<32 && x<qimgRead.width(); x++){
				d[y*32+x]=(qimgCRead.bits())[(y*qimgCRead.width()+x)];
				d[y*32+x]=255-d[y*32+x];

			}
	}
    else qDebug()<<"error al cargar"<<fn;
}

void pracAOC::pintarVH(){
	imageprocess::copiar(imgD,imgM,320*100);
	if (Hmin!=0 && Hmax!=0)
	{
		for (int x=0; x<320; x++)
			{
                if(Hmin>=0 && Hmin<100)
                    qimgDest->setPixel(x,Hmin,128);
                if(Hmax>=0 && Hmax<100)
                    qimgDest->setPixel(x,Hmax,128);
			}
	}
	if (Vhor[0]!=0)
	{
		int i=0;
		while (Vhor[i]!=0)
			{
				for (int y=0;y<99;y++){
                    if(Vhor[i]-16>=0)
                        qimgDest->setPixel(Vhor[i]-16,y,128);
                    if(Vhor[i]+16<320)
					qimgDest->setPixel(Vhor[i]+16,y,128);
				}
			i++;
			}
	}
		update();

}

void pracAOC::procesoCompleto()
{
    negar();
	umbralizar();
    eliminarRuido();
    detectarv();
    detectarh();
    recortar();
    matching();

	update();
}
void pracAOC::cargar()
{
	borrar();
	QImage qimgRead1(320,100,QImage::Format_Indexed8);
	QImage qimgCRead1(320,100,QImage::Format_Indexed8);
    QString fn = QFileDialog::getOpenFileName(this,"Elija la imagen a cargar",".", "Images (*.png *.xpm *.jpg)");
	if(qimgRead1.load(fn))
	{

		qimgCRead1=qimgRead1.convertToFormat(QImage::Format_Indexed8, ctable);
		qimgCRead1=qimgCRead1.copy(0,0,320,100);

		for(int y=0; y<100;y++)
			for(int x=0; x<320; x++){
				imgO[y*320+x]=(qimgCRead1.bits())[(y*qimgCRead1.width()+x)];
			}
		update();
	}
}



void pracAOC::copiarOrigen()
{
	imageprocess::copiar(imgO,imgD,320*100);
	imageprocess::copiar(imgO,imgM,320*100);

	update();
}

void pracAOC::copiarDestino()
{
	imageprocess::copiar(imgD,imgM,320*100);
	imageprocess::copiar(imgD,imgO,320*100);
	update();
}

void pracAOC::borrar()
{
	imageprocess::borrar(imgM,320,100);
	for (int i=0;i<7;i++) imageprocess::borrar(imgdigit[i],32,55);
	Hmin=0;
	Hmax=0;
	for (int i=0;i<320;i++) Vhor[i]=0;
	update();
}


void pracAOC::negar()
{
    imageprocess::invertir(imgO,imgD,320,100);
	imageprocess::copiar(imgD,imgM,320*100);
	update();
}


void pracAOC::umbralizar()
{
	imageprocess::umbralizar(imgD,320,100);
	imageprocess::copiar(imgD,imgM,320*100);
	update();
}

void pracAOC::eliminarRuido()
{
    imageprocess::eliminarRuido_F1(imgD, imgM, 320,100);
    imageprocess::copiar(imgM,imgD,320*100);
    imageprocess::eliminarRuido_F2(imgD, imgM, 320,100);
    imageprocess::copiar(imgM,imgD,320*100);
    update();
}


void pracAOC::detectarv()
{
	Hmin=0;
	Hmax=0;
	int U=mainWin->spinUdetv->value();
    Hmin = imageprocess::detectarV_min(imgD, U);
    Hmax = imageprocess::detectarV_max(imgD, U);
	pintarVH();


}

void pracAOC::detectarh()
{
    uchar V[320];

    for (int i=0;i<320;i++) Vhor[i]=0;
    int U=mainWin->spinUdeth->value();
    imageprocess::detectarH_F1(imgD, V, U);
    imageprocess::detectarH_F2(V, Vhor);
    pintarVH();
}

void pracAOC::recortar(){
	int W=mainWin->spinAncho->value();
	int H=mainWin->spinAlto->value();
    int iniF=Hmin;
    if(iniF+H>=100) iniF = 99-H;
	for (int i=0; i<7; i++){
        int iniC = Vhor[i]-16;
        if(iniC<0)
            iniC = 0;
        if(iniC+W>=320)
            iniC = 319-W;
        imageprocess::recortar(imgD,imgdigit[i],iniC,iniF,W,H);
	}
	update();
}

void pracAOC::matching(){
	QString matricula="";
	int val=0;
	for (int i=0; i<4; i++){
		val=imageprocess::matching(imgdigit[i],Idigit,0,10);
		matricula=matricula+QString(digit[val]);
		}

	matricula=matricula+" ";
	for (int i=4; i<7; i++){
		val=imageprocess::matching(imgdigit[i],Idigit,10,21);
		matricula=matricula+QString(digit[val]);
		}
	mainWin->labelMat->setText(matricula);
	update();
}


void pracAOC::closeEvent(QCloseEvent *event)
{
	event->accept();
	delete mainWin;

}
