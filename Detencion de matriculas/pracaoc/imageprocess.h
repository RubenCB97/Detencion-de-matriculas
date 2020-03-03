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

#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QtCore>

namespace imageprocess{
	extern void copiar(uchar * imgO, uchar * imgD, int tam);
    extern void borrar(uchar * imgD, int w, int h);
    extern void invertir(uchar * imgO, uchar * imgD, int w, int h);
    extern void umbralizar(uchar *imgD, int w, int h);
    extern void eliminarRuido_F1(uchar * imgO, uchar * imgD, int w, int h);
    extern void eliminarRuido_F2(uchar * imgO, uchar * imgD, int w, int h);
    extern int detectarV_min(uchar *imgD, int U);
    extern int detectarV_max(uchar *imgD, int U);
    extern void detectarH_F1(uchar *imgD, uchar * VA, uchar U);
    extern void detectarH_F2(uchar * VA, int * Vh);
    extern void recortar(uchar *imgO, uchar *imgD,int x, int y, int w, int h);
    extern int matching(uchar *caracM, uchar *patrones[31], int ini, int tam);
}

#endif
