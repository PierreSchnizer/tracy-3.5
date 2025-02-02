/***************************************************************************
                          naffutils.h  -  description
                             -------------------
    begin                : Wed May 25 20:24:44 CET 2005
    copyright            : (C) 2002 by Laurent Nadolski
    email                : nadolski@synchrotron-soleil.fr
 ***************************************************************************/

#ifndef NAFFUTILS_H
#define NAFFUTILS_H

/* definition form old soleilcommon.h */
#define NTURN 10000  // 2*NTURN for diffusion
#define DIM   6

/* Frequency Map Analysis */
void Get_NAFF(int nterm, long ndata, double Tab[DIM][NTURN],
	      double *fx, double *fz, int nbf[2]);

void Get_Tabshift(double Tab[DIM][NTURN], double Tab0[DIM][NTURN],
		  long nbturn, long nshift);

void Get_freq(double *fx, double *fz, double *nux, double *nuz);

void Trac_Simple(LatticeType &lat, double x, double px, double y, double py,
		 double dp, double ctau, long nmax, double Tx[][NTURN],
		 bool *status);

#endif
