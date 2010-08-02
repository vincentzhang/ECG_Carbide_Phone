
#ifndef wfdb_ECGMAP_H	/* avoid multiple definitions */
#define wfdb_ECGMAP_H

#ifndef wfdb_ECGCODES_H
#include "ecgcodes.h"
#endif

/* isann(A) is true if A is a legal annotation code, false otherwise */
#define isann(A)   (0<(wfdb_mt=(A)) && wfdb_mt<=ACMAX)
static int wfdb_mt;		/* macro temporary variable */

/* isqrs(A) is true (1) if A denotes a QRS complex, false (0) otherwise */
#ifndef isqrs
#define isqrs(A)   (isann(A) ? wfdb_qrs[wfdb_mt] : 0)
#define setisqrs(A, X)	(isann(A) ? (wfdb_qrs[wfdb_mt] = (X)) : 0)
static char wfdb_qrs[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1,			/* 0 - 9 */
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0,			/* 10 - 19 */
	0, 0, 0, 0, 0, 1, 0, 0, 0, 0,			/* 20 - 29 */
	1, 1, 0, 0, 1, 1, 0, 0, 1, 0,			/* 30 - 39 */
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0			/* 40 - 49 */
};
#endif

/* map1(A) maps A into one of {NOTQRS, NORMAL, PVC, FUSION, LEARN} */
#ifndef map1
#define map1(A)    (isann(A) ? wfdb_mp1[wfdb_mt] : NOTQRS)
#define setmap1(A, X)	(isann(A) ? (wfdb_mp1[wfdb_mt] = (X)) : NOTQRS)
static char wfdb_mp1[] = {
	NOTQRS,	NORMAL,	NORMAL,	NORMAL,	NORMAL,		/* 0 - 4 */
	PVC,	FUSION,	NORMAL,	NORMAL,	NORMAL,		/* 5 - 9 */
	PVC,	NORMAL,	NORMAL,	NORMAL,	NOTQRS,		/* 10 - 14 */
	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,		/* 15 - 19 */
	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,		/* 20 - 24 */
	NORMAL,	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,		/* 25 - 29 */
	LEARN,	PVC,	NOTQRS,	NOTQRS,	NORMAL,		/* 30 - 34 */
	NORMAL,	NOTQRS,	NOTQRS,	NORMAL, NOTQRS,		/* 35 - 39 */
	NOTQRS, PVC,	NOTQRS,	NOTQRS,	NOTQRS,		/* 40 - 44 */
	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS		/* 45 - 49 */
};
#endif

/* map2(A) maps A into one of {NOTQRS, NORMAL, SVPB, PVC, FUSION, LEARN} */
#ifndef map2
#define map2(A)    (isann(A) ? wfdb_mp2[wfdb_mt] : NOTQRS)
#define setmap2(A, X)	(isann(A) ? (wfdb_mp2[wfdb_mt] = (X)) : NOTQRS)
static char wfdb_mp2[] = {
	NOTQRS,	NORMAL,	NORMAL,	NORMAL,	SVPB,		/* 0 - 4 */
	PVC,	FUSION,	SVPB,	SVPB,	SVPB,		/* 5 - 9 */
	PVC,	NORMAL,	NORMAL,	NORMAL,	NOTQRS,		/* 10 - 14 */
	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,		/* 15 - 19 */
	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,		/* 20 - 24 */
	NORMAL,	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,		/* 25 - 29 */
	LEARN,	PVC,	NOTQRS,	NOTQRS,	NORMAL,		/* 30 - 34 */
	NORMAL,	NOTQRS, NOTQRS, NORMAL, NOTQRS,		/* 35 - 39 */
	NOTQRS, PVC,	NOTQRS,	NOTQRS,	NOTQRS,		/* 40 - 44 */
	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS		/* 45 - 49 */
};
#endif

/* ammap(A) maps an AHA annotation code, A, into an MIT annotation code */
#ifndef ammap
#define ammap(A)   (('D' < (wfdb_mt = (A)) && wfdb_mt <= ']') ? \
		    wfdb_ammp[wfdb_mt-'E'] : NOTQRS)
static char wfdb_ammp[] = {
	VESC,	FUSION,	NOTQRS,	NOTQRS,	NOTQRS,		/* 'E' - 'I' */
	NOTQRS,	NOTQRS,	NOTQRS,	NOTQRS,	NORMAL,		/* 'J' - 'N' */
	NOTE,	PACE,	UNKNOWN,RONT,	NOTQRS,		/* 'O' - 'S' */
	NOTQRS,	NOISE,	PVC,	NOTQRS,	NOTQRS,		/* 'T' - 'X' */
	NOTQRS,	NOTQRS,	VFON,	NOTQRS,	VFOFF		/* 'Y' - ']' */
};
#endif

/* mamap(A,S) maps MIT code A, subtype S, into an AHA annotation code */
#ifndef mamap
#define mamap(A,S) (isann(A) ? \
		    (((wfdb_mt = wfdb_mamp[wfdb_mt]) == 'U' && (S) != -1) ? \
		     'O': wfdb_mt) : 'O')
static char wfdb_mamp[] = {
	'O',	'N',	'N',	'N',	'N',		/* 0 - 4 */
	'V',	'F',	'N',	'N',	'N',		/* 5 - 9 */
	'E',	'N',	'P',	'Q',	'U',		/* 10 - 14 */
	'O',	'O',	'O',	'O',	'O',		/* 15 - 19 */
	'O',	'O',	'O',	'O',	'O',		/* 20 - 24 */
	'N',	'O',	'O',	'O',	'O',		/* 25 - 29 */
	'Q',	'O',	'[',	']',	'N',		/* 30 - 34 */
	'N',	'O',	'O',	'N',	'O',		/* 35 - 39 */
	'O',	'R',	'O',	'O',	'O',		/* 40 - 44 */
	'O',	'O',	'O',	'O',	'O'		/* 45 - 49 */
};
#endif

/* Annotation position codes.  These may be used by applications which plot
   signals and annotations to determine where to print annotation mnemonics. */
#define APUNDEF	0	/* for undefined annotation types */
#define APSTD	1	/* standard position */
#define APHIGH	2	/* a level above APSTD */
#define APLOW	3	/* a level below APSTD */
#define APATT	4	/* attached to the signal specified by `chan' */
#define APAHIGH	5	/* a level above APATT */
#define APALOW	6	/* a level below APATT */

/* annpos(A) returns the appropriate position code for A */
#ifndef annpos
#define annpos(A) (isann(A) ? wfdb_annp[wfdb_mt] : APUNDEF)
#define setannpos(A, X) (isann(A) ? (wfdb_annp[wfdb_mt] = (X)) : APUNDEF)
static char wfdb_annp[] = {
	APUNDEF,APSTD,	APSTD,	APSTD,	APSTD,		/* 0 - 4 */
	APSTD,	APSTD,	APSTD,	APSTD,	APSTD,		/* 5 - 9 */
	APSTD,	APSTD,	APSTD,	APSTD,	APHIGH,		/* 10 - 14 */
	APUNDEF,APHIGH,	APUNDEF,APHIGH,	APHIGH,		/* 15 - 19 */
	APHIGH,	APHIGH,	APHIGH,	APHIGH,	APHIGH,		/* 20 - 24 */
	APSTD,	APHIGH,	APHIGH,	APLOW,	APHIGH,		/* 25 - 29 */
	APSTD,	APSTD,	APSTD,	APSTD,	APSTD,		/* 30 - 34 */
	APSTD,	APHIGH,	APHIGH,	APSTD,	APHIGH,		/* 35 - 39 */
	APHIGH,	APSTD,	APUNDEF,APUNDEF,APUNDEF,	/* 40 - 44 */
	APUNDEF,APUNDEF,APUNDEF,APUNDEF,APUNDEF		/* 45 - 49 */
};
#endif

#endif
