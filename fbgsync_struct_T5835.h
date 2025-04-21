#ifndef ___TEST_FBGSYNC_STRUCT_H_
#define ___TEST_FBGSYNC_STRUCT_H_
#include "test.h"

#define FBGARG testarg->fbgarg

typedef struct _TEST_fbgarg{
    char          **patname;
    char          **label;
	USlider        *pc;
	int             ilmd;
	DSlider		   *tck;
	int				mode;
	double			out2out;	//by IDX6
	void          (*pre)();
	USlider        *group;
	void          (*post)();

}TEST_fbgarg;

#endif // ___TEST_FBGSYNC_STRUCT_H_
