// GridUnit.cpp: implementation of the CGridUnit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Surface.h"
#include "GridUnit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridUnit::CGridUnit()
{
	array[Rec]= -1;
	array[Raft]= -1;
	array[Ag]= -1;
	array[Ht]= -1;
	array[SM]= 0;
	array[SM_tmp]= 0;
	array[Cell]= -1;
}

CGridUnit::~CGridUnit()
{

}

