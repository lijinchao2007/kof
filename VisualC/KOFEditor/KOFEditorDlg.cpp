
// KOFEditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KOFEditor.h"
#include "KOFEditorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Uint8 globaldata[10240*10240];
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKOFEditorDlg 对话框



CKOFEditorDlg::CKOFEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKOFEditorDlg::IDD, pParent)
{
	m_sfffile.pSffList = NULL;
	m_sfffile.nTotalImages = -1;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKOFEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_SPR, m_Slider);
}

BEGIN_MESSAGE_MAP(CKOFEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CKOFEditorDlg::OnBnClickedBtnOpenfile)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SPR, &CKOFEditorDlg::OnNMCustomdrawSliderSpr)
	ON_BN_CLICKED(IDC_BTN_SCALE, &CKOFEditorDlg::OnBnClickedBtnSavescale)
	ON_EN_CHANGE(IDC_EDIT_SCALE, &CKOFEditorDlg::OnEnChangeEditScale)
	ON_BN_CLICKED(IDC_CHECK_SHOWBACK, &CKOFEditorDlg::OnBnClickedCheckShowback)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CKOFEditorDlg::OnBnClickedBtnSave)
	ON_COMMAND(IDD_KOFEDITOR_DIALOG, &CKOFEditorDlg::OnIddKofeditorDialog)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_BN_CLICKED(IDC_BTN_SCALEALL, &CKOFEditorDlg::OnBnClickedBtnScaleall)
END_MESSAGE_MAP()


// CKOFEditorDlg 消息处理程序

BOOL CKOFEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//int nRet= 0;
	//FILE* fp;
	//AllocConsole();
	//nRet= _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	//fp = _fdopen(nRet, "w");
	//*stdout = *fp;
	//setvbuf(stdout, NULL, _IONBF, 0);

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	for (int i = 0; i < 256; i++)
	{
		m_commonPal.color[i].a = 255;
		m_commonPal.color[i].r = 255-i;
		m_commonPal.color[i].g = 255-i;
		m_commonPal.color[i].b = 255-i;
	}
	SetDlgItemText(IDC_EDIT_SCALE, "1.0");

	char variable[256];
	CWnd* pWnd = this->GetDlgItem(IDC_VIEW);
	sprintf_s(variable, "0x%1x", pWnd->GetSafeHwnd());
	if (SDL_setenv("SDL_WINDOWID", variable, 1) != 0)
	{
		return FALSE;
	}
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER))
	{
		return FALSE;
	}
	SDL_Window * pWindow = SDL_CreateWindowFrom( (void *)(this->GetDlgItem(IDC_VIEW)->GetSafeHwnd() ) );
	m_render = SDL_CreateRenderer(pWindow, 0, SDL_RENDERER_ACCELERATED );

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKOFEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKOFEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
void CKOFEditorDlg::ClearRender()
{
	SDL_SetRenderDrawColor(m_render, 0,0, 0,0);
	SDL_RenderClear(m_render);
	SDL_RenderPresent(m_render);
}
void CKOFEditorDlg::DrawSprByIndex(int pos)
{
	SFFSPRITE* lpSprite = m_sfffile.pSffList+ pos-1;

	Uint32 width = lpSprite->PcxHeader.widht;
	Uint32 height = lpSprite->PcxHeader.height;
	Uint32 NPlane = lpSprite->PcxHeader.NPlanes;
	Uint32 length = width*NPlane*height;
	Uint8* data = DecodePcx(lpSprite->byPcxFile, lpSprite->PcxHeader);
	PaletteFormat* sharePallet = lpSprite->ColorPallet;
	if (lpSprite->bSharePallet)
	{
		sharePallet = &m_commonPal;
	}

	SDL_Surface *sur = SDL_CreateRGBSurfaceFrom(data, lpSprite->PcxHeader.widht, lpSprite->PcxHeader.height, 
		lpSprite->PcxHeader.BPP, lpSprite->PcxHeader.widht, 0,0,0,0);
	SDL_SetPaletteColors(sur->format->palette, sharePallet->color, 0, PALLET_SIZE);
	// last palette is transparent
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_CHECK_SHOWBACK))->GetCheck()) 
	{
		SDL_SetColorKey(sur, SDL_FALSE , 0);
	}else{
		SDL_SetColorKey(sur, SDL_TRUE , 0);
	}


	//SDL_Surface* sur = SDL_LoadBMP("controllermap.bmp");
	m_texture = SDL_CreateTextureFromSurface(m_render, sur);

	char scaletext[MAX_PATH];
	GetDlgItemText(IDC_EDIT_SCALE, scaletext, MAX_PATH);
	float scale = SDL_atof(scaletext);
	if (scale == 0.0)
	{
		return;
	}

	SDL_Rect src;
	SDL_Rect dest;
	Uint32 format;
	int acces;
	int startx = 350, starty = 300;
	SDL_QueryTexture(m_texture, &format, &acces, &src.w, &src.h);
	src.x=src.y =0;
	dest = src;
	dest.x = startx - lpSprite->x;
	dest.y = starty - lpSprite->y;
	dest.w *= scale;
	dest.h *= scale;

	SDL_SetRenderDrawColor(m_render, 0,0, 0,0);
	SDL_RenderClear(m_render);
	SDL_Rect r;
	r.x = startx;
	r.y = starty;
	r.w=r.h = 4;
	SDL_RenderCopy(m_render,m_texture, &src, &dest);
	SDL_SetRenderDrawColor(m_render, 255,255, 255,0);
	SDL_RenderDrawRect(m_render, &r);

	SDL_RenderPresent(m_render);

	//free(data);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(m_texture);
}
void CKOFEditorDlg::DrawSliderSpr()
{
	int pos = m_Slider.GetPos();
	if (pos<1||pos>m_sfffile.nTotalImages)
	{
		ClearRender();
		return;
	}
	DrawSprByIndex(pos);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKOFEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKOFEditorDlg::OnBnClickedBtnOpenfile()
{
	// TODO: 在此添加控件通知处理程序代码

	CString FilePathName;
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL, 
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("sff Files (*.sff)|*.sff||"),
		NULL);
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里
		SetDlgItemText(IDC_EDIT_FILEPATH, FilePathName.GetString());
		ClearSff();
		PareseSff(FilePathName);
		m_Slider.SetRange(1,m_sfffile.nTotalImages, TRUE);
		m_Slider.SetLineSize(0);
		m_Slider.SetPageSize(1);
		m_Slider.SetPos(0);
	}
	else
	{
		return;
	}

}


void CKOFEditorDlg::SaveAllSpr()
{
	char filePath[MAX_PATH];
	GetDlgItemText(IDC_EDIT_FILEPATH, filePath, MAX_PATH);
	if (m_sfffile.pSffList!=NULL)
	{
		CStdioFile myFile;
		myFile.Open(filePath, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);
		int filepos = 0;

		myFile.Write(&m_sfffile.head, sizeof(m_sfffile.head));
		filepos += sizeof(m_sfffile.head);
		for (int i=0;i<m_sfffile.nTotalImages;i++)
		{
			filepos = filepos + sizeof(SFFSUBHEADER) + sizeof(PCXHEADER)+m_sfffile.pSffList[i].byPcxFileLength;
			m_sfffile.pSffList[i].subhead.LenghtOfSubheader = sizeof(PCXHEADER)+ m_sfffile.pSffList[i].byPcxFileLength;
			if (!m_sfffile.pSffList[i].bSharePallet)
			{
				m_sfffile.pSffList[i].subhead.PalletSame = false; 
				filepos = filepos + 769;
				m_sfffile.pSffList[i].subhead.LenghtOfSubheader += 769;
			}else{
				m_sfffile.pSffList[i].subhead.PalletSame = true; 
			}
			m_sfffile.pSffList[i].subhead.NextSubheaderFileOffset = filepos;
			printf("write:%d, %d\n", m_sfffile.pSffList[i].subhead.LenghtOfSubheader, filepos);

			if (m_sfffile.pSffList[i].subhead.LenghtOfSubheader!=0)
			{
				myFile.Write(&m_sfffile.pSffList[i].subhead, sizeof(SFFSUBHEADER));
				m_sfffile.pSffList[i].PcxHeader.widht -= 1;
				m_sfffile.pSffList[i].PcxHeader.height -= 1;
				myFile.Write(&m_sfffile.pSffList[i].PcxHeader, sizeof(PCXHEADER));
				myFile.Write(m_sfffile.pSffList[i].byPcxFile, m_sfffile.pSffList[i].byPcxFileLength);
				if (!m_sfffile.pSffList[i].bSharePallet){
					char c = 0xc;
					myFile.Write(&c, 1);
					myFile.Write(&m_sfffile.pSffList[i].ColorPallet->paldata, 768);
				}
			}
		}
		myFile.Close();
	}
	
}

void CKOFEditorDlg::PareseSff(CString &file)
{
	CStdioFile myFile;
	myFile.Open(file, CFile::typeBinary|CFile::modeRead);

	myFile.Read(&m_sfffile.head,sizeof(SFFHEADER));
	//check file signatur
	if(strcmp((char*)m_sfffile.head.signature,"ElecbyteSpr")!=0)
	{
		return;                                           
	}

	myFile.Seek(m_sfffile.head.SubHeaderFileOffset, CFile::begin);
	SFFSUBHEADER subheader;
	myFile.Read(&subheader,sizeof(subheader));

	m_sfffile.nTotalImages = -1;
	m_sfffile.nImageListSize = 100;
	m_sfffile.pSffList = (SFFSPRITE*)malloc(sizeof(SFFSPRITE)*m_sfffile.nImageListSize);
	int index = 0;
	while(myFile.GetPosition() < myFile.GetLength())
	{
		m_sfffile.nTotalImages++;
		if(m_sfffile.nTotalImages > m_sfffile.nImageListSize-1)
		{
			m_sfffile.nImageListSize+=100;
			m_sfffile.pSffList=(SFFSPRITE*)realloc(m_sfffile.pSffList,sizeof(SFFSPRITE)*m_sfffile.nImageListSize);
		}

		m_sfffile.pSffList[m_sfffile.nTotalImages].GroupNumber=subheader.GroubNumber;
		m_sfffile.pSffList[m_sfffile.nTotalImages].ImageNumber=subheader.ImageNumber;
		m_sfffile.pSffList[m_sfffile.nTotalImages].x=subheader.x;
		m_sfffile.pSffList[m_sfffile.nTotalImages].y=subheader.y;
		m_sfffile.pSffList[m_sfffile.nTotalImages].subhead = subheader;
		//is it a linked sprite??
		if(subheader.LenghtOfSubheader!=0)
		{
			//read the pcx header
			myFile.Read(&m_sfffile.pSffList[m_sfffile.nTotalImages].PcxHeader, sizeof(PCXHEADER));
			//Correct the Image dimension 
			m_sfffile.pSffList[m_sfffile.nTotalImages].PcxHeader.widht=m_sfffile.pSffList[m_sfffile.nTotalImages].PcxHeader.widht - m_sfffile.pSffList[m_sfffile.nTotalImages].PcxHeader.x + 1;
			m_sfffile.pSffList[m_sfffile.nTotalImages].PcxHeader.height=m_sfffile.pSffList[m_sfffile.nTotalImages].PcxHeader.height - m_sfffile.pSffList[m_sfffile.nTotalImages].PcxHeader.y +1;

			//now read the pcx data 
			//TODO:check subheader.LenghtOfSubheader
			index++;
			printf("index:%d,g %d, i %d,%d,%d\n", index, subheader.GroubNumber, subheader.ImageNumber, subheader.LenghtOfSubheader, subheader.NextSubheaderFileOffset);
			if (index == 1062)
			{
				printf("");
			}
			Uint32 dataLength = subheader.LenghtOfSubheader-sizeof(PCXHEADER);
			if (!subheader.PalletSame)
			{
				dataLength = dataLength - 769;
			}
			//TODO:解压逻辑放在绘制的时候处理成最终纹理
			Uint8* data = (Uint8*)malloc(dataLength);
			myFile.Read(data, dataLength);
			m_sfffile.pSffList[m_sfffile.nTotalImages].byPcxFile=data;
			m_sfffile.pSffList[m_sfffile.nTotalImages].byPcxFileLength=dataLength;
			if (subheader.PalletSame)
			{
				m_sfffile.pSffList[m_sfffile.nTotalImages].bSharePallet = true;
				m_sfffile.pSffList[m_sfffile.nTotalImages].ColorPallet = NULL;
			}else{
				Uint8 flag;
				myFile.Read(&flag, 1);
				if (flag==0xC &&  m_sfffile.pSffList[m_sfffile.nTotalImages].PcxHeader.NPlanes<=1)
				{
					PaletteFormat* selfColorPallet = (PaletteFormat*)malloc(sizeof(PaletteFormat));
					myFile.Read(selfColorPallet->paldata, 768);
					Uint8* palData = selfColorPallet->paldata;
					for(int j=0;j<PALLET_SIZE;j++)
					{
						Uint8 r,g,b;
						r=palData[j*3];
						g=palData[j*3+1];
						b=palData[j*3+2];
						selfColorPallet->color[j].r = r;
						selfColorPallet->color[j].g = g;
						selfColorPallet->color[j].b = b;
						selfColorPallet->color[j].a = 0xff;
					}
					m_sfffile.pSffList[m_sfffile.nTotalImages].bSharePallet = false;
					m_sfffile.pSffList[m_sfffile.nTotalImages].ColorPallet = (PaletteFormat*)selfColorPallet;
				}else{
					assert(false);
				}
			}

		}
		else
		{
			//subheader.IndexOfPrevious-1 if the first ellement is 1 and not 0
			// we have a linked image here
			memcpy(&m_sfffile.pSffList[m_sfffile.nTotalImages],
				&m_sfffile.pSffList[subheader.IndexOfPrevious],
				sizeof(SFFSPRITE));

			m_sfffile.pSffList[m_sfffile.nTotalImages].GroupNumber=subheader.GroubNumber;
			m_sfffile.pSffList[m_sfffile.nTotalImages].ImageNumber=subheader.ImageNumber;

		}
		myFile.Seek(subheader.NextSubheaderFileOffset,CFile::begin);
		myFile.Read(&subheader, sizeof(subheader));
	}
	m_sfffile.nTotalImages ++;
	myFile.Close();


}


//decodes one PCX file
Uint8* CKOFEditorDlg::DecodePcx(Uint8* PcxByte,PCXHEADER header)
{
	Uint8* byImageBuffer=0;
	Uint8 BPP,byData;  
	u16 size;
	s16 x,y,widht;
	u32 Pos=0;

	u32 nCountByte,nTotalyByte,
		nHowManyBytes,nHowManyBlank;

	nTotalyByte=header.bytesPerLine*header.NPlanes;

	nHowManyBytes=0;
	nHowManyBlank=0;
	nCountByte=0;

	BPP=header.NPlanes*8; 

	//allocate memory
	if (header.widht*header.NPlanes*header.height>10240*10240)
	{
		return globaldata;
	}
	byImageBuffer=globaldata;//(Uint8*)malloc(sizeof(Uint8)*(header.widht*header.NPlanes*header.height));
	widht=header.widht;

	if(widht<header.bytesPerLine * header.NPlanes)
		widht=header.bytesPerLine*header.NPlanes;

	//we do not support 24bit pcx images
	if(BPP>8)
	{

		return byImageBuffer;
	}

	size=0;
	y=0;
	x=0;
	for(y=0;y<header.height;y++)
	{
		x=0;
		while(x < widht)
		{

			byData=PcxByte[Pos++];

			if( (byData & 0xC0) == 0xC0 )
			{
				size = byData & 0x3F;
				byData=PcxByte[Pos++];

			}
			else
			{
				size=1;
			}

			while(size-- > 0)
			{
				if(x <= header.widht)
				{
					byImageBuffer[x + (y * header.widht)]=byData;

				}
				//this it to Skip blank data on PCX image wich are on the right side
				//TODO:OK? Skip two bytes
				if(x == widht && widht != header.widht)
				{
					nHowManyBlank=widht-header.widht;
					for(u32 i=0;i<nHowManyBlank;i++)
						Pos+=2;
				}
				x++;

			}

		} 

	}

	return byImageBuffer;    
}


void CKOFEditorDlg::OnNMCustomdrawSliderSpr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str;
	int pos = m_Slider.GetPos();
	str.Format("%d/%d", pos, m_sfffile.nTotalImages);
	SetDlgItemText(IDC_TEXT_SPRNUM, str);
	UpdateData(FALSE); 

	if (m_pos!=pos)
	{
		m_pos = pos;
		DrawSliderSpr();
	}
	*pResult = 0;
}

void CKOFEditorDlg::ClearSff()
{
	if (m_sfffile.pSffList != NULL)
	{
		for (int i=0;i<m_sfffile.nTotalImages;i++)
		{
			free(m_sfffile.pSffList[i].byPcxFile);
			if (m_sfffile.pSffList[i].bSharePallet==false)
			{
				free(m_sfffile.pSffList[i].ColorPallet);
			}
		}
		free(m_sfffile.pSffList);
		m_sfffile.pSffList = NULL;
		m_sfffile.nTotalImages = -1;
	}
}
void CKOFEditorDlg::PostNcDestroy()
{
	ClearSff();
	SDL_DestroyRenderer(m_render);
	SDL_Quit();
	CDialog::PostNcDestroy();
}

void CKOFEditorDlg::RLEData(Uint8* data, PCXHEADER* header, Uint8** ddata, int* destlength)
{
	/*Uint8 tmp[1024];
	SDL_strlcpy((char*)tmp, (char*)data, 1024);*/


	int cur=-1,next=-1;   
	int count = 0;
	int width = header->bytesPerLine;
	int height = header->height;
	Uint8* destdata = (Uint8*)malloc(width*height*2);
	int destindex = 0;

	cur=next=data[0];
	int x=0,y=0;
	for(y=0;y<height;y++)
	{
		x=0;
		while(x < width)
		{
			next = data[y*width+x];
			if (x>=header->widht)
			{
				destdata[destindex++] = 0;
			}else{
				if (cur==next)
				{
					count++;
					if (count>=0x3f)
					{
						destdata[destindex++] = 0xc0|count;
						destdata[destindex++] = cur;
						count -= 0x3f;
					}
				}else{
					destdata[destindex++] = 0xc0|count;
					destdata[destindex++] = cur;
					cur = next;
					count=1;
				}
			}
			x++;
		} 
		if (count>0)
		{
			destdata[destindex++] = 0xc0|count;
			destdata[destindex++] = cur;
			cur = next;
			count=0;
		}
	}

	if (count>0)
	{
		destdata[destindex++] = 0xc0|count;
		destdata[destindex++] = cur;
		cur = next;
		count=0;
	}
	*ddata = destdata;
	*destlength=destindex;
}


void CKOFEditorDlg::ScaleSpr(int pos, float scale)
{
	SFFSPRITE* lpSprite = m_sfffile.pSffList+ pos-1;
	int width = lpSprite->PcxHeader.widht;
	Uint8* data = DecodePcx(lpSprite->byPcxFile, lpSprite->PcxHeader);
	Uint8* destdata=NULL;
	int destlength;

	/*
	 *	scale
	 */
	int scaleHeight = lpSprite->PcxHeader.height = lpSprite->PcxHeader.height*scale;
	int scaleWidth = lpSprite->PcxHeader.bytesPerLine = lpSprite->PcxHeader.bytesPerLine*scale;
	lpSprite->PcxHeader.widht = lpSprite->PcxHeader.widht*scale;
	Uint32 scalelength = scaleHeight*scaleWidth;
	Uint8*  scaledata = (Uint8*)malloc(scalelength);
	

	for (int h=0;h<scaleHeight;h++)
	{
		for (int w=0;w<scaleWidth;w++)
		{
			int index = h*scaleWidth+w;
			int scaleindex = int(h/scale)*width + int(w/scale);
			scaledata[index] = data[scaleindex];
		}
	}

	RLEData(scaledata, &lpSprite->PcxHeader, &destdata, &destlength);

	/*Uint8 tmp1[4096], tmp2[4096];
	SDL_strlcpy((char*)tmp1, (char*)lpSprite->byPcxFile, lpSprite->byPcxFileLength+1);
	SDL_strlcpy((char*)tmp2, (char*)destdata, destlength+1);*/

	//free(data);
	free(scaledata);
	free(lpSprite->byPcxFile);
	lpSprite->byPcxFile = destdata;
	lpSprite->byPcxFileLength = destlength;
	
}

void CKOFEditorDlg::OnBnClickedBtnSavescale()
{
	// TODO: 在此添加控件通知处理程序代码
	char scaletext[MAX_PATH];
	GetDlgItemText(IDC_EDIT_SCALE, scaletext, MAX_PATH);
	float scale = SDL_atof(scaletext);
	if (scale==0.0)
	{
		AfxMessageBox("scale should be num");
		return;
	}
	int pos = m_Slider.GetPos();
	if (pos<1||pos>m_sfffile.nTotalImages)
	{
		return;
	}
	ScaleSpr(pos, scale);
	SetDlgItemText(IDC_EDIT_SCALE, "1.0");
	DrawSliderSpr();
	//SaveAllSpr();
}


void CKOFEditorDlg::OnEnChangeEditScale()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DrawSliderSpr();
}


void CKOFEditorDlg::OnBnClickedCheckShowback()
{
	// TODO: 在此添加控件通知处理程序代码
	DrawSliderSpr();
}


void CKOFEditorDlg::OnBnClickedBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveAllSpr();
	AfxMessageBox("saved!");
}


void CKOFEditorDlg::OnIddKofeditorDialog()
{
	// TODO: 在此添加命令处理程序代码
}


void CKOFEditorDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int pos = m_Slider.GetPos();
	if (nChar==37)
	{
		pos--;
	}
	if (nChar==39)
	{
		pos++;
	}
	if (pos>=1&&pos<=m_sfffile.nTotalImages)
	{
		m_Slider.SetPos(pos);
		m_Slider.UpdateData(FALSE);
		DrawSliderSpr();
	}
	
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CKOFEditorDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnChar(nChar, nRepCnt, nFlags);
}


BOOL CKOFEditorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CKOFEditorDlg::OnBnClickedBtnScaleall()
{
	// TODO: 在此添加控件通知处理程序代码
	char scaletext[MAX_PATH];
	GetDlgItemText(IDC_EDIT_SCALE, scaletext, MAX_PATH);
	float scale = SDL_atof(scaletext);
	if (scale==0.0)
	{
		AfxMessageBox("scale should be num");
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	for (int i=1;i<=m_sfffile.nTotalImages;i++)
	{
		ScaleSpr(i, scale);
	}
	SetDlgItemText(IDC_EDIT_SCALE, "1.0");
	DrawSliderSpr();
	AfxMessageBox("scale all finished!");
}
