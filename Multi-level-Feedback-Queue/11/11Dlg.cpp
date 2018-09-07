// 11Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "11.h"
#include "11Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy11Dlg dialog

CMy11Dlg::CMy11Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy11Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy11Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy11Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy11Dlg)
	DDX_Control(pDX, IDC_LIST1, mylist);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy11Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy11Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy11Dlg message handlers

BOOL CMy11Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	int j,i;
	for( i=0;i<50;i++)
		root[i]=0;

	char  a[]={"����xxx"};
	
	//mylist.ModifyStyle(0l,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_NOSORTHEADER);
	//mylist.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	mylist.ModifyStyle( 0, LVS_REPORT);                                                      // ����ģʽ
	mylist.SetExtendedStyle(mylist.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT); // �����+��ѡ��
	//���ɱ�ͷ
	mylist.InsertColumn(0,"���ȼ�");
	for( i=1;i<=101;i++)
	{
		if(i<10)//С��10����ʾΪ00X
		{
			a[4]=48;
			a[5]=48;
			a[6]=48+i;
		}
		else
			if(i<100)//����10С��100����ʾΪ0XX
			{
				a[4]=48;
				a[5]=48+i/10;
				a[6]=48+i%10;
			}
			else//����100����ʾΪ1XX
			{
				a[4]=49;
				a[5]=48;
				a[6]=48+i%100;
			}
		 mylist.InsertColumn(i,a);
	}
	//�����еĿ�ȡ�
	CRect rect;
	mylist.GetClientRect(rect); 
	mylist.SetColumnWidth(0,rect.Width()/10); //��һ�н�С
	 mylist.SetColumnWidth(1,rect.Width()/3); //�������Ƚϴ����ڽ����м�¼����Ϣ�϶�
	for( i=2;i<=100;i++)
	{
		 mylist.SetColumnWidth(i,rect.Width()/3); 
	}
	//��ʼ����һ��
	mylist.DeleteAllItems();
	char b[]="���ȼ�xx";
	for(j=49,i=0;j>=0;j--,i++)
	{   
		if(j>=10)
		{
			b[6]=48+j/10;
			b[7]=48+j%10;
		}
		else
		{
			b[6]=48;
			b[7]=48+j;
		}
		mylist.InsertItem(i,b);
		
	}





	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy11Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy11Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy11Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CMy11Dlg:: update(int priority)
{
	//�رմ��ڵĸ���
	LockWindowUpdate();
	//��õ�ǰ���µ����ȼ�������������Խ����Խ��ǰ
	int curent=49-priority;
	CString str,str1,str2,str3;
	node *n=root[priority];
	int i=1;
	//����һ����
	while(n!=0)
	{
		//������ʾ����
		str="";
		str1.Format("%d", n->pid);
		if(n->status==0)
			str2="Ready";
		else
			str2="Run";
		str3.Format("%d", n->life);
		str="Pid is "+str1+"; Status is "+str2 +"; Life is "+str3+".";
		mylist.SetItemText(curent,i,str);
		i++;
		n=n->next;
	}
	//�������һ����ʾΪ�գ�����һ���о����и��������һ����ɾ�������
	str="";
	mylist.SetItemText(curent,i,str);
	UnlockWindowUpdate();//�򿪴��ڵĸ���
	::UpdateWindow(mylist.m_hWnd);
}

void CMy11Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	node *n=new node();
	node *current;
	//�������̣�����������������ȼ��������
	current=root[n->priority];
	if(current==0)//Ϊ����ֱ�ӹ���
	{
		root[n->priority]=n;
	}
	else//��������������
	{
		while(current->next!=0)
		{
			current=current->next;
		}
		current->next=n;
	}

	update(n->priority);//���ø��º���������������
}

void CMy11Dlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	int i=49,nn1,nn2;
	node *n,*n1;
	//�����ȼ���ߵĵط���ʼ��⣬������ڽ���������������
	for(;i>=0;i--)
	{
		while(root[i]!=0)//����Ϊ�գ�����ִ��
		{
			//�����ڽ������Ϊ�������У�������
			n=root[i];
			n->status=1;	
			nn1=n->priority;
			update(nn1);
			//˯��3�룬����Ϊ����ʱ��Ƭ�����������life�Ƿ�Ϊ0
			::Sleep(3000);
			n->life--;
			n->status=0;	
			if(n->life)
			{
				//��Ϊ�㣬���ȼ����룬ȥ��ԭ������λ�ã���������������ȼ������
				n->priority=n->priority/2;
				nn2=n->priority;
				n1=root[n->priority];
				root[i]=root[i]->next;
				if(n1==0)
				{
					root[n->priority]=n;
					n->next=0;
				}
				else
				{
					while(n1->next!=0)
					{
						n1=n1->next;
					}
					n1->next=n;
					n->next=0;
				}
				//���������޸ĵ�������
				update(nn1);
				update(nn2);
			}
			else//Ϊ�㣬��ȥ��ԭ������λ�ã�������������
			{
				root[i]=root[i]->next;
				pi[n->pid]=true;
				update(nn1);
				delete n;
			}
			//break;
		}
	}
}

void CMy11Dlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
		int i=49,nn1,nn2;
	node *n,*n1;
	//�����ȼ���ߵĵط���ʼ��⣬������ڽ����򽫵�һ���������У�������
	for(;i>=0;i--)
	{
		if(root[i]!=0)
		{
			//�����ڽ������Ϊ�������У�������
			n=root[i];
			n->status=1;	
			nn1=n->priority;
			update(nn1);
			//˯��3�룬����Ϊ����ʱ��Ƭ�����������life�Ƿ�Ϊ0
			::Sleep(3000);
			n->life--;
			n->status=0;	
			if(n->life)
			{
				//��Ϊ�㣬���ȼ����룬ȥ��ԭ������λ�ã���������������ȼ������
				n->priority=n->priority/2;
				nn2=n->priority;
				n1=root[n->priority];
				root[i]=root[i]->next;
				if(n1==0)
				{
					root[n->priority]=n;
					n->next=0;
				}
				else
				{
					while(n1->next!=0)
					{
						n1=n1->next;
					}
					n1->next=n;
					n->next=0;
				}
				//���������޸ĵ�������
				update(nn1);
				update(nn2);
			}
			else//Ϊ�㣬��ȥ��ԭ������λ�ã�������������
			{
				root[i]=root[i]->next;
				pi[n->pid]=true;
				update(nn1);
				delete n;
			}
			break;//����Ѱ��
		}
	}
}
