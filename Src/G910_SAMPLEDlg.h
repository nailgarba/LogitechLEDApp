
// G910_SAMPLEDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcolorbutton.h"


// CG910_SAMPLEDlg dialog
class CG910_SAMPLEDlg : public CDialogEx
{
// Construction
public:
	CG910_SAMPLEDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_G910_SAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSetlighting();
	afx_msg void OnBnClickedButtonW();
	afx_msg void OnBnClickedButtonA();
	afx_msg void OnBnClickedButtonS();
	afx_msg void OnBnClickedButtonD();
	afx_msg void OnBnClickedButtonBitmap();
	afx_msg void OnBnClickedButtonBitmapImage();
	afx_msg void OnBnClickedButtonToggleFlash();
	afx_msg void OnBnClickedButtonTogglePulse();
	afx_msg void OnBnClickedButtonSaveLighting();
	afx_msg void OnBnClickedButtonRestoreLighting();
	afx_msg void OnBnClickedButtonClearLighting();
	afx_msg void OnBnClickedButtonPulseRecorder();

	//mine
	afx_msg void OnBnClickedButtonBreathing();
	afx_msg void OnBnClickedButtonTwoFade();
	afx_msg void OnBnClickedButtonClearLighting14();
	afx_msg void OnBnClickedButtonFixed();
	afx_msg void OnBnClickedButtonClearLightingff();
	afx_msg void OnBnClickedButtonClearLightingff2();

	afx_msg void OnBnClickedButtonSaveProfile1();
	afx_msg void OnBnClickedButtonSaveProfile2();
	afx_msg void OnBnClickedButtonSaveProfile3();
	afx_msg void OnBnClickedButtonLoadProfile1();
	afx_msg void OnBnClickedButtonLoadProfile2();
	afx_msg void OnBnClickedButtonLoadProfile3();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CScrollBar m_scrollBarRed;
	CScrollBar m_scrollBarGreen;
	CScrollBar m_scrollBarBlue;
	CSliderCtrl m_Slider;


private:
	int ChangeRange(int oldVal, int oldMin, int oldMax, int newMin, int newMax); 
	void CheckBounds();
public:
    afx_msg void OnBnClickedButtonSetKeyFromScan();
    afx_msg void OnBnClickedButtonSetKeyFromHid();
    afx_msg void OnBnClickedButtonSetKeyFromName();
    afx_msg void OnBnClickedButtonStopEffects();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    
private:
    int m_targetDevice;
    void GetEffectColorValues(int *red, int *green, int *blue, bool startPicker);
public:
    afx_msg void OnBnClickedCheck1();
    CButton m_perKeyCheckBox;
    CButton m_rgbCheckBox;
	CButton m_rgbCheckBox11;
	CButton m_CheckBox6;
	CButton m_CheckBox7;
	CButton m_CheckBox8;
	CButton m_CheckBox9;
    CButton m_monochromeCheckBox;
    afx_msg void OnBnClickedGetVersion();
    afx_msg void OnBnClickedButtonInitialize();
    afx_msg void OnBnClickedButtonShutdown();
    afx_msg void OnBnClickedButtonFlashR();
    CMFCColorButton m_singleKeyStartColorPicker;
    CMFCColorButton m_singleKeyFinishColorPicker;
    afx_msg void OnBnClickedButtonPulse1();
    afx_msg void OnBnClickedButtonFkeys();
    CButton m_perKeyPulseLoop;
    afx_msg void OnBnClickedCheckExcludeNumpad();
    CButton m_disableNumpad;
    afx_msg void OnBnClickedButtonSetGkeys();
	afx_msg void OnBnClickedSinglekeyStartColor();
	afx_msg void OnBnClickedSinglekeyFinishColor();
	afx_msg void OnBnClickedSsdkcontrolGroup2();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnClickedCheck8();
	afx_msg void OnBnClickedCheck9();

//	afx_msg void OnBnClickedCheck13();
	afx_msg void OnDropdownCheck13(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedCheckPerkeyPulseLoop();
	afx_msg void OnBnClickedButtonClearLighting2();
	

	afx_msg void OnStatic();
	afx_msg void OnUpdateStatic(CCmdUI *pCmdUI);
	CStatic * pPCG;
	CStatic* speakersbmp;
	HBITMAP Entity = (HBITMAP)LoadImage(NULL, L"G910_SAMPLE\\g5602.bmp", IMAGE_BITMAP, 150, 100, LR_LOADFROMFILE);

	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	CButton breath;
	//bool zone1=true, zone2=true, zone3=true, zone4=true;
	//zone1 = true, zone2 , zone3 , zone4 ;
	CString profile1desc;
};
void PulseBetween(int startR, int startG, int startB, int finR, int finG, int finB, int interval);
