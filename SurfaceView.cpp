// SurfaceView.cpp : implementation of the CSurfaceView class
//

#include "stdafx.h"
#include "Surface.h"
#include "General.h"
#include "Receptor.h"
#include "SigMol.h"
#include "Cell.h"
#include "Grid.h"

#include "SurfaceDoc.h"
#include "SurfaceView.h"
#include "Option.h"
#include "BaseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSurfaceView
clock_t start, start1, fin;
int stepGl = 0, stepGlS = -2;
int isTimer = true;
//static int flag1 = false;
static int num = 0;	

bool IsMemDc = true;
bool isMemDc = true;

IMPLEMENT_DYNCREATE(CSurfaceView, CFormView)

BEGIN_MESSAGE_MAP(CSurfaceView, CFormView)
	//{{AFX_MSG_MAP(CSurfaceView)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
    ON_MESSAGE(GEN_ONE, OnMyMessage) //gg1
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSurfaceView construction/destruction

CSurfaceView::CSurfaceView()
	: CFormView(CSurfaceView::IDD)
{
	//{{AFX_DATA_INIT(CSurfaceView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	m_OptionDlg = 0;
	m_stopDraw = false; //false;
	m_PartGrid = 1;
	m_StepBy = false;
	m_PartGridNum = 1;
	m_Next = false;
	minZoom = 1;

}
CSurfaceView::~CSurfaceView()
{
}

void CSurfaceView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSurfaceView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CSurfaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CSurfaceView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	SetTimer(1, CGeneral::TimerInitialisator, NULL);
	m_pdlg = new CBaseDlg();
	m_pdlg->Create(this);

}

/////////////////////////////////////////////////////////////////////////////
// CSurfaceView printing

BOOL CSurfaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSurfaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSurfaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSurfaceView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CSurfaceView diagnostics

#ifdef _DEBUG
void CSurfaceView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSurfaceView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSurfaceDoc* CSurfaceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSurfaceDoc)));
	return (CSurfaceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSurfaceView message handlers

void CSurfaceView::OnDraw(CDC* pDC) 
{
//	return;
	// TODO: Add your specialized code here and/or call the base class
//	if(!CGeneral::RaftArray.size())	return;
	if(CGeneral::step == 0) return;
	CGeneral::is_draw_finished = false;

	clock_t startd, find;
	double	duration = 0;
	startd = clock();
	//yellow, cremovi
	static 	COLORREF colors[255*255*255];
	for(int r=0; r<255 ; r++)	{
		for(int g=0; g<255 ; g++)	{
			for(int b=0; b<255 ; b++)	{
				colors[r+g+b]= RGB( 255-r, 255-g, 255-b);
			}
		}
	}


	static 	COLORREF col[16] = { RGB( 255, 0, 0 ), RGB( 0, 255, 0 ), //krasnii-0, zelyonii-1
		RGB( 0, 0, 255), RGB( 0, 255, 255 ), //sinii-2, goluboiCian-3
		RGB( 255, 0, 255), RGB( 255, 255, 0 ), //malinovii-4, jyoltii-5
		RGB( 192, 192, 192), RGB( 80, 0, 80 ), //serii-6, t-malinovii-7
		RGB( 255, 255, 255), RGB( 80, 80, 0 ), //serii-8, t-jyoltii-9, 
		RGB( 80, 80, 0 ), RGB( 0, 0, 80 ), //4yornii-10, tyomn. golub - 11 
		RGB( 250, 166, 70 ), RGB( 207, 10, 243 ), //orange-12, tyomn. fioletovii - 13 
		RGB( 128, 128, 0 ), RGB( 0, 0, 0 )}; // seri 15

	GetClientRect(m_ClientRect );
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	
	static int key = 1;

	DrawSize = (m_ClientRect.Width( ) < m_ClientRect.Height( ) )
		? m_ClientRect.Width( ) : m_ClientRect.Height( ) ;
	if(DrawSize > GRID_SIZE)  DrawSize = GRID_SIZE;
	else
	{	
		minZoom = (GRID_SIZE-1)/DrawSize + 1 ;
		if(m_PartGrid < minZoom)
		{
			m_PartGrid = minZoom;
		}
	}
	DrawSize = GRID_SIZE/m_PartGrid;
	m_OptionDlg->SetZoom(m_PartGrid, GRID_SIZE/m_PartGrid,num);
	int xp = (m_PartGridNum - 1)%m_PartGrid ;
	int yp = (m_PartGridNum - 1) / m_PartGrid ;
	X = 0 + DrawSize * xp;
	Y = 0 + DrawSize * yp;
	X1 = X + DrawSize; 
	Y1 = Y + DrawSize;


//-----------------------------------------------------------------		
	CDC * myDc;
	CDC memdc;
	CBitmap bmp, *poldbmp;
	isMemDc = IsMemDc && !( CGeneral::DrawRaftIndexes 
		|| CGeneral::DrawRecIndexes
		|| CGeneral::DrawSigMolInd || CGeneral::DrawSigMolNames
		|| CGeneral::DrawRecNames);

	if(isMemDc)
	{
		// Create a compatible memory DC
		memdc.CreateCompatibleDC( pDC);
		bmp.CreateCompatibleBitmap (pDC, m_ClientRect.Height(), m_ClientRect.Height()); 
		//bmp.CreateCompatibleBitmap (pDC, DrawSize, DrawSize); 
		// Select the new bitmap object into the memory device context. 
		poldbmp = memdc.SelectObject( &bmp );

		memdc.BitBlt( 0,0,m_ClientRect.Height(), m_ClientRect.Height(),&memdc, 0, 0, WHITENESS );  
		myDc = &memdc;
	}
	else myDc = pDC;
	myDc->SetMapMode(MM_ISOTROPIC);
	SetWindowExtEx(*myDc,DrawSize,DrawSize,NULL);
	SetViewportExtEx(*myDc,m_ClientRect.right, -m_ClientRect.bottom,NULL);
	SetViewportOrgEx(*myDc,0,m_ClientRect.bottom,NULL);	
//-----------------------------------------------------------------		





	double sd = sqrt(DrawSize /27.) ;

	if( CGeneral::DrawSigMol ){

		double sd_sm = sd-1;
		if(sd_sm < 1) sd_sm = 1; //   ?????????????????

		CBrush br;
		br.CreateSolidBrush(col[1]);

		for(int in=0; in<GRID_SIZE ; in++)
		{
			for(int in1=0; in1<GRID_SIZE ; in1++)
			{
				CBrush br1;
				double IFN_prot_conc = CGeneral::grid.m_Grid[in1][in].array[SM];
				if(IFN_prot_conc == 0){
					continue;
				}
				int normalized_IFN_prot_conc = floor(IFN_prot_conc);
				br1.CreateSolidBrush(colors[normalized_IFN_prot_conc]);
				CBrush* pSMBr = myDc->SelectObject( &br1 );

	//			myDc->Rectangle(in - X, in1 -Y,	in + sd_sm -X, in1 + sd_sm - Y); 
				CRect rect(in - X, in1 -Y, in + sd_sm -X, in1 + sd_sm - Y);
				myDc->FillRect(&rect ,&br1); 

				if(CGeneral::DrawSigMolNames)
				{
					char buf[30] = "IFNprot: ";
					char buf5[10];
					itoa(IFN_prot_conc,buf5,10);
					strncat(buf, buf5, 10);//add coma
					myDc->TextOut(in - X, in1 -Y, buf, strlen(buf));
				}	

			}
		}

	}



	/////////////////// begin drawing rafts //////////////////////////////////
	if( CGeneral::DrawRafts )
	{
		CBrush gray_hatch_br, red_br, grey_br;
		gray_hatch_br.CreateHatchBrush(HS_BDIAGONAL, col[15]);
		grey_br.CreateSolidBrush(col[15]);
		red_br.CreateSolidBrush(col[1]);


		CBrush* pOldBr = myDc->SelectObject( &gray_hatch_br );

		std::vector<CCell>::iterator raft_iter;
		raft_iter = CGeneral::CellArray.begin();
		CCell * p_Raft = raft_iter;
		for(; raft_iter  != CGeneral::CellArray.end(); raft_iter++)
		{
			p_Raft = raft_iter;



			double rigI_rna_conc = p_Raft->GetRIGI_rna_conc();
//			double normalized_rigI_rna_conc = rigI_rna_conc/CGeneral::RIGI_rna_maxLevel;
			double IFN_prot_conc = p_Raft->GetIFN_prot_conc();
//			double normalized_IFN_prot_conc = IFN_prot_conc/CGeneral::IFN_prot_maxLevel;

			if( p_Raft->IsActivated() )
			{
				CBrush br;
 				double RIGI_rna_conc = p_Raft->GetRIGI_rna_conc();
				int val=0;
				if(CGeneral::DrawAgs)
					double rigI_rna_conc = p_Raft->GetRIGI_rna_conc();
				else
					double rigI_rna_conc = p_Raft->GetRIGI_rna_conc();


				if( !p_Raft->IsInfected() )//not infected
				{
					br.CreateHatchBrush(HS_BDIAGONAL, RGB( 128, 128, 128 ));
					CBrush* pSMBr = myDc->SelectObject( &br );
					myDc->Ellipse(p_Raft->Location.x - X, p_Raft->Location.y -Y,
								p_Raft->Location.x  -X, p_Raft->Location.y - Y); 

				} 	           
				else// infected
				{
					if( CGeneral::step != 1)
					{
						CBrush* pSMBr = myDc->SelectObject( &red_br );
						myDc->Ellipse(p_Raft->Location.x - X, p_Raft->Location.y -Y,
									p_Raft->Location.x  -X, p_Raft->Location.y  - Y); 
					}
					if(p_Raft->m_blinking_counter == p_Raft->m_blinking_const)
					{
						p_Raft->m_blinking_counter = 0;
						p_Raft->m_justChangedStatus = !p_Raft->m_justChangedStatus;
					}
					else{p_Raft->m_blinking_counter++;}

					br.CreateSolidBrush(RGB( 128, 128, 128 ));
					CBrush* pSMBr = myDc->SelectObject( &br );
					myDc->Ellipse(p_Raft->Location.x - X, p_Raft->Location.y -Y,
								p_Raft->Location.x -X, p_Raft->Location.y - Y); 
					if(p_Raft->m_blinking_counter == p_Raft->m_blinking_const)
					{
						p_Raft->m_blinking_counter = 0;
						p_Raft->m_justChangedStatus = !p_Raft->m_justChangedStatus;
					}
					else{p_Raft->m_blinking_counter++;}
				}

			} // if	                 
			else // not activated
			{
				CBrush brt,brt1;
				int val_msg;
				int val_prot;
				if(!CGeneral::DrawAgs) {//DDX58
//					if(CGeneral::DrawAgIndexes)//msg
						val_msg = p_Raft->GetRIGI_rna_conc();
//					else //prot
						val_prot = p_Raft->GetRIGI_prot_conc();
				}
				else {//IFNB1
//					if(CGeneral::DrawAgIndexes)//IFNB1
						val_msg = p_Raft->GetIFN_rna_conc();
//					else   //prot
						val_prot = p_Raft->GetIFN_prot_conc();
				}

				if( p_Raft->IsInfected() )//NOT UNFECTED		
				{
					brt.CreateSolidBrush(colors[val_prot]);
					CBrush* pSMBr = myDc->SelectObject( &brt );
					myDc->Ellipse(p_Raft->Location.x - X-1, p_Raft->Location.y -Y-1,
								p_Raft->Location.x -X+sd+1, p_Raft->Location.y  - Y+sd+1); 

					brt1.CreateSolidBrush(colors[val_msg]);
					pSMBr = myDc->SelectObject( &brt1 );
					myDc->Ellipse(p_Raft->Location.x - X, p_Raft->Location.y -Y,
								p_Raft->Location.x -X+sd, p_Raft->Location.y  - Y+sd); 

/*					myDc->SetTextColor(col[0]); 
					char buf[30] = "*";
					myDc->TextOut(p_Raft->Location.x - X+1, p_Raft->Location.y -Y+1, 
						buf, strlen(buf));
						*/

				} // if	  
				else//not infected
				{	
//					brt.CreateSolidBrush(colors[col[2]]);
					brt.CreateHatchBrush(HS_BDIAGONAL, colors[val_prot]);
					CBrush* pSMBr = myDc->SelectObject( &brt );
					myDc->Ellipse(p_Raft->Location.x - X-1, p_Raft->Location.y -Y-1,
								p_Raft->Location.x -X+sd+1, p_Raft->Location.y  - Y+sd+1); 

					brt1.CreateHatchBrush(HS_FDIAGONAL, colors[val_prot]);
					pSMBr = myDc->SelectObject( &brt1 );
					myDc->Ellipse(p_Raft->Location.x - X, p_Raft->Location.y -Y,
								p_Raft->Location.x -X+sd, p_Raft->Location.y  - Y+sd); 
				}
				
			}
			myDc->SetTextColor(col[0]); 
			int boundTypeIR = p_Raft->Get_boundTypeIR();
			if(boundTypeIR)	{
				char buf1[3] = "|";
				char buf2[3] = "--";
				char buf3[3]="";
				char buf[30] = "";
				char buf5[10];
				if((boundTypeIR%2)){
					strncat(buf3, buf1, 3);//add coma					
				}else{
					strncat(buf3, buf2, 3);//add coma					
				}
				myDc->TextOut(p_Raft->Location.x - X+1, p_Raft->Location.y -Y+1, 
					buf3, strlen(buf3));
			}
			myDc->SetTextColor(RGB(0,0,0)); 

			if( !p_Raft->IsInfected() ) {//not infected
			

			} 	           
			else {// infected
			
			}

			/*

			double rigI_rna_conc = p_Raft->GetRIGI_rna_conc();
			double normalized_rigI_rna_conc = rigI_rna_conc/CGeneral::RIGI_rna_maxLevel;
			double IFN_rna_conc = p_Raft->GetIFN_rna_conc();
			double normalized_IFN_rna_conc = IFN_rna_conc/CGeneral::IFN_rna_maxLevel;

			int sd_rna = sd+3;
			int val;
			if(CGeneral::DrawAgs)
				val = 255 - normalized_rigI_rna_conc * 255;
			else
				val = 255 - normalized_IFN_rna_conc * 255;
			CBrush br_rna;
			br_rna.CreateSolidBrush(RGB( val, val, val ));
			CBrush* pSMBr = myDc->SelectObject( &br_rna );
//			myDc->Ellipse(p_Raft->m_shape.Centroid().x - X, p_Raft->m_shape.Centroid().y -Y,
//				p_Raft->m_shape.Centroid().x + sd_rna -X, p_Raft->m_shape.Centroid().y + sd_rna - Y); 

*/



			if(CGeneral::DrawRaftIndexes)
			{
				char buf[30]="";
				char buf5[10]="";
				if(!CGeneral::DrawAgs){
//					if(CGeneral::DrawAgIndexes)	{
						strncat(buf, "DDX58: ", 10);//add coma
						itoa(p_Raft->GetRIGI_rna_conc(),buf5,10);
						strncat(buf, buf5, 10);//add coma
						myDc->TextOut(p_Raft->Location.x - X, p_Raft->Location.y -Y, 
							buf, strlen(buf));
//					}
//					else{
						strncat(buf, ", RIGI: ", 10);//add coma
						itoa(p_Raft->GetRIGI_prot_conc(),buf5,10);
						strncat(buf, buf5, 10);//add coma
						myDc->TextOut(p_Raft->Location.x - X, p_Raft->Location.y -Y, 
							buf, strlen(buf));
//					}
				}
				else{
//					if(CGeneral::DrawAgIndexes)	{
						strncat(buf, "IFNB:", 10);//add coma
//						buf = "IFNB: ";
						itoa(p_Raft->GetIFN_rna_conc(),buf5,10);
						strncat(buf, buf5, 10);//add coma
						myDc->TextOut(p_Raft->Location.x - X, p_Raft->Location.y -Y, 
							buf, strlen(buf));
//					}
//					else{
/*						strncat(buf, ", IFNb:", 10);//add coma
						itoa(p_Raft->GetIFN_prot_conc(),buf5,10);
						strncat(buf, buf5, 10);//add coma
						myDc->TextOut(p_Raft->Location.x - X, p_Raft->Location.y -Y, 
							buf, strlen(buf));*/
//					}

				}
			}

		}
		myDc->SelectObject( pOldBr);
		num++;
		myDc->SetBkMode(oldBkMode);
	}
//------------------------ end drawing rafts ---------------------------//

	
	if(isMemDc)
	{
		pDC->StretchBlt( 0,0,m_ClientRect.Height( ) ,m_ClientRect.Height( ),&memdc, 0, 0,
			DrawSize, DrawSize, SRCCOPY); 
		//pDC->BitBlt( 0,0,DrawSize, DrawSize,&memdc, 0, 0, SRCCOPY ); 
		bmp.DeleteObject();
		memdc.DeleteDC();
	}
	pDC->SetBkMode(oldBkMode);

	CGeneral::is_draw_finished = true;
	if(stepGl == 10 || stepGl == 1000 || stepGl == 10000
		|| stepGl == 100000 || stepGl == 300000 || stepGl == 2000000)
	{
		find = clock();
		duration = (double)(find - startd) / CLOCKS_PER_SEC;	
//		CGeneral::out << "\n Draw duration " << duration << " step " << stepGl << endl;
	}
}

void CSurfaceView::OnTimer(UINT nIDEvent) 
{
begin:
	// TODO: Add your message handler code here and/or call default
	if(!m_OptionDlg || !CGeneral::is_draw_finished || !CGeneral::is_simul_finished) 
	{
		if(isTimer) CFormView::OnTimer(nIDEvent);
		return;
	}
	CGeneral::is_simul_finished = true;
	static int flag2 = false;
	int step = 0;
	if(CGeneral::START_SIM && ((m_StepBy && m_Next) || !m_StepBy))
	{
		if(!flag2)
		{
			CWaitCursor curs;
			CGeneral::InitProcess();
		}
		
		flag2 = true;
		try
		{
			start = clock();
			step =  CGeneral::BeginSimulation();
			stepGl = step;
			CGeneral::Simulation_Duration = step*CGeneral::TIME_STEP_LENGHT/60;
			double	duration = 0;
			if(stepGl == 10 || stepGl == 1000 || stepGl == 10000
				|| stepGl == 100000 || stepGl == 300000 || stepGl == 2000000)
			{
				fin = clock();
				stepGlS = stepGl;
				duration = (double)(fin - start) / CLOCKS_PER_SEC;	
				CGeneral::out << "\n Sim duration " << duration << " step " << stepGl << endl;
				start1 = start;
			}
			else if(stepGlS == stepGl - 1)
			{
				duration = (double)(start - start1) / CLOCKS_PER_SEC;	
				CGeneral::out << "\n Time duration " << duration << " step " << stepGl << endl;
			}
			else if(step > 1000 && stepGlS == step - 100)
			{
				duration = (double)(start - start1) / CLOCKS_PER_SEC;	
				CGeneral::out << "\n Time of 100 steps " << duration << " step " << stepGl << endl;
			}
		}
		catch(int exep)
		{
				CGeneral::START_SIM = false;
				switch(exep)
				{
				case -1:
					AfxMessageBox("Simulation problem: Too many attempts to create new Antigen!");
					AfxGetMainWnd()->PostMessage(WM_CLOSE);
					return;
				case -2:
					AfxMessageBox("Simulation problem: There is no free receptor for Ag binding!");
					AfxGetMainWnd()->PostMessage(WM_CLOSE);
					return;
				case -3:
					AfxMessageBox("Simulation problem: There is no raft to initialise SMs!");
					AfxGetMainWnd()->PostMessage(WM_CLOSE);
					return;
				}
		}
		if(!step)
		{
				CGeneral::Record_Results_to_files();
				CGeneral::Record_Results_to_files1();
				CGeneral::START_SIM = false;
				AfxMessageBox("Simulation complete");
				m_OptionDlg->OnFinishSim();
//				AfxGetMainWnd()->PostMessage(WM_CLOSE);
		}
		if(step && !(step % CGeneral::UpdateWindowVariable) && !m_stopDraw)
		{
			SetRedraw(TRUE);
			Invalidate(	!isMemDc);
			//Invalidate(!CGeneral::is_draw_rec_path);
			UpdateWindow();
		}
		m_OptionDlg->UpdateData();
		m_Next = false;
	}

	if(!CGeneral::START_SIM)
	{
				SetRedraw(FALSE);
				CGeneral::step = 0;
				flag2 = false;
				CGeneral::RecInRaft = 0;
				num = 0;
				m_PartGrid = minZoom;
	}
	if(!m_stopDraw)
	{
		if(!isTimer) 
		{
			SetTimer(1, CGeneral::TimerInitialisator, NULL);
			isTimer = true;
		}
		else
			CFormView::OnTimer(nIDEvent);
	}
	else
	{
//		if(!isTimer && !(step % 1))
		if(!isTimer && !(step % 100))
		{
			SetTimer(1, 2, NULL);
			isTimer = true;
		}
		else
		{
			if(isTimer) { KillTimer(nIDEvent); isTimer = false;}
			goto begin;
		}
	}
}
////gg1
LRESULT CSurfaceView::OnMyMessage(WPARAM WParam, LPARAM LParam)
{
	Sleep(600);
	 return (LRESULT)0;
}
