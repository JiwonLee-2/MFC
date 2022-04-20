
// CalDlg.cpp: 구현 파일
//


#include "pch.h"
#include "framework.h"
#include "Cal.h"
#include "CalDlg.h"
#include "afxdialogex.h"


#define OP_PLUS		1
#define OP_MINUS	2
#define OP_MUL		3
#define OP_DIV		4
#define OP_Equal	5

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalDlg 대화 상자



CCalDlg::CCalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	mResInt = 0;
	mPreint = 0;
	mPreOP = 1; 
	mPreReal = L""; //위아래 두개다 실수치 값 초기화 하는 거(string 타입이니까 null로 값 주는 거임)
	mResReal = L""; //
	mAfterDot = -1;
}

void CCalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CCalDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_1, &CCalDlg::OnBnClicked1)
	ON_BN_CLICKED(IDC_2, &CCalDlg::OnBnClicked2)
	ON_BN_CLICKED(IDC_3, &CCalDlg::OnBnClicked3)
	ON_BN_CLICKED(IDC_4, &CCalDlg::OnBnClicked4)
	ON_BN_CLICKED(IDC_5, &CCalDlg::OnBnClicked5)
	ON_BN_CLICKED(IDC_6, &CCalDlg::OnBnClicked6)
	ON_BN_CLICKED(IDC_7, &CCalDlg::OnBnClicked7)
	ON_BN_CLICKED(IDC_8, &CCalDlg::OnBnClicked8)
	ON_BN_CLICKED(IDC_9, &CCalDlg::OnBnClicked9)
	ON_BN_CLICKED(IDC_0, &CCalDlg::OnBnClicked0)
	ON_EN_CHANGE(IDC_Res, &CCalDlg::OnEnChangeRes)
	ON_BN_CLICKED(IDC_PLUS, &CCalDlg::OnBnClickedPlus)
	ON_BN_CLICKED(IDC_MINUS, &CCalDlg::OnBnClickedMinus)
	ON_BN_CLICKED(IDC_MUL, &CCalDlg::OnBnClickedMul)
	ON_BN_CLICKED(IDC_DIV, &CCalDlg::OnBnClickedDiv)
	ON_BN_CLICKED(IDC_Back, &CCalDlg::OnBnClickedBack)
	ON_BN_CLICKED(IDC_Equal, &CCalDlg::OnBnClickedEqual)
	ON_BN_CLICKED(IDC_CLEAR, &CCalDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_DOT, &CCalDlg::OnBnClickedDot)
END_MESSAGE_MAP()


// CCalDlg 메시지 처리기

BOOL CCalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	DispRes(mResInt);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCalDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CCalDlg::OnBnClicked1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PutNum(1);
}

void CCalDlg::OnBnClicked2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PutNum(2);
}

void CCalDlg::OnBnClicked3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PutNum(3);
}

void CCalDlg::OnBnClicked4()
{
	PutNum(4);
}


void CCalDlg::OnBnClicked5()
{
	PutNum(5);
}


void CCalDlg::OnBnClicked6()
{
	PutNum(6);
}


void CCalDlg::OnBnClicked7()
{
	PutNum(7);
}


void CCalDlg::OnBnClicked8()
{
	PutNum(8);
}


void CCalDlg::OnBnClicked9()
{
	PutNum(9);
}


void CCalDlg::OnBnClicked0()
{
	PutNum(0);
}



void CCalDlg::OnEnChangeRes() 
{

}
void CCalDlg::DispRes(int val)
{
	CString s;
	s.Format(L"%d", val);
	SetDlgItemText(IDC_Res, s);
}


void CCalDlg::OnBnClickedPlus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CalPreOP(OP_PLUS);
}


void CCalDlg::OnBnClickedMinus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CalPreOP(OP_MINUS);
}

void CCalDlg::OnBnClickedMul()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CalPreOP(OP_MUL);
}

void CCalDlg::OnBnClickedDiv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CalPreOP(OP_DIV);
}

void CCalDlg::OnBnClickedBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (mResInt == 0) return;
	if (mAfterDot < 0) {
		mResInt = mResInt / 10;      //mAfterDot <= 0을 할 필요없음 차피 해도 또 if문으로 새로 짜줘야되기때문.
		DispRes(mResInt);
	}
	else {
		if (mAfterDot == 0) {
			mAfterDot = -1;
			DispRes(mResInt);    // .만 남았을 때 그것마저 지울때는 정수형 부분만 출력한다는 뜻
		}
		else {
			mResReal = mResReal.Left(--mAfterDot);
			DispRes(mResInt, mResReal);  //. 뒤에를 지울때 뒤쪽을 지우고 mResReal에 넣는다. 그리고나서 mResInt와 mResReal을 출력한다.
		}
	}
}


void CCalDlg::OnBnClickedEqual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CalPreOP(OP_Equal);
}


void CCalDlg::OnBnClickedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mPreint = 0;
	mResInt = 0;
	DispRes(mResInt);

}
void CCalDlg::OnBnClickedDot()
{
	if (mAfterDot >= 0) { //.을 두번 눌렀을 경우
		MessageBox(L"Pushed two times of dot");
		return;
	}
	DispRes(mResInt, mResReal);
	mAfterDot = 0;

}
void CCalDlg::DispRes(int a, CString b)
{
	CString s;
	s.Format(L"%d", a);
	s = s + L"." + b;
	SetDlgItemText(IDC_Res, s);
}

void CCalDlg::PutNum(int n)
{
	if (mAfterDot == -1) {
		mResInt = mResInt * 10 + n;
		DispRes(mResInt);
	}
	else {
		CString t;
		mAfterDot++; //내가 .을 눌렀다는 걸 알리기 위해서 하나 올리는 거임.
		t.Format(L"%d", n); // 새로 누른걸 string타입으로 바꿔서 t에 저장하겠다.
		mResReal += t; //그 전에꺼와 합쳐서 계속 나타내겠다.
		DispRes(mResInt, mResReal); //253.0에서 5나 아무거나 넘겨주기위해서 해야함.
	}
}

void CCalDlg::CalPreOP(int op) {
	
	double a, b;
	CString c;
	switch (mPreOP) {
	case OP_PLUS:
		if (mAfterDot == -1 && mPreReal == L"")
			mPreint += mResInt;
		else {
			c = L"0." + mPreReal;
			a = _ttof(c) + mPreint;
			c = L"0." + mResReal;
			b = _ttof(c) + mResInt;
			a = a + b;																// 중복된걸 따로 빼는건 오히려 더 비효율적일 수 있음.
			mPreint = (int)a;
			mPreReal.Format(L"%f", a - mPreint);
			mPreReal = mPreReal.Right(mPreReal.GetLength() - 2);
		}
		break;
	case OP_MINUS:
		if (mAfterDot == -1 && mPreReal == L"")
			mPreint -= mResInt;
		else {
			c = L"0." + mPreReal;
			a = _ttof(c) + mPreint;
			c = L"0." + mResReal;
			b = _ttof(c) + mResInt;
			a = a - b;
			mPreint = (int)a;
			mPreReal.Format(L"%f", a - mPreint);
			mPreReal = mPreReal.Right(mPreReal.GetLength() - 2);
		}
		break;
	case OP_MUL:
		if (mAfterDot == -1 && mPreReal == L"")
			mPreint *= mResInt;
		else {
			c = L"0." + mPreReal;
			a = _ttof(c) + mPreint;
			c = L"0." + mResReal;
			b = _ttof(c) + mResInt;
			a = a * b;
			mPreint = (int)a;
			mPreReal.Format(L"%f", a - mPreint);
			mPreReal = mPreReal.Right(mPreReal.GetLength() - 2);
		}
		break;
	case OP_DIV:
		if (mAfterDot == -1 && mPreReal == L"")
			mPreint /= mResInt;
		else {
			c = L"0." + mPreReal;
			a = _ttof(c) + mPreint;
			c = L"0." + mResReal;
			b = _ttof(c) + mResInt;
			a = a / b;
			mPreint = (int)a;
			mPreReal.Format(L"%f", a - mPreint);
			mPreReal = mPreReal.Right(mPreReal.GetLength() - 2);
		}
		break;
	case OP_Equal:
		if (mResInt != 0) mPreint = mResInt;
		break;
	}
		if (mAfterDot < 0 && mPreReal == L"") DispRes(mPreint);
		else DispRes(mPreint, mPreReal); // 다시 하나의 숫자로 만들었으니 다시 분리해서 string타입으로 해야함.
	mResInt = 0;
	mResReal = L"";
	mAfterDot = -1;
	mPreOP = op;
}

//과제 : 정수 . 문자열로 지금은 했음. 그렇다면 정수. 정수로 만들어오기
// 정수. 정수로 했을 때 과정을 기술하여 정수형으로 했을 때 발생하는 문제점을 서술하며 해오기.