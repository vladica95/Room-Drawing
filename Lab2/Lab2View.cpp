
// Lab2View.cpp : implementation of the CLab2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab2.h"
#endif

#include "Lab2Doc.h"
#include "Lab2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab2View

IMPLEMENT_DYNCREATE(CLab2View, CView)

BEGIN_MESSAGE_MAP(CLab2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CLab2View construction/destruction

CLab2View::CLab2View() noexcept
{
	// TODO: add construction code here
	malaKazaljka = false; mkUgao = 180;
	velikaKazaljka = false; vkUgao = 180;
	klatnoUgao = -5; kuPrev = 0;

}

CLab2View::~CLab2View()
{
}

BOOL CLab2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}
void CLab2View::CrtajMaluKazaljku(CDC * pDC) {
	int kazx = 12;
	int kayy = 3 * kazx;
	HENHMETAFILE MF = GetEnhMetaFile(_T("MalaKazaljka.emf"));
	PlayEnhMetaFile(pDC->m_hDC, MF, CRect(kazx-6, kayy-9, -6, -9));
	DeleteEnhMetaFile(MF);
}
void CLab2View::CrtajVelikuKazaljku(CDC * pDC) {
	int kazx = 12;
	int kayy = 3 * kazx;
	HENHMETAFILE MF = GetEnhMetaFile(_T("VelikaKazaljka.emf"));
	PlayEnhMetaFile(pDC->m_hDC, MF, CRect(kazx - 6, kayy - 9 ,-6, -9));
	DeleteEnhMetaFile(MF);
}

void CLab2View::CrtajKlatno(CDC * pDC)
{
	
	CrtajPravougaonik(pDC, 0, 0, 6, 100, RGB(219, 195, 39));
	CrtajElipsu(pDC,-12,90,18,120, RGB(219, 195, 39));
}

void CLab2View::PomeriKlatno(CDC * pDC)
{
	
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM oldXForm;
	float rx = 0, ry = 0, cx = 477, cy = 130;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, klatnoUgao, &oldXForm);
	CrtajKlatno(pDC);
	SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);
}

void CLab2View::CrtajProzor(CDC * pDC)
{
	CrtajPravougaonik(pDC, 280, 100, 385, 330, RGB(139, 69, 19));//prozor okvir
	CrtajZPravougaonik(pDC,263, 67, 403, 90, 15, 55, RGB(139, 69, 19));//garnišna
	CrtajPravougaonik(pDC, 285, 105, 330, 325, RGB(0, 191, 255));//prozor staklo1
	CrtajPravougaonik(pDC, 335, 105, 380, 325, RGB(0, 191, 255));//prozor staklo2

	CPoint tacke[3];
	tacke[2] = CPoint(270, 310);
	tacke[1] = CPoint(320, 270);
	tacke[0] = CPoint(370, 330);
	CBrush pom;
	pom.CreateSolidBrush(RGB(240, 230, 140));
	CBrush* oldBrush = pDC->SelectObject(&pom);
	pDC->BeginPath();
	pDC->MoveTo(270, 310);
	pDC->LineTo(270, 90);
	pDC->LineTo(395, 90);
	pDC->LineTo(395, 310);
	pDC->PolyBezierTo(tacke, 3);
	pDC->EndPath();
	pDC->StrokeAndFillPath();
	pDC->SelectObject(&oldBrush);
	pom.DeleteObject();

}

void CLab2View::CrtajPoligon(CDC * pDC, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, COLORREF boja)
{
	CBrush pom;
	pom.CreateSolidBrush(boja);
	CBrush* oldBrush = pDC->SelectObject(&pom);

	CPoint tacke[4];
	tacke[0] = CPoint(x1, y1);
	tacke[1] = CPoint(x2, y2);
	tacke[2] = CPoint(x3, y3);
	tacke[3] = CPoint(x4, y4);

	pDC->Polygon(tacke, 4);
	pDC->SelectObject(&oldBrush);
	pom.DeleteObject();
}

void CLab2View::CrtajPravougaonik(CDC * pDC, int x1, int y1, int x2, int y2, COLORREF boja)
{
	CBrush pom;
	pom.CreateSolidBrush(boja);
	CBrush* oldBrush = pDC->SelectObject(&pom);
	pDC->Rectangle(x1, y1, x2, y2);
	pDC->SelectObject(&oldBrush);
	pom.DeleteObject();
}

void CLab2View::CrtajElipsu(CDC * pDC, int x1, int y1, int x2, int y2, COLORREF boja)
{
	CBrush pom;
	pom.CreateSolidBrush(boja);
	CBrush* oldBrush = pDC->SelectObject(&pom);
	pDC->Ellipse(x1, y1, x2, y2);
	pDC->SelectObject(&oldBrush);
	pom.DeleteObject();
}

void CLab2View::CrtajOrman(CDC * pDC)
{
	CrtajPravougaonik(pDC, 30, 90, 125, 477, RGB(139, 69, 19));//osnova plakara
	CrtajPravougaonik(pDC, 35, 95, 80, 340, RGB(139, 69, 19));//jedno krilo
	CrtajPravougaonik(pDC, 80, 95, 120, 340, RGB(139, 69, 19));//drugo krilo
	CrtajPravougaonik(pDC, 35, 345, 120, 405, RGB(139, 69, 19));//jedna fioka
	CrtajPravougaonik(pDC, 35, 410, 120, 470, RGB(139, 69, 19));//druga fioka
	CrtajPoligon(pDC, 125, 90, 125, 477, 160, 450, 160, 120, RGB(139, 69, 19));//zadnji deo plakara

	CrtajElipsu(pDC, 65, 210, 75, 220, RGB(218, 165, 32));//rucica krilo1
	CrtajElipsu(pDC, 85, 210, 95, 220, RGB(218, 165, 32));//rucica krilo2
	CrtajElipsu(pDC, 75, 370, 85, 380, RGB(218, 165, 32));//rucica fioka1
	CrtajElipsu(pDC, 75, 435, 85, 445, RGB(218, 165, 32));//rucica fioka2

}

void CLab2View::CrtajVrata(CDC * pDC)
{
	CrtajPoligon(pDC, 565, 90, 615, 65, 615, 495, 565, 453, RGB(139, 69, 19));//vrata
	CrtajElipsu(pDC, 602, 282, 610, 292, RGB(218, 165, 32));//kvaka1
	CrtajElipsu(pDC, 585, 280, 605, 295, RGB(218, 165, 32));//kvaka
	CrtajElipsu(pDC, 605, 296, 608, 305, RGB(47, 79, 79));//kljucaonica

}

void CLab2View::CrtajSobu(CDC * pDC)
{
	CPen zidnaOlovka(BS_SOLID, 2, RGB(40, 26, 13)); CPen* old = pDC->SelectObject(&zidnaOlovka);
	CrtajPoligon(pDC, 0, 0, 60, 50, 560, 50, 620, 0, RGB(255, 255, 255));//plafon
	CrtajPoligon(pDC, 0, 0, 60, 50, 60, 450, 0, 500, RGB(130, 75, 40));//levi zid
	CrtajPoligon(pDC, 620, 0, 560, 50, 560, 450, 620, 500, RGB(130, 75, 40));//desni zid
	CrtajPravougaonik(pDC, 60, 50, 560, 450, RGB(255, 192, 128));//zadnji zid
	CrtajPoligon(pDC, 0, 500, 60, 450, 560, 450, 620, 500, RGB(169, 169, 169));//pod
	CPen obicnaOlovka(BS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(&obicnaOlovka);
	zidnaOlovka.DeleteObject();
	CrtajZPravougaonik(pDC,5, 5, 55, 45, 5, 5, RGB(169, 169, 169));
	CrtajProzor(pDC);
	CrtajOrman(pDC);
	CrtajVrata(pDC);
	CrtajSat(pDC);


}

void CLab2View::CrtajSat(CDC * pDC)
{
	CrtajZPravougaonik(pDC, 450, 130, 510, 260, 10, 10, RGB(139, 69, 19));
	CrtajZPravougaonik(pDC, 455, 135, 505, 255, 10, 10, RGB(0, 0, 0));
	PomeriKlatno(pDC);
	CrtajElipsu(pDC, 430, 167, 530, 67, RGB(139, 69, 19));//prva linija
	CrtajElipsu(pDC, 440, 157, 520, 77, RGB(219, 195, 39));//druga
	CrtajElipsu(pDC, 455, 142, 505, 92, RGB(255, 255, 255));// podeoci
	CrtajPodeoci(pDC);
	CrtajKruzici(pDC);
	CrtajBrojeve(pDC);
	//satov centar je x=>430+50=480;y=>67+50=117;
	
}

void CLab2View::CrtajKruzici(CDC * pDC)
{
	CBrush pom;
	pom.CreateSolidBrush(RGB(252,228,112));
	CBrush* oldBrush = pDC->SelectObject(&pom);
	
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM oldXForm;
	float rx = -7.5, ry = -40, alfa = 0, cx = 480, cy = 117;
	for (int i = 1; i < 13; i++) {
		PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
		pDC->Ellipse(0, 0, 15, 15);
		alfa =i* 30;
	}
		
	SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);

	pDC->SelectObject(&oldBrush);
	pom.DeleteObject();
}

void CLab2View::CrtajBrojeve(CDC * pDC)
{
	CString* niz = new CString[13];
	niz[1] = "XII"; niz[2] = "I"; niz[3] = "II"; niz[4] = "III"; niz[5] = "IV";
	niz[6] = "V"; niz[7] = "VI"; niz[8] = "VII"; niz[9] = "VIII"; niz[10] = "IX";
	niz[11] = "X"; niz[12] = "XI";

	CFont font;
	font.CreateFont(10, 5, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, 0);
	CFont* oldF = pDC->SelectObject(&font);
	int qweqwqw = SetBkMode(pDC->m_hDC, TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER);
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM oldXForm;
	
	float rx = -5, ry = -40, alfa = 0, cx = 485, cy = 120;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[1]);

	rx = -5, ry = -40, alfa += 30, cx = 485, cy = 120;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[2]);

	rx = -5, ry = -40, alfa += 30, cx = 482, cy = 122;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[3]);

	rx = -7.5, ry = -35, alfa += 30, cx = 485, cy = 126;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[4]);

	rx = -4.5, ry = -35, alfa += 30, cx = 481, cy = 125;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[5]);

	rx = -4.5, ry = -32, alfa += 30, cx = 481, cy = 125;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[6]);

	rx = -2.5, ry = -35, alfa += 30, cx = 479, cy = 120;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[7]);


	rx = -2.5, ry = -35, alfa += 30, cx = 475, cy = 122;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[8]);


	rx = -2.5, ry = -35, alfa += 30, cx = 473, cy = 117;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[9]);


	rx = -2.5, ry = -35, alfa += 30, cx = 479, cy = 113;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[10]);


	rx = -2.5, ry = -37, alfa += 30, cx = 479, cy = 115;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[11]);


	rx = -2.5, ry = -38.5, alfa += 30, cx = 482, cy = 117;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	pDC->TextOutW(0, 0, niz[12]);
	
	SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);
}

void CLab2View::CrtajPodeoci(CDC * pDC)
{
	CPen debela(BS_SOLID, 2, RGB(0, 0, 0));
	CPen tanka(BS_SOLID, 1, RGB(0, 0, 0));
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM oldXForm;
	CPen oldPen;
	float rx = -0, ry = -0, alfa = 90, cx = 480, cy = 117;
	for (int i = 1; i < 61; i++) {
		PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
		if (i % 5 == 0) {
			pDC->SelectObject(&debela);
			}
		else
			pDC->SelectObject(&tanka);
		pDC->MoveTo(0, 0);
		pDC->LineTo(0, 25);
		alfa = i * 6;
	}
	rx = -0, ry = -0, alfa = 0, cx = 460, cy = 97;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, alfa, &oldXForm);
	CrtajElipsu(pDC, 0, 0, 40, 40, RGB(255, 255, 255));//druga podeoci
	SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);
	pDC->SelectObject(&oldPen);
	debela.DeleteObject();
	tanka.DeleteObject();

}

void CLab2View::PomeriMaluKazaljku(CDC * pDC)
{
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM oldXForm;
	float rx =0, ry =0, cx = 480, cy = 117;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, mkUgao, &oldXForm);
	CrtajMaluKazaljku(pDC);
	SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);
}

void CLab2View::PomeriVelikuKazaljku(CDC * pDC)
{
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM oldXForm;
	float rx = 0, ry = 0, cx = 480, cy = 117;
	PrimeniTransformaciju(pDC, cx, cy, rx, ry, vkUgao, &oldXForm);
	CrtajVelikuKazaljku(pDC);
	SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);
}

void CLab2View::CrtajZPravougaonik(CDC * pDC, int left, int top, int right, int bottom, int width, int height, COLORREF boja)
{
	CBrush pom;
	pom.CreateSolidBrush(boja);
	CBrush* oldBrush = pDC->SelectObject(&pom);
	pDC->RoundRect(left, top, right, bottom,width,height);
	pDC->SelectObject(&oldBrush);
	pom.DeleteObject();
}

void CLab2View::PrimeniTransformaciju(CDC * pDC, float cx, float cy, float rx, float ry, float alfa, XFORM * oldXForm)
{
	DWORD dw = GetLastError();
	float pi = 3.14;
	float ug = 3.14 / 180;
	XFORM Xform, XformOld;

	bool b = GetWorldTransform(pDC->m_hDC, oldXForm);

	//translacija eDx,eDy
	Xform.eM11 = (FLOAT)1.0;
	Xform.eM12 = (FLOAT)0;
	Xform.eM21 = (FLOAT)0;
	Xform.eM22 = (FLOAT)1.0;

	Xform.eDx = (FLOAT)rx;
	Xform.eDy = (FLOAT)ry;

	b = SetWorldTransform(pDC->m_hDC, &Xform);
	dw = GetLastError();

	//rotacija
	Xform.eM11 = cos(ug*alfa);
	Xform.eM12 = sin(ug*alfa);
	Xform.eM21 = -sin(ug*alfa);
	Xform.eM22 = cos(ug*alfa);

	Xform.eDx = 0;
	Xform.eDy = 0;

	ModifyWorldTransform(pDC->m_hDC, &Xform, MWT_RIGHTMULTIPLY);

	//translacija
	Xform.eM11 = (FLOAT)1.0;
	Xform.eM12 = (FLOAT)0;
	Xform.eM21 = (FLOAT)0;
	Xform.eM22 = (FLOAT)1.0;

	Xform.eDx = (FLOAT)cx;
	Xform.eDy = (FLOAT)cy;

	ModifyWorldTransform(pDC->m_hDC, &Xform, MWT_RIGHTMULTIPLY);
}

// CLab2View drawing

void CLab2View::OnDraw(CDC* pDC)
{
	CLab2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CrtajSobu(pDC);
	PomeriVelikuKazaljku(pDC);

	PomeriMaluKazaljku(pDC);
	
}


// CLab2View printing

BOOL CLab2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLab2View diagnostics

#ifdef _DEBUG
void CLab2View::AssertValid() const
{
	CView::AssertValid();
}

void CLab2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab2Doc* CLab2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab2Doc)));
	return (CLab2Doc*)m_pDocument;
}
#endif //_DEBUG


// CLab2View message handlers


void CLab2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//m=>77
	//v=>86
	if (nChar == 77) {
		mkUgao = mkUgao + 30;
		if (kuPrev == 0) {
			klatnoUgao++;
			if (klatnoUgao == 5)
				kuPrev = 1;
		}
		else {
			klatnoUgao--;
			if (klatnoUgao == -5)
				kuPrev = 0;
		}
		Invalidate();
	}

	if (nChar == 86) {
		vkUgao = vkUgao + 6;
		if (kuPrev == 0) {
			klatnoUgao++;
			if (klatnoUgao == 5)
				kuPrev = 1;
		}
		else {
			klatnoUgao--;
			if (klatnoUgao == -5)
				kuPrev = 0;
		}
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
