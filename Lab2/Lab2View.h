
// Lab2View.h : interface of the CLab2View class
//

#pragma once


class CLab2View : public CView
{
protected: // create from serialization only
	CLab2View() noexcept;
	DECLARE_DYNCREATE(CLab2View)
	bool malaKazaljka, velikaKazaljka;
	int mkUgao, vkUgao,klatnoUgao,kuPrev;
// Attributes
public:
	CLab2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void CrtajProzor(CDC* pDC);
	virtual void CrtajPoligon(CDC * pDC, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, COLORREF boja);
	virtual void CrtajPravougaonik(CDC * pDC, int x1, int y1, int x2, int y2, COLORREF boja);
	virtual void CrtajElipsu(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF boja);
	virtual void CrtajOrman(CDC* pDC);
	virtual void CrtajVrata(CDC* pDC);
	virtual void CrtajSobu(CDC* pDC);
	virtual void CrtajSat(CDC* pDC);
	virtual void CrtajKruzici(CDC* pDC);
	virtual void CrtajBrojeve(CDC* pDC);
	virtual void CrtajPodeoci(CDC* pDC);
	virtual void CrtajMaluKazaljku(CDC* pDC);
	virtual void CrtajVelikuKazaljku(CDC* pDC);
	virtual void CrtajKlatno(CDC* pDC);
	virtual void PomeriKlatno(CDC* pDC);
	virtual void PomeriMaluKazaljku(CDC* pDC);
	virtual void PomeriVelikuKazaljku(CDC* pDC);
	virtual void CrtajZPravougaonik(CDC* pDC, int left, int top, int right, int bottom, int width, int height, COLORREF boja);
	virtual void PrimeniTransformaciju(CDC* pDC, float cx, float cy, float rx, float ry, float alfa, XFORM* oldXForm);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLab2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	
};

#ifndef _DEBUG  // debug version in Lab2View.cpp
inline CLab2Doc* CLab2View::GetDocument() const
   { return reinterpret_cast<CLab2Doc*>(m_pDocument); }
#endif

