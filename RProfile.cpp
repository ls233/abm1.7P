// RProfile.cpp: implementation of the CRProfile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "surface.h"
#include "RProfile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRProfile::CRProfile()
{

}

CRProfile::~CRProfile()
{

}
bool CRProfile::IsSubstrate(SM_Type type)
{
	bool ret = false;
	if(find(m_SubstratesArray.begin(),m_SubstratesArray.end(), type) != m_SubstratesArray.end())
	{
		ret = true;
	}
	return ret;
}