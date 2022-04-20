
// CalDlg.h: 헤더 파일
//

#pragma once

// CCalDlg 대화 상자
class CCalDlg : public CDialogEx
{
// 생성입니다.
public:
	CCalDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int mResInt, mPreint, mPreOP, mAfterDot; //도트는 점을 눌렀냐 안눌렀냐 확인하는거, cnt는 자릿수
public:
	CString mResReal, mPreReal;  //3.7+6.2에서 3은 mPreint가 가지고 있고, 6은 mResInt에.. 7은 mPreReal, 2는 mResReal에 저장 
public:									//소수점 뒤에 자릿수를 알리는 변수
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClicked1();
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClicked3();
	afx_msg void OnBnClicked4();
	afx_msg void OnBnClicked5();
	afx_msg void OnBnClicked6();
	afx_msg void OnBnClicked7();
	afx_msg void OnBnClicked8();
	afx_msg void OnBnClicked9();
	afx_msg void OnBnClicked0();
	void DispRes(int val);
	void CalPreOP(int op);
	void DispRes(int a, CString b);
	void PutNum(int n);
	afx_msg void OnEnChangeRes();
	afx_msg void OnBnClickedPlus();
	afx_msg void OnBnClickedMinus();
	afx_msg void OnBnClickedMul();
	afx_msg void OnBnClickedDiv();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedEqual();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedDot();
};
