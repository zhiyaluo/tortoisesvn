// TortoiseSVN - a Windows shell extension for easy version control

// Copyright (C) 2003-2007 - Stefan Kueng

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
#include "stdafx.h"
#include "TortoiseProc.h"
#include "Settings.h"
#include "MessageBox.h"



IMPLEMENT_DYNAMIC(CSettings, CTreePropSheet)
CSettings::CSettings(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CTreePropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	AddPropPages();
}

CSettings::~CSettings()
{
	RemovePropPages();
}

void CSettings::AddPropPages()
{
	m_pMainPage = new CSetMainPage();
	m_pOverlayPage = new CSetOverlayPage();
	m_pOverlaysPage = new CSetOverlayIcons();
	m_pProxyPage = new CSetProxyPage();
	m_pProgsDiffPage = new CSettingsProgsDiff();
	m_pProgsMergePage = new CSettingsProgsMerge();
	m_pProgsUniDiffPage = new CSettingsProgsUniDiff();
	m_pLookAndFeelPage = new CSetLookAndFeelPage();
	m_pDialogsPage = new CSetDialogs();
	m_pMiscPage = new CSetMisc();
	m_pColorsPage = new CSettingsColors();
	m_pSavedPage = new CSetSavedDataPage();
	m_pHooksPage = new CSetHooks();
	m_pTBlamePage = new CSettingsTBlame();

	SetPageIcon(m_pMainPage, m_pMainPage->GetIconID());
	SetPageIcon(m_pOverlayPage, m_pOverlayPage->GetIconID());
	SetPageIcon(m_pOverlaysPage, m_pOverlaysPage->GetIconID());
	SetPageIcon(m_pProxyPage, m_pProxyPage->GetIconID());
	SetPageIcon(m_pProgsDiffPage, m_pProgsDiffPage->GetIconID());
	SetPageIcon(m_pProgsMergePage, m_pProgsMergePage->GetIconID());
	SetPageIcon(m_pProgsUniDiffPage, m_pProgsUniDiffPage->GetIconID());
	SetPageIcon(m_pLookAndFeelPage, m_pLookAndFeelPage->GetIconID());
	SetPageIcon(m_pDialogsPage, m_pDialogsPage->GetIconID());
	SetPageIcon(m_pMiscPage, m_pMiscPage->GetIconID());
	SetPageIcon(m_pColorsPage, m_pColorsPage->GetIconID());
	SetPageIcon(m_pSavedPage, m_pSavedPage->GetIconID());
	SetPageIcon(m_pHooksPage, m_pHooksPage->GetIconID());
	SetPageIcon(m_pTBlamePage, m_pTBlamePage->GetIconID());

	AddPage(m_pMainPage);
	AddPage(m_pOverlayPage);
	AddPage(m_pOverlaysPage);
	AddPage(m_pProxyPage);
	AddPage(m_pProgsDiffPage);
	AddPage(m_pProgsMergePage);
	AddPage(m_pProgsUniDiffPage);
	AddPage(m_pLookAndFeelPage);
	AddPage(m_pDialogsPage);
	AddPage(m_pMiscPage);
	AddPage(m_pColorsPage);
	AddPage(m_pSavedPage);
	AddPage(m_pHooksPage);
	AddPage(m_pTBlamePage);
}

void CSettings::RemovePropPages()
{
	delete m_pMainPage;
	delete m_pOverlayPage;
	delete m_pOverlaysPage;
	delete m_pProxyPage;
	delete m_pProgsDiffPage;
	delete m_pProgsMergePage;
	delete m_pProgsUniDiffPage;
	delete m_pLookAndFeelPage;
	delete m_pDialogsPage;
	delete m_pMiscPage;
	delete m_pColorsPage;
	delete m_pSavedPage;
	delete m_pHooksPage;
	delete m_pTBlamePage;
}

void CSettings::SaveData()
{
	int restart = 0;
	restart |= m_pMainPage->SaveData();
	restart |= m_pOverlayPage->SaveData();
	restart |= m_pOverlaysPage->SaveData();
	restart |= m_pProxyPage->SaveData();
	restart |= m_pProgsDiffPage->SaveData();
	restart |= m_pProgsMergePage->SaveData();
	restart |= m_pProgsUniDiffPage->SaveData();
	restart |= m_pLookAndFeelPage->SaveData();
	restart |= m_pDialogsPage->SaveData();
	restart |= m_pMiscPage->SaveData();
	restart |= m_pColorsPage->SaveData();
	restart |= m_pSavedPage->SaveData();
	restart |= m_pHooksPage->SaveData();
	restart |= m_pTBlamePage->SaveData();
	if (restart)
		CMessageBox::Show(NULL, IDS_SETTINGS_RESTARTSYSTEM, IDS_APPNAME, MB_ICONINFORMATION);
}

BEGIN_MESSAGE_MAP(CSettings, CTreePropSheet)
	ON_WM_QUERYDRAGICON()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CSettings::OnInitDialog()
{
	BOOL bResult = CTreePropSheet::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CenterWindow(CWnd::FromHandle(hWndExplorer));
	return bResult;
}

void CSettings::OnPaint()
{
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
		CTreePropSheet::OnPaint();
	}
}

HCURSOR CSettings::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
