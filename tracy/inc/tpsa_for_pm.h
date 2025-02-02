/* Author:        Johan Bengtsson

    Definitions:  Interface to Fortran library for Truncated Power
		  Series Algebra.

    Note, linear case is a special case, see e.g. daexp

*/

#ifndef TPSA_FOR_PM_H
#define TPSA_FOR_PM_H

extern int  bufsize;  // Note, max no of monomials is (no+nv)!/(nv!*no!)
 

long int fact(long int n);

long int nok(long int n, long int k);

double getmat(const ss_vect<tps> &map, const int i, const int j);

void putmat(ss_vect<tps> &map, const int i, const int j, const double r);

void getlinmat(const int nv, const ss_vect<tps> &map, arma::mat &mat);

ss_vect<tps> putlinmat(const int nv, const arma::mat &mat);

void idprset(const int level);

tps atan2(const tps &b,const tps &a);

#endif
