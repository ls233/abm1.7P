// Grid.h: interface for the CGrid class.
//
//////////////////////////////////////////////////////////////////////
#include "General.h"


#if !defined(AFX_GRID_H__DC9E8991_078D_4BA3_9BC7_14D08489FCBA__INCLUDED_)
#define AFX_GRID_H__DC9E8991_078D_4BA3_9BC7_14D08489FCBA__INCLUDED_

#include "GridUnit.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGrid  
{
public:
	CGridUnit m_Grid[GRID_SIZE][GRID_SIZE];
	CGrid();
	bool MoveSM(int,int,Kind_of_Move,int);
	bool killSM(int,int,int);
	virtual ~CGrid();
};

#endif // !defined(AFX_GRID_H__DC9E8991_078D_4BA3_9BC7_14D08489FCBA__INCLUDED_)
