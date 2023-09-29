
// G910_SAMPLEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "G910_SAMPLE.h"
#include "G910_SAMPLEDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>
#include <string>
//#include <SDL2/SDL.h> 
std::string filename1 = "profile1.txt";
std::string filename2 = "profile2.txt";
std::string filename3 = "profile3.txt";




#pragma comment(lib, "LogitechLEDLib.lib")

#include "LogitechLEDLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ULONG_PTR g_gdiplusToken;

#define RGB_MIN 0
#define RGB_MAX 255
#define RGB_PERCENT_MAX 100
#define ALPHA_MAX 255
//bool zone1 = true, zone2 = true, zone3 = true, zone4 = true;
bool zone1 = true, zone2 = true, zone3 = true, zone4 = true;
int interval, profileloaded;
std::string p1desc;
// CG910_SAMPLEDlg dialog




CG910_SAMPLEDlg::CG910_SAMPLEDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CG910_SAMPLEDlg::IDD, pParent)
    , profile1desc(_T("Profile 1 description"))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CG910_SAMPLEDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SCROLLBAR_RED, m_scrollBarRed);
    DDX_Control(pDX, IDC_SCROLLBAR_GREEN, m_scrollBarGreen);
    DDX_Control(pDX, IDC_SCROLLBAR_BLUE, m_scrollBarBlue);
    DDX_Control(pDX, IDC_CHECK6, m_CheckBox6);
    DDX_Control(pDX, IDC_CHECK7, m_CheckBox7);
    DDX_Control(pDX, IDC_CHECK8, m_CheckBox8);
    DDX_Control(pDX, IDC_CHECK9, m_CheckBox9);


    DDX_Control(pDX, IDC_SLIDER1, m_Slider);

    //DDX_Control(pDX, IDC_STATIC27, m_disableNumpad);
    //pPCG = (CStatic*)GetDlgItem(IDC_STATIC27);

    DDX_Control(pDX, IDC_BUTTON_BREATHING, breath);
    //DDX_Text(pDX, IDC_EDIT1, profile1desc);
}

BEGIN_MESSAGE_MAP(CG910_SAMPLEDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_BUTTON_SETLIGHTING, &CG910_SAMPLEDlg::OnBnClickedButtonSetlighting)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_LIGHTING, &CG910_SAMPLEDlg::OnBnClickedButtonSaveLighting)
    ON_BN_CLICKED(IDC_BUTTON_RESTORE_LIGHTING, &CG910_SAMPLEDlg::OnBnClickedButtonRestoreLighting)
    ON_BN_CLICKED(IDC_BUTTON_CLEAR_LIGHTING, &CG910_SAMPLEDlg::OnBnClickedButtonClearLighting)
    ON_WM_SYSCOMMAND()
    ON_BN_CLICKED(IDC_GET_VERSION, &CG910_SAMPLEDlg::OnBnClickedGetVersion)
    ON_BN_CLICKED(IDC_BUTTON_INITIALIZE, &CG910_SAMPLEDlg::OnBnClickedButtonInitialize)
    ON_BN_CLICKED(IDC_BUTTON_SHUTDOWN, &CG910_SAMPLEDlg::OnBnClickedButtonShutdown)
    ON_BN_CLICKED(IDC_SSDKCONTROL_GROUP2, &CG910_SAMPLEDlg::OnBnClickedSsdkcontrolGroup2)

    //mine
    ON_BN_CLICKED(IDC_BUTTON_BREATHING, &CG910_SAMPLEDlg::OnBnClickedButtonBreathing)
    ON_BN_CLICKED(IDC_BUTTON_TWO_FADE, &CG910_SAMPLEDlg::OnBnClickedButtonTwoFade)
    ON_BN_CLICKED(IDC_BUTTON_CLEAR_LIGHTING14, &CG910_SAMPLEDlg::OnBnClickedButtonClearLighting14)
    ON_BN_CLICKED(IDC_BUTTON_FIXED, &CG910_SAMPLEDlg::OnBnClickedButtonFixed)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_PROFILE1, &CG910_SAMPLEDlg::OnBnClickedButtonSaveProfile1)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_PROFILE2, &CG910_SAMPLEDlg::OnBnClickedButtonSaveProfile2)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_PROFILE3, &CG910_SAMPLEDlg::OnBnClickedButtonSaveProfile3)

    ON_BN_CLICKED(IDC_BUTTON_LOAD_PROFILE1, &CG910_SAMPLEDlg::OnBnClickedButtonLoadProfile1)
    ON_BN_CLICKED(IDC_BUTTON_LOAD_PROFILE2, &CG910_SAMPLEDlg::OnBnClickedButtonLoadProfile2)
    ON_BN_CLICKED(IDC_BUTTON_LOAD_PROFILE3, &CG910_SAMPLEDlg::OnBnClickedButtonLoadProfile3)
    ON_BN_CLICKED(IDC_BUTTON_PLAY, &CG910_SAMPLEDlg::OnBnClickedButtonPlay)



    ON_BN_CLICKED(IDC_CHECK6, &CG910_SAMPLEDlg::OnBnClickedCheck6)
    ON_BN_CLICKED(IDC_CHECK7, &CG910_SAMPLEDlg::OnBnClickedCheck7)
    ON_BN_CLICKED(IDC_CHECK8, &CG910_SAMPLEDlg::OnClickedCheck8)
    ON_BN_CLICKED(IDC_CHECK9, &CG910_SAMPLEDlg::OnBnClickedCheck9)

    ON_NOTIFY(BCN_DROPDOWN, IDC_CHECK13, &CG910_SAMPLEDlg::OnDropdownCheck13)
    ON_BN_CLICKED(IDC_BUTTON_CLEAR_LIGHTING2, &CG910_SAMPLEDlg::OnBnClickedButtonClearLighting2)
    //	ON_COMMAND(IDC_STATIC27, &CG910_SAMPLEDlg::OnStatic)
    //	ON_UPDATE_COMMAND_UI(IDC_STATIC27, &CG910_SAMPLEDlg::OnUpdateStatic)
    ON_EN_CHANGE(IDC_EDIT1, &CG910_SAMPLEDlg::OnEnChangeEdit1)
    ON_EN_CHANGE(IDC_EDIT2, &CG910_SAMPLEDlg::OnEnChangeEdit2)
    ON_EN_CHANGE(IDC_EDIT2, &CG910_SAMPLEDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lasteffect, loadeffect;
//zone struct to control each zone
struct zone {
    int zonenum, rs, gs, bs, re, ge, be, r, g, b;
    bool rb, gb, bb;
    int effect;
    int state;//0=off,1=on
    void zoneinit(int zonenum) {
        this->zonenum = zonenum;
        rs = 0, gs = 0, bs = 0, re = 0, ge = 0, be = 0, r = 0, g = 0, b = 0;
        rb = true, gb = true, bb = true;
        effect = 0;
        state = 1;
    }
    void lightZone() {
        LogiLedSetLightingForTargetZone(LogiLed::Speaker, zonenum, r, g, b);
    }
    void lightZone(int r, int g, int b) {
        LogiLedSetLightingForTargetZone(LogiLed::Speaker, zonenum, r, g, b);
    }
    std::string toString() {
        std::string srs, sgs, sbs, sre, sge, sbe;
        //ifs
        {
            if (rs < 100 && rs >= 10) {
                srs = "0" + std::to_string(rs);
            }
            else if (rs <= 0) {
                srs = "000";
            }
            else if (rs < 10 && rs>0) {
                srs = "00" + std::to_string(rs);
            }
            else if (rs >= 100) {
                srs = "100";
            }
            //
            if (gs < 100 && gs >= 10) {
                sgs = "0" + std::to_string(gs);
            }
            else if (gs <= 0) {
                sbs = "000";
            }
            else if (gs < 10) {
                sgs = "00" + std::to_string(gs);
            }
            else if (gs >= 100) {
                sgs = "100";
            }//
            if (bs < 100 && bs >= 10) {
                sbs = "0" + std::to_string(bs);
            }
            else if (bs <= 0) {
                sbs = "000";
            }
            else if (bs < 10) {
                sbs = "00" + std::to_string(bs);
            }
            else if (bs >= 100) {
                sbs = "100";
            }//
            if (re < 100 && re >= 10) {
                sre = "0" + std::to_string(re);
            }
            else if (re <= 0) {
                sre = "000";
            }
            else if (re < 10) {
                sre = "00" + std::to_string(re);
            }
            else if (re >= 100) {
                sre = "100";
            }//
            if (ge < 100 && ge >= 10) {
                sge = "0" + std::to_string(ge);
            }
            else if (ge <= 0) {
                sge = "000";
            }
            else if (ge < 10) {
                sge = "00" + std::to_string(ge);
            }
            else if (ge >= 100) {
                sge = "100";
            }//
            if (be < 100 && be >= 10) {
                sbe = "0" + std::to_string(be);
            }
            else if (be <= 0) {
                sbe = "000";
            }
            else if (be < 10) {
                sbe = "00" + std::to_string(be);
            }
            else  if (be >= 100) {
                sbe = "100";
            }
        }
        std::string val = std::to_string(zonenum) + std::to_string(state) + srs + sgs + sbs + sre + sge + sbe;
        return val;
    }

};
zone zz1, zz2, zz3, zz4;

void loopNum(int& x, bool& flip) {
    if (flip) {
        if (x < 100) {
            x++;
            if (x == 100) { flip = !flip; }
        }
    }
    else {
        x--;
        if (x == 0) { flip = !flip; }
    }
}

void loopNum(int& x, int uplim, bool& flip) {
    if (flip) {
        if (x < uplim) {
            x++;
            if (x == uplim) { flip = !flip; }
        }
    }
    else {
        x--;
        if (x == 0) { flip = !flip; }
    }
}
void loopNum(int& x, int uplim, int downlim, bool& flip) {
    if (flip) {
        if (x < uplim) {
            x++;
            if (x == uplim) { flip = !flip; }
        }
    }
    else {
        x--;
        if (x == downlim) { flip = !flip; }
    }
}

// CG910_SAMPLEDlg message handlers

BOOL CG910_SAMPLEDlg::OnInitDialog()
{
    speakersbmp = (CStatic*)GetDlgItem(SPEAKERSBMP);
    CDialogEx::OnInitDialog();
    zz1.zoneinit(1);
    zz2.zoneinit(2);
    zz3.zoneinit(3);
    zz4.zoneinit(0);


    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here
    if (!LogiLedInit())
    {
        MessageBox(L"Couldn't initialize LED SDK", L"ERROR", 0);
    }
    m_targetDevice = LOGI_DEVICETYPE_ALL;

    // set the edit boxes to have valid numbers
    SetDlgItemInt(IDC_EDIT_RED, 100, 0);
    SetDlgItemInt(IDC_EDIT_GREEN, 0, 0);
    SetDlgItemInt(IDC_EDIT_BLUE, 50, 0);
    // HWND hWnd = GetDlgItem(IDC_EDIT1);
    SetDlgItemInt(IDC_EDIT_RED2, 0, 0);
    SetDlgItemInt(IDC_EDIT_GREEN2, 50, 0);
    SetDlgItemInt(IDC_EDIT_BLUE2, 100, 0);
    SetDlgItemInt(IDC_EDIT_COUNT, 1, 0);




    m_Slider.SetPos(50);


    //setup scrollbars
    m_scrollBarRed.SetScrollRange(0, 100);
    m_scrollBarRed.SetScrollPos(0);
    m_scrollBarGreen.SetScrollRange(0, 100);
    m_scrollBarGreen.SetScrollPos(0);
    m_scrollBarBlue.SetScrollRange(0, 100);
    m_scrollBarBlue.SetScrollPos(0);
    m_CheckBox6.SetCheck(1);
    m_CheckBox7.SetCheck(1);
    m_CheckBox8.SetCheck(1);
    m_CheckBox9.SetCheck(1);

    m_targetDevice = LOGI_DEVICETYPE_ALL;
    LogiLedSetTargetDevice(m_targetDevice);
    return TRUE;  // return TRUE  unless you set the focus to a control
    pPCG->SetBitmap(Entity);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
// Draw bitmap image of speakers
void CG910_SAMPLEDlg::OnPaint()
{
    HBITMAP Speakerimg = (HBITMAP)LoadImage(NULL, L"g5602.bmp", IMAGE_BITMAP, 250, 180, LR_LOADFROMFILE);
    speakersbmp->SetBitmap(Speakerimg);
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;




        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CG910_SAMPLEDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);

}

void CG910_SAMPLEDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    int CurPos = pScrollBar->GetScrollPos();
    // Determine the new position of scroll box.
    switch (nSBCode)
    {
    case SB_LEFT:      // Scroll to far left.
        CurPos = RGB_MIN;
        break;

    case SB_RIGHT:      // Scroll to far right.
        CurPos = RGB_PERCENT_MAX;
        break;

    case SB_ENDSCROLL:   // End scroll.
        break;

    case SB_LINELEFT:      // Scroll left.
        if (CurPos > RGB_MIN)
            CurPos--;
        break;

    case SB_LINERIGHT:   // Scroll right.
        if (CurPos < RGB_PERCENT_MAX)
            CurPos++;
        break;

    case SB_PAGELEFT:    // Scroll one page left.
    {
        // Get the page size.
        SCROLLINFO   info;
        pScrollBar->GetScrollInfo(&info, SIF_ALL);

        if (CurPos > RGB_MIN)
            CurPos = max(0, CurPos - (int)info.nPage);
    }
    break;

    case SB_PAGERIGHT:      // Scroll one page right
    {
        // Get the page size.
        SCROLLINFO   info;
        pScrollBar->GetScrollInfo(&info, SIF_ALL);

        if (CurPos < RGB_PERCENT_MAX)
            CurPos = min(122, CurPos + (int)info.nPage);
    }
    break;

    case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
        CurPos = nPos;      // of the scroll box at the end of the drag operation.
        break;

    case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
        CurPos = nPos;     // position that the scroll box has been dragged to.
        break;
    }

    pScrollBar->SetScrollPos(CurPos);

    int red = m_scrollBarRed.GetScrollPos();
    int green = m_scrollBarGreen.GetScrollPos();
    int blue = m_scrollBarBlue.GetScrollPos();

    bool ret = LogiLedSetLighting(red, green, blue);

    CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

// change a range from oldMin - oldMax to newMin - newMax
int CG910_SAMPLEDlg::ChangeRange(int oldVal, int oldMin, int oldMax, int newMin, int newMax)
{
    return (((oldVal - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

// check the bounds of whatever is in the box to make sure nothing goes out of range
void CG910_SAMPLEDlg::CheckBounds()
{
    // get the values to be checked
    int checkRed = GetDlgItemInt(IDC_EDIT_RED, 0, 0);
    int checkGreen = GetDlgItemInt(IDC_EDIT_GREEN, 0, 0);
    int checkBlue = GetDlgItemInt(IDC_EDIT_BLUE, 0, 0);

    int checkRed2 = GetDlgItemInt(IDC_EDIT_RED2, 0, 0);
    int checkGreen2 = GetDlgItemInt(IDC_EDIT_GREEN2, 0, 0);
    int checkBlue2 = GetDlgItemInt(IDC_EDIT_BLUE2, 0, 0);

    // check to see if any are above max/below min, then set the checked val to the valid value
    checkRed > RGB_PERCENT_MAX ? checkRed = RGB_PERCENT_MAX : checkRed = checkRed;
    checkRed < RGB_MIN ? checkRed = RGB_MIN : checkRed = checkRed;

    checkGreen > RGB_PERCENT_MAX ? checkGreen = RGB_PERCENT_MAX : checkGreen = checkGreen;
    checkGreen < RGB_MIN ? checkGreen = RGB_MIN : checkGreen = checkGreen;

    checkBlue > RGB_PERCENT_MAX ? checkBlue = RGB_PERCENT_MAX : checkBlue = checkBlue;
    checkBlue < RGB_MIN ? checkBlue = RGB_MIN : checkBlue = checkBlue;


    checkRed2 > RGB_PERCENT_MAX ? checkRed2 = RGB_PERCENT_MAX : checkRed2 = checkRed2;
    checkRed2 < RGB_MIN ? checkRed2 = RGB_MIN : checkRed2 = checkRed2;

    checkGreen2 > RGB_PERCENT_MAX ? checkGreen2 = RGB_PERCENT_MAX : checkGreen2 = checkGreen2;
    checkGreen2 < RGB_MIN ? checkGreen2 = RGB_MIN : checkGreen2 = checkGreen2;

    checkBlue2 > RGB_PERCENT_MAX ? checkBlue2 = RGB_PERCENT_MAX : checkBlue2 = checkBlue2;
    checkBlue2 < RGB_MIN ? checkBlue2 = RGB_MIN : checkBlue2 = checkBlue2;

    // it wouldn't make sense to have an interval of 0, so make it 50 min (super fast for blinking - good for pulsing)

    // reflect those changes on the sample
    SetDlgItemInt(IDC_EDIT_RED, checkRed, 0);
    SetDlgItemInt(IDC_EDIT_GREEN, checkGreen, 0);
    SetDlgItemInt(IDC_EDIT_BLUE, checkBlue, 0);

    SetDlgItemInt(IDC_EDIT_RED2, checkRed2, 0);
    SetDlgItemInt(IDC_EDIT_GREEN2, checkGreen2, 0);
    SetDlgItemInt(IDC_EDIT_BLUE2, checkBlue2, 0);
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS

bool stop = false;

// read profile txt files and insert values into zone structs
void readprofiles(std::string filename) {
    using namespace std;
    ifstream myfile;
    string line;
    myfile.open(filename, ios::in);
    while (getline(cin, line)) {
        int x = stoi(line.substr(0, 1));//get zone num
        int y = stoi(line.substr(1, 2));//check if enabled
        switch (x) {
        case 1:
            //zone is on
            zz1.state = y;
            if (y == 1) {
                zz1.rs = stoi(line.substr(2, 5));
                zz1.gs = stoi(line.substr(5, 8));
                zz1.bs = stoi(line.substr(8, 11));
                zz1.re = stoi(line.substr(11, 14));
                zz1.ge = stoi(line.substr(14, 17));
                zz1.be = stoi(line.substr(17, 20));
                // zz1.interval = stoi(line.substr(20));
            }
            break;
        case 2:
            zz2.state = y;
            if (y == 1) {
                zz2.rs = stoi(line.substr(2, 5));
                zz2.gs = stoi(line.substr(5, 8));
                zz2.bs = stoi(line.substr(8, 11));
                zz2.re = stoi(line.substr(11, 14));
                zz2.ge = stoi(line.substr(14, 17));
                zz2.be = stoi(line.substr(17, 20));
                //zz2.interval = stoi(line.substr(20));
            }
            break;
        case 3:
            zz3.state = y;
            if (y == 1) {
                zz3.rs = stoi(line.substr(2, 5));
                zz3.gs = stoi(line.substr(5, 8));
                zz3.bs = stoi(line.substr(8, 11));
                zz3.re = stoi(line.substr(11, 14));
                zz3.ge = stoi(line.substr(14, 17));
                zz3.be = stoi(line.substr(17, 20));
                //  zz3.interval = stoi(line.substr(20));
            }
            break;
        case 0:
            zz4.state = y;
            if (y == 1) {
                zz4.rs = stoi(line.substr(2, 5));
                zz4.gs = stoi(line.substr(5, 8));
                zz4.bs = stoi(line.substr(8, 11));
                zz4.re = stoi(line.substr(11, 14));
                zz4.ge = stoi(line.substr(14, 17));
                zz4.be = stoi(line.substr(17, 20));
                // zz4.interval = stoi(line.substr(20));
            }
            break;
        case 5:
            loadeffect = stoi(line.substr(1, 2));
            break;
        }
    }
}

// write zone values into profile txt files
void writeprofiles(std::string filename) {
    using namespace std;
    fstream myfile;
    myfile.open(filename, ios::out | ios::trunc);
    myfile << zz1.toString() << "\n" << zz2.toString() << "\n" << zz3.toString() << "\n" << zz4.toString() << "\n" << 5 << lasteffect;


}
void writeprofiles(std::string filename, std::string s) {
    using namespace std;
    fstream myfile;
    myfile.open(filename, ios::out | ios::trunc);
    myfile << zz1.toString() << "\n" << zz2.toString() << "\n" << zz3.toString() << "\n" << zz4.toString() << "\n" << 5 << lasteffect << s;

}

//function to set lighting for each zone if its on

void ZoneSetLighting(int r, int g, int b) {
    if (zz1.state) {
        zz1.effect = lasteffect;
        zz1.r = r;
        zz1.g = g;
        zz1.b = b;
        LogiLedSetLightingForTargetZone(LogiLed::Speaker, 1, r, g, b);
    }
    if (zz2.state) {
        zz2.effect = lasteffect;
        zz2.r = r;
        zz2.g = g;
        zz2.b = b;
        LogiLedSetLightingForTargetZone(LogiLed::Speaker, 2, r, g, b);
    }

    if (zz3.state) {
        zz3.effect = lasteffect;
        zz3.r = r;
        zz3.g = g;
        zz3.b = b;
        LogiLedSetLightingForTargetZone(LogiLed::Speaker, 3, r, g, b);
    }
    if (zz4.state) {
        zz4.effect = lasteffect;
        zz4.r = r;
        zz4.g = g;
        zz4.b = b;
        LogiLedSetLightingForTargetZone(LogiLed::Speaker, 0, r, g, b);
    }
}
void ZoneSetLightingValues(int r, int g, int b) {
    if (zz1.state) {
        zz1.effect = lasteffect;
        zz1.rs = r;
        zz1.gs = g;
        zz1.bs = b;
    }
    if (zz2.state) {
        zz2.effect = lasteffect;
        zz2.rs = r;
        zz2.gs = g;
        zz2.bs = b;
    }

    if (zz3.state) {
        zz3.effect = lasteffect;
        zz3.rs = r;
        zz3.gs = g;
        zz3.bs = b;
    }
    if (zz4.state) {
        zz4.effect = lasteffect;
        zz4.rs = r;
        zz4.gs = g;
        zz4.bs = b;
    }
}
void ZoneSetLightingValues(int r, int g, int b, int re, int ge, int be) {
    if (zz1.state) {
        zz1.effect = lasteffect;
        zz1.rs = r;
        zz1.gs = g;
        zz1.bs = b;
        zz1.re = re;
        zz1.ge = ge;
        zz1.be = be;
    }
    if (zz2.state) {
        zz2.effect = lasteffect;
        zz2.rs = r;
        zz2.gs = g;
        zz2.bs = b;
        zz2.re = re;
        zz2.ge = ge;
        zz2.be = be;
    }

    if (zz3.state) {
        zz3.effect = lasteffect;
        zz3.rs = r;
        zz3.gs = g;
        zz3.bs = b;
        zz3.re = re;
        zz3.ge = ge;
        zz3.be = be;
    }
    if (zz4.state) {
        zz4.effect = lasteffect;
        zz4.rs = r;
        zz4.gs = g;
        zz4.bs = b;
        zz4.re = re;
        zz4.ge = ge;
        zz4.be = be;
    }
}

//PulseBetween(100, 100, 0, 0, 0, 0, 50);
void IntervalPulseBetween(int startR, int startG, int startB, int finR, int finG, int finB, int interval) {
    for (int x = 0; x < 2; x++) {
        while (startG > 20) {
            LogiLedSetLighting(startR, startG, startB);
            Sleep(interval);
            startG--;
        }
        while (startG < 100) {
            LogiLedSetLighting(startR, startG, startB);
            Sleep(interval);
            startG++;
        }
        while (startR > 100) {
            LogiLedSetLighting(startR, startG, startB);
            Sleep(interval);
            startR--;
        }
        while (startR < 100) {
            LogiLedSetLighting(startR, startG, startB);
            Sleep(interval);
            startR++;
        }
        /*while (startB > 100) {
           LogiLedSetLighting(startR, startG, startB);
           Sleep(interval);
           startB++;
       }
       while (startB < 100) {
           LogiLedSetLighting(startR, startG, startB);
           Sleep(interval);
           startB++;
       }*/
    }
}
void IntervalPulseBetweenZoned(int startR, int startG, int startB, int finR, int finG, int finB, int interval, int zone) {
    for (int x = 0; x < 2; x++) {
        while (startG > 20) {
            LogiLedSetLightingForTargetZone(LogiLed::DeviceType::Speaker, zone, startR, startG, startB);
            Sleep(interval);
            startG--;
        }
        while (startG < 100) {
            LogiLedSetLightingForTargetZone(LogiLed::DeviceType::Speaker, zone, startR, startG, startB);
            Sleep(interval);
            startG++;
        }
        while (startR > 100) {
            LogiLedSetLightingForTargetZone(LogiLed::DeviceType::Speaker, zone, startR, startG, startB);
            Sleep(interval);
            startR--;
        }
        while (startR < 100) {
            LogiLedSetLightingForTargetZone(LogiLed::DeviceType::Speaker, zone, startR, startG, startB);
            Sleep(interval);
            startR++;
        }
        /*while (startB > 100) {
           LogiLedSetLighting(startR, startG, startB);
           Sleep(interval);
           startB++;
       }
       while (startB < 100) {
           LogiLedSetLighting(startR, startG, startB);
           Sleep(interval);
           startB++;
       }*/
    }
}


void PulseBetween(int startR, int startG, int startB, int finR, int finG, int finB) {
    for (int x = 0; x < 2; x++) {
        while (startG > 20) {
            LogiLedSetLighting(startR, startG, startB);
            Sleep(interval);
            startG--;
        }
        while (startG < 100) {
            LogiLedSetLighting(startR, startG, startB);
            Sleep(interval);
            startG++;
        }
        while (startR > 100) {
            LogiLedSetLighting(startR, startG, startB);
            Sleep(interval);
            startR--;
        }
        while (startR < 100) {
            LogiLedSetLighting(startR, startG, startB);
            Sleep(interval);
            startR++;
        }
        /*while (startB > 100) {
           LogiLedSetLighting(startR, startG, startB);
           Sleep(interval);
           startB++;
       }
       while (startB < 100) {
           LogiLedSetLighting(startR, startG, startB);
           Sleep(interval);
           startB++;
       }*/
    }
}


void colorBrightness(double r, double g, double b, double brightness) {
    if (0 <= brightness && 1.0 >= brightness && !stop) {
        //LogiLedSetLighting((int)(r * brightness), (int)(g * brightness), (int)(b * brightness));
        ZoneSetLighting((int)(r * brightness), (int)(g * brightness), (int)(b * brightness));
    }
}
void twoColorSkew(double r1, double g1, double b1, double r2, double g2, double b2, double skew) {
    if (0 <= skew && 1.0 >= skew && !stop) {
        int r, g, b;
        r = (int)(r1 * skew + r2 * (1 - skew));
        g = (int)(g1 * skew + g2 * (1 - skew));
        b = (int)(b1 * skew + b2 * (1 - skew));
        ZoneSetLighting(r, g, b);


    }
}

void colorTransition(int r1, int g1, int b1, int r2, int g2, int b2, int interval, int count) {
    double skew = 1.0;
    double flip = true, stop = true;
    while (count > 0) {
        count--;
        while (skew >= 0) {
            twoColorSkew(r1, g1, b1, r2, g2, b2, skew);
            Sleep(interval);
            skew = skew - 0.01;

        }
        while (skew <= 1.0) {
            twoColorSkew(r1, g1, b1, r2, g2, b2, skew);
            Sleep(interval);
            skew = skew + 0.01;


        }
    }

}



void breatheOneColor(double r, double g, double b, int interval, int count) {
    bool flip = true;
    while (count > 0 && !stop) {
        count--;
        if (flip) {
            for (double perc = 1.0; 0 < perc && !stop; perc = perc - 0.01) {
                colorBrightness(r, g, b, perc);
                Sleep(interval);
            }
            flip = !flip;
        }
        if (!flip) {
            for (double perc = 0.0; 1 > perc && !stop; perc = perc + 0.01) {
                colorBrightness(r, g, b, perc);
                Sleep(interval);
            }
            flip = !flip;
        }
    }
}






///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//buttons



//NAIL TEST
void CG910_SAMPLEDlg::OnBnClickedButtonClearLighting()
{
    // TODO: Add your control notification handler code here
    //LogiLedPulseSingleKey();
    //IntervalPulseBetween(100, 100, 0, 0, 0, 0, 100);
    breatheOneColor(100, 10, 46, 50, 2);
}


//BREATHING
void CG910_SAMPLEDlg::OnBnClickedButtonBreathing()
{
    interval = m_Slider.GetPos();
    int redVal = GetDlgItemInt(IDC_EDIT_RED, 0, 0);
    int greenVal = GetDlgItemInt(IDC_EDIT_GREEN, 0, 0);
    int blueVal = GetDlgItemInt(IDC_EDIT_BLUE, 0, 0);
    breatheOneColor(redVal, greenVal, blueVal, interval, 1);

    //LogiLedSetLighting(100, 100, 100);
    lasteffect = 1;
    ZoneSetLightingValues(redVal, greenVal, blueVal);
}

//TWO color fade
void CG910_SAMPLEDlg::OnBnClickedButtonTwoFade()
{
    CheckBounds();
    interval = m_Slider.GetPos();
    int redVal = GetDlgItemInt(IDC_EDIT_RED, 0, 0);
    int greenVal = GetDlgItemInt(IDC_EDIT_GREEN, 0, 0);
    int blueVal = GetDlgItemInt(IDC_EDIT_BLUE, 0, 0);

    int redVal2 = GetDlgItemInt(IDC_EDIT_RED2, 0, 0);
    int greenVal2 = GetDlgItemInt(IDC_EDIT_GREEN2, 0, 0);
    int blueVal2 = GetDlgItemInt(IDC_EDIT_BLUE2, 0, 0);
    lasteffect = 2;

    colorTransition(redVal, greenVal, blueVal, redVal2, greenVal2, blueVal2, interval, 1);

    ZoneSetLightingValues(redVal, greenVal, blueVal, redVal2, greenVal2, blueVal2);
}



///SAVE PROFILES
void CG910_SAMPLEDlg::OnBnClickedButtonSaveProfile1()
{
    writeprofiles(filename1);
}
void CG910_SAMPLEDlg::OnBnClickedButtonSaveProfile2()
{
    writeprofiles(filename2);
}void CG910_SAMPLEDlg::OnBnClickedButtonSaveProfile3()
{
    writeprofiles(filename3);
}

//LOAD PROFILES

void CG910_SAMPLEDlg::OnBnClickedButtonLoadProfile1()
{
    profileloaded = 1;
    lasteffect = 0;
}
void CG910_SAMPLEDlg::OnBnClickedButtonLoadProfile2()
{
    profileloaded = 2;
    lasteffect = 1;
}
void CG910_SAMPLEDlg::OnBnClickedButtonLoadProfile3()
{
    profileloaded = 3;
    lasteffect = 2;
}

//PLAY
void CG910_SAMPLEDlg::OnBnClickedButtonPlay()
{
    //0=still, 1=breathe, 2=fade 2 colors 
    if (profileloaded == 1) {
        readprofiles(filename1);
    }
    else if (profileloaded == 2) {
        readprofiles(filename2);
    }
    else if (profileloaded == 3) {
        readprofiles(filename3);
    }
    int count = GetDlgItemInt(IDC_EDIT_COUNT, 0, 0);
    int rs, gs, bs, re, ge, be, r, g, b;
    rs = 0, gs = 0, bs = 0, re = 0, ge = 0, be = 0, r = 0, g = 0, b = 0;
    switch (lasteffect) {
    case 0:
        zz1.lightZone(zz1.rs, zz1.gs, zz1.bs);
        zz2.lightZone(zz2.rs, zz2.gs, zz2.bs);
        zz3.lightZone(zz3.rs, zz3.gs, zz3.bs);
        zz4.lightZone(zz4.rs, zz4.gs, zz4.bs);
        break;

    case 1:
        if (zz1.state == 1) {
            r = zz1.rs;
            g = zz1.gs;
            b = zz1.bs;
        }
        else if (zz2.state == 1) {
            r = zz2.rs;
            g = zz2.gs;
            b = zz2.bs;
        }
        else if (zz3.state == 1) {
            r = zz3.rs;
            g = zz3.gs;
            b = zz3.bs;
        }
        else if (zz4.state == 1) {
            r = zz4.rs;
            g = zz4.gs;
            b = zz4.bs;
        }
        else {

        }
        breatheOneColor(r, g, b, interval, count);
        break;

    case 2:
        if (zz1.state == 1) {
            rs = zz1.rs;
            gs = zz1.gs;
            bs = zz1.bs;
            re = zz1.re;
            ge = zz1.ge;
            be = zz1.be;
        }
        else if (zz2.state == 1) {
            rs = zz2.rs;
            gs = zz2.gs;
            bs = zz2.bs;
            re = zz2.re;
            ge = zz2.ge;
            be = zz2.be;
        }
        else if (zz3.state == 1) {
            rs = zz3.rs;
            gs = zz3.gs;
            bs = zz3.bs;
            re = zz3.re;
            ge = zz3.ge;
            be = zz3.be;
        }
        else if (zz4.state == 1) {
            rs = zz4.rs;
            gs = zz4.gs;
            bs = zz4.bs;
            re = zz4.re;
            ge = zz4.ge;
            be = zz4.be;
        }
        colorTransition(rs, gs, bs, re, ge, be, interval, count);
        break;
    }
}


//stop button
void CG910_SAMPLEDlg::OnBnClickedButtonClearLighting14()
{
    stop = !stop;

}
//Fixed
void CG910_SAMPLEDlg::OnBnClickedButtonFixed()
{
    // TODO: Add your control notification handler code here
    //LogiLedPulseSingleKey();
    int r = m_scrollBarRed.GetScrollPos();
    int g = m_scrollBarGreen.GetScrollPos();
    int b = m_scrollBarBlue.GetScrollPos();
    ZoneSetLighting(r, g, b);
    lasteffect = 0;
    if (zz1.state) {
        //LogiLedSetLightingForTargetZone(LogiLed::Speaker, 1, r, g, b);
        zz1.effect = lasteffect;
        zz1.rs = r;
        zz1.gs = g;
        zz1.bs = b;
    }
    if (zz2.state) {
        zz2.effect = lasteffect;
        //LogiLedSetLightingForTargetZone(LogiLed::Speaker, 2, r, g, b);
        zz2.rs = r;
        zz2.gs = g;
        zz2.bs = b;
    }

    if (zz3.state) {
        zz3.effect = lasteffect;
        //  LogiLedSetLightingForTargetZone(LogiLed::Speaker, 3, r, g, b);
        zz3.rs = r;
        zz3.gs = g;
        zz3.bs = b;
    }
    if (zz4.state) {
        zz4.effect = lasteffect;
        // LogiLedSetLightingForTargetZone(LogiLed::Speaker, 0, r, g, b);
        zz4.rs = r;
        zz4.gs = g;
        zz4.bs = b;
    }

    //IntervalPulseBetween(100, 100, 0, 0, 0, 0, 100);
}



//zone1  front right
void CG910_SAMPLEDlg::OnBnClickedCheck6()
{

    UpdateData();
    //  zone1 = ((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck();
    if (m_CheckBox6.GetCheck())
    {
        //zone1 = true;
        zz1.state = 1;
    }
    else {
        // zone1 = false;
        zz1.state = 0;
        zz1.lightZone(0, 0, 0);
    }

}

//zone 2 back left
void CG910_SAMPLEDlg::OnBnClickedCheck7()
{
    UpdateData();
    if (m_CheckBox7.GetCheck())
    {
        zz2.state = 1;
    }
    else {
        zz2.state = 0;
        zz2.lightZone(0, 0, 0);
    }

}

//zone3 back right
void CG910_SAMPLEDlg::OnClickedCheck8()
{
    UpdateData();
    if (m_CheckBox8.GetCheck())
    {
        zz3.state = 1;
    }
    else {
        zz3.state = 0;

        zz3.lightZone(0, 0, 0);
    }
}

//zone4 front left actually zone 0
void CG910_SAMPLEDlg::OnBnClickedCheck9()
{
    UpdateData();
    if (m_CheckBox9.GetCheck())
    {
        zz4.state = 1;
    }
    else {
        zz4.state = 0;
        zz4.lightZone(0, 0, 0);
    }
}






/////////////////////////////////////////////////////////////////////////////////////////////////////////


void CG910_SAMPLEDlg::OnBnClickedButtonSetlighting()
{

    // TODO: Add your control notification handler code here

}





void CG910_SAMPLEDlg::OnBnClickedButtonBitmap()
{
    // TODO: Add your control notification handler code here
    // setup the bitmap
    unsigned char bitmap[LOGI_LED_BITMAP_SIZE];

    // loop through the bitmap, every four bits is a key so act on i/+1/+2/+3
    for (int i = 0; i < LOGI_LED_BITMAP_SIZE; i += 4)
    {
        bitmap[i] = rand() % 256;		// blue
        bitmap[i + 1] = rand() % 256;		// green
        bitmap[i + 2] = rand() % 256;		// red
        if (i > 84)
        {
            bitmap[i + 3] = ALPHA_MAX;	// brightness
        }
        else
        {
            //Setting the first row (any key < 21*4=84) to be ignored. This is usually used to avoid flickering when
            //updating certain keys with separate calls.
            //setting the alpha channel to 0 or <0 it makes the key to be ignored.
            bitmap[i + 3] = 0;
        }
    }

    // set the lighting from the bitmap
    LogiLedSetLightingFromBitmap(bitmap);
}















void CG910_SAMPLEDlg::OnBnClickedButtonSaveLighting()
{
    // TODO: Add your control notification handler code here
    LogiLedInit();
    LogiLedSaveCurrentLighting();
}


void CG910_SAMPLEDlg::OnBnClickedButtonRestoreLighting()
{
    // TODO: Add your control notification handler code here
    LogiLedRestoreLighting();

}






void CG910_SAMPLEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if (nID == SC_CLOSE)
    {
        LogiLedShutdown();
    }

    CDialog::OnSysCommand(nID, lParam);

}




void CG910_SAMPLEDlg::OnBnClickedCheck1()
{

    m_targetDevice = 0;
    UpdateData();
    if (m_rgbCheckBox.GetCheck())
    {
        m_targetDevice |= LOGI_DEVICETYPE_RGB;
    }
    if (m_monochromeCheckBox.GetCheck())
    {
        m_targetDevice |= LOGI_DEVICETYPE_MONOCHROME;
    }
    if (m_perKeyCheckBox.GetCheck())
    {
        m_targetDevice |= LOGI_DEVICETYPE_PERKEY_RGB;
    }
    LogiLedSetTargetDevice(m_targetDevice);
}

void CG910_SAMPLEDlg::OnBnClickedGetVersion()
{
    int major, minor, build = 0;
    if (!LogiLedGetSdkVersion(&major, &minor, &build))
    {
        ::MessageBox(NULL, L"Could not retrieve SDK version", L"error", 0);
    }
    else
    {
        wchar_t versionStr[128];
        swprintf_s(versionStr, L"SDK VERSION : %d.%d.%d", major, minor, build);
        ::MessageBox(NULL, versionStr, L"LED SDK VERSION", 0);
    }

}


void CG910_SAMPLEDlg::OnBnClickedButtonInitialize()
{
    if (!LogiLedInit())
    {
        ::MessageBox(NULL, L"Could not Initialize SDK", L"Init failed", 0);
    }
}


void CG910_SAMPLEDlg::OnBnClickedButtonShutdown()
{
    LogiLedShutdown();
}






void CG910_SAMPLEDlg::GetEffectColorValues(int* red, int* green, int* blue, bool startPicker)
{
}











void CG910_SAMPLEDlg::OnBnClickedSsdkcontrolGroup2()
{
    // TODO: Add your control notification handler code here
}






//void CG910_SAMPLEDlg::OnBnClickedCheck13()
//{
//	
//}


void CG910_SAMPLEDlg::OnDropdownCheck13(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMBCDROPDOWN pDropDown = reinterpret_cast<LPNMBCDROPDOWN>(pNMHDR);
    // TODO: Add your control notification handler code here
    *pResult = 0;
}



void CG910_SAMPLEDlg::OnBnClickedButtonClearLighting2()
{
    // TODO: Add your control notification handler code here
}




void CG910_SAMPLEDlg::OnStatic()
{
    // TODO: Add your command handler code here
    pPCG->SetBitmap(Entity);
}


void CG910_SAMPLEDlg::OnUpdateStatic(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
}


void CG910_SAMPLEDlg::OnEnChangeEdit1()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}


void CG910_SAMPLEDlg::OnEnChangeEdit2()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}
