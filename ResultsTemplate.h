// ResultsTemplate.h: interface for the CResultsTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTSTEMPLATE_H__929C98B4_9256_46F9_A92A_7CE97FEB4E59__INCLUDED_)
#define AFX_RESULTSTEMPLATE_H__929C98B4_9256_46F9_A92A_7CE97FEB4E59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#define ARR_SIZE 21
typedef vector<double>doublesVec;
class CResultsTemplate  
{
public:
//	static int results_param_number;
	int step;
	int IFNreleased;
	int IFNbound;
	doublesVec rigI_prot_Vec;
	doublesVec rigI_rna_Vec;
	doublesVec IFN_prot_Vec;
	doublesVec IFN_rna_Vec;

	doublesVec rigI_transcriptionRate_Vec;
	doublesVec rigI_decayRate_Vec;
	doublesVec rigI_translationRate_Vec;
	doublesVec rigI_degradationRate_Vec;
	doublesVec IFN_transcriptionRate_Vec;
	doublesVec IFN_decayRate_Vec;
	doublesVec IFN_translationRate_Vec;
	doublesVec IFN_degradationRate_Vec;
	doublesVec boundRs_Vec;



	CResultsTemplate();
	virtual ~CResultsTemplate();

};

#endif // !defined(AFX_RESULTSTEMPLATE_H__929C98B4_9256_46F9_A92A_7CE97FEB4E59__INCLUDED_)
