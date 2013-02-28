// SMprofile.cpp: implementation of the CSMprofile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "surface.h"
#include "SMprofile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMprofile::CSMprofile()
{

}

CSMprofile::CSMprofile(string sm_type)
{

}

CSMprofile::~CSMprofile()
{

}

bool CSMprofile::IsSubstrate(SM_Type type)
{
	bool ret = false;
	if(find(m_SubstratesArray.begin(),m_SubstratesArray.end(), type) != m_SubstratesArray.end())
	{
		ret = true;
	}
	return ret;
}