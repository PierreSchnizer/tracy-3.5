
// Poincare Map Object.
//
// Computes the Poincare map for fast tracking, for a general lattice of
// arbitray complexity, e.g. with: linear coupling, imperfections, and related
// corrections. It is partitioned so that nonlinear effects can be included to
// arbitrary order by a parametric approach. In particular: momentum compaction,
// chromaticity, and anharmonic terms.
//
// Use Cases include lattice modelling for collective phenomena.
//
// Johan Bengtsson 29/03/20.


struct PoincareMapType;


struct BeamType {
private:
public:
  int                            n_part;
  std::vector< ss_vect<double> > ps;
  ss_vect<double>                mean;
  ss_vect<tps>                   Sigma;

  void BeamInit_dist(const int n_part, const double eps_x, const double eps_y,
		     const double sigma_delta);
  void BeamStats(void);
  void print(void);
};


struct PoincareMapType {
private:
public:
  int n_DOF;           // Degrees-of-Freedom.
  bool
    cav_on,            // RF Cavity on/off.
    rad_on;            // Classical Radiation on/off.
  double
    C,                 // Circumference.
    E0,                // Beam Energy.
    alpha[3], beta[3], // Twiss Parameters.
    nu[3],             // Tunes; in Floquet Space.
    ksi1[2],           // Linear Chromaticity.
    ksi2[2],           // Second Order Chromaticity.
    alpha_c,           // Linear Momentum Compaction.
    dnu_dJ[3],         // Anharmonic terms.
    U0,                // Energy loss per turn.
    delta_rad,         // Momentum change.
    V_RF,              // RF Voltage.
    f_RF,              // RF frequency.
    phi0,              // Synchronous phase.
    tau[3],            // Damping times.
    D[3];              // Diffusion Coefficients.
  ss_vect<double>
    ps_cod,            // Fixed Point.
    eta;               // Linear Dispersion.
  ss_vect<tps>
    M_num,             // numerical Poincare Map.
    M_lat,             // Linear Map for Lattice.
    M_cav,             // Linear Map for RF Cavity.
    A,                 // Transformation to Floquet Space.
    M_Fl,              // Map in Floquet Space.
    M_delta,           // Radiation Loss Map.
    M_tau,             // Radiation Damping Map.
    M,                 // Poincare Map.
    M_diff, M_Chol;    // Diffusion Matrix & Cholesky Decomposition.

  void GetMap(void);
  void GetDisp(void);
  void GetM_cav(void);
  void GetM_delta(void);
  void GetM_tau(void);
  void GetM_diff(void);
  void GetM_Chol(void);
  void GetM_rad(void);
  void GetM(const bool cav, const bool rad);
  void propagate(const int n, BeamType &beam) const;
  void propagate(const int n, ss_vect<tps> &Sigma) const;
  void print(void);
};


void PrtMap(const string &str, const double n_DOF, ss_vect<tps> map)
{
  int i, j;

  const int    n_dec = 6;
  const double eps   = 1e-20;

  printf("%s\n", str.c_str());
  for (i = 0; i < 2*n_DOF; i++) {
    for (j = 0; j < 2*n_DOF; j++) {
      if (!true)
	printf("%*.*e", n_dec+8, n_dec, map[i][j]);
      else
	printf("%*.*e",
	       n_dec+8, n_dec, (fabs(map[i][j]) > eps)? map[i][j] : 0e0);
    }
    printf("\n");
  }
}


double DetMap(const int n, ss_vect<tps> A)
{
  Matrix A_mat;

  getlinmat(2*n, A, A_mat);
  return DetMat(2*n, A_mat);
}


ss_vect<tps> TpMap(const int n, ss_vect<tps> A)
{
  Matrix A_mat;

  getlinmat(2*n, A, A_mat);
  TpMat(2*n, A_mat);
  return putlinmat(2*n, A_mat);
}


ss_vect<tps>  GetSigma(const ss_vect<tps> &var)
{
  int          j, k;
  ss_vect<tps> Id, Sigma;

  Id.identity(); Sigma.zero();
  for (j = 0; j < 6; j++)
    for (k = 0; k < 6; k++)
      Sigma[j] += ((var[j][k] >= 0e0)? sqrt(var[j][k]) : 0e0)*Id[k];

  return Sigma;
}


ss_vect<tps> GetVar(const ss_vect<tps> &Sigma)
{
  int          j, k;
  ss_vect<tps> Id, var;

  Id.identity(); var.zero();
  for (j = 0; j < 6; j++)
    for (k = 0; k < 6; k++)
      var[j] += sqr(Sigma[j][k])*Id[k];

  return var;
}


void GetSigma(const double C, const double tau[], const double D[],
	      ss_vect<tps> &A)
{
  int          j, k;
  double       eps[3];
  ss_vect<tps> Id, var, sigma;

  Id.identity();

  for (k = 0; k < 3; k++)
    eps[k] = D[k]*tau[k]*c0/(2e0*C);
  printf("\neps = [%10.3e, %10.3e, %10.3e]\n", eps[X_], eps[Y_], eps[Z_]);
  for (k = 0; k < 6; k++)
    var[k] = sqrt(eps[k/2])*Id[k];
  var = var*A*TpMap(3, A)*var;

  sigma.zero();
  for (j = 0; j < 6; j++)
    for (k = 0; k < 6; k++)
      sigma[j] += sqrt((var[j][k] > 0e0)? var[j][k] : 0e0)*Id[k];

  PrtMap("\nsigma:", 3, sigma);
  printf("\nsigma_x, sigma_px: %12.5e %12.5e\n",
	 sqrt(sqr(sigma[x_][x_])+sqr(sigma[x_][delta_])),
	 sqrt(sqr(sigma[px_][x_])+sqr(sigma[px_][delta_])));
}


void GetA(const int n_DOF, const double C, const ss_vect<tps> &M,
	  ss_vect<tps> &A, ss_vect<tps> &R, double tau[])
{
  int    k;
  double nu_z, alpha_c, dnu[3];
  Matrix M_mat, A_mat, A_inv_mat, R_mat;

  getlinmat(6, M, M_mat);
  GDiag(2*n_DOF, C, A_mat, A_inv_mat, R_mat, M_mat, nu_z, alpha_c);

  for (k = 0; k < n_DOF; k++)
    tau[k] = -C/(c0*globval.alpha_rad[k]);

  A = putlinmat(2*n_DOF, A_mat);
  if (n_DOF < 3) {
    // Coasting longitudinal plane.
    A[ct_] = tps(0e0, ct_+1);
    A[delta_] = tps(0e0, delta_+1);
  }
  A = get_A_CS(n_DOF, A, dnu);
  R = putlinmat(2*n_DOF, R_mat);
}


ss_vect<tps> GetA0(const ss_vect<double> &eta)
{
  // Canonical Transfomation to delta dependent Fixed Point.
  int          k;
  ss_vect<tps> Id, A0;

  Id.identity(); A0.identity();
  for (k = 0; k < 2; k++)
    A0[k] += eta[k]*Id[delta_];
  // Symplectic flow.
  A0[ct_] += eta[px_]*Id[x_] - eta[x_]*Id[px_];
  return A0;
}


ss_vect<tps> GetA1(const double alpha[], const double beta[])
{
  // Canonical Transformation to Floquet Space.
  int          k;
  ss_vect<tps> Id, A;

  Id.identity(); A.zero();
  for (k = 0; k < 3; k++) {
    if (k < 2) {
      A[2*k] += sqrt(beta[k])*Id[2*k];
      A[2*k+1] += -alpha[k]/sqrt(beta[k])*Id[2*k] + 1e0/sqrt(beta[k])*Id[2*k+1];
    } else {
      A[ct_] += sqrt(beta[Z_])*Id[ct_];
      A[delta_] +=
	-alpha[Z_]/sqrt(beta[Z_])*Id[ct_] + 1e0/sqrt(beta[Z_])*Id[delta_];
    }
  }
  return A;
}


ss_vect<tps> GetR(const double nu[])
{
  int          k;
  ss_vect<tps> Id, R;

  Id.identity(); R.zero();
  for (k = 0; k < 3; k++) {
    R[2*k] = cos(2e0*M_PI*nu[k])*Id[2*k] + sin(2e0*M_PI*nu[k])*Id[2*k+1];
    R[2*k+1] = -sin(2e0*M_PI*nu[k])*Id[2*k] + cos(2e0*M_PI*nu[k])*Id[2*k+1];
  }
  R[ct_] = cos(2e0*M_PI*nu[Z_])*Id[ct_] + sin(2e0*M_PI*nu[Z_])*Id[delta_];
  R[delta_] = -sin(2e0*M_PI*nu[Z_])*Id[ct_] + cos(2e0*M_PI*nu[Z_])*Id[delta_];
  return R;
}


void GetEta(const ss_vect<tps> &M, ss_vect<double> &eta)
{
  long int     jj[ss_dim];
  int          k;
  ss_vect<tps> Id, M_x;

  Id.identity();
  for (k = 0; k < 2; k++)
    M_x[k] = M[k][x_]*Id[x_] + M[k][px_]*Id[px_];
  for (k = 0; k < ss_dim; k++)
    jj[k] = 0;
  jj[x_] = 1; jj[px_] = 1;
  eta.zero();
  for (k = 0; k < 2; k++)
    eta[k] = M[k][delta_];
  eta = (PInv(Id-M_x, jj)*eta).cst();
}


void GetTwiss(const ss_vect<tps> &A, const ss_vect<tps> &R,
	      double alpha[], double beta[], ss_vect<double> &eta, double nu[])
{
  long int     jj[ss_dim];
  int          k;
  ss_vect<tps> Id, A_t, scr, A0, A_A_tp;

  Id.identity();

  A_t.zero();
  for (k = 4; k < 6; k++)
    A_t[k] = A[k][ct_]*Id[ct_] + A[k][delta_]*Id[delta_];
  for (k = 0; k < ss_dim; k++)
    jj[k] = 0;
  jj[ct_] = 1; jj[delta_] = 1;
  scr = A*PInv(A_t, jj);
  eta.zero();
  for (k = 0; k < 2; k++)
    eta[k] = scr[k][delta_];
 
  // A_t.identity();
  // for (k = 4; k < 6; k++)
  //   A_t[k] = A[k][ct_]*Id[ct_] + A[k][delta_]*Id[delta_];
  // scr = A*Inv(A_t);
  // eta.zero();
  // for (k = 0; k < 4; k++)
  //   eta[k] = scr[k][delta_];

  for (k = 0; k < 3; k++) {
    if (k < 2) {
      // Phase space rotation by betatron motion.
      alpha[k] = -(A[2*k][2*k]*A[2*k+1][2*k] + A[2*k][2*k+1]*A[2*k+1][2*k+1]);
      beta[k] = sqr(A[2*k][2*k]) + sqr(A[2*k][2*k+1]);
      nu[k] = atan2(R[2*k][2*k+1], R[2*k][2*k])/(2e0*M_PI);
    } else {
      alpha[Z_] =
	-(A[ct_][ct_]*A[delta_][ct_] + A[ct_][delta_]*A[delta_][delta_]);
      beta[Z_] = sqr(A[ct_][ct_]) + sqr(A[ct_][delta_]);
      nu[Z_] = atan2(R[ct_][delta_], R[ct_][ct_])/(2e0*M_PI);
    }
  }
}


void PoincareMapType::GetM_cav(void)
{
  const int loc = Elem_GetPos(ElemIndex("cav"), 1);

  V_RF = Cell[loc].Elem.C->Pvolt;
  f_RF = Cell[loc].Elem.C->Pfreq;
  phi0 = asin(U0/V_RF);

  M_cav.identity();
  M_cav[delta_] -=
    V_RF*2e0*M_PI*f_RF*cos(phi0)/(1e9*globval.Energy*c0)*tps(0e0, ct_+1);
}


void PoincareMapType::GetM_delta(void)
{
  int          k;
  ss_vect<tps> Id;

  Id.identity();

  M_delta.identity();
  for (k = 0; k < n_DOF; k++) {
    M_delta[2*k] *= 1e0 + delta_rad;
    M_delta[2*k+1] /= 1e0 + delta_rad;
  }
}


void PoincareMapType::GetM_tau(void)
{
  int          k;
  ss_vect<tps> Id;

  Id.identity(); M_tau.zero();
  for (k = 0; k < n_DOF; k++) {
    M_tau[2*k] = exp(-C/(c0*tau[k]))*Id[2*k];
    M_tau[2*k+1] = exp(-C/(c0*tau[k]))*Id[2*k+1];
  }
}


void PoincareMapType::GetM_diff(void)
{
  int long     lastpos;
  int          k;
  ss_vect<tps> Id, As, D_diag;

  Id.identity();

  globval.Cavity_on = true; globval.radiation = true;
  globval.emittance = true;

  As = A + ps_cod;
  Cell_Pass(0, globval.Cell_nLoc, As, lastpos);

  globval.emittance = false;

  for (k = 0; k < n_DOF; k++)
    D[k] = globval.D_rad[k];

  D_diag.zero();
  for (k = 0; k < 2*n_DOF; k++)
    D_diag[k] = sqrt(D[k/2])*Id[k];
  M_diff = D_diag*A*TpMap(n_DOF, A)*D_diag;

  GetM_Chol();
}


ss_vect<tps> Mat2Map(const int n, double **M)
{
  int          j, k;
  ss_vect<tps> map;

  map.zero();
  for (j = 1; j <= n; j++)
    for (k = 1; k <= n; k++)
      map[j-1] += M[j][k]*tps(0e0, k);
  return map;
}


void PoincareMapType::GetM_Chol(void)
{
  int          j, k, j1, k1;
  double       *diag, **d1, **d2;

  const int n = 2*n_DOF;

  diag = dvector(1, n); d1 = dmatrix(1, n, 1, n);
  d2 = dmatrix(1, n, 1, n);

  // Remove vertical plane.
  for (j = 1; j <= 4; j++) {
    j1 = (j < 3)? j : j+2;
    for (k = 1; k <= 4; k++) {
      k1 = (k < 3)? k : k+2;
      d1[j][k] = M_diff[j1-1][k1-1];
    }
  }
  dcholdc(d1, 4, diag);
  for (j = 1; j <= 4; j++)
    for (k = 1; k <= j; k++)
      d2[j][k] = (j == k)? diag[j] : d1[j][k];
  M_Chol.zero();
  for (j = 1; j <= 4; j++) {
     j1 = (j < 3)? j : j+2;
     for (k = 1; k <= 4; k++) {
       k1 = (k < 3)? k : k+2;
       M_Chol[j1-1] += d2[j][k]*tps(0e0, k1);
     }
  }

  free_dvector(diag, 1, n); free_dmatrix(d1, 1, n, 1, n);
  free_dmatrix(d2, 1, n, 1, n);
}


void PoincareMapType::GetMap(void)
{
  int long lastpos;

  globval.Cavity_on = cav_on; globval.radiation = rad_on;

  getcod(0e0, lastpos);

  M_num = putlinmat(2*n_DOF, globval.OneTurnMat);
  ps_cod = globval.CODvect;

  U0 = globval.dE*E0;
  delta_rad = U0/E0;
  alpha_c = M_num[ct_][delta_]/C;
}


void PoincareMapType::GetM(const bool cav, const bool rad)
{
  cav_on = cav; rad_on = rad;

  C = Cell[globval.Cell_nLoc].S; E0 = 1e9*globval.Energy;
  n_DOF = (!cav_on)? 2 : 3;

  GetMap();
  GetA(n_DOF, C, M_num, A, M_Fl, tau);
  GetM_tau();
  GetM_delta();
  GetM_cav();

  M = M_num;

  // Nota Bene: the Twiss parameters are not used; i.e., included for
  // convenience, e.g. cross checks, etc.
  GetA(n_DOF, C, M_num, A, M_Fl, tau);
  GetTwiss(A, M_Fl, alpha, beta, eta, nu);
  GetEta(M, eta);

  // M = Inv(M_cav)*Inv(M_tau)*Inv(M_delta)*M_num;
  // PrtMap("\nM:", 3, M);
  // GetA(n_DOF, C, M, A, M_Fl, tau);
  // GetTwiss(A, M_Fl, alpha, beta, eta, nu);
  // cout << scientific << setprecision(6)
  //      << "\neta:\n" << setw(14) << eta << "\n";
  // GetEta(M, eta); eta[delta_] = 1e0;

  if (rad) GetM_diff();
}


void PoincareMapType::propagate(const int n, BeamType &beam) const
{
  int             i, j = 0, k;
  ss_vect<double> X;
  ofstream        outf;

  const int    n_prt     = 10;
  const string file_name = "propagate.out";

  file_wr(outf, file_name.c_str());

  for (i = 1; i <= n; i++) {
    for (j = 0; j < (int)beam.ps.size(); j++) {
      for (k = 0; k < 6; k++)
	X[k] = normranf();
      beam.ps[j] = (M*beam.ps[j]+M_Chol*X).cst();
    }

    beam.BeamStats();

    if (i % n_prt == 0) {
      outf << setw(7) << i;
      for (j = 0; j < 6; j++)
	outf << scientific << setprecision(5) << setw(13) << beam.sigma[j][j];
      outf << "\n";
    }
  }
  if (n % n_prt != 0) {
    outf << setw(7) << n;
    for (k = 0; k < 6; k++)
      outf << scientific << setprecision(5) << setw(13) << beam.sigma[j][j];
    outf << "\n";
  }

  outf.close();
}


void PoincareMapType::propagate(const int n, ss_vect<tps> &var) const
{
  int          j, k;
  ss_vect<tps> Id, X, sigma;
  ofstream     outf;

  const int    n_prt     = 1;
  const string file_name = "propagate.out";

  file_wr(outf, file_name.c_str());

  Id.identity();

  for (j = 1; j <= n; j++) {
    for (k = 0; k < 6; k++)
      X[k] = sqrt(fabs(normranf()))*Id[k];
    var = M*TpMap(3, M*var) + X*M_diff*X;

    if (j % n_prt == 0) {
      sigma = GetSigma(var);

      outf << setw(7) << j;
      for (k = 0; k < 6; k++)
	outf << scientific << setprecision(5) << setw(13) << sigma[k][k];
      outf << "\n";
    }
  }
  if (n % n_prt != 0) {
    outf << setw(7) << n;
    for (k = 0; k < 6; k++)
      outf << scientific << setprecision(5) << setw(13) << sigma[k][k];
    outf << "\n";
  }

  outf.close();
}


ss_vect<tps> GetM_track(const bool cav_on, const bool rad_on,
			const ss_vect<tps> &ps_cod)
{
  int long     lastpos;
  ss_vect<tps> M;

  globval.Cavity_on = cav_on; globval.radiation = rad_on;
  M.identity(); M += ps_cod;
  Cell_Pass(0, globval.Cell_nLoc, M, lastpos);
  return M;
}


ss_vect<tps> GetMTwiss(const double alpha[], const double beta[],
		       const ss_vect<double> eta, const double nu[])
{
  ss_vect<tps> Id, A, M;

  Id.identity();
  A = GetA0(eta)*GetA1(alpha, beta);
  M = A*GetR(nu)*Inv(A);
  return M;
}


void PoincareMapType::print(void)
{
  printf("\nCavity %d, Radiation %d\n", cav_on, rad_on);
  printf("\nC [m]      = %7.5f\n", C);

  printf("alpha      = [%9.5f, %9.5f, %9.5f]\n",
	 alpha[X_], alpha[Y_], alpha[Z_]);
  printf("beta       = [%9.5f, %9.5f, %9.5f]\n",
	 beta[X_], beta[Y_], beta[Z_]);
  printf("eta        = [%9.5f, %9.5f]\n", eta[x_], eta[px_]);
  printf("nu         = [%9.5f, %9.5f, %9.5f]\n", nu[X_], nu[Y_], nu[Z_]);

  printf("V_RF       = %7.5e\n", V_RF);
  printf("f_RF [MhZ] = %7.5f\n", 1e-6*f_RF);
  printf("phi0       = %7.5f\n", phi0*180.0/M_PI);

  printf("E0 [GeV]   = %7.5f\n", 1e-9*E0);
  printf("U0 [keV]   = %7.5f\n", 1e-3*U0);
  printf("delta_rad  = %11.5e\n", delta_rad);
  printf("alpha_c    = %11.5e\n", alpha_c);
  printf("tau        = [%11.5e, %11.5e, %11.5e]\n", tau[X_], tau[Y_], tau[Z_]);
  printf("D          = [%11.5e, %11.5e, %11.5e]\n", D[X_], D[Y_], D[Z_]);

  cout << scientific << setprecision(6) << "\nCOD:\n" << setw(14) << ps_cod
       << "\n";

  PrtMap("\nM_num (input map):", 3, M_num);
  printf("\nDet{M_num}-1 = %10.3e\n", DetMap(n_DOF, M_num)-1e0);

  PrtMap("\nM = A*M_Fl*A^-1:", 3, A*M_Fl*Inv(A));
  printf("\nDet{A*M_Fl*A^-1}-1 = %10.3e\n",
	 DetMap(n_DOF, A*M_Fl*Inv(A))-1e0);

  PrtMap("\nA:", 3, A);
  printf("\nDet{A}-1 = %10.3e\n", DetMap(n_DOF, A)-1e0);

  PrtMap("\nM_lat (w/o Cavity):", 3, M_lat);
  printf("\nDet{M_lat}-1 = %10.3e\n", DetMap(n_DOF, M_lat)-1e0);

  if (!false) {
    ss_vect<tps> M1;
    M1 = GetM_track(false, true, ps_cod);
    PrtMap("\nM_lat; cross check from tracking:", 3, M1);
    printf("\nDet{M_lat}-1 = %10.3e\n", DetMap(n_DOF, M1)-1e0);
  }

  PrtMap("\nM_cav:", 3, M_cav);

  if (rad_on) {
    PrtMap("\nM_delta (radiation loss):", 3, M_delta);
    printf("\nDet{M_delta}-1 = %10.3e\n", DetMap(n_DOF, M_delta)-1e0);
    PrtMap("\nM_tau (radiation damping):", 3, M_tau);
    printf("\nDet{M_tau}-1 = %10.3e\n", DetMap(n_DOF, M_tau)-1e0);

    PrtMap("\nM_diff:", n_DOF, M_diff);
    PrtMap("\nM_Chol:", n_DOF, M_Chol);
  }
}


void BeamType::BeamInit_dist(const int n_part, const double eps_x,
			     const double eps_y, const double sigma_s)
{
  int             j, k;
  double          phi;
  ss_vect<double> ps;

  this->n_part = n_part;

  globval.Cavity_on = false; globval.radiation = false;
  Ring_GetTwiss(true, 0e0);

  const double
    eps[]   = {eps_x, eps_y},
    alpha[] = {Cell[0].Alpha[X_], Cell[0].Alpha[Y_]},
    beta[]  = {Cell[0].Beta[X_],  Cell[0].Beta[Y_]};

  for (j = 0; j < n_part; j++) {
    ps.zero();
    for (k = 0; k < 2; k++) {
      phi = 2e0*M_PI*ranf();
      ps[2*k] = sqrt(beta[k]*eps[k])*cos(phi);
      ps[2*k+1] = -sqrt(eps[k]/beta[k])*(sin(phi)-alpha[k]*cos(phi));
      ps[ct_] = sigma_s*(2e0*ranf()-1e0);
      // ps_delta = ;
    }
    this->ps.push_back(ps);
  }
}


ss_vect<tps> BeamInit_var(const PoincareMapType &map, const double eps_x,
			  const double eps_y, const double eps_z)
{
  int          k;
  double       gamma[3];
  ss_vect<tps> Id, var;

  const double eps[] = {eps_x, eps_y, eps_y};

  Id.identity();

  globval.Cavity_on = false; globval.radiation = false;
  Ring_GetTwiss(true, 0e0);

  for (k = 0; k < 3; k++)
    gamma[k] = (1e0+sqr(map.alpha[k]))/map.beta[k];

  var.zero();
  for (k = 0; k < 3; k++) {
    var[2*k] += map.beta[k]*eps[k]*Id[2*k] - map.alpha[k]*eps[k]*Id[2*k+1];
    var[2*k+1] += -map.alpha[k]*eps[k]*Id[2*k] + gamma[k]*eps[k]*Id[2*k+1];
  }

  return var;
}


void BeamType::BeamStats(void)
{
  int             i, j, k;
  double          val;
  ss_vect<double> sum;
  ss_vect<tps>    sum2;

  sum.zero(); sum2.zero();
  for (i = 0; i < n_part; i++) {
    sum += ps[i];
    for (j = 0; j < 6; j++)
      for (k = 0; k < 6; k++)
	sum2[j] += ps[i][j]*ps[i][k]*tps(0e0, k+1);
  }

  sigma.zero();
  for (j = 0; j < 6; j++) {
    mean[j] = sum[j]/n_part;
    for (k = 0; k < 6; k++) {
      val = (n_part*sum2[j][k]-sum[j]*sum[k])/(n_part*(n_part-1e0));
      if (val >= 0e0) sigma[j] += sqrt(val)*tps(0e0, k+1);
    }
  }
}


void BeamType::print(void)
{
  printf("\nmean: ");
  cout << scientific << setprecision(5) << setw(13) << mean << "\n";
  PrtMap("\nsigma:", 3, sigma);
}


void BenchMark(const PoincareMapType &map, const int n_part, const int n_turn)
{
  BeamType beam;

  const int long seed = 1121;

  iniranf(seed); setrancut(5e0);

  printf("\nBenchMark:\n");
  beam.BeamInit_dist(n_part, 0e-9, 6e-9, 0e-3);
  beam.BeamStats(); beam.print();
  map.propagate(n_turn, beam);
  beam.BeamStats(); beam.print();
}


void BenchMark(const PoincareMapType &map, const int n_turn)
{
  BeamType     beam;
  ss_vect<tps> var;

  const int long seed = 1121;

  iniranf(seed); setrancut(5e0);

  printf("\nBenchMark:\n");
  var = BeamInit_var(map, 0e-9, 6e-9, 0e-9);
  PrtMap("\nsigma:", 3, GetSigma(var));
  map.propagate(n_turn, var);
  PrtMap("\nsigma:", 3, GetSigma(var));
}


void get_Poincare_Map(void)
{
  ss_vect<double> eta1;
  ss_vect<tps>    Id, M, A0;
  PoincareMapType map;

  if (!false) no_sxt();

  Id.identity();

  map.GetM(true, true); map.print();

  // PrtMap("\nM_num:", 3, map.M_num);
  // M = Inv(map.M_tau*map.M_cav*map.M_delta)*map.M_num;

  if (false) {
    eta1 =  map.eta;
    cout << scientific << setprecision(16) << "\neta:  \n" << setw(14) << eta1
	 << "\n";
    cout << scientific << setprecision(6) << "M*eta:\n"
	 << setw(14) << (M*eta1).cst() << "\n";

    A0.identity();
    A0[x_] += map.eta[x_]*Id[delta_]; A0[px_] += map.eta[px_]*Id[delta_];
    PrtMap("\nA0:", 3, A0);
    map.A = Inv(A0)*map.A;
    PrtMap("\nA1:", 3, map.A);
    M = Inv(A0*map.A)*M*A0*map.A;
    PrtMap("\nR = (A_0*A_1)^-1*M*A_1*A_0:", 3, M);
  }

  if (false) {
    Matrix       L_tp_mat;
    ss_vect<tps> L, L_tp, Id;
    Id.identity();
    L.zero();
    L[x_] = 3.6592e-06*Id[x_];
    L[px_] = 1.7514e-08*Id[x_] + 3.1063e-07*Id[px_];
    L[delta_] = 2.1727e-05*Id[x_] - 4.4389e-06*Id[px_] + 2.6758e-05*Id[delta_];
    L[ct_] =
      8.4551e-07*Id[x_] - 1.1983e-07*Id[px_]
      + 1.2481e-06*Id[delta_] + 8.7481e-07*Id[ct_];

    getlinmat(6, L, L_tp_mat);
    TpMat(6, L_tp_mat); L_tp = putlinmat(6, L_tp_mat);

    PrtMap("\nL:", 3, L);
    PrtMap("\nL*L_tp:", 3, L*L_tp);
  }

  if (!false) {
    // BenchMark(map, 1000, 10000);
    BenchMark(map, 10000);
    GetSigma(map.C, map.tau, map.D, map.A);
  }
}
