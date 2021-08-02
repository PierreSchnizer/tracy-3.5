/* Tracy-2

   J. Bengtsson, CBP, LBL      1990 - 1994   Pascal version
                 SLS, PSI      1995 - 1997
   M. Boege      SLS, PSI      1998          C translation
   L. Nadolski   SOLEIL        2002          Link to NAFF, Radia field maps
   J. Bengtsson  NSLS-II, BNL  2004 -        

   Note, the operators "operator*=()", etc. requires
   the use of a local variable

*/


#define danamlen 10
#define dafunlen  4

typedef char danambuf[danamlen];
typedef char     funnambuf[dafunlen];

extern const int nv_tps, nd_tps, iref_tps;

extern int    no_tps, ndpt_tps;
extern double eps_tps;


void daeps_(const double eps) { eps_tps = eps; }


void danot_(const int no) {
  if (no != 1) {
    printf("danot_: max order exceeded %d (%d)\n", no, 1);
    exit_(0);
  }
}


void daini_(int no, int nv, int fio)
{
  eps_tps = 1e-25;
  if (no != 1) {
    printf("daini_: max order exceeded %d (%d)\n", no, 1);
    exit_(1);
  }
  if ((nv < 1) || (nv > nv_tps))
    printf("daini_: to many dimensions %d(%d)\n", nv, nv_tps);
}


void lieini(const int no, const int nv, const int nd2i)
{
  if ((nv < 1) || (nv > nv_tps))
    printf("lieini: max dim exceeded %d (%d)\n", nv, nv_tps);
}


void daall_(std::vector<double> &x, const int nd2, const char *daname,
	   const int no, const int nv)
{ for (int j = 0; j <= nv_tps; j++) x[j] = 0.0; }


void dadal_(std::vector<double> &x, const int nv_tps) { }


void davar_(std::vector<double> &x, const double r, const int i)
{
  x[0] = r;
  for (int j = 1; j <= nv_tps; j++) x[j] = 0e0;
  x[i] = 1e0;
}


void dacon_(std::vector<double> &x, const double r)
{
  x[0] = r;
  for (int j = 1; j <= nv_tps; j++) x[j] = 0e0;
}


void dapek_(const std::vector<double> &x, const long int jj[], double &r)
{
  int n_zero = 0;

  for (int i = 0; i < nv_tps; i++) {
    if (jj[i] == 0)
      n_zero++;
    else if (jj[i] == 1)
      r = x[i+1];
    else {
      printf("\ndapek_: invalid jj\n");
      exit(1);
    }
  }

  if (n_zero == nv_tps)
    r = x[0];
  else if (n_zero < nv_tps-1) {
    printf("\ndapek_: invalid jj\n");
    exit(1);
  }
}


void dapok_(std::vector<double> &x, const long int jj[], const double r)
{
  int n_zero = 0;

  for (int i = 0; i < nv_tps; i++) {
    if (jj[i] == 0)
      n_zero++;
    else if (jj[i] == 1)
      x[i+1] = r;
    else {
      printf("\ndapok_: invalid jj\n");
      exit(1);
    }
  }
  if (n_zero == nv_tps)
    x[0] = r;
  else if (n_zero < nv_tps-1) {
    printf("\ndapok_: invalid jj\n");
    exit(1);
  }
}


double get_m_ij(const ss_vect<tps> &map, const int i, const int j)
{ return map[i-1].ltps[j]; }


void put_m_ij(ss_vect<tps> &map, const int i, const int j, const double r)
{ map[i-1].ltps[j] = r; }


ss_vect<tps> stlmattomap(const std::vector< std::vector<double> > &stlmat)
{
  ss_vect<tps> map;

  const int n = (int)stlmat[0].size();

  for (int j = 0; j < nv_tps; j++)
    for (int k = -1; k < nv_tps; k++)
      if (k == -1)
	put_m_ij(map, j+1, 0, stlmat[j][n-1]);
      else
	put_m_ij(map, j+1, k+1, stlmat[j][k]);
  return map;
}

std::vector< std::vector<double> > maptostlmat(const ss_vect<tps> &map)
{
  std::vector<double>                row;
  std::vector< std::vector<double> > stlmat;

  for (int j = 0; j < nv_tps; j++) {
    row.clear();
    for (int k = 0; k < nv_tps; k++)
      row.push_back(map[j][k+1]);
    row.push_back(map[j][0]);
    stlmat.push_back(row);
  }
  row.clear();
  for (int k = 0; k < nv_tps; k++)
    row.push_back(0e0);
  stlmat.push_back(row);
  return stlmat;
}

arma::mat maptomat(const ss_vect<tps> &map)
{
  arma::mat mat(tps_n, tps_n);

  for (int j = 0; j < nv_tps; j++) {
    for (int k = 0; k < nv_tps; k++)
      mat(j, k) = get_m_ij(map, j+1, k+1);
    mat(j, tps_n-1) = get_m_ij(map, j+1, 0);
  }
  mat(tps_n-1, tps_n-1) = 1e0;
  return mat;
}


ss_vect<tps> mattomap(const arma::mat &mat)
{
  ss_vect<tps> map;

  for (int j = 0; j < nv_tps; j++) {
    for (int k = 0; k < nv_tps; k++)
      put_m_ij(map, j+1, k+1, mat(j, k));
    if (j < nv_tps) put_m_ij(map, j+1, 0, mat(j, tps_n-1));
  }
  return map;
}


arma::mat stlmattomat(const std::vector< std::vector<double> > &stlmat)
{
  const int
    m = (int)stlmat.size(),
    n = (int)stlmat[0].size();

  arma::mat mat(m, n);

  for (int j = 0; j < m; j++)
    for (int k = 0; k < n; k++)
      mat(j, k) = stlmat[j][k];
  return mat;
}


std::vector< std::vector<double> > mattostlmat(const arma::mat &mat)
{
  std::vector<double>                row;
  std::vector< std::vector<double> > stlmat;

  for (int j = 0; j < (int)mat.n_rows; j++) {
    row.clear();
    for (int k = 0; k < (int)mat.n_cols; k++)
      row.push_back(mat(j, k));
    stlmat.push_back(row);
  }
  return stlmat;
}


std::vector< std::vector<double> > get_stlmat(const ss_vect<tps> &map)
{
  std::vector<double>                row;
  std::vector< std::vector<double> > mat;

  for (int j = 0; j < nv_tps; j++) {
    row.clear();
    for (int k = 0; k < nv_tps; k++)
      row.push_back(get_m_ij(map, j+1, k+1));
    mat.push_back(row);
  }
  return mat;
}


void dacop_(const std::vector<double> &x, std::vector<double> &z)
{ for (int i = 0; i <= nv_tps; i++) z[i] = x[i]; }

void daadd_(const std::vector<double> &x, const std::vector<double> &y,
	    std::vector<double> &z)
{ for (int i = 0; i <= nv_tps; i++) z[i] = x[i] + y[i]; }

void dasub_(const std::vector<double> &x, const std::vector<double> &y,
	    std::vector<double> &z)
{ for (int i = 0; i <= nv_tps; i++) z[i] = x[i] - y[i]; }


void damul_(const std::vector<double> &x, const std::vector<double> &y,
	    std::vector<double> &z)
{
  std::vector<double> u(tps_n, 0e0);

  u[0] = x[0]*y[0];
  for (int i = 1; i <= nv_tps; i++)
    u[i] = x[0]*y[i] + x[i]*y[0];
  dacop_(u, z);
}


void dafun_(const char *fun, const std::vector<double> &x,
	    std::vector<double> &z);

void dadiv_(const std::vector<double> &x, const std::vector<double> &y,
	    std::vector<double> &z)
{
  std::vector<double> yinv(tps_n, 0e0);

  dafun_("INV ", y, yinv); damul_(x, yinv, z);
}


void dacad_(const std::vector<double> &x, const double y,
	    std::vector<double> &z)
{
  z[0] = x[0] + y;
  for (int i = 1; i <= nv_tps; i++)
    z[i] = x[i];
}


void dacsu_(const std::vector<double> &x, const double y,
	    std::vector<double> &z)
{ dacad_(x, -y, z); }


void dacmu_(const std::vector<double> &x, const double y,
	    std::vector<double> &z)
{
  for (int i = 0; i <= nv_tps; i++)
    z[i] = x[i]*y;
}


void dasuc_(const std::vector<double> &x, const double y,
	    std::vector<double> &z)
{
  std::vector<double> negx(tps_n, 0e0);

  dacmu_(x, -1.0, negx); dacad_(negx, y, z);
}


void dacdi_(const std::vector<double> &x, const double y,
	    std::vector<double> &z)
{ dacmu_(x, 1.0/y, z); }


void dadic_(const std::vector<double> &x, const double y,
	    std::vector<double> &z)
{
  std::vector<double> xinv(tps_n, 0e0);

  dafun_("INV ", x, xinv); dacmu_(xinv, y, z);
}


void dapos_(const std::vector<double> &x, std::vector<double> &z)
{ if (x[0] < 0.0) dacmu_(x, -1.0, z); }


void dasqr_(const std::vector<double> &x, std::vector<double> &z)
{ damul_(x, x, z); }


void dacma_(const std::vector<double> &x, const std::vector<double> &y,
	    const double rb, std::vector<double> &z)
{
  std::vector<double> x1(tps_n, 0e0);

  dacmu_(y, rb, x1);  /* x1=y*rb */
  daadd_(x, x1, z);   /* z =x+x1 */
}


void dalin_(const std::vector<double> &x, const double ra,
	    const std::vector<double> &y,
	    const double rb, std::vector<double> &z)
{
  std::vector<double> x1(tps_n, 0e0), x2(tps_n, 0e0);

  dacmu_(x, ra, x1); dacmu_(y, rb, x2); daadd_(x1, x2, z);
}


void dainv_(const std::vector<double> &x, std::vector<double> &z)
{
  double a;

  a = -1e0/sqr(x[0]); z[0] = 1e0/x[0];
  for (int i = 1; i <= nv_tps; i++)
    z[i] = a*x[i];
}


void dasqrt(const std::vector<double> &x, std::vector<double> &z)
{
  double a;

  a = sqrt(x[0]); z[0] = a; a = 0.5/a;
  for (int i = 1; i <= nv_tps; i++)
    z[i] = a*x[i];
}


void daexp(const std::vector<double> &x, std::vector<double> &z)
{
  double a;

  a = exp(x[0]); z[0] = a;
  for (int i = 1; i <= nv_tps; i++)
    z[i] = a*x[i];
}


void dalog(const std::vector<double> &x, std::vector<double> &z)
{
  z[0] = log(x[0]);
  for (int i = 1; i <= nv_tps; i++)
    z[i] = x[i]/x[0];
}


void dasin(const std::vector<double> &x, std::vector<double> &z)
{
  double a;

  z[0] = sin(x[0]); a = cos(x[0]);
  for (int i = 1; i <= nv_tps; i++)
    z[i] = a*x[i];
}


void dacos(const std::vector<double> &x, std::vector<double> &z)
{
  double a;

  z[0] = cos(x[0]); a = -sin(x[0]);
  for (int i = 1; i <= nv_tps; i++)
    z[i] = a*x[i];
}


void dasinh(const std::vector<double> &x, std::vector<double> &z)
{
  double a;

  z[0] = sinh(x[0]); a = cosh(x[0]);
  for (int i = 1; i <= nv_tps; i++)
    z[i] = a*x[i];
}


void dacosh(const std::vector<double> &x, std::vector<double> &z)
{
  double a;

  z[0] = cos(x[0]); a = sinh(x[0]);
  for (int i = 1; i <= nv_tps; i++)
    z[i] = a*x[i];
}


void datan(const std::vector<double> &x, std::vector<double> &z)
{
  std::vector<double> c(tps_n, 0e0), s(tps_n, 0e0);

  dacos(x, c); dasin(x, s); dadiv_(s, c, z);
}


void daarctan(const std::vector<double> &x, std::vector<double> &z)
{
  double a;

  a = x[0]; z[0] = atan(a); a = 1.0/(1.0+sqr(a));
  for (int i = 1; i <= nv_tps; i++)
    z[i] = a*x[i];
}


void dafun_(const char *fun, const std::vector<double> &x,
	    std::vector<double> &z)
{
  std::vector<double> u(tps_n, 0e0);

  if (!strncmp(fun, "INV ", dafunlen))
    dainv_(x, u);
  else if (!strncmp(fun, "SQRT", dafunlen))
    dasqrt(x, u);
  else if (!strncmp(fun, "EXP ", dafunlen))
    daexp(x, u);
  else if (!strncmp(fun, "LOG ", dafunlen))
    dalog(x, u);
  else if (!strncmp(fun, "SIN ", dafunlen))
    dasin(x, u);
  else if (!strncmp(fun, "COS ", dafunlen))
    dacos(x, u);
  else if (!strncmp(fun, "SINH ", dafunlen))
    dasinh(x, u);
  else if (!strncmp(fun, "COSH ", dafunlen))
    dacosh(x, u);
  else if (!strncmp(fun, "TAN ", dafunlen))
    datan(x, u);
  else if (!strncmp(fun, "ATAN", dafunlen))
    daarctan(x, u);
  else {
    printf("dafun: illegal function %s\n", fun);
    exit_(0);
  }

  dacop_(u, z);
}


void dacct_(const ss_vect<tps> &x, const int i,
	    const ss_vect<tps> &y, const int j, ss_vect<tps> &z, const int k)
{
  int          l, m, n;
  ss_vect<tps> u;

  for (l = 0; l < k; l++) {
    u[l].ltps[0] = x[l].ltps[0];
    for (m = 1; m <= j; m++)
      u[l].ltps[m] = 0.0;
    for (m = 0; m <= j; m++)
      for (n = 1; n <= i; n++)
        u[l].ltps[m] += x[l].ltps[n]*y[n-1].ltps[m];
  }
  for (l = 0; l < k; l++)
    z[l] = u[l];
}


void dainv_(const ss_vect<tps> &x, const int i, ss_vect<tps> &z, const int k)
{ z = mattomap(arma::inv(maptomat(x))); }


void Rotmap(const int n, ss_vect<tps> &map, const arma::mat &R)
{ map = mattomap(maptomat(map)*R); }


void daabs_(const std::vector<double> &x, double &r)
{
  r = 0e0;
  for (int k = 0; k <= nv_tps; k++)
    r += fabs(x[k]);
}


void daabs2_(const std::vector<double> &x, double &r)
{
  r = 0e0;
  for (int k = 0; k <= nv_tps; k++)
    r += sqr(x[k]);
}
