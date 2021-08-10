
// C wrapper for Pascal global variablse.
static std::vector<ElemFamType> *ElemFam_;
static LatticeType              *Lat_;


#define debug       false

#define DBNameLen   39

#define LatLLng     (2000+1)
#define Lat_nkw_max 200          // no. of key words

// tables

#define emax        322
#define emin        (-292)
#define kmax        15           // max no. of significant digits

#define nmax        LONG_MAX

#define nn          3

typedef enum
{
  bndsym, defsym, dfcsym, drfsym, elmsym, fcssym, horsym, monsym,
  qdsym, sexsym, versym, plus_, minus_, lparent, rparent, eql, comma, lbrack,
  rbrack, neq, andsy, semicolon, times, rdiv, intcon, realcon, becomes, colon,
  leq, pwrsym, lss, geo, gtr, period_, charcon, stringcon, ident, geq, lsym,
  bobrhosym, bobrhovsym, bobrhohsym, kxvsym, kxhsym, phisym, ksym,
  tsym, t1sym, t2sym,
  gapsym, thksym, invsym, thnsym,
  endsym, tsksym, bemsym, corsym, prnsym, tblsym, possym, prmsym,
  udisym, squote, linsym, mthsym, celsym, mapsym, cavsym, symsym, chmsym,
  cctsym, usesym, andsym, dspsym, kicksym, wglsym, nsym, mrksym,
  nbdsym, frgsym, latsym, mpsym, dbnsym, kssym, homsym, lmdsym, dtsym, xytsym,
  vrfsym, harnumsym, frqsym, gstsym, typsym, rollsym, idsym,
  fnamesym1, fnamesym2, scalingsym, fmsym, harmsym, sprsym, recsym, solsym,
  entryfsym, exitfsym
} Lat_symbol;

// idsym fnamesym1 fnamesym2 scalingsym added for insertion
// ring sym added

/* p2c: t2lat.pas, line 52:
 * Note: Line breaker spent 0.0 seconds, 5000 tries on line 603 [251] */


//#define SETBITS  (8*(unsigned)sizeof(long int))
#define SETBITS  32  /* Length of set is assumed to be 32,
			see e.g. DealWithDefns             */

const int  max_set = (solsym-bndsym+1)/SETBITS + 2;

// array for set
typedef long int  symset[max_set];

#define NameLength 150  // Max length of identifiers (e.g. file names).

typedef char partsName[NameLength];

typedef struct _REC_BlockStype
{
  partsName Bname;   /* name of a beam line */
  long      BSTART, BOWARI;
} _REC_BlockStype;

typedef std::vector<_REC_BlockStype> BlockStype;

typedef long index_;

typedef enum {
  notyp, ints, reals, bools, chars, arrays, records
} types;

typedef long typset;

typedef struct _REC_UDItable {
  partsName Uname;
  double    Uvalue;
} _REC_UDItable;


typedef char alfa_[NameLength];

typedef alfa_      Lat_keytype[Lat_nkw_max];
typedef Lat_symbol Lat_ksytype[Lat_nkw_max];
typedef Lat_symbol Lat_spstype[256];

// Local variables for Lat_Read:
struct LOC_Lat_Read
{
  FILE              *fi, *fo;
  jmp_buf           _JL9999;
  long              Symmetry;
  bool              Ring;          // true is CELL is a ring

  long              NoB;           // Number of defined Blocks
  BlockStype        BlockS;

  std::vector<long> Bstack;
  long              Bpointer;
  std::vector<bool> Reverse_stack; // Reverse element.

  long              UDIC;          // Number of user defined constants
  std::vector<_REC_UDItable>
  UDItable;

  long              nkw;           // number of key word
  Lat_symbol        sym;           // last symbol read by GetSym*/
  alfa_             id;            // identifier from GetSym*/
  long              inum;          // integer from GetSym*/
  double            rnum;          // double number from GetSym*/
  char              chin;          // last character read from source program
  long              cc;            // character counter*/
  long              lc;            // program location counter*/
  long              ll;            // length of current line*/
  long              errpos;
  string            *line;

  Lat_keytype       key;
  Lat_ksytype       ksy;
  Lat_spstype       sps;

  symset            defbegsys, elmbegsys;
  bool              skipflag, rsvwd;
};


/* Local variables for Lat_EVAL: */
struct LOC_Lat_EVAL
{
  struct LOC_Lat_Read *LINK;
  FILE       *fi, *fo;
  long       *cc, *ll, *errpos, *lc, *nkw, *inum, emax_, emin_, kmax_, nmax_;
  char       *chin;
  char       *id;
  double     *rnum;
  bool       *skipflag, *rsvwd;
  string     *line;
  Lat_symbol *sym;
  alfa_      *key;
  Lat_symbol *ksy;
  Lat_symbol *sps;
  jmp_buf    _JL999;

  std::vector<double> S;
  long t;
  symset facbegsys;
};


/* Local variables for Lat_ProcessBlockInput: */
struct LOC_Lat_ProcessBlockInput
{
  struct LOC_Lat_Read *LINK;
  FILE       *fi, *fo;
  long       *cc, *ll, *errpos, *lc, *nkw, *inum, emax_, emin_, kmax_, nmax_;
  char       *chin;
  char       *id;
  double     *rnum;
  bool       *skipflag, *rsvwd;
  string     *line;
  Lat_symbol *sym;
  alfa_      *key;
  Lat_symbol *ksy;
  Lat_symbol *sps;
};


struct DBName
{
  char name[DBNameLen];
};

struct LOC_Lat_DealElement
{
  struct     LOC_Lat_Read *LINK;
  FILE       *fi, *fo;
  long       *cc, *ll, *errpos, *lc, *nkw, *inum, emax_, emin_, kmax_, nmax_;
  char       *chin;
  char       *id;
  char       *BlockName;
  double     *rnum;
  bool       *skipflag, *rsvwd;
  string     *line;
  Lat_symbol *sym;
  alfa_      *key;
  Lat_symbol *ksy;
  Lat_symbol *sps;
  jmp_buf    _JL9999;
  double     B[HOMmax+HOMmax+1];
  bool       BA[HOMmax+HOMmax+1];
  int        n_harm, harm[n_harm_max];
  double     kxV[n_harm_max], BoBrhoV[n_harm_max];
  double     kxH[n_harm_max], BoBrhoH[n_harm_max], phi[n_harm_max];
  long       DBNsavemax;
  std::vector<DBName>
    DBNsave;
};


/* Local variables for Lat_GetSym: */
struct LOC_Lat_GetSym
{
  struct LOC_Lat_Read *LINK;
  FILE   *fi, *fo;
  long   *cc, *ll, *errpos, *lc, emax_, emin_;
  char   *chin;
  double *rnum;
  bool   *skipflag;
  string *line;
  long   k, e;
};


struct CellListType {
  int  Fnum;
  bool Reverse;
};

std::vector<CellListType> Cell_List;


// Set operations

// val IN s
int P_inset(unsigned val, long *s)
{
  unsigned  bit;

  bit = val % SETBITS; val /= SETBITS;
  if (val < (unsigned)*s++ && ((1L<<bit) & (unsigned)s[val]))
    return 1;
  return 0;
}


// s := s + [val]
long *P_addset(long *s, unsigned val)
{
  long      *sbase = s;
  unsigned  bit, size;

  bit = val % SETBITS; val /= SETBITS; size = *s;
  if (++val > size) {
    s += size;
    while (val > size)
      *++s = 0, size++;
    *sbase = size;
  } else
    s += val;
  *s |= 1L<<bit;
  if (size+1 > (unsigned)max_set) {
    std::cout << "P_addset: size+1 > max_set " << size+1
	 << "(" << max_set << ")" << std::endl;
    exit_(1);
  }
  return sbase;
}


// d := s
long *P_expset(long *d, long s)
{
  if (s) {
    d[1] = s;
    *d = 1;
  } else
    *d = 0;
  return d;
}


// d := s1 + s2
long *P_setunion(long *d, long *s1, long *s2)
{
  long          *dbase = d++;
  int  sz1 = *s1++, sz2 = *s2++;

 while (sz1 > 0 && sz2 > 0) {
    *d++ = *s1++ | *s2++;
    sz1--, sz2--;
  }
  while (--sz1 >= 0)
    *d++ = *s1++;
  while (--sz2 >= 0)
    *d++ = *s2++;
  *dbase = d - dbase - 1;
  return dbase;
}


static long CheckElementtable(const char *name, struct LOC_Lat_Read *LINK)
{
  /* Lat_->conf.Elem_nFam = Number of parts in a Element */
  long  i, j;

  j = 0;
  //  if (strstr(LINK->line,"insertion") != NULL) return 0;

  for (i = 1; i <= Lat_->conf.Elem_nFam; i++) {
    if (!strncmp((*ElemFam_)[i-1].ElemF->Name.c_str(), name, sizeof(partsName)))
      j = i;
  }
  return j;
}


static long CheckBLOCKStable(const char *name, struct LOC_Lat_Read *LINK)
{
  /* NoB = Number of Block defs */
  long  i, j;

  j = 0;
  //  if (strstr(LINK->line,"insertion") != NULL) return 0;

  for (i = 1; i <= LINK->NoB; i++) {
    if (!strncmp(LINK->BlockS[i-1].Bname, name, sizeof(partsName)))
      j = i;
  }
  return j;
}


//static void InitUDItable(struct LOC_Lat_Read *LINK)
//{
//  LINK->UDIC = 0;
//}


static long CheckUDItable(const char *name, struct LOC_Lat_Read *LINK)
{
  long  i, j;

  j = 0;
  for (i = 1L; i <= LINK->UDIC; i++) {
    if (!strncmp(LINK->UDItable[i - 1L].Uname, name, sizeof(partsName)))
      j = i;
  }
  return j;
}


static void EnterUDItable(const char *name, double X, struct LOC_Lat_Read *LINK)
{
  _REC_UDItable *WITH;

  LINK->UDIC++;
  LINK->UDItable.resize(LINK->UDIC);
  WITH = &LINK->UDItable[LINK->UDIC-1];
  if (strlen(name)+1 <= 2*sizeof(WITH->Uname))
    // memcpy(WITH->Uname, name, sizeof(partsName));
    strcpy(WITH->Uname, name);
  else {
    printf("\nEnterUDItable: string length exceeded %lu (%lu)\n",
	   strlen(name)+1, 2*sizeof(WITH->Uname));   
    exit(1);
  }
  WITH->Uvalue = X;
}


static void ModUDItable(long N, double X, struct LOC_Lat_Read *LINK)
{
  _REC_UDItable *WITH;

  WITH = &LINK->UDItable[N-1];
  WITH->Uvalue = X;
}


static void RefUDItable(const char *name, double *X,
			struct LOC_Lat_Read *LINK)
{
  long k;

  k = CheckUDItable(name, LINK);
  *X = LINK->UDItable[k-1].Uvalue;
}


//static void PrintUpname(char *name, struct LOC_Lat_Read *LINK)
//{
//  /*(var name:partsname)*/
//  long i;
//  char ch;
//
//  for (i = 0; i < NameLength; i++) {
//    ch = name[i];
//    if ('a' <= ch && ch <= 'z')
//      ch = _toupper(ch);
//    putc(ch, *LINK->fo);
//  }
//}


//static void PrintUpname1(char *name, long *pos,
//                         struct LOC_Lat_Read *LINK)
//{  /*1*/
//  /*var name : partsname; var pos : integer*/
//  long i;
//  char ch;
//
//  *pos = 0;
//  for (i = 0; i < NameLength; i++) {  /*2*/
//    ch = name[i];
//    if ('a' <= ch && ch <= 'z')
//      ch = _toupper(ch);
//    if (ch != ' ') {
//      putc(ch, *LINK->fo);
//      (*pos)++;
//    }
//  }  /*2*/
//}  /*1*/

//void PrintUpname2(char *name, struct LOC_Lat_Read *LINK)
//{
//  /*(var name:partsname)*/
//  long i;
//  char ch;
//
//  for (i = 0; i < NameLength; i++) {
//    ch = name[i];
//    if ('a' <= ch && ch <= 'z')
//      ch = _toupper(ch);
//    putc(ch, *LINK->fo);
//  }
//}


static void abort_(struct LOC_Lat_Read *LINK)
{
  long i;

  for (i = 1; i <= nn; i++)
    putchar('\007');
  printf("\nabort_: >>>>> error detected in the lattice file <<<<<<\n\n");
  Lat_->conf.ErrFlag = true;
  /*goto 9999*/
//  printf("% .5E\n", sqrt(-1.0));
  exit_(1);
}


static void ENDskip(FILE *fo, long *errpos, long *cc, bool *skipflag,
		    struct LOC_Lat_Read *LINK)
{
  /*underline skips part of input*/
  while (*errpos < *cc) {
    putc('-', fo);
    (*errpos)++;
  }
  *skipflag = false;
}


static void Lat_Error(long n, FILE *fo, long *cc, long *errpos,
		      struct LOC_Lat_Read *LINK)
{
  if (*errpos != 0L)   /*write(fo, ' ****')*/
    return;
  if (*cc > *errpos) {
    fprintf(fo, "%*c^%2ld", (int)(*cc - *errpos), ' ', n);
    *errpos = *cc + 3;
  }
}


static void Lat_Nextch(FILE *fi, FILE *fo, long *cc, long *ll, long *errpos,
		       long *lc, char *chin, bool *skipflag, string *line,
		       struct LOC_Lat_Read *LINK)
{
  if (*cc == *ll) {
    if (P_eof(fi)) {
      fprintf(fo, "\nprogram incomplete\n");
      /*errormsg;*/
      abort_(LINK);
    }

    if (*errpos != 0) {
      if (*skipflag)
	ENDskip(fo, errpos, cc, skipflag, LINK);
      putc('\n', fo);
      *errpos = 0;
    }
    /* write(fo, */
    /*lc: 5, */
    /* '  ');*/
    (*lc)++;

    *ll = 0;
    *cc = 0;
    
    *line = "";
    while (!P_eoln(fi)) {
      (*ll)++;
      if ((*ll) > LatLLng) {
        printf("\nLat_Nextch: LatLLng exceeded %ld (%d)\n", (*ll)-1, LatLLng-1);
        exit_(1);
      }
      *chin = getc(fi);
      if (*chin == '\n')
	*chin = ' ';
      putc(*chin, fo);
      // *line[*ll-1] = *chin;
      *line += *chin;
    }
    (*ll)++;
    fscanf(fi, "%*[^\n]");

    getc(fi);
    // *line[*ll-1] = ' ';
    *line += ' ';
    /*read(fi, *line[ll]);*/
    putc('\n', fo);
  }

  (*cc)++;
  if ((*cc) > LatLLng) {
    printf("\nLat_Nextch: LatLLng exceeded %ld (%d)\n", (*cc), LatLLng);
    exit_(1);
  }
  *chin = (*line)[*cc-1];
  /* upper case to lower case */
  if (isupper(*chin))
    *chin = _tolower(*chin);
  /* tab */
  if (*chin == '\t')
    *chin = ' ';
} /* Lat_Nextch */


static void Lat_errorm(const char *cmnt, FILE *fi, FILE *fo, long *cc,
		       long *ll, long *errpos, long *lc, char *chin,
		       bool *skipflag, string *line,
		       struct LOC_Lat_Read *LINK)
{
  /*write(fo, ' ****')*/
  if (*cc > *errpos) {
    fprintf(fo, "%*c^%.80s", (int)(*cc - *errpos), ' ', cmnt);
    *errpos = *cc + 3;
  }
  while (!P_eof(fi))
    Lat_Nextch(fi, fo, cc, ll, errpos, lc, chin, skipflag, line, LINK);
  Lat_->conf.ErrFlag = true;
  abort_(LINK);
}


static void NextCh(struct LOC_Lat_GetSym *LINK)
{
  Lat_Nextch(LINK->fi, LINK->fo, LINK->cc, LINK->ll, LINK->errpos, LINK->lc,
	     LINK->chin, LINK->skipflag, LINK->line, LINK->LINK);
}


static void readscale(struct LOC_Lat_GetSym *LINK)
{
  long s, sign;

  /* readscale  */
  NextCh(LINK);
  while (*LINK->chin == ' ')
    NextCh(LINK);
  sign = 1;
  s = 0;
  if (*LINK->chin == '+')
    NextCh(LINK);
  else if (*LINK->chin == '-') {
    NextCh(LINK);
    sign = -1;
  }
  if (!isdigit(*LINK->chin))
    Lat_Error(40, LINK->fo, LINK->cc, LINK->errpos, LINK->LINK);
  else {
    do {
      s = s * 10 + *LINK->chin - '0';
      NextCh(LINK);
    }
    while (isdigit(*LINK->chin));
  }
  LINK->e += s * sign;
}


static void adjustscale(struct LOC_Lat_GetSym *LINK)
{
  long s;
  double d, t;

  /*  adjustscale  */
  if (LINK->k + LINK->e > LINK->emax_) {
    Lat_Error(21, LINK->fo, LINK->cc, LINK->errpos, LINK->LINK);
    return;
  }
  if (LINK->k + LINK->e < LINK->emin_) {
    *LINK->rnum = 0.0;
    return;
  }
  s = abs(LINK->e);
  t = 1.0;
  d = 10.0;
  do {
    while (!(s & 1)) {
      s /= 2;
      d *= d;
    }
    s--;
    t = d * t;
  }
  while (s != 0);

  if (LINK->e >= 0)
    *LINK->rnum *= t;
  else
    *LINK->rnum /= t;
}


static void Lat_GetSym(FILE *fi_, FILE *fo_, long *cc_, long *ll_,
		       long *errpos_, long *lc_, long *nkw, long *inum,
		       long emax__, long emin__, long kmax_, long nmax_,
		       char *chin_, char *id, double *rnum_, bool *skipflag_,
		       bool *rsvwd, string *line_, Lat_symbol *sym, alfa_ *key,
		       Lat_symbol *ksy, Lat_symbol *sps,
		       struct LOC_Lat_Read *LINK)
{  /*GetSym*/
  struct LOC_Lat_GetSym V;
  long                  i, j, mysign;
  bool                  parsename;

  const char empty_str[] = "               ";

  V.LINK = LINK;
  /*GetSym*/
  V.fi = fi_;
  V.fo = fo_;
  V.cc = cc_;
  V.ll = ll_;
  V.errpos = errpos_;
  V.lc = lc_;
  V.emax_ = emax__;
  V.emin_ = emin__;
  V.chin = chin_;
  V.rnum = rnum_;
  V.skipflag = skipflag_;
  V.line = line_;
  *rsvwd = false;
  mysign = 1;
  parsename = false;

 _L1:
  while (*V.chin == ' ')
    NextCh(&V);

  switch (*V.chin) {
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z':
  case '"':  /*identifier or wordsymbol*/
    V.k = 0;
    if (strlen(empty_str)+1 <= 2*sizeof(id))
      // memcpy(id, empty_str, sizeof(alfa_));
      strcpy(id, empty_str);
    else {
      printf("\nLat_GetSym: string length exceeded %lu (%lu)\n",
	     strlen(empty_str)+1, 2*sizeof(id));   
    exit(1);
    }
    do {
      if (*V.chin == '"')
	parsename = !parsename;
      if (V.k < NameLength) {
	V.k++; id[V.k-1] = *V.chin;
      } else {
	printf("Lat_GetSym: %s (%d)\n", id, NameLength);
	exit_(1);
      }
      NextCh(&V);
    } while (parsename || *V.chin == '_' || islower(*V.chin) ||
	     isdigit(*V.chin));

    /*writeln(fo, 'GetSym detected: id=', id);*/

    i = 1;
    j = *nkw;   /*binary search*/
    do {
      V.k = (i + j) / 2;
      if (strncmp(id, key[V.k-1], sizeof(alfa_)) <= 0)
	j = V.k - 1;
      if (strncmp(id, key[V.k-1], sizeof(alfa_)) >= 0)
	i = V.k + 1;
      /*  writeln(fo, '  binary: id=', id, '  key[', k:3, ']=', key[k],
	  'i=', i:4, ' j=', j:4, ' k=', k:4, ' i-1-j=', (i-1-j):4);*/
    }
    while (i <= j);
    if (i - 1 > j) {
      *sym = ksy[V.k-1]; *rsvwd = true;
      /*  writeln(fo, 'GetSym detected reserved word: id=', id,
	  '  k=', k:4, '  key[', k:4, ']=', key[k]);*/
    } else {
      if (!strncmp(id, "t              ", sizeof(alfa_)))
	*sym = tsym;
      else if (!strncmp(id, "gap            ", sizeof(alfa_)))
	*sym = gapsym;
      else if (!strncmp(id, "l              ", sizeof(alfa_)))
	*sym = lsym;
      else if (!strncmp(id, "n              ", sizeof(alfa_)))
	*sym = nsym;
      else if (!strncmp(id, "bobrho         ", sizeof(alfa_)))
	*sym = bobrhosym;
      else if (!strncmp(id, "bobrhov        ", sizeof(alfa_)))
	*sym = bobrhovsym;
      else if (!strncmp(id, "bobrhoh        ", sizeof(alfa_)))
	*sym = bobrhohsym;
      else if (!strncmp(id, "kxv            ", sizeof(alfa_)))
	*sym = kxvsym;
      else if (!strncmp(id, "kxh            ", sizeof(alfa_)))
	*sym = kxhsym;
      else if (!strncmp(id, "phi            ", sizeof(alfa_)))
	*sym = phisym;
      else if (!strncmp(id, "k              ", sizeof(alfa_)))
	*sym = ksym;
      else if (!strncmp(id, "harnum         ", sizeof(alfa_)))
	*sym = harnumsym;
      else
	*sym = ident;
    }
    break;

  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':  /*number*/
    V.k = 0;
    *inum = 0;
    *sym = intcon;
    do {
      *inum = *inum * 10 + *V.chin - '0';
      V.k++;
      NextCh(&V);
    }
    while (isdigit(*V.chin));
    if (V.k > kmax_ || *inum > nmax_) {
      Lat_Error(21, V.fo, V.cc, V.errpos, LINK);
      *inum = 0;
      V.k = 0;
    }
    if (*V.chin == '.') {
      NextCh(&V);
      if (*V.chin == '.')
	*V.chin = ':';
      else {
	*sym = realcon;
	*V.rnum = *inum;
	V.e = 0;
	while (isdigit(*V.chin)) {
	  V.e--;
	  *V.rnum = 10.0 * *V.rnum + *V.chin - '0';
	  NextCh(&V);
	}
	while (*V.chin == ' ')
	  NextCh(&V);
	if (V.e == 0)
	  Lat_Error(40, V.fo, V.cc, V.errpos, LINK);
	if (*V.chin == 'd' || *V.chin == 'D' || *V.chin == 'e' ||
	    *V.chin == 'E')
	  readscale(&V);
	if (V.e != 0)
	  adjustscale(&V);
      }
    } else {
      if (*V.chin == 'd' || *V.chin == 'D' || *V.chin == 'e' ||
	  *V.chin == 'E') {
	*sym = realcon;
	*V.rnum = *inum;
	V.e = 0;
	readscale(&V);
	if (V.e != 0)
	  adjustscale(&V);
      }
    }
    if (*sym == intcon)
      *inum *= mysign;
    else {
      if (*sym == realcon)
	*V.rnum = mysign * *V.rnum;
    }
    break;

  case ':':   /*, col*/
    NextCh(&V);
    if (*V.chin == '=') {
      *sym = becomes;
      NextCh(&V);
    }
    else
      *sym = colon;
    break;

  case '<':
    NextCh(&V);
    if (*V.chin == '=')
      {
	*sym = leq;
	NextCh(&V);
      }
    else {
      if (*V.chin == '>') {
	*sym = neq;
	NextCh(&V);
      }
      else
	*sym = lss;
    }
    break;

  case '>':
    NextCh(&V);
    if (*V.chin == '=') {
      *sym = geq;
      NextCh(&V);
    }
    else
      *sym = gtr;
    break;

  case '.':
    NextCh(&V);
    *sym = period_;
    break;

  case '*':
    NextCh(&V);
    if (*V.chin == '*') {
      *sym = pwrsym;
      NextCh(&V);
    }
    else
      *sym = times;
    break;

  case '{':
    do {
      NextCh(&V);
    }
    while (*V.chin != '}');
    NextCh(&V);
    goto _L1;
    break;

  case '+':
  case '-':
  case '/':
  case '(':
  case ')':
  case '=':
  case ',':
  case ';':
  case '[':
  case ']':
  case '\'':
    *sym = sps[(int)*V.chin];
    /* IF chin='+' THEN BEGIN nextch; goto 1 END ELSE
       IF chin='-' THEN BEGIN nextch; mysign:=-1; goto 1 END ELSE*/
    NextCh(&V);
    break;

  case '$':
  case '!':
  case '@':
  case '?':
  case '_':
  case '&':
  case '\\':
  case '^':
    Lat_Error(24L, V.fo, V.cc, V.errpos, LINK);
    NextCh(&V);
    goto _L1;
    break;

  default:
    Lat_Error(24L, V.fo, V.cc, V.errpos, LINK);
    NextCh(&V);
    goto _L1;
    break;
  }
}

static void Expression(struct LOC_Lat_EVAL *LINK);


static void GetSym(struct LOC_Lat_EVAL *LINK)
{
  /* reads next symbol  */
  Lat_GetSym(LINK->fi, LINK->fo, LINK->cc, LINK->ll, LINK->errpos, LINK->lc,
	     LINK->nkw, LINK->inum, LINK->emax_, LINK->emin_, LINK->kmax_,
	     LINK->nmax_, LINK->chin, LINK->id, LINK->rnum, LINK->skipflag,
	     LINK->rsvwd, LINK->line, LINK->sym, LINK->key, LINK->ksy,
	     LINK->sps, LINK->LINK);
}


static void errorm(const char *cmnt, struct LOC_Lat_EVAL *LINK)
{
  Lat_errorm(cmnt, LINK->fi, LINK->fo, LINK->cc, LINK->ll, LINK->errpos,
	     LINK->lc, LINK->chin, LINK->skipflag, LINK->line, LINK->LINK);
}

static void test(long *s1, const char *cmnt, struct LOC_Lat_EVAL *LINK)
{
  if (!P_inset(*LINK->sym, s1))
    errorm(cmnt, LINK);
}


static void getest(long *s1, const char *cmnt, struct LOC_Lat_EVAL *LINK)
{
  GetSym(LINK);
  if (!P_inset(*LINK->sym, s1))
    errorm(cmnt, LINK);
}


static double ArcSin(double x, struct LOC_Lat_EVAL *LINK)
{
  if (fabs(x) > 1e0)
    longjmp(LINK->_JL999, 1);
  if (x == 1e0)
    return (M_PI / 2e0);
  else if (x == -1e0)
    return (M_PI / -2e0);
  else
    return atan(x / sqrt(1e0 - x * x));
}


static double ArcCos(double x, struct LOC_Lat_EVAL *LINK)
{
  if (fabs(x) > 1e0)
    longjmp(LINK->_JL999, 1);
  if (x == 1e0)
    return 0e0;
  else if (x == -1e0)
    return M_PI;
  else
    return atan(sqrt(1e0 - x * x) / x);
}


static void writes(struct LOC_Lat_EVAL *LINK)
{
  /*writeln('PUSH:  s[', t:3, ']=', s[t]);*/
}


static void PUSH(double x, struct LOC_Lat_EVAL *LINK)
{
  LINK->t++;
  LINK->S.resize(LINK->t+1);
  LINK->S[LINK->t] = x;
  writes(LINK);
}


static double BlockLength(long ii, struct LOC_Lat_EVAL *LINK)
{
  long    k1, k2, k3;
  double  S;

  S = 0.0;
  if (ii == 0)
    return S;
  k2 = LINK->LINK->BlockS[ii-1].BSTART;
  k3 = LINK->LINK->BlockS[ii-1].BOWARI;
  for (k1 = k2 - 1; k1 < k3; k1++)
    S += (*ElemFam_)[LINK->LINK->Bstack[k1]-1].ElemF->PL;
  return S;
}

/* Local variables for Expression: */
struct LOC_Expression
{
  struct LOC_Lat_EVAL *LINK;
};

/* Local variables for Term: */
struct LOC_Term
{
  struct LOC_Expression *LINK;
};

/* Local variables for Factor: */
struct LOC_Factor
{
  struct LOC_Term *LINK;
  long i;
};


static double GetKparm(long direction, struct LOC_Factor *LINK)
{
  double Result;
  symset SET;

  getest(P_expset(SET, 1 << ((long)lbrack)), "<[> expected",
	 LINK->LINK->LINK->LINK);
  GetSym(LINK->LINK->LINK->LINK);
  Expression(LINK->LINK->LINK->LINK);
  test(P_expset(SET, 1 << ((long)rbrack)), "<]> expected",
       LINK->LINK->LINK->LINK);
  if (direction == 1)
    Result =
      dynamic_cast<MpoleType*>((*ElemFam_)[LINK->i-1].ElemF)
      ->PBpar[(long)((long)LINK->LINK->LINK->LINK
		    ->S[LINK->LINK->LINK->LINK->t])+HOMmax];
  else
    Result =
      dynamic_cast<MpoleType*>((*ElemFam_)[LINK->i-1].ElemF)
      ->PBpar[HOMmax-(long)LINK->LINK->LINK->LINK
	      ->S[LINK->LINK->LINK->LINK->t]];
  LINK->LINK->LINK->LINK->t--;
  LINK->LINK->LINK->LINK->S.resize(LINK->LINK->LINK->LINK->t+1);
  /* GetSym;*/
  return Result;
}


static void Factor(struct LOC_Term *LINK)
{
  struct LOC_Factor V;
  double x = 0.0;
  partsName fname;
  long SET[(long)period_ / 32 + 2];
  ElemType *WITH;
  MpoleType *WITH1;
  symset SET1;
  long SET2[(long)lsym / 32 + 2];

  V.LINK = LINK;
  /* factor */
  if (!P_inset(*LINK->LINK->LINK->sym, LINK->LINK->LINK->facbegsys))
    longjmp(LINK->LINK->LINK->_JL999, 1);
  /*while sym in facbegsys do*/
  if (*LINK->LINK->LINK->sym == ident) {  /*1:  of ident */
    V.i = CheckUDItable(LINK->LINK->LINK->id, LINK->LINK->LINK->LINK);
    if (V.i != 0) {   /* UDI */
      x = LINK->LINK->LINK->LINK->UDItable[V.i-1].Uvalue;
      PUSH(x, LINK->LINK->LINK);
      GetSym(LINK->LINK->LINK);
    } else {
      V.i = CheckElementtable(LINK->LINK->LINK->id, LINK->LINK->LINK->LINK);
      if (V.i != 0) {
	getest(P_addset(P_expset(SET, 0), (long)period_), "<.> expected",
	       LINK->LINK->LINK);
	/*--> new */
	GetSym(LINK->LINK->LINK);
	if (strlen(LINK->LINK->LINK->id)+1 <= 2*sizeof(fname))
	  // memcpy(fname, LINK->LINK->LINK->id, sizeof(alfa_));
	  // memset(fname+sizeof(alfa_), ' ', sizeof(partsName)-sizeof(alfa_));
	  strcpy(fname, LINK->LINK->LINK->id);
        else {
	  printf("\n: string length exceeded %lu (%lu)\n",
		 strlen(LINK->LINK->LINK->id)+1, 2*sizeof(fname));   
	  exit(1);
	}
	WITH = (*ElemFam_)[V.i-1].ElemF;
	WITH1 = dynamic_cast<MpoleType*>(WITH);
	if (!strncmp(fname, "l              ", sizeof(partsName)))
	  x = WITH->PL;
	else if (!strncmp(fname, "t              ", sizeof(partsName))) {
	  if (WITH->PL != 0.0)
	    x = radtodeg(WITH1->Pirho*WITH->PL);
	  else
	    x = radtodeg(WITH1->Pirho);
	} else if (!strncmp(fname, "t1             ", sizeof(partsName)))
	  x = WITH1->PTx1;
	else if (!strncmp(fname, "t2             ", sizeof(partsName)))
	  x = WITH1->PTx2;
	else if (!strncmp(fname, "gap            ", sizeof(partsName)))
	  x = WITH1->Pgap;
	else if (!strncmp(fname, "roll           ", sizeof(partsName))) {
	  if (WITH->Pkind == Mpole)
	    x = WITH1->PdTpar;
	  else if (WITH->Pkind == Wigl)
	    x = WITH1->PdTpar;
	} else if (!strncmp(fname, "n              ", sizeof(partsName))) {
	  if (((1 << ((long)WITH->Pkind)) &
	       ((1 << ((long)Mpole)) | (1 << ((long)Wigl)))) != 0)
	    x = WITH1->PN;
	} else if (!strncmp(fname, "b              ", sizeof(partsName)))
	  x = GetKparm(1, &V);
	else if (!strncmp(fname, "a              ", sizeof(partsName)))
	  x = GetKparm(2L, &V);
	else {
	  /* error detected */
	  getest(P_expset(SET1, 0), "  illegal extension...",
		 LINK->LINK->LINK);
	}
	PUSH(x, LINK->LINK->LINK);
	GetSym(LINK->LINK->LINK);
      } else {
	V.i = CheckBLOCKStable(LINK->LINK->LINK->id, LINK->LINK->LINK->LINK);
	if (V.i != 0) {
	  getest(P_addset(P_expset(SET, 0), (long)period_), "<.> expected",
		 LINK->LINK->LINK);
	  getest(P_addset(P_expset(SET2, 0), (long)lsym), "illegal component",
		 LINK->LINK->LINK);
	  x = BlockLength(V.i, LINK->LINK->LINK);
	  PUSH(x, LINK->LINK->LINK);
	  GetSym(LINK->LINK->LINK);
	} else {  /*4: function ?*/
	  if (strlen(LINK->LINK->LINK->id)+1 <= 2*sizeof(fname))
	    // memcpy(fname, LINK->LINK->LINK->id, sizeof(alfa_));
	    // memset(fname+sizeof(alfa_), ' ', sizeof(partsName)-sizeof(alfa_));
	    strcpy(fname, LINK->LINK->LINK->id);
	  else {
	    printf("\n: string length exceeded %lu (%lu)\n",
		   strlen(LINK->LINK->LINK->id)+1, 2*sizeof(fname));   
	    exit(1);
	  }
	  GetSym(LINK->LINK->LINK);
	  switch (*LINK->LINK->LINK->sym) {   /*5*/

	  case semicolon:
	    GetSym(LINK->LINK->LINK);
	    break;

	  case lparent:  /*6: of lparent*/
	    GetSym(LINK->LINK->LINK);
	    Expression(LINK->LINK->LINK);
	    if (!strncmp(fname, "sin            ", sizeof(partsName)))
	      LINK->LINK->LINK->S[LINK->LINK->LINK->t] =
		sin(LINK->LINK->LINK->S[LINK->LINK->LINK->t]);
	    else if (!strncmp(fname, "cos            ", sizeof(partsName)))
	      LINK->LINK->LINK->S[LINK->LINK->LINK->t] =
		cos(LINK->LINK->LINK->S[LINK->LINK->LINK->t]);
	    else if (!strncmp(fname, "tan            ", sizeof(partsName)))
	      LINK->LINK->LINK->S[LINK->LINK->LINK->t] =
		tan(LINK->LINK->LINK->S[LINK->LINK->LINK->t]);
	    else if (!strncmp(fname, "arcsin         ", sizeof(partsName)))
	      LINK->LINK->LINK->S[LINK->LINK->LINK->t] =
		ArcSin(LINK->LINK->LINK->S[LINK->LINK->LINK->t],
		       LINK->LINK->LINK);
	    else if (!strncmp(fname, "arccos         ", sizeof(partsName)))
	      LINK->LINK->LINK->S[LINK->LINK->LINK->t] =
		ArcCos(LINK->LINK->LINK->S[LINK->LINK->LINK->t],
		       LINK->LINK->LINK);
	    else if (!strncmp(fname, "arctan         ", sizeof(partsName)))
	      LINK->LINK->LINK->S[LINK->LINK->LINK->t] =
		atan(LINK->LINK->LINK->S[LINK->LINK->LINK->t]);
	    else if (!strncmp(fname, "sqrt           ", sizeof(partsName)))
	      LINK->LINK->LINK->S[LINK->LINK->LINK->t] =
		sqrt(LINK->LINK->LINK->S[LINK->LINK->LINK->t]);
	    else if (!strncmp(fname, "log            ", sizeof(partsName)))
	      LINK->LINK->LINK->S[LINK->LINK->LINK->t] =
		log(LINK->LINK->LINK->S[LINK->LINK->LINK->t]);
	    else if (!strncmp(fname, "exp            ", sizeof(partsName)))
	      LINK->LINK->LINK->S[LINK->LINK->LINK->t] =
		exp(LINK->LINK->LINK->S[LINK->LINK->LINK->t]);
	    writes(LINK->LINK->LINK);
	    if (*LINK->LINK->LINK->sym == rparent)
	      GetSym(LINK->LINK->LINK);
	    else
	      longjmp(LINK->LINK->LINK->_JL999, 1);
	    break;
	    /*6:of lparent*/
	  default:
	    break;
	  }/*5: of case */
	}  /*4: of function?*/
      }
    }
  }  /*1: of ident*/
  else if (*LINK->LINK->LINK->sym == realcon) {
    PUSH(*LINK->LINK->LINK->rnum, LINK->LINK->LINK);
    GetSym(LINK->LINK->LINK);
  } else if (*LINK->LINK->LINK->sym == intcon) {
    x = *LINK->LINK->LINK->inum;
    PUSH(x, LINK->LINK->LINK);
    GetSym(LINK->LINK->LINK);
  } else if (*LINK->LINK->LINK->sym == lparent) {
    GetSym(LINK->LINK->LINK);
    Expression(LINK->LINK->LINK);
    if (*LINK->LINK->LINK->sym == rparent)
      GetSym(LINK->LINK->LINK);
    else
      longjmp(LINK->LINK->LINK->_JL999, 1);
  } else
    longjmp(LINK->LINK->LINK->_JL999, 1);

  if (*LINK->LINK->LINK->sym != pwrsym)
    return;

  GetSym(LINK->LINK->LINK);
  if (*LINK->LINK->LINK->sym != intcon)
    longjmp(LINK->LINK->LINK->_JL999, 1);
  LINK->LINK->LINK->S[LINK->LINK->LINK->t] =
    pow(LINK->LINK->LINK->S[LINK->LINK->LINK->t],
	(double)(*LINK->LINK->LINK->inum));
  GetSym(LINK->LINK->LINK);
}


static void Term(struct LOC_Expression *LINK)
{
  struct LOC_Term V;
  Lat_symbol mulop;

  V.LINK = LINK;
  /* term */
  Factor(&V);
  while ((unsigned int)(*LINK->LINK->sym) < 32 &&
	 ((1 << ((long)(*LINK->LINK->sym))) &
	  ((1 << ((long)times)) | (1 << ((long)rdiv)))) != 0) {
    mulop = *LINK->LINK->sym;
    GetSym(LINK->LINK);
    Factor(&V);
    if (mulop == times) {
      LINK->LINK->S[LINK->LINK->t-1] *= LINK->LINK->S[LINK->LINK->t];
      LINK->LINK->t--;
      LINK->LINK->S.resize(LINK->LINK->t+1);
      writes(LINK->LINK);
    } else {
      if (mulop == rdiv) {
	LINK->LINK->S[LINK->LINK->t-1] /= LINK->LINK->S[LINK->LINK->t];
	LINK->LINK->t--;
	LINK->LINK->S.resize(LINK->LINK->t+1);
	writes(LINK->LINK);
      }
    }
  }
}


static void Expression(struct LOC_Lat_EVAL *LINK)
{
  struct LOC_Expression V;
  Lat_symbol addop;

  V.LINK = LINK;
  /* Expression */
  if ((unsigned int)(*LINK->sym) < 32 &&
      ((1 << ((long)(*LINK->sym))) &
       ((1 << ((long)plus_)) | (1 << ((long)minus_)))) != 0) {
    addop = *LINK->sym;
    GetSym(LINK);
    Term(&V);
    if (addop == minus_)
      LINK->S[LINK->t] = -LINK->S[LINK->t];
  } else
    Term(&V);

  while ((unsigned int)(*LINK->sym) < 32 &&
	 ((1 << ((long)(*LINK->sym))) &
	  ((1 << ((long)plus_)) | (1 << ((long)minus_)))) != 0) {
    addop = *LINK->sym;
    GetSym(LINK);
    Term(&V);
    if (addop == plus_) {
      LINK->S[LINK->t-1] += LINK->S[LINK->t];
      LINK->t--;
      LINK->S.resize(LINK->t+1);
      writes(LINK);
    } else {
      if (addop == minus_) {
	LINK->S[LINK->t-1] -= LINK->S[LINK->t];
	LINK->t--;
	LINK->S.resize(LINK->t+1);
	writes(LINK);
      }
    }
  }
}

/******************************
 *                           *
 *        E V A L            *
 *                           *
 ******************************/

static double Lat_EVAL(FILE *fi_, FILE *fo_, long *cc_, long *ll_,
		       long *errpos_,
		       long *lc_, long *nkw_, long *inum_, long emax__,
		       long emin__,
		       long kmax__, long nmax__, char *chin_, char *id_,
		       double *rnum_,
		       bool *skipflag_, bool *rsvwd_, string *line_,
		       Lat_symbol *sym_,
		       alfa_ *key_, Lat_symbol *ksy_, Lat_symbol *sps_,
		       struct LOC_Lat_Read *LINK)
{  /* eval */
  struct LOC_Lat_EVAL V;
  double Result = 0.0;
  symset SET;

  V.LINK = LINK;
  V.fi = fi_;
  V.fo = fo_;
  V.cc = cc_;
  V.ll = ll_;
  V.errpos = errpos_;
  V.lc = lc_;
  V.nkw = nkw_;
  V.inum = inum_;
  V.emax_ = emax__;
  V.emin_ = emin__;
  V.kmax_ = kmax__;
  V.nmax_ = nmax__;
  V.chin = chin_;
  V.id = id_;
  V.rnum = rnum_;
  V.skipflag = skipflag_;
  V.rsvwd = rsvwd_;
  V.line = line_;
  V.sym = sym_;
  V.key = key_;
  V.ksy = ksy_;
  V.sps = sps_;
  if (setjmp(V._JL999))
    goto _L999;
  P_addset(P_expset(V.facbegsys, 0), (long)intcon);
  P_addset(V.facbegsys, (long)realcon);
  P_addset(V.facbegsys, (long)ident);
  P_addset(V.facbegsys, (long)lparent);
  GetSym(&V);
  V.t = 0;
  Expression(&V);
  if (V.t != 1)
    goto _L999;
  Result = V.S[1];
  goto _L888;

 _L999:
  Lat_->conf.ErrFlag = true;
  test(P_expset(SET, 0), "** Lat_Eval: error",
       &V);
 _L888:   /* exit */

  return Result;
}


static void GetBlock(struct LOC_Lat_ProcessBlockInput *LINK);


static void errorm_(const char *cmnt, struct LOC_Lat_ProcessBlockInput *LINK)
{
  Lat_errorm(cmnt, LINK->fi, LINK->fo, LINK->cc, LINK->ll, LINK->errpos,
	     LINK->lc, LINK->chin, LINK->skipflag, LINK->line, LINK->LINK);
}


static void GetSym_(struct LOC_Lat_ProcessBlockInput *LINK)
{
  Lat_GetSym(LINK->fi, LINK->fo, LINK->cc, LINK->ll, LINK->errpos, LINK->lc,
	     LINK->nkw, LINK->inum, LINK->emax_, LINK->emin_, LINK->kmax_,
	     LINK->nmax_, LINK->chin, LINK->id, LINK->rnum, LINK->skipflag,
	     LINK->rsvwd, LINK->line, LINK->sym, LINK->key, LINK->ksy,
	     LINK->sps, LINK->LINK);
}


static void test_(long *s1, const char *cmnt,
		  struct LOC_Lat_ProcessBlockInput *LINK)
{
  /*test*/
  if (!P_inset(*LINK->sym, s1))
    errorm_(cmnt, LINK);
}


static void getest_(long *s1, const char *cmnt,
		    struct LOC_Lat_ProcessBlockInput *LINK)
{
  /*test*/
  GetSym_(LINK);
  if (!P_inset(*LINK->sym, s1))
    errorm_(cmnt, LINK);
}


double EVAL(struct LOC_Lat_ProcessBlockInput *LINK)
{
  return (Lat_EVAL(LINK->fi, LINK->fo, LINK->cc, LINK->ll, LINK->errpos,
		   LINK->lc, LINK->nkw, LINK->inum, LINK->emax_, LINK->emin_,
		   LINK->kmax_, LINK->nmax_, LINK->chin, LINK->id, LINK->rnum,
		   LINK->skipflag, LINK->rsvwd, LINK->line, LINK->sym,
		   LINK->key, LINK->ksy, LINK->sps, LINK->LINK));
}


static void DeBlock(long ii, long k4, struct LOC_Lat_ProcessBlockInput *LINK)
{
  long  k1, k2, k3, k5;

  k2 = LINK->LINK->BlockS[ii-1].BSTART;
  k3 = LINK->LINK->BlockS[ii-1].BOWARI;
  for (k5 = 1; k5 <= k4; k5++) {
    for (k1 = k2 - 1; k1 < k3; k1++) {  /*11*/
      LINK->LINK->Bpointer++;
      LINK->LINK->Bstack.resize(LINK->LINK->Bpointer);
      LINK->LINK->Reverse_stack.resize(LINK->LINK->Bpointer);
      LINK->LINK->Bstack[LINK->LINK->Bpointer-1] = LINK->LINK->Bstack[k1];
      LINK->LINK->Reverse_stack[LINK->LINK->Bpointer-1] =
	LINK->LINK->Reverse_stack[k1];
    }  /*11*/
  }
  GetSym_(LINK);
  if (*LINK->sym == comma)
    GetSym_(LINK);
}

/* Local variables for GetBlock: */
struct LOC_GetBlock
{
  struct LOC_Lat_ProcessBlockInput *LINK;
};


static void InsideParent(long k4, struct LOC_GetBlock *LINK)
{
  long    b, b1, b2, k1;
  symset  SET;

  b1 = LINK->LINK->LINK->Bpointer + 1;
  GetSym_(LINK->LINK);
  GetBlock(LINK->LINK);
  b2 = LINK->LINK->LINK->Bpointer;
  if (k4 >= 2) {
    for (k1 = 2; k1 <= k4; k1++) {
      for (b = b1 - 1; b < b2; b++) {
	LINK->LINK->LINK->Bpointer++;
	LINK->LINK->LINK->Bstack.resize(LINK->LINK->LINK->Bpointer);
	LINK->LINK->LINK->Reverse_stack.resize(LINK->LINK->LINK->Bpointer);
	LINK->LINK->LINK->Bstack[LINK->LINK->LINK->Bpointer-1] =
	  LINK->LINK->LINK->Bstack[b];
	LINK->LINK->LINK->Reverse_stack[LINK->LINK->LINK->Bpointer-1] =
	  LINK->LINK->LINK->Reverse_stack[b];
      }
    }
  }
  test_(P_expset(SET, 1 << ((long)rparent)), "<)> expected",
	LINK->LINK);
  getest_(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon)) |
		   (1 << ((long)rparent))), "<, > or <;> expected",
	  LINK->LINK);
  if (*LINK->LINK->sym == comma)
    GetSym_(LINK->LINK);
}


static void Doinverse(struct LOC_GetBlock *LINK)
{
  bool    rev;
  long    b, b1, b2, k1 = 0, block_no, n_elem, tmp;
  symset  SET;

  getest_(P_expset(SET, 1 << ((long)lparent)), "<(> expected after INV",
	  LINK->LINK);
  b1 = LINK->LINK->LINK->Bpointer + 1;
  GetSym_(LINK->LINK);
  GetBlock(LINK->LINK);
  b2 = LINK->LINK->LINK->Bpointer;
  if (debug) printf("\n  Doinverse: b2-b1+1 = %ld\n", b2-b1+1);
  /* Bug fix: INV(A, B, ...) for 2 elements
  n_elem = b2 - b1 */
  n_elem = b2 - b1 + 1;
  if (n_elem >= 2) {
    /* Bug fix: INV(A, B, ...) for 2 elements
    for (b = b1-1; b < b1+n_elem/2; b++) { */
    for (b = b1-1; b < b1+n_elem/2-1; b++) {
      tmp = LINK->LINK->LINK->Bstack[b];
      LINK->LINK->LINK->Bstack[b] = LINK->LINK->LINK->Bstack[b2-k1-1];
      LINK->LINK->LINK->Bstack[b2-k1-1] = tmp;

      rev = LINK->LINK->LINK->Reverse_stack[b];
      LINK->LINK->LINK->Reverse_stack[b] =
	!LINK->LINK->LINK->Reverse_stack[b2-k1-1];
      LINK->LINK->LINK->Reverse_stack[b2-k1-1] = !rev;

      if (debug) {
	block_no =
	  CheckBLOCKStable(
	    LINK->LINK->LINK->BlockS[LINK->LINK->LINK->NoB-1].Bname,
	    LINK->LINK->LINK);
	printf("  Doinverse:       |%s| 2%ld %2ld %2ld %1d %2ld %1d\n",
	       LINK->LINK->LINK->BlockS[LINK->LINK->LINK->NoB-1].Bname,
	       block_no, LINK->LINK->LINK->NoB,
	       LINK->LINK->LINK->Bstack[b],
	       LINK->LINK->LINK->Reverse_stack[b],
	       LINK->LINK->LINK->Bstack[b2-k1-1],
	       LINK->LINK->LINK->Reverse_stack[b2-k1-1]);
      }

      k1++;
    }
  }
  if (n_elem % 2 == 1) {
    // If odd number of elements.
    LINK->LINK->LINK->Reverse_stack[b2-k1-1] =
      !LINK->LINK->LINK->Reverse_stack[b2-k1-1];
    if (debug) {
      block_no =
	CheckBLOCKStable(
	  LINK->LINK->LINK->BlockS[LINK->LINK->LINK->NoB-1].Bname,
	  LINK->LINK->LINK);
      printf("  Doinverse (odd): |%s| 2%ld %2ld %2ld %1d\n",
	     LINK->LINK->LINK->BlockS[LINK->LINK->LINK->NoB-1].Bname,
	     block_no, LINK->LINK->LINK->NoB,
	     LINK->LINK->LINK->Bstack[b2-k1-1],
	     LINK->LINK->LINK->Reverse_stack[b2-k1-1]);
    }
  }
  test_(P_expset(SET, 1 << ((long)rparent)), "<)> expected", LINK->LINK);
  getest_(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon)) |
		   (1 << ((long)rparent))), "<, > or <;> expected",
	  LINK->LINK);
  if (*LINK->LINK->sym == comma) GetSym_(LINK->LINK);
}


static void GetBlock(struct LOC_Lat_ProcessBlockInput *LINK)
{
  struct  LOC_GetBlock V;
  long    i, ii, k1, k4 = 0;
  long    SET[(long)invsym / 32 + 2];
  symset  SET1;

  V.LINK = LINK;
  do {   /*7*/
    P_addset(P_expset(SET, 0), (long)ident);
    P_addset(SET, (long)intcon);
    P_addset(SET, (long)lparent);
    test_(P_addset(SET, (long)invsym),
	  "<Element/Block name>, <integer>, <INV> or <(> expected",
	  LINK);
    if (*LINK->sym == lparent)   /*7*/
      InsideParent(1, &V);
    else {
      if (*LINK->sym == invsym)
	Doinverse(&V);
      else {
	if (*LINK->sym == ident) {  /*8*/
	  i = CheckElementtable(LINK->id, LINK->LINK);
	  if (i != 0) {  /*9*/
	    LINK->LINK->Bpointer++;
	    LINK->LINK->Bstack.resize(LINK->LINK->Bpointer);
	    LINK->LINK->Reverse_stack.resize(LINK->LINK->Bpointer);
	    LINK->LINK->Bstack[LINK->LINK->Bpointer-1] = i;
	    LINK->LINK->Reverse_stack[LINK->LINK->Bpointer-1] = false;
	    GetSym_(LINK);
	    if (*LINK->sym == comma)
	      GetSym_(LINK);
	  } else {  /*9*/
	    ii = CheckBLOCKStable(LINK->id, LINK->LINK);
	    if (ii != 0) {  /*10*/
	      DeBlock(ii, 1, LINK);
	    } else {  /*10*/
	      ii = CheckUDItable(LINK->id, LINK->LINK);
	      if (ii != 0) {  /*11*/
		k4 = (long)floor(LINK->LINK->UDItable[ii-1].Uvalue + 0.5);
		GetSym_(LINK);
	      } else
		test_(P_expset(SET1, 0), "invalid identifier",
		      LINK);
	      /*11*/
	      test_(P_expset(SET1, 1 << ((long)times)), "<*> expected",
		    LINK);
	      if (*LINK->sym == times) {  /*11*/
		P_addset(P_expset(SET, 0), (long)ident);
		P_addset(SET, (long)lparent);
		getest_(P_addset(SET, (long)invsym),
			"<element/Block name>, <INV> or <(> expected",
			LINK);
		if (*LINK->sym == lparent)
		  InsideParent(k4, &V);
		else {
		  if (*LINK->sym == invsym)
		    Doinverse(&V);
		  else {
		    if (*LINK->sym == ident) {  /*12*/
		      i = CheckElementtable(LINK->id, LINK->LINK);
		      if (i != 0) {  /*13*/
			for (k1 = 1; k1 <= k4; k1++) {  /*14*/
			  LINK->LINK->Bpointer++;
			  LINK->LINK->Bstack.resize(LINK->LINK->Bpointer);
			  LINK->LINK->Reverse_stack.resize
			    (LINK->LINK->Bpointer);
			  LINK->LINK->Bstack[LINK->LINK->Bpointer-1] = i;
			  LINK->LINK->Reverse_stack[LINK->LINK->Bpointer-1] =
			    false;
			}  /*14*/
			GetSym_(LINK);
			if (*LINK->sym == comma)
			  GetSym_(LINK);
		      } else {  /*13*/
			ii = CheckBLOCKStable(LINK->id, LINK->LINK);
			if (ii == 0)
			  test_(P_expset(SET1, 0), "invalid name",
				LINK);
			DeBlock(ii, k4, LINK);
		      }  /*13*/
		    }  /*12*/
		  }
		}
	      }  /*11*/
	    }  /*10*/
	  }  /*9*/
	} else {
	  if (*LINK->sym == intcon) {  /*8*/
	    k4 = *LINK->inum;
	    GetSym_(LINK);
	    test_(P_expset(SET1, 1 << ((long)times)), "<*> expected",
		  LINK);
	    if (*LINK->sym == times) {  /*9*/
	      GetSym_(LINK);
	      P_addset(P_expset(SET, 0), (long)ident);
	      P_addset(SET, (long)lparent);
	      test_(P_addset(SET, (long)invsym),
		    "<element/Block name>, <INV> or <(> expected",
		    LINK);
	      if (*LINK->sym == lparent)
		InsideParent(k4, &V);
	      else {
		if (*LINK->sym == invsym)
		  Doinverse(&V);
		else {
		  if (*LINK->sym == ident) {  /*10*/
		    i = CheckElementtable(LINK->id, LINK->LINK);
		    if (i != 0) {  /*11*/
		      for (k1 = 1; k1 <= k4; k1++) {  /*12*/
			LINK->LINK->Bpointer++;
			LINK->LINK->Bstack.resize(LINK->LINK->Bpointer);
			LINK->LINK->Reverse_stack.resize(LINK->LINK->Bpointer);
			LINK->LINK->Bstack[LINK->LINK->Bpointer-1] = i;
			LINK->LINK->Reverse_stack[LINK->LINK->Bpointer-1] =
			  false;
		      }  /*12*/
		      GetSym_(LINK);
		      if (*LINK->sym == comma)
			GetSym_(LINK);
		    } else {  /*11*/
		      ii = CheckBLOCKStable(LINK->id, LINK->LINK);
		      if (ii == 0)
			test_(P_expset(SET1, 0), "invalid name",
			      LINK);
		      DeBlock(ii, k4, LINK);
		    }  /*11*/
		  }  /*10*/
		}
	      }
	    }  /*9*/
	  } else {
	    if (*LINK->sym == minus_) {  /*8*/
	      GetSym_(LINK);
	      i = CheckElementtable(LINK->id, LINK->LINK);
	      if (i != 0) {  /*9*/
		LINK->LINK->Bpointer++;
		LINK->LINK->Bstack.resize(LINK->LINK->Bpointer);
		LINK->LINK->Reverse_stack.resize(LINK->LINK->Bpointer);
		LINK->LINK->Bstack[LINK->LINK->Bpointer-1] = -i;
		LINK->LINK->Reverse_stack[LINK->LINK->Bpointer-1] = false;
		GetSym_(LINK);
		if (*LINK->sym == comma)
		  GetSym_(LINK);
	      } else
		test_(P_expset(SET1, 0), "<element name> expected.",
		      LINK);
	    }  /*8*/
	  }
	}
      }
    }
  } while (*LINK->sym == (long)invsym || *LINK->sym == (long)minus_ ||
	   *LINK->sym == (long)intcon || *LINK->sym == (long)ident);
}


static void Lat_ProcessBlockInput(FILE *fi_, FILE *fo_, long *cc_, long *ll_,
				  long *errpos_, long *lc_, long *nkw_,
				  long *inum_, long emax__, long emin__,
				  long kmax__, long nmax__, char *chin_,
				  char *id_, char *BlockName,
				  double *rnum_, bool *skipflag_, bool *rsvwd_,
				  string *line_,
				  Lat_symbol *sym_, alfa_ *key_,
				  Lat_symbol *ksy_, Lat_symbol *sps_,
				  struct LOC_Lat_Read *LINK)
{
  struct LOC_Lat_ProcessBlockInput V;
  long i;
  symset SET;
  _REC_BlockStype *WITH;

  V.LINK = LINK;
  V.fi = fi_;
  V.fo = fo_;
  V.cc = cc_;
  V.ll = ll_;
  V.errpos = errpos_;
  V.lc = lc_;
  V.nkw = nkw_;
  V.inum = inum_;
  V.emax_ = emax__;
  V.emin_ = emin__;
  V.kmax_ = kmax__;
  V.nmax_ = nmax__;
  V.chin = chin_;
  V.id = id_;
  V.rnum = rnum_;
  V.skipflag = skipflag_;
  V.rsvwd = rsvwd_;
  V.line = line_;
  V.sym = sym_;
  V.key = key_;
  V.ksy = ksy_;
  V.sps = sps_;
  i = CheckElementtable(BlockName, LINK);
  if (i != 0) {
    test_(P_expset(SET, 0), "<Block name>: conflict with Element name", &V);
    return;
  }
  /* Increment number of defined blocks */
  
  LINK->NoB++;
  LINK->BlockS.resize(LINK->NoB);
  WITH = &LINK->BlockS[LINK->NoB-1];
  if (strlen(BlockName)+1 <= 2*sizeof(WITH->Bname))
    // memcpy(WITH->Bname, BlockName, sizeof(partsName));
    strcpy(WITH->Bname, BlockName);
  else {
    printf("\n: string length exceeded %lu (%lu)\n",
	   strlen(BlockName)+1, 2*sizeof(WITH->Bname));   
    exit(1);
  }
  WITH->BSTART = LINK->Bpointer + 1;
  GetBlock(&V);
  test_(P_expset(SET, 1 << ((long)semicolon)), "<;> expected", &V);
  GetSym_(&V);
  WITH->BOWARI = LINK->Bpointer;
}  /* ProcessBlockInput */


static bool Lat_CheckWiggler(FILE *fo, long i, struct LOC_Lat_Read *LINK)
{
  double       a, Lambda, L, diff;
  long         NN;
  ElemType     *WITH1;
  WigglerType  *WITH2;

  WITH1 = (*ElemFam_)[i-1].ElemF;
  WITH2 = dynamic_cast<WigglerType*>(WITH1);
  Lambda = WITH2->Lambda;
  L = WITH1->PL; a = L/Lambda;
  NN = (long)floor(a+0.01+0.5);
  diff = fabs((L-NN*Lambda)/L);
  if (diff < 1e-5) return true;
  printf("\nLat_CheckWiggler: >>> Incorrect definition of %.*s\n\n",
	 NameLength, WITH1->Name.c_str());
  printf("    L      ( total length ) =%20.12f [m]\n", L);
  printf("    Lambda ( wave  length ) =%20.12f [m]\n", Lambda);
  printf("    # of Period = L/Lambda  =%20.12f ?????\n\n", L / Lambda);
  return true;
}

/* Local variables for Lat_DealElement: */

static void errorm__(const char *cmnt, struct LOC_Lat_DealElement *LINK)
{
  Lat_errorm(cmnt, LINK->fi, LINK->fo, LINK->cc, LINK->ll, LINK->errpos,
	     LINK->lc, LINK->chin, LINK->skipflag, LINK->line, LINK->LINK);
}


static void GetSym__(struct LOC_Lat_DealElement *LINK)
{
  Lat_GetSym(LINK->fi, LINK->fo, LINK->cc, LINK->ll, LINK->errpos, LINK->lc,
	     LINK->nkw, LINK->inum, LINK->emax_, LINK->emin_, LINK->kmax_,
	     LINK->nmax_, LINK->chin, LINK->id, LINK->rnum, LINK->skipflag,
	     LINK->rsvwd, LINK->line, LINK->sym, LINK->key, LINK->ksy,
	     LINK->sps, LINK->LINK);
}

static void test__(long *s1, const char *cmnt, struct LOC_Lat_DealElement *LINK)
{
  /*test*/
  if (!P_inset(*LINK->sym, s1))
    errorm__(cmnt, LINK);
}


static void getest__(long *s1, const char *cmnt,
		     struct LOC_Lat_DealElement *LINK)
{
  /*test*/
  GetSym__(LINK);
  if (!P_inset(*LINK->sym, s1))
    errorm__(cmnt, LINK);
}


static double EVAL_(struct LOC_Lat_DealElement *LINK)
{
  return Lat_EVAL(LINK->fi, LINK->fo, LINK->cc, LINK->ll, LINK->errpos,
		  LINK->lc, LINK->nkw, LINK->inum, LINK->emax_, LINK->emin_,
		  LINK->kmax_, LINK->nmax_, LINK->chin, LINK->id, LINK->rnum,
		  LINK->skipflag, LINK->rsvwd, LINK->line, LINK->sym,
		  LINK->key, LINK->ksy, LINK->sps, LINK->LINK);
}

static void ProcessBlockInput(struct LOC_Lat_DealElement *LINK)
{
  Lat_ProcessBlockInput(LINK->fi, LINK->fo, LINK->cc, LINK->ll, LINK->errpos,
			LINK->lc, LINK->nkw, LINK->inum, LINK->emax_,
			LINK->emin_, LINK->kmax_, LINK->nmax_, LINK->chin,
			LINK->id, LINK->BlockName, LINK->rnum, LINK->skipflag,
			LINK->rsvwd, LINK->line, LINK->sym, LINK->key,
			LINK->ksy, LINK->sps, LINK->LINK);
}  /* ProcessBlockInput */


static void CheckWiggler(long i, struct LOC_Lat_DealElement *LINK)
{
  if (!Lat_CheckWiggler(LINK->fo, i, LINK->LINK))
    longjmp(LINK->_JL9999, 1);
}

static void GetHOM(struct LOC_Lat_DealElement *LINK)
{
  long    i;
  double  x, y;
  symset  SET;

  getest__(P_expset(SET, 1 << ((long)lparent)), "<(> expected", LINK);
  do {
    i = (long)floor(EVAL_(LINK) + 0.5);
    if (i < 1 || HOMmax < i)
      getest__(P_expset(SET, 0), "invalid value detected", LINK);
    test__(P_expset(SET, 1 << ((long)comma)), "<, > expected", LINK);
    x = EVAL_(LINK);
    test__(P_expset(SET, 1 << ((long)comma)), "<, > expected", LINK);
    y = EVAL_(LINK);
    LINK->B[i+HOMmax] = x; LINK->B[HOMmax-i] = y;
    LINK->BA[i+HOMmax] = true; LINK->BA[HOMmax-i] = true;
    test__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)rparent))),
	   "<, > or <)> expected", LINK);
  } while (*LINK->sym != rparent);
  GetSym__(LINK);
}


static void ClearHOMandDBN(struct LOC_Lat_DealElement *LINK)
{
  long i;

  for (i = -HOMmax; i <= HOMmax; i++) {
    LINK->B[i+HOMmax] = 0e0;
    LINK->BA[i+HOMmax] = false;
  }
  LINK->DBNsavemax = 0;
}


static void AssignHOM(MpoleType *M, struct LOC_Lat_DealElement *LINK)
{
  long i;

  for (i = -HOMmax; i <= HOMmax; i++) {
    if (LINK->BA[i+HOMmax]) {
      M->PBpar[i+HOMmax] = LINK->B[i+HOMmax];
      M->Porder = max(abs(i), (long)M->Porder);
    }
  }
}


static void GetHarm(struct LOC_Lat_DealElement *LINK)
{
  long    i, n;
  symset  SET;

  getest__(P_expset(SET, 1 << ((long)lparent)), "<(> expected", LINK);
  LINK->n_harm = 0;
  do {
    LINK->n_harm++; n = LINK->n_harm;
    i = (long)floor(EVAL_(LINK)+0.5);
    if (i < 1 || n_harm_max < LINK->n_harm+1)
      getest__(P_expset(SET, 0), "invalid value detected", LINK);
    LINK->harm[n-1] = i;
    test__(P_expset(SET, 1 << ((long)comma)), "<, > expected", LINK);
    LINK->kxV[n-1] = EVAL_(LINK);
    test__(P_expset(SET, 1 << ((long)comma)), "<, > expected", LINK);
    LINK->BoBrhoV[n-1] = EVAL_(LINK);
    test__(P_expset(SET, 1 << ((long)comma)), "<, > expected", LINK);
    LINK->kxH[n-1] = EVAL_(LINK);
    test__(P_expset(SET, 1 << ((long)comma)), "<, > expected", LINK);
    LINK->BoBrhoH[n-1] = EVAL_(LINK);
    test__(P_expset(SET, 1 << ((long)comma)), "<, > expected", LINK);
    LINK->phi[n-1] = EVAL_(LINK);
    test__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)rparent))),
	   "<, > or <)> expected", LINK);
  } while (*LINK->sym != rparent);
  GetSym__(LINK);
}


static void AssignHarm(long elem, struct LOC_Lat_DealElement *LINK)
{
  long         i;
  WigglerType  *W;

  W = dynamic_cast<WigglerType*>((*ElemFam_)[elem-1].ElemF);
  W->n_harm += LINK->n_harm;
  // the fundamental is stored in harm[0], etc.
  for (i = 1; i < W->n_harm; i++) {
    W->harm[i] = LINK->harm[i-1];
    W->kxV[i] = LINK->kxV[i-1]; W->BoBrhoV[i] = LINK->BoBrhoV[i-1];
    W->kxH[i] = LINK->kxH[i-1]; W->BoBrhoH[i] = LINK->BoBrhoH[i-1];
    W->phi[i] = LINK->phi[i-1];
  }
}


static void GetDBN_(struct LOC_Lat_DealElement *LINK)

{
  long i;
  symset SET;
  long SET1[(long)squote / 32 + 2];

  getest__(P_expset(SET, 1 << ((long)lparent)), "GetDBN: <(> expected", LINK);
  do {
    getest__(P_addset(P_expset(SET1, 0), (long)squote),
	     "GetDBN <'> expected:", LINK);
    LINK->DBNsavemax++;
    LINK->DBNsave.resize(LINK->DBNsavemax);
    for (i = 0; i < DBNameLen; i++)
      LINK->DBNsave[LINK->DBNsavemax-1].name[i] = ' ';
    i = 0;
    while (*LINK->chin != '\'' && i < DBNameLen) {
      i++;
      LINK->DBNsave[LINK->DBNsavemax-1].name[i-1] = *LINK->chin;
      Lat_Nextch(LINK->fi, LINK->fo, LINK->cc, LINK->ll, LINK->errpos,
		 LINK->lc, LINK->chin, LINK->skipflag, LINK->line,
		 LINK->LINK);
    }
    getest__(P_addset(P_expset(SET1, 0), (long)squote),
	     "<'> expected:GetDBN", LINK);
    getest__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)rparent))),
	     "<, > or <)> expected:GetDBN", LINK);
  }
  while (*LINK->sym != rparent);
  GetSym__(LINK);
}


static void SetDBN(ElemFamType &elemf, struct LOC_Lat_DealElement *LINK)
{
  long i, j;

  if (elemf.NoDBN > 0) {
    elemf.DBNlist.push_back("");
    for (i = 0; i < elemf.NoDBN; i++) {
      j = 0;
      do {
  	elemf.DBNlist.back().push_back(LINK->DBNsave[i].name[j]);
  	j++;
      } while(LINK->DBNsave[i].name[j] != ' ');
    }
  }
}


static bool Lat_DealElement(FILE *fi_, FILE *fo_, long *cc_, long *ll_,
                            long *errpos_, long *lc_, long *nkw_, long *inum_,
			    long emax__, long emin__,
                            long kmax__, long nmax__, char *chin_, char *id_,
			    char *ElementName,
                            char *BlockName_, double *rnum_, bool *skipflag_,
			    bool *rsvwd_,
                            string *line_, Lat_symbol *sym_, alfa_ *key_,
			    Lat_symbol *ksy_,
                            Lat_symbol *sps_, struct LOC_Lat_Read *LINK)
{
  struct LOC_Lat_DealElement V;
  bool           Result = false;
  double         t = 0e0, t1, t2, gap, QL = 0.0, QK;
  double         QKV, QKH, QKxV, QKxH, QPhi, QKS;
  double         dt, Frf, Vrf;
  long           k1, k2, harnum;
  Lat_symbol     sym1;
  symset         mysys, SET;
  long           SET1[(long)lsym / 32 + 2];
  DriftType      *WITHD;
  MpoleType      *WITH2;
  MarkerType     *WITHMk;
  symset         SET2;
  CavityType     *WITH3;
  long           SET3[(long)possym / 32 + 2];
  long           SET4[(long)dbnsym / 32 + 2];
  WigglerType    *WITH4;
  FieldMapType   *WITH6;
  /* ID Laurent */
  InsertionType  *WITH5;
  SpreaderType   *WITHSpr;
  RecombinerType *WITHRec;
  SolenoidType   *WITH7;
  MapType        *WITH8;
  char str1[100] = "";
  char str2[100] = "";
  bool firstflag  = false; // flag for first kick input
  bool secondflag = false; // flag for second kick input
  long           i;
  int            kx, kz;
  double         scaling;
  int            entryf, exitf;

  V.LINK = LINK;
  V.fi = fi_; V.fo = fo_; V.cc = cc_; V.ll = ll_; V.errpos = errpos_;
  V.lc = lc_; V.nkw = nkw_; V.inum = inum_; V.emax_ = emax__; V.emin_ = emin__;
  // 2/21/12 J.B. & J.C.
  V.n_harm = 0;

  V.kmax_ = kmax__; V.nmax_ = nmax__; V.chin = chin_; V.id = id_;
  V.BlockName = BlockName_; V.rnum = rnum_; V.skipflag = skipflag_;
  V.rsvwd = rsvwd_;
  V.line = line_;
  V.sym = sym_; V.key = key_; V.ksy = ksy_;
  V.sps = sps_;
  if (setjmp(V._JL9999)) goto _L9999;
  Result = false;

  switch (*V.sym) {

    /**************************************************************************
       Drift
    **************************************************************************

    <name>: Drift,
            L=<length>; [m]

    Example

      L1: Drift, L=0.30;

    *************************************************************************/

  case drfsym:
    getest__(P_expset(SET, 1 << ((long)comma)), "<comma> expected", &V);
    getest__(P_addset(P_expset(SET1, 0), (long)lsym), "<L> expected", &V);
    getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
    *V.rnum = EVAL_(&V);
    test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected", &V);
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITHD = Drift_Alloc();
    WITHD->Name = ElementName;
    WITHD->PL = *V.rnum;
    WITHD->Pkind = PartsKind(drift);
    // Add family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITHD;
    break;

    /**************************************************************************
      bending
    **************************************************************************

    <name>: Bending,
            L      = <length>, ( [m] )
            T      = <bending angle>, ( [degree] )
            T1     = <entrance angle>, ( [degree] )
            T2     = <exit angle>, ( [degree] )
            gap    = <total magnet gap>, ( [m] )
            K      = <K-value>, ( [m^-2] )
                     ( K > 0 : focusing in horizontal plane )
                     ( K < 0 : defocusing in horizontal plane )
            N      = <# of kicks>,
            method = <method>, ( 2 or 4. The method to divide Q into slices.)
                           ( The detail of <method> will be discussed later.)
            Default value is 2.
            Roll   = <roll angle>, ( [deg], design roll angle )
            HOM    = (i, <Bi>, <Ai>, ( multipole compoments (power series) )
                      j, <Bj>, <Aj>, ( Systematic error Only )
                      ............   ( Random errors are assigned )
                     n, <Bn>, <An>); ( in a Program File using procedures )

    Example

      B: bending, L=0.70, T=10.0, T1:=5.0, T2:=5.0, K=-1.0, N=8, Method=2;

    *************************************************************************/

  case bndsym:  /*4*/
    getest__(P_expset(SET, 1 << ((long)comma)), "<, > expected", &V);
    GetSym__(&V);
    QL = 0.0;   /* L */
    QK = 0.0;   /* K */
    k1 = 0;   /* N */
    t  = 0.0;   /* T */
    t1 = 0.0;   /* T1 */
    t2 = 0.0;   /* T2 */
    gap = 0.0;   /* gap */
    k2 = Meth_Linear;   /* method */
    dt = 0.0;
    ClearHOMandDBN(&V);
    P_addset(P_expset(mysys, 0), (long)lsym);
    P_addset(mysys, (long)ksym);
    P_addset(mysys, (long)nsym);
    P_addset(mysys, (long)mthsym);
    P_addset(mysys, (long)tsym);
    P_addset(mysys, (long)rollsym);
    P_addset(mysys, (long)t1sym);
    P_addset(mysys, (long)t2sym);
    P_addset(mysys, (long)gapsym);
    P_addset(mysys, (long)homsym);
    P_addset(mysys, (long)dbnsym);
    do {
      test__(mysys, "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);

      switch (sym1) {

      case lsym:
	QL = EVAL_(&V);
	break;

      case ksym:
	QK = EVAL_(&V);
	break;

      case nsym:
	k1 = (long)floor(EVAL_(&V) + 0.5);
	break;

      case tsym:
	t = EVAL_(&V);
	break;

      case rollsym:
	dt = EVAL_(&V);
	break;

      case t1sym:
	t1 = EVAL_(&V);
	break;

      case t2sym:
	t2 = EVAL_(&V);
	break;

      case gapsym:
	gap = EVAL_(&V);
	break;

      case mthsym:
	k2 = (long)floor(EVAL_(&V) + 0.5);
	if ((unsigned int)k2 >= 32 ||
	    ((1 << k2) & ((1 << Meth_Linear) | (1 << Meth_Second) |
			  (1 << Meth_Fourth))) == 0)
	  getest__(P_expset(SET, 0), "Check integrator..", &V);
	break;

      case homsym:
	GetHOM(&V);
	break;

      case dbnsym:
	GetDBN_(&V);
	break;
      default:
	break;
      }
      test__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
      if (*V.sym == comma)
	GetSym__(&V);
    } while (P_inset(*V.sym, mysys));
    test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected.", &V);
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITH2 = Mpole_Alloc();
    WITH2->Name = ElementName;
    WITH2->PL = QL;
    WITH2->Pkind = Mpole;
    WITH2->Pmethod = k2;
    WITH2->PN = k1;
    if (WITH2->PL != 0.0)
      WITH2->Pirho = degtorad(t)/WITH2->PL;
    else
      WITH2->Pirho = degtorad(t);
    WITH2->PTx1 = t1; WITH2->PTx2 = t2; WITH2->Pgap = gap;
    WITH2->n_design = Dip;
    AssignHOM(WITH2, &V);
    WITH2->PBpar[HOMmax+2] = QK; WITH2->PdTpar = dt;
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH2;
    SetDBN((*ElemFam_)[Lat_->conf.Elem_nFam-1], &V);
    break;

    /**************************************************************************
      Quadrupole
    **************************************************************************

    <name>: Quadrupole,
            L=<length>, ( [m] )
            K =<K-value>, ( [m-2] )
            N =<# of kicks>,
            Method=<method>,
            Roll=<roll angle>, ( [deg], design roll angle )
            HOM=(i, <Bi>, <Ai>, ( higher order component in USA notation )
                 j, <Bj>, <Aj>, ( Systematic error Only )
                 ............    ( Random errors are assigned )
                 n, <Bn>, <An>); ( in a Program File using procedures )

    Example

      Q1: Quadrupole, L=0.5, K=2.213455, N=4, Method=4;

    **************************************************************/

  case qdsym:  /*4*/
    getest__(P_expset(SET, 1 << ((long)comma)), "<, > expected", &V);
    GetSym__(&V);
    QL = 0.0;   /* L */
    QK = 0.0;   /* K */
    k1 = 0;   /* N */
    k2 = Meth_Fourth;   /* method */
    dt = 0.0;
    ClearHOMandDBN(&V);
    P_addset(P_expset(mysys, 0), (long)lsym);
    P_addset(mysys, (long)ksym);
    P_addset(mysys, (long)nsym);
    P_addset(mysys, (long)mthsym);
    P_addset(mysys, (long)rollsym);
    P_addset(mysys, (long)homsym);
    P_addset(mysys, (long)dbnsym);
    do {   /*5: read L, K, N, T, T1, T2 */
      test__(mysys, "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
      switch (sym1) {   /*6*/

      case lsym:
	QL = EVAL_(&V);
	break;

      case ksym:
	QK = EVAL_(&V);
	break;

      case nsym:
	k1 = (long)floor(EVAL_(&V) + 0.5);
	break;

      case mthsym:
	k2 = (long)floor(EVAL_(&V) + 0.5);
	if ((unsigned int)k2 >= 32 ||
	    ((1 << k2) & ((1 << Meth_Linear) | (1 << Meth_First) |
			  (1 << Meth_Second) | (1 << Meth_Fourth))) == 0)
	  getest__(P_expset(SET, 0), "Check integrator..", &V);
	break;

      case rollsym:
	dt = EVAL_(&V);
	break;

      case homsym:
	GetHOM(&V);
	break;

      case dbnsym:
	GetDBN_(&V);
	break;
      default:
	break;
      }
      test__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
      if (*V.sym == comma)
	GetSym__(&V);
    } while (P_inset(*V.sym, mysys));   /*5*/
    test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected.", &V);
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITH2 = Mpole_Alloc();
    WITH2->Name = ElementName;
    WITH2->PL = QL; WITH2->Pkind = Mpole;
    WITH2->Pmethod = k2; WITH2->PN = k1; WITH2->PdTpar = dt;
    AssignHOM(WITH2, &V);
    WITH2->n_design = Quad; WITH2->PBpar[HOMmax+2] = QK;
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH2;
    SetDBN((*ElemFam_)[Lat_->conf.Elem_nFam-1], &V);
    break;

    /**************************************************************************
      Sextupole
    ***************************************************************************

    <name>: Sextupole,
            L=<length>, ( [m] )
            K =<K-value>, ( [m-3] )
            Roll=<roll angle>, ( [degree], design roll angle )
            HOM=(i, <Bi>, <Ai>, ( higher order component in USA notation )
                 j, <Bj>, <Aj>, ( Systematic error Only )
                 ............    ( Random errors are assigned )
                 n, <Bn>, <An>); ( in a Program File using procedures )

    Example

      SF: Sextupole, K=-10.236345;

    **************************************************************************/

  case sexsym:  /*4*/
    QL = 0.0;   /* L */
    QK = 0.0;   /* K */
    k1 = 0;   /* N */
    k2 = Meth_Fourth;   /* method */
    dt = 0.0;
    ClearHOMandDBN(&V);
    getest__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
    if (*V.sym == comma) {
      GetSym__(&V);
      P_addset(P_expset(mysys, 0), (long)lsym);
      P_addset(mysys, (long)ksym);
      P_addset(mysys, (long)nsym);
      P_addset(mysys, (long)mthsym);
      P_addset(mysys, (long)rollsym);
      P_addset(mysys, (long)homsym);
      P_addset(mysys, (long)dbnsym);
      do {   /*5: read L, K, N, T, T1, T2 */
	test__(mysys, "illegal parameter", &V);
	sym1 = *V.sym;
	getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
	switch (sym1)
	  {   /*6*/
	  case lsym:
	    QL = EVAL_(&V);
	    break;

	  case ksym:
	    QK = EVAL_(&V);
	    break;

	  case nsym:
	    k1 = (long)floor(EVAL_(&V) + 0.5);
	    break;

	  case mthsym:
	    k2 = (long)floor(EVAL_(&V) + 0.5);
	    if ((unsigned int)k2 >= 32 ||
		((1 << k2) & ((1 << Meth_Linear) | (1 << Meth_Second) |
			      (1 << Meth_Fourth))) == 0)
	      getest__(P_expset(SET, 0), "Check integrator..", &V);
	    break;

	  case rollsym:
	    dt = EVAL_(&V);
	    break;

	  case homsym:
	    GetHOM(&V);
	    break;

	  case dbnsym:
	    GetDBN_(&V);
	    break;
	  default:
	    break;
	  }

	test__(P_expset(SET,
			(1 << ((long)comma)) | (1 << ((long)semicolon))),
	       "<, > or <;> expected", &V);

	if (*V.sym == comma)
	  GetSym__(&V);

      } while (P_inset(*V.sym, mysys));   /*5*/
      test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected.", &V);
    }
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITH2 = Mpole_Alloc();
    WITH2->Name = ElementName;
    WITH2->PL = QL;
    WITH2->Pkind = Mpole;
    WITH2->Pmethod = k2;
    WITH2->PN = k1;
    if (WITH2->PL != 0.0)
      WITH2->Pthick = pthicktype(thick);
    else
      WITH2->Pthick = pthicktype(thin);
    WITH2->PdTpar = dt; WITH2->n_design = Sext;
    AssignHOM(WITH2, &V);
    WITH2->PBpar[HOMmax+3] = QK;
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH2;
    SetDBN((*ElemFam_)[Lat_->conf.Elem_nFam-1], &V);
    break;

    /**************************************************************************
      Cavity
    ***************************************************************************

    <name>: Cavity,
            L         = <length>, ( [m] )
            Frequency = <Frf>,   ( [Hz] )
            Voltage   = <Vrf>,   ( [V]  )
            Phase     = <phi_rf>, (degrees)
            rf_focus1 = <0|1>,
            rf_focus2 = <0|1>,
            harnum    = <h>,
            N         = <# of kicks>

    Example

      CAV: Cavity, Frequency = 499.95e6, Voltage=1.22e6, harnum=328;

    **************************************************************************/

  case cavsym:
    ClearHOMandDBN(&V);
    getest__(P_expset(SET, 1 << ((long)comma)), "<, > expected", &V);
    GetSym__(&V);
    QL = 0.0;   /* L */
    Frf = 0.0;  /* Frf */
    Vrf = 0.0;  /* Vrf */
    QPhi = 0.0;
    harnum = 1; /* Voff */
    k1 = 0;     /* N */
    entryf = 0;
    exitf = 0;
    P_addset(P_expset(mysys, 0), (long)lsym);
    P_addset(mysys, (long)frqsym);
    P_addset(mysys, (long)vrfsym);
    P_addset(mysys, (long)phisym);
    P_addset(mysys, (long)harnumsym);
    P_addset(mysys, (long)nsym);
    P_addset(mysys, (long)entryfsym);
    P_addset(mysys, (long)exitfsym);
    P_addset(mysys, (long)dbnsym);
    do {
      test__(mysys, "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
      switch (sym1) {

      case lsym:
	QL = EVAL_(&V);
	break;

      case frqsym:
	Frf = EVAL_(&V);
	break;

      case vrfsym:
	Vrf = EVAL_(&V);
	break;

      case phisym:
	QPhi = EVAL_(&V);
	break;

      case harnumsym:
	harnum = (long)floor(EVAL_(&V) + 0.5);
	break;

      case nsym:
	k1 = (long)floor(EVAL_(&V) + 0.5);
	break;

      case entryfsym:
	entryf = EVAL_(&V);
	break;

      case exitfsym:
	exitf = EVAL_(&V);
	break;

      case dbnsym:
	GetDBN_(&V);
	break;
      default:
	break;
      }
      test__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
      if (*V.sym == comma)
	GetSym__(&V);
    } while (P_inset(*V.sym, mysys));
    test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected.", &V);
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITH3 = Cavity_Alloc();
    WITH3->Name = ElementName;
    WITH3->PL = QL;
    WITH3->Pkind = Cavity;
    WITH3->Pvolt = Vrf;   /* Voltage [V] */
    WITH3->Pfreq = Frf;   /* Frequency in Hz */
    WITH3->phi = degtorad(QPhi);
    WITH3->Ph = harnum;
    WITH3->PN = k1;
    WITH3->entry_focus = entryf == 1;
    WITH3->exit_focus = exitf == 1;
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH3;
    SetDBN((*ElemFam_)[Lat_->conf.Elem_nFam-1], &V);
    break;


    /**************************************************************************
      Orbit Corrector
    ***************************************************************************

    <name>: Corrector, <direction>, L=<length>, ;

    <name> :== Alphanumeric string. Up to NameLength character length.
              BEGIN with an alphabet.
    <direction> :== 'horizontal'|'vertical'

    Example

      COH: Corrector, horizontal;

    **************************************************************************/

  case corsym:  /*4*/
    QL = 0.0;   /* L */
    QK = 0.0;   /* K */
    k1 = 0;     /* N */
    k2 = Meth_Linear;   /* method */
    dt = 0.0;
    ClearHOMandDBN(&V);
    getest__(P_expset(SET, 1 << ((long)comma)), "<, > expected", &V);
    if (*V.sym == comma) {
      GetSym__(&V);
      P_addset(P_expset(mysys, 0), (long)lsym);
      P_addset(mysys, (long)nsym);
      P_addset(mysys, (long)mthsym);
      P_addset(mysys, (long)horsym);
      P_addset(mysys, (long)versym);
      P_addset(mysys, (long)rollsym);
      P_addset(mysys, (long)dbnsym);
      do {   /*5: read L, K, N, T, T1, T2 */
	test__(mysys, "illegal parameter", &V); sym1 = *V.sym;
	if (*V.sym == (long)dbnsym || *V.sym == (long)rollsym ||
	    *V.sym == (long)mthsym ||
	    *V.sym == (long)nsym || *V.sym == (long)lsym)
	  {
	    getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
	    if (*V.sym == eql) {
	      switch (sym1) {   /*6*/

	      case lsym:
		QL = EVAL_(&V);
		break;

	      case nsym:
		k1 = (long)floor(EVAL_(&V) + 0.5);
		break;

	      case mthsym:
		k2 = (long)floor(EVAL_(&V) + 0.5);
		if ((unsigned int)k2 >= 32 ||
		    ((1 << k2) & ((1 << Meth_Linear) | (1 << Meth_Second) |
				  (1 << Meth_Fourth))) == 0)
		  getest__(P_expset(SET2, 0), "Check integrator..", &V);
		break;

	      case rollsym:
		dt = EVAL_(&V);
		break;
	      case dbnsym:
		GetDBN_(&V);
		break;
	      default:
		break;
	      }
	    }
	  } else {
	    if (sym1 == horsym)
	      QK = 1.0;
	    else
	      QK = -1.0;
	    GetSym__(&V);
	  }
	test__(P_expset(SET,
			(1 << ((long)comma)) | (1 << ((long)semicolon))),
	       "<, > or <;> expected", &V);
	if (*V.sym == comma)
	  GetSym__(&V);
      } while (P_inset(*V.sym, mysys));   /*5*/

      test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected.", &V);
    }
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITH2 = Mpole_Alloc();
    WITH2->Name = ElementName;
    WITH2->PL = QL;
    WITH2->Pkind = Mpole;
    if (WITH2->PL != 0.0)
      WITH2->Pthick = pthicktype(thick);
    else
      WITH2->Pthick = pthicktype(thin);
    WITH2->Pmethod = k2;
    WITH2->PN = k1;
    WITH2->PdTpar = dt;
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH2;
    SetDBN((*ElemFam_)[Lat_->conf.Elem_nFam-1], &V);
    break;

    /**************************************************************************
      Beam Position Monitor
    ***************************************************************************

    <name>: Beam Position Monitor;

    <name>:== Alphanumeric string. Up to NameLength character length.
              BEGIN with an alphabet.

    Example

      BPM: Beam Position Monitor;

    **************************************************************************/

  case bemsym:
    ClearHOMandDBN(&V);
    getest__(P_addset(P_expset(SET3, 0), (long)possym),
	     "<position> expected", &V);
    getest__(P_expset(SET, 1 << ((long)monsym)), "<monitor> expected", &V);
    getest__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
    if (*V.sym == comma) {
      getest__(P_addset(P_expset(SET4, 0), (long)dbnsym),
	       "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
      if (sym1 == dbnsym)
	GetDBN_(&V);
      test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected", &V);
    }
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITH2 = Mpole_Alloc();
    WITH2->Name = ElementName;
    WITH2->Pkind = Mpole;
    WITH2->Pthick = pthicktype(thin);
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH2;
    SetDBN((*ElemFam_)[Lat_->conf.Elem_nFam-1], &V);
    break;


    /**************************************************************************
      Marker
    ***************************************************************************

    <name>: Marker;

    <name>:== Alphanumeric string. Up to NameLength character length.
              BEGIN with an alphabet.

    Example

      SYM: Marker;

    **************************************************************************/

  case mrksym:
    ClearHOMandDBN(&V);
    getest__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
    if (*V.sym == comma) {
      getest__(P_addset(P_expset(SET4, 0), (long)dbnsym),
	       "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
      if (sym1 == dbnsym)
	GetDBN_(&V);
      test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected", &V);
    }
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITHMk = Marker_Alloc();
    WITHMk->Name = ElementName;
    WITHMk->Pkind = PartsKind(marker);
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITHMk;
    SetDBN((*ElemFam_)[Lat_->conf.Elem_nFam-1], &V);
    break;


    /**************************************************************************
      Ghost
    ***************************************************************************

     <name>: Ghost;

     <name>:== Alphanumeric string. Up to NameLength character length.
               BEGIN with an alphabet.

     Example

       OBAKE : Ghost;

    **************************************************************************/
    /*----------->>>
      GstSym:BEGIN
      getest([comma], '<, > expexted');
      getest([typsym], '<type> expected');
      getest([eql], '<=> expected');
      QL:=Eval;
      test([semicolon], '<;> expected');
      getsym;
      if sym=DBNsym then GetDBN;
      Lat_->conf.Elem_nFam := Lat_->conf.Elem_nFam + 1;
      if Lat_->conf.Elem_nFam <= Elem_nFamMax then
      begin
      with ElemFam[Lat_->conf.Elem_nFam].ElemF do
      with ElementT[Lat_->conf.Elem_nFam] do
      BEGIN
      Pname:=ElementName; Pkind:=Ghost; PN:=round(QL);
      SetDBN;
      END;
      end
      else
      writeln('Elem_nFamMax exceeded: ', Lat_->conf.Elem_nFam:1,
      '(', Elem_nFamMax:1, ')');
      END;
      <<-----------------------------*/


    /**************************************************************************
      Multipole
    ***************************************************************************

    <name>: Multipole,
            L=<length>, ( [m] )
            T =<bending angle>, ( [degree] )
            T1=<entrance angle>, ( [degree] )
            T2=<exit angle>, ( [degree] )
            Roll=<roll angle>, ( [deg], design roll angle )
            N =<# of kicks>,
            method=<method>, ( 2 or 4. The method to divide Q into slices.)
                    ( The detail of <method> will be discussed later.)
            Default value is 2.
            HOM=(i, <Bi>, <Ai>, ( higher order component in USA notation )
                 j, <Bj>, <Aj>, ( Systematic error Only )
                 ............    ( Random errors are assigned )
                 n, <Bn>, <An>); ( in a Program File using procedures )

    Example

      B: multipole, L=0.70, T=10.0, T1=5.0, T2=5.0,
         HOM=(2, -1.0, 0), N=8, Method=2;


      QF: multipole, L=0.70,
          HOM=(2, 2.50, 0.0,
               4, 1.01e7, 0.0),
          N=8, Method=2;

    **************************************************************************/

  case mpsym:  /*4*/
    getest__(P_expset(SET, 1 << ((long)comma)), "<, > expected", &V);
    GetSym__(&V);
    QL = 0.0;   /* L */
    QK = 0.0;   /* K */
    k1 = 0;   /* N */
    t = 0.0;   /* T */
    t1 = 0.0;   /* T1 */
    t2 = 0.0;   /* T2 */
    gap = 0.0;   /* gap */
    k2 = Meth_Linear;   /* method */
    dt = 0.0;
    ClearHOMandDBN(&V);
    P_addset(P_expset(mysys, 0), (long)lsym);
    P_addset(mysys, (long)nsym);
    P_addset(mysys, (long)mthsym);
    P_addset(mysys, (long)tsym);
    P_addset(mysys, (long)t1sym);
    P_addset(mysys, (long)t2sym);
    P_addset(mysys, (long)gapsym);
    P_addset(mysys, (long)rollsym);
    P_addset(mysys, (long)homsym);
    P_addset(mysys, (long)dbnsym);
    do {   /* read L, K, N */
      test__(mysys, "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
      switch (sym1) {

      case lsym:
	QL = EVAL_(&V);
	break;

      case nsym:
	k1 = (long)floor(EVAL_(&V) + 0.5);
	break;

      case tsym:
	t = EVAL_(&V);
	break;

      case rollsym:
	dt = EVAL_(&V);
	break;

      case t1sym:
	t1 = EVAL_(&V);
	break;

      case t2sym:
	t2 = EVAL_(&V);
	break;

      case gapsym:
	gap = EVAL_(&V);
	break;

      case mthsym:
	k2 = (long)floor(EVAL_(&V) + 0.5);
	if ((unsigned int)k2 >= 32 ||
	    ((1 << k2) & ((1 << Meth_Linear) | (1 << Meth_Second) |
			  (1 << Meth_Fourth))) == 0)
	  getest__(P_expset(SET, 0), "Check integrator..", &V);
	break;

      case homsym:
	GetHOM(&V);
	break;

      case dbnsym:
	GetDBN_(&V);
	break;
      default:
	break;
      }
      test__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
      if (*V.sym == comma)
	GetSym__(&V);
    } while (P_inset(*V.sym, mysys));
    test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected.", &V);
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITH2 = Mpole_Alloc();
    WITH2->Name = ElementName;
    WITH2->Pkind = Mpole;
    WITH2->PL = QL;
    if (WITH2->PL != 0e0) {
      WITH2->Pthick = pthicktype(thick);
      WITH2->Pirho = degtorad(t)/WITH2->PL;
    } else {
      WITH2->Pthick = pthicktype(thin);
      WITH2->Pirho = degtorad(t);
    }
    WITH2->PN = k1; WITH2->Pmethod = k2;
    WITH2->PTx1 = t1; WITH2->PTx2 = t2; WITH2->Pgap = gap;
    WITH2->PdTpar = dt;
    AssignHOM(WITH2, &V);
    WITH2->n_design = WITH2->Porder;
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH2;
    SetDBN((*ElemFam_)[Lat_->conf.Elem_nFam-1], &V);
    break;

    /************************************************************************
      Wiggler
    *************************************************************************

    <name>: Wiggler,
            L       = <length [m]>,
            BoBrhoV = <B/Brho [1/m]>,
            BoBrhoH = <B/Brho [1/m]>,
            Lambda  = <period [m]>,
            kxV     = <[m]>,
            kxH     = <[m]>,
            phi     = <phase [deg]>,
            harm(n, kxV, BoBrhoV, kxH, BoBrhoH, phi)
            ...
            N       = <no of integration steps>,
            Method  = <method>,

    Example

      U143: wiggler, L=4.80, K=0.5, Lambda=0.15, N=20, Method=0;

      EPU:  wiggler, L=4.80, Lambda=0.15, N=20, Method=0,
            harm=(3, kxV_3, BoBrhoV_3, kxH_3, BoBrhoH_3, phi_3,
                  ...
                  5, kxV_5, BoBrhoV_5, kxH_5, BoBrhoH_5, phi_5);

    **************************************************************************/

  case wglsym:
    getest__(P_expset(SET, 1 << ((long)comma)), "<, > expected", &V);
    GetSym__(&V);
    QL = 0e0; QK = 0e0; QKV = 0e0; QKH = 0e0; QKxV = 0e0; QKxH = 0e0;
    QPhi = 0e0; QKS = 0e0; k1 = 0; k2 = Meth_Linear; dt = 0e0;
    ClearHOMandDBN(&V);
    P_addset(P_expset(mysys, 0), (long)lsym);
    P_addset(mysys, (long)lmdsym);
    P_addset(mysys, (long)bobrhovsym);
    P_addset(mysys, (long)bobrhohsym);
    P_addset(mysys, (long)kxvsym);
    P_addset(mysys, (long)kxhsym);
    P_addset(mysys, (long)phisym);
    P_addset(mysys, (long)harmsym);
    P_addset(mysys, (long)nsym);
    P_addset(mysys, (long)mthsym);
    P_addset(mysys, (long)rollsym);
    P_addset(mysys, (long)dbnsym);
    do {
      test__(mysys, "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
      switch (sym1) {   /*6*/

      case lsym:
	QL = EVAL_(&V);
	break;

      case bobrhovsym:
	QKV = EVAL_(&V);
	break;

      case bobrhohsym:
	QKH = EVAL_(&V);
	break;

      case kxvsym:
	QKxV = EVAL_(&V);
	break;

      case kxhsym:
	QKxH = EVAL_(&V);
	break;

      case phisym:
	QPhi = EVAL_(&V);
	break;

      case nsym:
	k1 = (long)floor(EVAL_(&V) + 0.5);
	break;

      case mthsym:
	k2 = (long)floor(EVAL_(&V) + 0.5);
	if ((unsigned int)k2 >= 32 ||
	    ((1 << k2) &
	     ((1 << Meth_Linear) | (1 << Meth_First) | (1 << Meth_Second) |
	      (1 << Meth_Fourth))) == 0)
	  getest__(P_expset(SET, 0), "Check integrator..", &V);
	break;

      case lmdsym:
	QKS = EVAL_(&V);
	break;

      case rollsym:
	dt = EVAL_(&V);
	break;

      case harmsym:
	GetHarm(&V);
	break;

      case dbnsym:
	GetDBN_(&V);
	break;

      default:
	break;
      }
      test__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
      if (*V.sym == comma)
	GetSym__(&V);
    } while (P_inset(*V.sym, mysys));   /*5*/
    test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected", &V);
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITH4 = Wiggler_Alloc();
    WITH4->Name = ElementName;
    WITH4->PL = QL; WITH4->Pkind = Wigl;
    WITH4->Pmethod = k2; WITH4->PN = k1;
    WITH4->PdTpar = dt;
    WITH4->Lambda = QKS; WITH4->n_harm = 1; WITH4->harm[0] = 1;
    WITH4->kxV[0] = QKxV; WITH4->BoBrhoV[0] = QKV;
    WITH4->kxH[0] = QKxH; WITH4->BoBrhoH[0] = QKH;
    WITH4->phi[0] = QPhi;
    AssignHarm(Lat_->conf.Elem_nFam, &V);
    /* Equivalent vertically focusing gradient */
    //       WITH4->PBW[HOMmax+2] = -QK*QK/2e0;
    CheckWiggler(Lat_->conf.Elem_nFam, &V);
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH4;
    SetDBN((*ElemFam_)[Lat_->conf.Elem_nFam-1], &V);
    break;

    /************************************************************************
      Field Map
    *************************************************************************

    <name> : Fieldmap,
             scaling = <scale factor>
             L       = <length [m]>,
             T       = <bending angle>, ( [degree] )
             N       = <no of periods>,
             file1   = <file name (lower case)>

    Example

      FM: Fieldmap, L = 1.0, T=5.0, N = 20, file1 = "U19_Bxyz.dat";

    **************************************************************************/

  case fmsym:
    getest__(P_expset(SET, 1 << ((long)comma)), "<, > expected", &V);
    GetSym__(&V);
    QL = 0.0; k1 = 0; t  = 0.0; strcpy(str1, ""); strcpy(str2, "");
    scaling = 1.0; // scaling factor
    P_addset(P_expset(mysys, 0), (long)lsym);
    P_addset(mysys, (long)tsym);
    P_addset(mysys, (long)nsym);
    P_addset(mysys, (long)scalingsym);
    P_addset(mysys, (long)fnamesym1);
    P_addset(mysys, (long)fnamesym2);
    do {
      test__(mysys, "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
      switch (sym1) {   /*6*/

      case lsym:
	QL = EVAL_(&V);
	break;

      case tsym:
	t = EVAL_(&V);
	break;

      case nsym:
	k1 = (long)floor(EVAL_(&V) + 0.5);
	break;

      case scalingsym:
	scaling = EVAL_(&V);
	break;

      case fnamesym1:
	GetSym__(&V);
	for (i = 1; i < (signed)strlen(id_); i++) {
	  if (id_[i] == '"') break;
	  strncat(str1, &id_[i], 1);
	}
	GetSym__(&V);
	break;

      default:
	break;
      }
      test__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
      if (*V.sym == comma)
	GetSym__(&V);
    } while (P_inset(*V.sym, mysys));   /*5*/
    test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected", &V);
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITH6 = FieldMap_Alloc();
    WITH6->Name = ElementName;
    WITH6->PL = QL; WITH6->Pkind = FieldMap;
    WITH6->phi = degtorad(t); WITH6->n_step = k1; WITH6->scl = scaling;
    if (CheckUDItable("energy         ", LINK) != 0) {
      RefUDItable("energy         ", &Lat_->conf.Energy, LINK);
      if (strcmp(str1, "") != 0) get_B(Lat_->conf, str1, WITH6);
      // Allocate family to lattice object.
      (*ElemFam_).emplace_back();
      (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH6;
    } else {
      std::cout << "Fieldmap: energy not defined" << std::endl;
      exit_(1);
    }
    break;

    /**********************************************************************
      Insertion introduced for SOLEIL using Radia Maps
    ***********************************************************************

    <name> : insertion,
             N = <number of thin lenses>,
             scaling = scaling factor: should be 1. Default value
             file1 = <filename>, in lowercases (first order defaults)
             file2 = <filename>, in lowercases (second order defauts)
             method = <method>, ( 2 or 4. The method to divide Q into slices.)
             ( The detail of <method> will be discussed later.)

    Example

      ID1 : insertion, scaling = 1, N=10, file2=hu80_lh;
      ID2 : insertion, scaling = 1, N=10, file1=hu80_lh_bdl;
      ID3 : insertion, scaling = 1, N=10, file1=hu80_lh_dbl; file2=hu80_lh;

    Notes
      file1 and file2 must have the same structures and meshing
      optional parameter scaling must be at first (weird bug otherwise)
    **************************************************************************/

  case idsym:
    getest__(P_expset(SET, 1L << ((long)comma)), "<, > expected", &V);
    GetSym__(&V);
    QK  = 0e0; QKxV = 0e0; QKS = 0e0;
    k1  = 1;
    k2  = 1;       // linear interpolation by default
    dt  = 0e0;
    scaling = 1.0; // scaling factor
    P_addset(P_expset(mysys, 0), (long)nsym);
    P_addset(mysys, (long)tsym);
    P_addset(mysys, (long)scalingsym);
    P_addset(mysys, (long)fnamesym1);
    P_addset(mysys, (long)fnamesym2);
    P_addset(mysys, (long)mthsym);
    do {
      test__(mysys, "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1L << ((long)eql)), "<=> expected", &V);
      switch (sym1) {

      case nsym: /* Read number of sclices */
	k1 = abs((long)floor(EVAL_(&V)));
	GetSym__(&V);
	break;

      case tsym:
	t = EVAL_(&V);
	break;

      case scalingsym: /* read scaling factor for debugging purpose*/
	scaling = EVAL_(&V);
	break;

      case fnamesym1: /* Read filename for insertion device first order kicks*/
	firstflag = true;
	GetSym__(&V);
	for (i = 1; i < (signed)strlen(id_); i++) {
	  if (id_[i] == '"')
	    break;
	  strncat(str1,&id_[i],1);
	}
	GetSym__(&V);
	break;

      case fnamesym2: /* Read filename for insertion
			 device second order kicks */
	secondflag = true;
	GetSym__(&V);
	for (i = 1; i < (signed)strlen(id_); i++) {
	  if (id_[i] == '"')
	    break;
	  strncat(str2,&id_[i],1);
	}
	GetSym__(&V);
	break;

      case mthsym: // method for interpolation: 1 means linear 2 spline
	k2 = (long)floor(EVAL_(&V) + 0.5);
	break;
      default:
	break;
      }
      if (*V.sym == comma)
	GetSym__(&V);
    } while (P_inset(*V.sym, mysys));   /*5*/
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    /* Fills up the ID */
    WITH5 = Insertion_Alloc();
    WITH5->Name = ElementName;
    WITH5->Pkind = Insertion;
    WITH5->phi = degtorad(t);
    WITH5->Pmethod = k2;
    WITH5->PN = k1;
    WITH5->scaling = scaling;
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH5;
    if (CheckUDItable("energy         ", LINK) != 0) {
      RefUDItable("energy         ", &Lat_->conf.Energy, LINK);
      // 	if (strcmp(str1, "") != 0) get_B(str1, WITH6);

      // Check if filename given for first order kicks
      if (firstflag) {
	if (strcmp(str1,"") == 0)
	  strcpy(WITH5->fname1,"/*No_Filename1_Given*/");
	strcpy(WITH5->fname1,str1);
	// Read Id file for first order kicks
	WITH5->firstorder = true;
	Read_IDfile(WITH5->fname1, Lat_->conf, WITH5);
	// scale factor from Radia: Tmm to get Tm.
	for (kx = 0; kx < WITH5->nx; kx++) {
	  for (kz = 0; kz < WITH5->nz; kz++) {
	    WITH5->thetax1[kz][kx] = 1e-3*WITH5->thetax1[kz][kx];
	    WITH5->thetaz1[kz][kx] = 1e-3*WITH5->thetaz1[kz][kx];
	  }
	}
      } else {
	strcpy(WITH5->fname1,"/*No_Filename1_Given*/");
      }

      // Check if filename given for Second order kicks
      if (secondflag) {
	if (strcmp(str2,"") != 0)
	  strcpy(WITH5->fname2,"/*No_Filename2_Given*/");
	strcpy(WITH5->fname2,str2);
	WITH5->secondorder = secondflag;
	// Read Id file for second order kicks
	Read_IDfile(WITH5->fname2, Lat_->conf, WITH5);
      } else {
	strcpy(WITH5->fname2,"/*No_Filename2_Given*/");
      }

      // check whether no Radia filename read: something is wrong
      if (!firstflag && !secondflag) {
	printf("\nErreur no Insertion filename found as"
	       " an input in lattice file\n");
	exit_(-1);
      }

      if (k2 != 1) { // linear interpolation
	WITH5->linear = false;
      } else { // cubic interpolation
	WITH5->linear = true;
      }

      // stuff for spline interpolation
      if (!WITH5->linear) {
	// WITH5->tx = dmatrix(1,WITH5->nz,1,WITH5->nx);
	// WITH5->tz = dmatrix(1,WITH5->nz,1,WITH5->nx);
	// WITH5->tab1 = (double *)malloc((WITH5->nx)*sizeof(double));
	// WITH5->tab2 = (double *)malloc((WITH5->nz)*sizeof(double));
	// WITH5->f2x = dmatrix(1,WITH5->nz,1,WITH5->nx);
	// WITH5->f2z = dmatrix(1,WITH5->nz,1,WITH5->nx);
	// Matrices4Spline(WITH5);
      }
      // to put somewhere
      //      /** Free memory **/
      //      free(tab1);
      //      free(tab2);
      //
      //      free_matrix(tx,1,nz,1,nx);
      //      free_matrix(tz,1,nz,1,nx);
      //      free_matrix(f2x,1,nz,1,nx);
      //      free_matrix(f2z,1,nz,1,nx);
    }
    break;

    /**************************************************************************
       Spreader
    **************************************************************************

    <name>: Spreader,

    Example

      S1: Spreader;

    *************************************************************************/

  case sprsym:
    getest__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
    if (*V.sym == comma) {
      getest__(P_addset(P_expset(SET4, 0), (long)dbnsym),
	       "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
      if (sym1 == dbnsym)
	GetDBN_(&V);
      test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected", &V);
    }
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITHSpr = Spreader_Alloc();
    WITHSpr->Name = ElementName;
    WITHSpr->PL = *V.rnum;
    WITHSpr->Pkind = PartsKind(Spreader);
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITHSpr;
    break;

    /**************************************************************************
       Recombiner
    **************************************************************************

    <name>: Recombiner,

    Example

      S1: Recombiner;

    *************************************************************************/

  case recsym:
    getest__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
    if (*V.sym == comma) {
      getest__(P_addset(P_expset(SET4, 0), (long)dbnsym),
	       "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
      if (sym1 == dbnsym)
	GetDBN_(&V);
      test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected", &V);
    }
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITHRec = Recombiner_Alloc();
    WITHRec->Name = ElementName;
    WITHRec->PL = *V.rnum;
    WITHRec->Pkind = PartsKind(Recombiner);
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITHRec;
    break;

    /**************************************************************************
      Solenoid
    ***************************************************************************

    <name>: Solenoid,
            L=<length>, ( [m] )
            BoBrho = <B/Brho [1/m]>,
            N =<# of kicks>,
            method=<method>

    Example

      B: solenoid, L=0.70, BoBrho=10.0;

    **************************************************************************/

  case solsym:
    getest__(P_expset(SET, 1 << ((long)comma)), "<, > expected", &V);
    GetSym__(&V);
    QL = 0.0; /* L */
    QK = 0.0; /* K */
    k1 = 0;   /* N */
    P_addset(P_expset(mysys, 0), (long)lsym);
    P_addset(mysys, (long)bobrhosym);
    P_addset(mysys, (long)nsym);
    do { /* read L, K, N */
      test__(mysys, "illegal parameter", &V);
      sym1 = *V.sym;
      getest__(P_expset(SET, 1 << ((long)eql)), "<=> expected", &V);
      switch (sym1) {

      case lsym:
	QL = EVAL_(&V);
	break;

      case bobrhosym:
	QK = EVAL_(&V);
	break;

      case nsym:
	k1 = (long)floor(EVAL_(&V) + 0.5);
	break;

      default:
	std::cout << "Solenoid: undef. case" << std::endl;
	exit_(1);
	break;
      }
      test__(P_expset(SET, (1 << ((long)comma)) | (1 << ((long)semicolon))),
	     "<, > or <;> expected", &V);
      if (*V.sym == comma)
	GetSym__(&V);
    } while (P_inset(*V.sym, mysys));
    test__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected.", &V);
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITH7 = Solenoid_Alloc();
    WITH7->Name = ElementName;
    WITH7->Pkind = Solenoid;
    WITH7->PL = QL; WITH7->N = k1; WITH7->BoBrho = QK;
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH7;
    break;

    /**************************************************************************
      Map
    ***************************************************************************

    <name>: Map

    Example

      M: map;

    **************************************************************************/

  case mapsym:
    getest__(P_expset(SET, 1 << ((long)semicolon)), "<;> expected", &V);
    GetSym__(&V);
    Lat_->conf.Elem_nFam++;
    WITH8 = Map_Alloc();
    WITH8->Name = ElementName;
    WITH8->Pkind = Map;
    // Allocate family to lattice object.
    (*ElemFam_).emplace_back();
    (*ElemFam_)[Lat_->conf.Elem_nFam-1].ElemF = WITH8;
    break;

    /**************************************************************************
      BLOCK DEFINITION
    **************************************************************************/

  case ident:
  case intcon:
  case invsym:   /* Block Definition */
    ProcessBlockInput(&V);
    break;
  default:
    break;
  }/*3.5:of CASE*/

  Result = true;

 _L9999:

  return Result;
}  /*of procedure Lat_DealElement*/


static void errorm___(const char *cmnt, struct LOC_Lat_Read *LINK)
{
  /*write(fo, ' ****')*/
  /*error*/
  if (LINK->cc > LINK->errpos) {
    fprintf(LINK->fo, "%*c^%.80s", (int)(LINK->cc - LINK->errpos),
	    ' ', cmnt);
    LINK->errpos = LINK->cc + 3;
  }
  while (!P_eof(LINK->fi))
    Lat_Nextch(LINK->fi, LINK->fo, &LINK->cc, &LINK->ll, &LINK->errpos,
	       &LINK->lc, &LINK->chin, &LINK->skipflag, LINK->line, LINK);
  Lat_->conf.ErrFlag = true;
  longjmp(LINK->_JL9999, 1);
}


static void GetSym___(struct LOC_Lat_Read *LINK)
{
  /* reads next symbol  */
  /*GetSym*/
  Lat_GetSym(LINK->fi, LINK->fo, &LINK->cc, &LINK->ll, &LINK->errpos,
	     &LINK->lc, &LINK->nkw, &LINK->inum, (long)emax, (long)emin,
	     (long)kmax, nmax, &LINK->chin, LINK->id, &LINK->rnum,
	     &LINK->skipflag, &LINK->rsvwd, LINK->line, &LINK->sym, LINK->key,
	     LINK->ksy, LINK->sps, LINK);
}


static void test___(long *s1, const char *cmnt, struct LOC_Lat_Read *LINK)
{
  /*test*/
  if (!P_inset(LINK->sym, s1))
    errorm___(cmnt, LINK);
}


static void getest___(long *s1, const char *cmnt, struct LOC_Lat_Read *LINK)
{
  /*test*/
  GetSym___(LINK);
  if (!P_inset(LINK->sym, s1))
    errorm___(cmnt, LINK);
}


/* Local variables for init_reserved_words: */
struct LOC_init_reserved_words
{
  struct LOC_Lat_Read *LINK;
};


static void Reg(const char *name, Lat_symbol ks,
		struct LOC_init_reserved_words *LINK)
{
  LINK->LINK->nkw++;  /* incrementation of the number of keywords */
  if (LINK->LINK->nkw > Lat_nkw_max) {
    std::cout << "\nReg: Lat_nkw_max exceeded " << LINK->LINK->nkw
	 << "(" << Lat_nkw_max << ")" << std::endl;
  }
  if (strlen(name)+1 <= 2*sizeof(LINK->LINK->key[LINK->LINK->nkw-1]))
    // memcpy(LINK->LINK->key[LINK->LINK->nkw-1], name, sizeof(alfa_));
    strcpy(LINK->LINK->key[LINK->LINK->nkw-1], name);
  else {
    printf("\n: string length exceeded %lu (%lu)\n",
	   strlen(name)+1, 2*sizeof(LINK->LINK->key[LINK->LINK->nkw-1]));   
    exit(1);
  }
  LINK->LINK->ksy[LINK->LINK->nkw-1] = ks;
}


static void init_reserved_words(struct LOC_Lat_Read *LINK)
{
  struct LOC_init_reserved_words V;

  V.LINK = LINK;
  LINK->nkw = 0; /* Number of keywords equals zero */
  /* Must follow alphabetical list */
  Reg("and            ", andsym, &V);
  Reg("beam           ", bemsym, &V);
  Reg("bending        ", bndsym, &V);
  Reg("cavity         ", cavsym, &V);
  Reg("cell           ", celsym, &V);
  Reg("chromaticity   ", chmsym, &V);
  Reg("corrector      ", corsym, &V);
  Reg("dbname         ", dbnsym, &V);
  Reg("define         ", defsym, &V);
  Reg("dispersion     ", dspsym, &V);
  Reg("drift          ", drfsym, &V);
  Reg("dt             ", dtsym, &V);
  Reg("end            ", endsym, &V);
  Reg("fieldmap       ", fmsym, &V);
  Reg("file1          ", fnamesym1, &V);   /* ID Laurent */
  Reg("file2          ", fnamesym2, &V);   /* ID Laurent */
  Reg("focusing       ", fcssym, &V);
  Reg("frequency      ", frqsym, &V);
  Reg("fringe         ", frgsym, &V);
  Reg("galilean       ", xytsym, &V);
  Reg("gap            ", gapsym, &V);
  Reg("ghost          ", gstsym, &V);
  Reg("harm           ", harmsym, &V);
  Reg("harnum         ", harnumsym, &V);
  Reg("hom            ", homsym, &V);
  Reg("horizontal     ", horsym, &V);
  Reg("insertion      ", idsym, &V);   /* ID Laurent */
  Reg("inv            ", invsym, &V);
  Reg("kicker         ", kicksym, &V);
  Reg("ks             ", kssym, &V);
  Reg("lambda         ", lmdsym, &V);
  Reg("lattice        ", latsym, &V);
  Reg("map            ", mapsym, &V);
  Reg("marker         ", mrksym, &V);
  Reg("method         ", mthsym, &V);
  Reg("monitor        ", monsym, &V);
  Reg("multipole      ", mpsym, &V);
  Reg("nonlinear      ", nbdsym, &V);
  Reg("parameter      ", prmsym, &V);
  Reg("position       ", possym, &V);
  Reg("print          ", prnsym, &V);
  Reg("quadrupole     ", qdsym, &V);
  Reg("recombiner     ", recsym, &V);
  Reg("rf_focus1      ", entryfsym, &V);
  Reg("rf_focus2      ", exitfsym, &V);
  Reg("roll           ", rollsym, &V);
  Reg("scaling        ", scalingsym, &V); /* ID Laurent */
  Reg("sextupole      ", sexsym, &V);
  Reg("solenoid       ", solsym, &V);
  Reg("spreader       ", sprsym, &V);
  Reg("symmetry       ", symsym, &V);
  Reg("t1             ", t1sym, &V);
  Reg("t2             ", t2sym, &V);
  Reg("table          ", tblsym, &V);
  Reg("task           ", tsksym, &V);
  Reg("type           ", typsym, &V);
  Reg("use            ", usesym, &V);
  Reg("vertical       ", versym, &V);
  Reg("voltage        ", vrfsym, &V);
  Reg("wiggler        ", wglsym, &V);

  if (Lat_->conf.trace)
    printf("\ninit_reserved_words: no of keywords = %ld (%d)\n",
	   LINK->nkw, Lat_nkw_max);

  LINK->sps[(int)'+'] = plus_;
  LINK->sps[(int)'-'] = minus_;
  LINK->sps[(int)'('] = lparent;
  LINK->sps[(int)')'] = rparent;
  LINK->sps[(int)'='] = eql;
  LINK->sps[(int)','] = comma;
  LINK->sps[(int)'['] = lbrack;
  LINK->sps[(int)']'] = rbrack;
  LINK->sps[(int)'\''] = squote;
  LINK->sps[(int)'&'] = andsy;
  LINK->sps[(int)';'] = semicolon;
  LINK->sps[(int)'/'] = rdiv;
  LINK->sps[(int)':'] = colon;

  if (Lat_->conf.trace)
    printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d \n",
	   (int)'+', (int)'-', (int)'(', (int)')', (int)'=',
	   (int)',', (int)'[', (int)'[', (int)']', (int)'\'',
	   (int)'&', (int)';', (int)'/', (int)':');

  LINK->lc = 0;             /* reset line counter */
  LINK->ll = 0;             /* reset line length  */
  LINK->cc = 0;             /* reset char counter */
  LINK->errpos = 0;         /* reset error position */
  LINK->chin = ' ';         /* reset current char   */
  LINK->skipflag = false;   /* reset skip flag  */
  P_addset(P_expset(LINK->defbegsys, 0), (long)ident);
  P_addset(P_expset(LINK->elmbegsys, 0), (long)qdsym);
  P_addset(LINK->elmbegsys, (long)sexsym);
  P_addset(LINK->elmbegsys, (long)corsym);
  P_addset(LINK->elmbegsys, (long)bemsym);
  P_addset(LINK->elmbegsys, (long)gstsym);
  P_addset(LINK->elmbegsys, (long)mrksym);
  P_addset(LINK->elmbegsys, (long)nbdsym);
  P_addset(LINK->elmbegsys, (long)frgsym);
  P_addset(LINK->elmbegsys, (long)xytsym);
  P_addset(LINK->elmbegsys, (long)drfsym);
  P_addset(LINK->elmbegsys, (long)bndsym);
  P_addset(LINK->elmbegsys, (long)wglsym);
  P_addset(LINK->elmbegsys, (long)mpsym);
  P_addset(LINK->elmbegsys, (long)cavsym);
  P_addset(LINK->elmbegsys, (long)idsym);      /* ID Laurent */
  P_addset(LINK->elmbegsys, (long)fmsym);
  P_addset(LINK->elmbegsys, (long)sprsym);
  P_addset(LINK->elmbegsys, (long)recsym);
  P_addset(LINK->elmbegsys, (long)solsym);
  P_addset(LINK->elmbegsys, (long)mapsym);
//  P_addset(LINK->elmbegsys, (long)fnamesym1);  /* ID file name Laurent */
//  P_addset(LINK->elmbegsys, (long)fnamesym2);  /* ID file name Laurent */
//  P_addset(LINK->elmbegsys, (long)scalingsym); /* ID scale factor Laurent */
}

/* Local variables for DealWithDefns: */
struct LOC_DealWithDefns
{
  struct LOC_Lat_Read *LINK;
};

static double EVAL__(struct LOC_DealWithDefns *LINK)
{
  return (Lat_EVAL(LINK->LINK->fi, LINK->LINK->fo, &LINK->LINK->cc,
		   &LINK->LINK->ll, &LINK->LINK->errpos, &LINK->LINK->lc,
		   &LINK->LINK->nkw, &LINK->LINK->inum, (long)emax,
		   (long)emin, (long)kmax, nmax, &LINK->LINK->chin,
		   LINK->LINK->id, &LINK->LINK->rnum, &LINK->LINK->skipflag,
		   &LINK->LINK->rsvwd, LINK->LINK->line, &LINK->LINK->sym,
		   LINK->LINK->key, LINK->LINK->ksy, LINK->LINK->sps,
		   LINK->LINK));
}


/******************************************************
 *                                                   *
 *                  P A R S E R                      *
 *                                                   *
 ******************************************************/

static void DealWithDefns(struct LOC_Lat_Read *LINK)
{  /*0*/
  struct LOC_DealWithDefns V;
  partsName idsave, ElementName, BlockName, IdentName;
  long i, j, k, k1;
  symset SET;
  long SET1[(long)ident / 32 + 2];
  long SET2[(long)period_ / 32 + 2];
  long SET3[(long)invsym / 32 + 2];
  _REC_BlockStype *WITH;
  long SET4[(long)symsym / 32 + 2];
  long SET5[(long)endsym / 32 + 2];

  /************** DEAL WITH DEFINITIONS *********************************/

  V.LINK = LINK;
  GetSym___(LINK);
  if (LINK->sym != latsym) {  /*1*/
    test___(P_expset(SET, 0), "<illegal operand> detected", LINK);
    return;
  }
  /****** The first word must be 'lattice' **********/
  getest___(P_expset(SET, 1 << ((long)semicolon)), "<;> expected", LINK);
  // Test whether expression exists
  getest___(P_addset(P_expset(SET1, 0), (long)ident),
	    "<identifier> expected", LINK);

  /***************************************************************************/
  if (LINK->sym == ident) {
    do {   /*2*/
      if (LINK->sym == ident) {  /*2.5:-----------------------*/
	if (strlen(LINK->id)+1 <= 2*sizeof(idsave))
	  // memcpy(idsave, LINK->id, sizeof(alfa_));
	  // memset(idsave+sizeof(alfa_), ' ', sizeof(partsName)-sizeof(alfa_));
	  strcpy(idsave, LINK->id);
        else {
	  printf("\n: string length exceeded %lu (%lu)\n",
		 strlen(LINK->id)+1, 2*sizeof(idsave));   
	  exit(1);
	}
	if (strlen(LINK->id)+1 <= 2*sizeof(ElementName))
	  // memcpy(ElementName, LINK->id, sizeof(alfa_));
	  // memset(ElementName+sizeof(alfa_), ' ', sizeof(partsName)-sizeof(alfa_));
	  strcpy(ElementName, LINK->id);
        else {
	  printf("\n: string length exceeded %lu (%lu)\n",
		 strlen(LINK->id)+1, 2*sizeof(ElementName));   
	  exit(1);
	}
	if (strlen(LINK->id)+1 <= 2*sizeof(BlockName))
	  // memcpy(BlockName, LINK->id, sizeof(alfa_));
	  // memset(BlockName+sizeof(alfa_), ' ', sizeof(partsName)-sizeof(alfa_));
	  strcpy(BlockName, LINK->id);
        else {
	  printf("\n: string length exceeded %lu (%lu)\n",
		 strlen(LINK->id)+1, 2*sizeof(BlockName));   
	  exit(1);
	}
	P_addset(P_expset(SET2, 0), (long)colon);
	P_addset(SET2, (long)eql);
	getest___(P_addset(SET2, (long)period_),
		  "<colon>, <=> or <.> expected", LINK);
	if (LINK->sym == colon)   /*3:of IF sym=colon*/ {  /*3*/
	  P_addset(P_expset(SET3, 0), (long)ident);
	  P_addset(SET3, (long)intcon);
	  getest___(P_setunion(SET, LINK->elmbegsys,
			       P_addset(SET3, (long)invsym)),
		    "<identifier>, <integer> or <INV> expected", LINK);
	  P_addset(P_expset(SET3, 0), (long)ident);
	  P_addset(SET3, (long)intcon);
	  if (P_inset(LINK->sym,
		      P_setunion(SET, LINK->elmbegsys,
				 P_addset(SET3, (long)invsym)))) {
	    if (!Lat_DealElement(LINK->fi, LINK->fo, &LINK->cc,
				 &LINK->ll,
				 &LINK->errpos, &LINK->lc, &LINK->nkw,
				 &LINK->inum, (long)emax, (long)emin,
				 (long)kmax, nmax, &LINK->chin,
				 LINK->id,
				 ElementName, BlockName, &LINK->rnum,
				 &LINK->skipflag, &LINK->rsvwd,
				 LINK->line,
				 &LINK->sym, LINK->key, LINK->ksy,
				 LINK->sps, LINK))
	      longjmp(LINK->_JL9999, 1);
	  }

	} else {
	  /**************************************************************
	   *                                                           *
	   *         P A R A M E T E R  A S S I G N M E N T            *
	   *                                                           *
	   **************************************************************/

	  if (LINK->sym == eql) {  /*3:of parameter*/
	    if (strlen(idsave)+1 <= 2*sizeof(IdentName))
	      // memcpy(IdentName, idsave, sizeof(partsName));
	      strcpy(IdentName, idsave);
	    else {
	      printf("\n: string length exceeded %lu (%lu)\n",
		     strlen(idsave)+1, 2*sizeof(IdentName));   
	      exit(1);
	    }
	    i = CheckUDItable(IdentName, LINK);
	    if (i == 0)
	      EnterUDItable(IdentName, EVAL__(&V), LINK);
	    else
	      ModUDItable(i, EVAL__(&V), LINK);
	    test___(P_expset(SET, 1 << ((long)semicolon)),
		    "<;> expected", LINK);
	    GetSym___(LINK);
	    /*3:of parameter*/
	    /*-----
	      IdentName:=idsave;
	      i:=CheckElementtable(IdentName);
	      IF i=0 THEN Test([], '<element name> expected');
	      getest([lsym, tsym, t1sym, t2sym, gapsym, ksym],
	             'illegal component');
	      sym1:=sym;
	      getest([eql], '<=> expected');
	      case sym1 of
	      lsym:  ElemFam[i].ElemF->PL :=Eval;
	      ksym:  ElemFam[i].ElemF->Pk :=Eval;
	      tsym:  ElemFam[i].ElemF->Pt :=Eval;
	      t1sym: ElemFam[i].ElemF->Pt1:=Eval;
	      t2sym: ElemFam[i].ElemF->Pt2:=Eval;
	      gapsym: ElemFam[i].ElemF->Pgap:=Eval;
	      END;
	      test([semicolon], '<;> expected');
	      GetSym;
	      -----*/
	    /*3:of parameter */
	  }  /*3:of parameter */
	}

	/*****************************
	 *                           *
	 *     DEAL WITH ELEMENT     *
	 *                           *
	 *****************************/

      }  /*2.5*/

      /**************************************************************
       *                                                           *
       *         C E L L    D E F I N I T I O N                    *
       *                                                           *
       *************************************************************

       CELL : <block name>, SYMMETRY=<symmetry>;

              <block name>:== name of a block.
              <symmetry>:== number of supersymmetry:== number of the block/ring

       Example

         CELL : BL1, Symmetry=12;

      ************************************************************************/

      if (LINK->sym == celsym) {  /*3*/
	getest___(P_expset(SET, 1 << ((long)colon)),
		  "<colon> expected", LINK);
	getest___(P_addset(P_expset(SET1, 0), (long)ident),
		  "<Block name> expected", LINK);
	i = CheckBLOCKStable(LINK->id, LINK);
	if (i == 0)
	  test___(P_expset(SET, 0),
		  "<Block name> expected", LINK);
	k = 0;
	if (i != 0) {  /*4*/
	  WITH = &LINK->BlockS[i-1];
	  for (j = WITH->BSTART - 1; j < WITH->BOWARI; j++) {  /*6*/
	    k++;
	    k1 = LINK->Bstack[j];
	    // Allocate family for local list.
	    Cell_List.emplace_back();
	    Cell_List[k].Fnum = k1;
	    Cell_List[k].Reverse = LINK->Reverse_stack[j];
	    if (debug)
	      printf("  Cell definition: |%s| %2ld %3ld %2d %1d\n",
		     WITH->Bname, i, k, Cell_List[k].Fnum,
		     Cell_List[k].Reverse);
	  }
	  /*5*/
	}
	/*4*/
	Lat_->conf.Cell_nLoc = k;   /*number of Elements in a cell*/
	getest___(P_expset(SET, 1 << ((long)comma)),
		  "<, > expected", LINK);
	getest___(P_addset(P_expset(SET4, 0), (long)symsym),
		  "<symmetry> expected", LINK);
	getest___(P_expset(SET, 1 << ((long)eql)),
		  "<=> expected", LINK);
	LINK->Symmetry = (long)floor(EVAL__(&V) + 0.5);
	if (LINK->Symmetry >= 1)
	  LINK->Ring = true;
	else {
	  LINK->Symmetry = 1;
	  LINK->Ring = false;
	}
	test___(P_expset(SET, 1 << ((long)semicolon)),
		"<;> expected", LINK);
	GetSym___(LINK);
      }  /*3: of celsym*/


      switch (LINK->sym) {   /*2*/

	/******************************************

                     PRINT element-name
                     PRINT block_name
                     PRINT parameter

	******************************************/

      case prnsym:  /*4*/
	getest___(P_addset(P_expset(SET1, 0), (long)ident),
		  "<identifiler> expected", LINK);
	if (strlen(LINK->id)+1 <= 2*sizeof(IdentName))
	  // memcpy(IdentName, LINK->id, sizeof(alfa_));
	  // memset(IdentName+sizeof(alfa_), ' ', sizeof(partsName)-sizeof(alfa_));
	  strcpy(IdentName, LINK->id);
        else {
	  printf("\n: string length exceeded %lu (%lu)\n",
		 strlen(LINK->id)+1, 2*sizeof(IdentName));   
	  exit(1);
	}
	i = CheckElementtable(IdentName, LINK);
	if (i == 0) {   /*PrintElementParam(i)*/
	  i = CheckBLOCKStable(IdentName, LINK);
	  if (i == 0) {   /*PrintBlockParam(i)*/
	    i = CheckUDItable(IdentName, LINK);
	    if (i == 0)
	      getest___(P_expset(SET, 0),
			" invalid expression", LINK);
	    /*PrintUDIParam(i)*/
	  }
	}
	if (i != 0) {
	  getest___(P_expset(SET, 1 << ((long)semicolon)),
		    "<;> expected", LINK);
	  GetSym___(LINK);
	}
	break;
	/*4*/
      default:
	break;
      }/*3:of CASE*/

    } while (LINK->sym == (long)prnsym || LINK->sym == (long)celsym ||
	     LINK->sym == (long)dspsym ||
	     LINK->sym == (long)chmsym || LINK->sym == (long)ident);
  }

  test___(P_addset(P_expset(SET5, 0), (long)endsym), "<END> expected", LINK);
  getest___(P_expset(SET, 1 << ((long)semicolon)), "<;> expexted", LINK);



  /*8888888888*/
  /*5*/
  /*6*/
  /*6*/
  /*5*/
  /*1*/
  /*1*/
}  /*0*/


void GetEnergy(struct LOC_Lat_Read *LINK)
{
  long k;

  k = CheckUDItable("energy         ", LINK);
  if (k == 0) {
    printf("\nGetEnergy: beam energy is not defined.\n");
    printf("  Input beam energy in [GeV] := ");
    scanf("%lg%*[^\n]", &Lat_->conf.Energy);
    getchar();
    EnterUDItable("energy         ", Lat_->conf.Energy, LINK);
  } else
    RefUDItable("energy         ", &Lat_->conf.Energy, LINK);
}


void GetRingType(struct LOC_Lat_Read *LINK)
{
  long k;

  k = CheckUDItable("ringtype       ", LINK);
  if (k == 0L) {
    printf("\nGetRingType: RingType not defined, default is ring.\n");
    Lat_->conf.RingType = 1;
  } else {
    Lat_->conf.RingType = (int) LINK->UDItable[k - 1L].Uvalue;
    if (Lat_->conf.RingType != 1 && Lat_->conf.RingType != 0) {
      printf("GetEnergy: ringtype variable is not defined"
	      " properly in the lattice file\n");
      printf("  ringtype set to 1 means ring\n");
      printf("  ringtype set to 0 means transfer line\n");
      exit_(1);
    }
  }
}


static void GetDP(struct LOC_Lat_Read *LINK)
{
  long k;

  k = CheckUDItable("dp             ", LINK);
  if (k != 0) {
      RefUDItable("dp             ", &Lat_->conf.dPcommon, LINK);
      return;
  }
  printf("\nGetDP: dP/P is not defined.\n");
  printf("  Input dP/P := ");
  scanf("%lg%*[^\n]", &Lat_->conf.dPcommon);
  getchar();
  EnterUDItable("dp             ", Lat_->conf.dPcommon, LINK);
}

static void GetCODEPS(struct LOC_Lat_Read *LINK)
{
  long k;

  k = CheckUDItable("codeps         ", LINK);
  if (k != 0) {
    RefUDItable("codeps         ", &Lat_->conf.CODeps, LINK);
    return;
  }
  printf("\nGetCODEPS: CODeps is not defined.\n");
  printf("  Input CODEPS := ");
  scanf("%lg%*[^\n]", &Lat_->conf.CODeps);
  getchar();
  EnterUDItable("codeps         ", Lat_->conf.Energy, LINK);
}


static double Circumference(struct LOC_Lat_Read *LINK)
{
  long i;
  double S;

  S = 0e0;
  for (i = 1; i <= Lat_->conf.Cell_nLoc; i++)
    S += (*ElemFam_)[Cell_List[i].Fnum-1].ElemF->PL;
  return S;
}


/*
 * Warning! Modfies str (should be a pointer not a reference)
 */
void fixedtostr(std::string &str)
{
  std::string str1 = str;

  str = "";
  for(int j = 0; (j < (int)str1.length()) && str1[j] != ' '; ++j)
    str += str1[j];
}


static void RegisterKids(struct LOC_Lat_Read *LINK)
{
  long        i;
  ElemFamType *WITH;

  if (debug) printf("\nRegisterKids:\n");

  for (i = 0; i < Lat_->conf.Elem_nFam; i++) {
    fixedtostr((*ElemFam_)[i].ElemF->Name);

    (*ElemFam_)[i].nKid = 0;
    if (debug)
      printf("  RegisterKids: %2ld %8s\n", i+1,
	     (*ElemFam_)[i].ElemF->Name.c_str());
  }

  for (i = 1; i <= Lat_->conf.Cell_nLoc; i++) {
    WITH = &(*ElemFam_)[Cell_List[i].Fnum-1];
    WITH->nKid++;
    // Allocate Kid Number.
    WITH->KidList.push_back(i);
    // Flag reverse element by negative kid number.
    if ((WITH->ElemF->Pkind == Mpole) && Cell_List[i].Reverse)
      WITH->KidList[WITH->nKid-1] *= -1;
  }
}


void PrintResult(struct LOC_Lat_Read *LINK)
{
  long      j, nKid;
  struct tm *newtime;

  /* Get time and date */
  newtime = GetTime();

  printf("\n");
  printf("  TRACY III v. 3.5 compiled on %s\n",__DATE__);
  printf("\n");
  printf("  LATTICE Statistics for today %s \n\n", asctime2(newtime));
  printf("  Number of constants: UDIC                 =%5ld\n", LINK->UDIC);
  printf("  Number of keywords : nkw                  =%5ld"
	 ", Lat_nkw_max     =%5d\n",
	 LINK->nkw, Lat_nkw_max);
  printf("  Number of Families : Lat_->conf.Elem_nFam =%5ld\n",
	 Lat_->conf.Elem_nFam);
  nKid = 0L;
  for (j = 0L; j < Lat_->conf.Elem_nFam; j++) {
    if ((*ElemFam_)[j].nKid > nKid)
      nKid = (*ElemFam_)[j].nKid;
  }
  printf("  Max number of Kids : nKid                 =%5ld\n", nKid);
  printf("  Number of Blocks   : NoB                  =%5ld\n", LINK->NoB);
  printf("  Max Block size     : NoBE                 =%5ld\n", LINK->Bpointer);
  printf("  Number of Elements : Lat_->conf.Cell_nLoc =%5ld\n",
	 Lat_->conf.Cell_nLoc);
  printf("  Circumference      : %12.7f [m]\n\n\n", Circumference(LINK));
}


bool LatticeType::Lat_Read(const std::string &filnam)
{
  struct LOC_Lat_Read V;
  FILE                *fi_, *fo_;

  V.line = new string;  

  ElemFam_ = &elemf;
  Lat_     = this;

  fi_ = file_read((filnam+".lat").c_str());
  fo_ = file_write((filnam+".lax").c_str());

  if (Lat_->conf.trace)
    printf("\nLat_Read: dndsym = %d, solsym = %d, max_set = %d"
	   ", SETBITS = %u\n",
	   bndsym, solsym, max_set, (unsigned)(4*sizeof(long int)));

  V.fi = fi_; /* input lattice file */
  V.fo = fo_; /* output lattice file */
  if (setjmp(V._JL9999)) goto _L9999;
  V.UDIC = 0; Lat_->conf.Cell_nLoc = 0; Lat_->conf.Elem_nFam = 0; V.NoB = 0;
  V.Symmetry = 0; V.Bpointer = 0;

  Lat_->conf.CODeps = 0e0; Lat_->conf.dPcommon = 0e0; Lat_->conf.Energy = 0e0;

  Lat_->conf.ErrFlag = false;

  init_reserved_words(&V);

  // Allocate element 0 to local list: Cell_List[0..Cell_nLoc].
  Cell_List.emplace_back();

  GetSym___(&V);

  if (V.sym == defsym)
    DealWithDefns(&V);

  if (V.Symmetry != 0) {
    GetRingType(&V);                /* define ring vs. transfer line */
    GetEnergy(&V);                  /* define particle energy */
    GetCODEPS(&V);                  /* define COD precision */
    GetDP(&V);                      /* define energy offset */
  }

  if (V.fi != NULL) fclose(V.fi); /* Close lat file */
  V.fi = NULL;
  if (V.fo != NULL) fclose(V.fo); /* Close lax file */
  V.fo = NULL;

  RegisterKids(&V);                 /* Check wether too many elements */

  if (debug) this->prt_fams();
  PrintResult(&V);                  /* Print lattice statistics */

  delete V.line;  

 _L9999:
  return (!Lat_->conf.ErrFlag);
}

#undef UDImax
#undef LatLLng
#undef Lat_nkw_max
#undef emax
#undef emin
#undef kmax
#undef nmax

#undef nn

#undef debug
