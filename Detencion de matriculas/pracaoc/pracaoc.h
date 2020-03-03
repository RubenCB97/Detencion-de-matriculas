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


#ifndef PRACAOC_H
#define PRACAOC_H

#include "ui_mainForm.h"
#include <QtCore>
#include <QPainter>
#include <QtWidgets/QFileDialog>
#include <QMouseEvent>
#include "imageprocess.h"

using namespace Ui;


class pracAOC:public QWidget
{
    Q_OBJECT

public:
    pracAOC();
    ~pracAOC();
		
		

private:

		QMainForm * mainWin;
		QImage * qimgOrig, * qimgDest;
		QImage * qimgDigit[7];
		uchar * imgO, * imgD, * imgM;
		uchar * imgdigit[7];
		int Vhor[320];
		int Hmin;
		int Hmax;

		char digit[31]; //caracteres que intervienen en las matriculas
		uchar * Idigit[31]; //vector de punteros a cada una de las imagenes de cada digito
		int v;
		QVector<QRgb> ctable;



protected:


		void closeEvent(QCloseEvent *event);
		void pintarVH();
		void init_digit();
		void cargar_digit(uchar *d,char name);

public slots:

		void paintEvent(QPaintEvent *);
        void procesoCompleto();
		void cargar();
		void copiarOrigen();
		void copiarDestino();
		void borrar();
		void negar();
		void umbralizar();
        void eliminarRuido();
		void detectarv();
		void detectarh();
		void recortar();
		void matching();
};




#endif
